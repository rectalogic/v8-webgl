// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


// WebGL Typed Arrays
// http://www.khronos.org/registry/typedarray/specs/latest

#ifndef V8WEBGL_TYPED_ARRAY_H
#define V8WEBGL_TYPED_ARRAY_H

#include "v8_binding.h"

namespace v8_webgl {

class ArrayDataInterface {
 public:
  virtual ~ArrayDataInterface() {}
  virtual void* GetArrayData() = 0;
  // Length of data in bytes
  virtual uint32_t GetArrayLength() = 0;
};

//////

class ArrayBuffer : public V8Object<ArrayBuffer>, public ArrayDataInterface {
 public:
  static const char* const ClassName() { return "ArrayBuffer"; }
  static v8::Handle<v8::Value> ConstructorCallback(const v8::Arguments& args);

  void* GetArrayData() { return data_; }
  uint32_t GetArrayLength() { return data_length_; }

  static v8::Handle<v8::Object> Create(uint32_t length);

 protected:
  ArrayBuffer(void* data, uint32_t data_length, v8::Handle<v8::Object> instance = v8::Local<v8::Object>());
  ~ArrayBuffer();

 private:
  uint32_t data_length_;
  void* data_;
};

//////

class ArrayBufferView : public V8Object<ArrayBufferView> {
 public:
  static void ConfigureGlobal(v8::Handle<v8::ObjectTemplate>) {
    // Don't expose "ArrayBufferView" constructor name
  }
  static const char* const ClassName() { return "ArrayBufferView"; }
};

//////

template<class T, v8::ExternalArrayType TArrayType, typename TNative>
class TypedArray : public V8Object<T>, public ArrayDataInterface {
 public:
  static v8::Handle<v8::Object> Create(TNative* values, uint32_t length) {
    v8::Handle<v8::Value> argv[1] = { TypeToV8<uint32_t>(length) };
    v8::Handle<v8::Object> array = V8Object<T>::Create(1, argv);
    if (array.IsEmpty())
      return array;
    if (length > 0) {
      void* data = array->GetIndexedPropertiesExternalArrayData();
      memcpy(data, values, length * sizeof(TNative));
    }
    return array;
  }

  static void ConfigureConstructorTemplate(v8::Persistent<v8::FunctionTemplate> constructor) {
    // In JS, TypedArray inherits from ArrayBufferView
    ArrayBufferView::Reparent(constructor);

    v8::Handle<v8::ObjectTemplate> proto = constructor->PrototypeTemplate();
    v8::Handle<v8::ObjectTemplate> instance = constructor->InstanceTemplate();
    v8::Local<v8::Signature> signature = v8::Signature::New(constructor);

    V8ObjectBase::AddConstant("BYTES_PER_ELEMENT", TypeToV8<uint32_t>(sizeof(TNative)), proto, constructor);
    //XXX need subarray and set() with array arg
  }

  // TypedArray(unsigned long length)
  // TypedArray(TypedArray array)
  // TypedArray(type[] array)
  // TypedArray(ArrayBuffer buffer, optional unsigned long byteOffset, optional unsigned long length)
  static v8::Handle<v8::Value> ConstructorCallback(const v8::Arguments& args) {
    bool ok = true;
    v8::Handle<v8::Object> buffer_value;
    unsigned int length = 0;
    unsigned int byte_offset = 0;

    v8::Handle<v8::Object> self(args.This());

    // TypedArray(ArrayBuffer buffer, optional unsigned long byteOffset, optional unsigned long length)
    if (ArrayBuffer::HasInstance(args[0])) {
      ArrayBuffer* buffer = V8ToNative<ArrayBuffer>(args[0], ok);
      if (!ok)
        return v8::Undefined();
      buffer_value = v8::Handle<v8::Object>::Cast(args[0]);
      uint32_t buflen = buffer->GetArrayLength();

      // byteOffset
      if (args.Length() >= 2) {
        byte_offset = V8ToType<uint32_t>(args[1], ok);
        if (!ok)
          return v8::Undefined();
        v8::Handle<v8::Value> err = CheckAlignment(byte_offset, ok);
        if (!ok)
          return err;
      }

      // length
      if (args.Length() >= 3) {
        length = V8ToType<uint32_t>(args[2], ok);
        if (!ok)
          return v8::Undefined();
      }
      else {
        if (buflen <= byte_offset)
          return ThrowRangeError("Byte offset out of range.");
        // Byte length minus offset must be multiple of element size
        v8::Handle<v8::Value> err = CheckAlignment(buflen - byte_offset, ok);
        if (!ok)
          return err;

        // Adjust length for byte_offset
        length = (buflen - byte_offset) / sizeof(TNative);
      }

      if (byte_offset >= buflen || byte_offset + length * sizeof(TNative) > buflen)
        return ThrowRangeError("Length out of range.");

      void* data = buffer->GetArrayData();
      self->SetIndexedPropertiesToExternalArrayData
          (reinterpret_cast<char*>(data) + byte_offset, TArrayType, length);
    }
    // TypedArray(TypedArray array)
    // TypedArray(type[] array)
    else if (args[0]->IsObject()) {
      v8::Local<v8::Object> object = v8::Local<v8::Object>::Cast(args[0]);
      length = V8ToType<uint32_t>(object->Get(v8::String::New("length")), ok);
      if (!ok)
        return v8::Undefined();

      buffer_value = ArrayBuffer::Create(length * sizeof(TNative));
      if (buffer_value.IsEmpty())
        return v8::Undefined();
      ArrayBuffer* buffer = V8ToNative<ArrayBuffer>(buffer_value, ok);
      if (!ok)
        return v8::Undefined();

      void* buf = buffer->GetArrayData();
      self->SetIndexedPropertiesToExternalArrayData
          (buf, TArrayType, length);

      // Copy array data
      for (uint32_t i = 0; i < length; i++)
        self->Set(i, object->Get(i));
    }
    // TypedArray(unsigned long length)
    else {
      if (args.Length() >= 1) {
        length = V8ToType<uint32_t>(args[0], ok);
        if (!ok)
          return v8::Undefined();
      }

      buffer_value = ArrayBuffer::Create(length * sizeof(TNative));
      if (buffer_value.IsEmpty())
        return v8::Undefined();
      ArrayBuffer* buffer = V8ToNative<ArrayBuffer>(buffer_value, ok);
      if (!ok)
        return v8::Undefined();

      self->SetIndexedPropertiesToExternalArrayData
          (buffer->GetArrayData(), TArrayType, length);
    }

    V8ObjectBase::SetProperty(self, "buffer", buffer_value);
    V8ObjectBase::SetProperty(self, "length", TypeToV8<uint32_t>(length));
    V8ObjectBase::SetProperty(self, "byteOffset", TypeToV8<uint32_t>(byte_offset));
    V8ObjectBase::SetProperty(self, "byteLength", TypeToV8<uint32_t>(length * sizeof(TNative)));

    new T(self);

    return self;
  }

  void* GetArrayData() {
    v8::Handle<v8::Object> array = V8ObjectBase::ToV8();
    return array->GetIndexedPropertiesExternalArrayData();
  }

  uint32_t GetArrayLength() {
    v8::Handle<v8::Object> array = V8ObjectBase::ToV8();
    int32_t length = array->GetIndexedPropertiesExternalArrayDataLength();
    return length * sizeof(TNative);
  }

 protected:
  TypedArray<T, TArrayType, TNative>(v8::Handle<v8::Object> instance)
  : V8Object<T>(true, instance) {}

 private:
  inline static v8::Handle<v8::Value> CheckAlignment(uint32_t val, bool& ok) {
    ok = (val & (sizeof(TNative) - 1)) == 0;
    if (!ok)
      return ThrowRangeError("Byte offset is not aligned.");
    return v8::Undefined();
  }
};

//////

#define DECLARE_TYPED_ARRAY(name, arraytype, native)                    \
  class name : public TypedArray<name, arraytype, native> {             \
   public:                                                              \
   static const char* const ClassName() { return #name; }               \
   protected:                                                           \
   name(v8::Handle<v8::Object> instance)                                \
       : TypedArray<name, arraytype, native>(instance) {}               \
   friend class TypedArray<name, arraytype, native>;                    \
  };

DECLARE_TYPED_ARRAY(Int8Array, v8::kExternalByteArray, int8_t)
DECLARE_TYPED_ARRAY(Uint8Array, v8::kExternalUnsignedByteArray, uint8_t)
DECLARE_TYPED_ARRAY(Uint8ClampedArray, v8::kExternalPixelArray, uint8_t)
DECLARE_TYPED_ARRAY(Int16Array, v8::kExternalShortArray, int16_t)
DECLARE_TYPED_ARRAY(Uint16Array, v8::kExternalUnsignedShortArray, uint16_t)
DECLARE_TYPED_ARRAY(Int32Array, v8::kExternalIntArray, int32_t)
DECLARE_TYPED_ARRAY(Uint32Array, v8::kExternalUnsignedIntArray, uint32_t)
DECLARE_TYPED_ARRAY(Float32Array, v8::kExternalFloatArray, float)
DECLARE_TYPED_ARRAY(Float64Array, v8::kExternalDoubleArray, double)

#undef DECLARE_TYPED_ARRAY

//////

//XXX DataView

}

#endif
