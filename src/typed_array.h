// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


// WebGL Typed Arrays
// http://www.khronos.org/registry/typedarray/specs/latest

#ifndef V8WEBGL_TYPED_ARRAY_H
#define V8WEBGL_TYPED_ARRAY_H

#include "v8_binding.h"

namespace v8_webgl {

class ArrayBuffer : public V8Object<ArrayBuffer> {
 public:
  static const char* const ClassName() { return "ArrayBuffer"; }
  static v8::Handle<v8::Value> ConstructorCallback(const v8::Arguments& args);

  uint32_t get_data_length() { return data_length_; }
  void* get_data() { return data_; }

  static v8::Handle<v8::Object> Create(uint32_t length);

 protected:
  ArrayBuffer(void* data, uint32_t data_length, v8::Handle<v8::Object> instance = v8::Local<v8::Object>());
  ~ArrayBuffer();

 private:
  uint32_t data_length_;
  void* data_;
};

//////


template<class T, v8::ExternalArrayType TArrayType, typename TNative>
class TypedArray : public V8Object<T> {
 public:
  static void ConfigureConstructorTemplate(v8::Persistent<v8::FunctionTemplate> constructor) {
    v8::Handle<v8::ObjectTemplate> proto = constructor->PrototypeTemplate();
    v8::Handle<v8::ObjectTemplate> instance = constructor->InstanceTemplate();
    v8::Local<v8::Signature> signature = v8::Signature::New(constructor);

    V8ObjectBase::AddConstant("BYTES_PER_ELEMENT", Uint32ToV8(sizeof(TNative)), proto, constructor);
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
      uint32_t buflen = buffer->get_data_length();

      // byteOffset
      if (args.Length() >= 2) {
        byte_offset = V8ToUint32(args[1], ok);
        if (!ok)
          return v8::Undefined();
        v8::Handle<v8::Value> err = CheckAlignment(byte_offset, ok);
        if (!ok)
          return err;
      }

      // length
      if (args.Length() >= 3) {
        length = V8ToUint32(args[2], ok);
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

      void* data = buffer->get_data();
      self->SetIndexedPropertiesToExternalArrayData
          (reinterpret_cast<char*>(data) + byte_offset, TArrayType, length);
    }
    // TypedArray(TypedArray array)
    // TypedArray(type[] array)
    else if (args[0]->IsObject()) {
      v8::Local<v8::Object> object = v8::Local<v8::Object>::Cast(args[0]);
      length = V8ToUint32(object->Get(v8::String::New("length")), ok);
      if (!ok)
        return v8::Undefined();

      buffer_value = ArrayBuffer::Create(length * sizeof(TNative));
      if (buffer_value.IsEmpty())
        return v8::Undefined();
      ArrayBuffer* buffer = V8ToNative<ArrayBuffer>(buffer_value, ok);
      if (!ok)
        return v8::Undefined();

      void* buf = buffer->get_data();
      self->SetIndexedPropertiesToExternalArrayData
          (buf, TArrayType, length);

      // Copy array data
      for (uint32_t i = 0; i < length; i++)
        self->Set(i, object->Get(i));
    }
    // TypedArray(unsigned long length)
    else {
      if (args.Length() >= 1) {
        length = V8ToUint32(args[0], ok);
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
          (buffer->get_data(), TArrayType, length);
    }

    V8ObjectBase::SetProperty(self, "buffer", buffer_value);
    V8ObjectBase::SetProperty(self, "length", Uint32ToV8(length));
    V8ObjectBase::SetProperty(self, "byteOffset", Uint32ToV8(byte_offset));
    V8ObjectBase::SetProperty(self, "byteLength", Uint32ToV8(length * sizeof(TNative)));

    return self;
  }

 private:
  inline static v8::Handle<v8::Value> CheckAlignment(uint32_t val, bool& ok) {
    ok = (val & (sizeof(TNative) - 1)) == 0;
    if (!ok)
      return ThrowRangeError("Byte offset is not aligned.");
    return v8::Undefined();
  }

};

//////

class Int8Array : public TypedArray<Int8Array, v8::kExternalByteArray, int8_t> {
 public:
  static const char* const ClassName() { return "Int8Array"; }
};

class Uint8Array : public TypedArray<Uint8Array, v8::kExternalUnsignedByteArray, uint8_t> {
 public:
  static const char* const ClassName() { return "Uint8Array"; }
};

class Uint8ClampedArray : public TypedArray<Uint8ClampedArray, v8::kExternalPixelArray, uint8_t> {
 public:
  static const char* const ClassName() { return "Uint8ClampedArray"; }
};

class Int16Array : public TypedArray<Int16Array, v8::kExternalShortArray, int16_t> {
 public:
  static const char* const ClassName() { return "Int16Array"; }
};

class Uint16Array : public TypedArray<Uint16Array, v8::kExternalUnsignedShortArray, uint16_t> {
 public:
  static const char* const ClassName() { return "Uint16Array"; }
};

class Int32Array : public TypedArray<Int32Array, v8::kExternalIntArray, int32_t> {
 public:
  static const char* const ClassName() { return "Int32Array"; }
};

class Uint32Array : public TypedArray<Uint32Array, v8::kExternalUnsignedIntArray, uint32_t> {
 public:
  static const char* const ClassName() { return "Uint32Array"; }
};

class Float32Array : public TypedArray<Float32Array, v8::kExternalFloatArray, float> {
 public:
  static const char* const ClassName() { return "Float32Array"; }
};

class Float64Array : public TypedArray<Float64Array, v8::kExternalDoubleArray, double> {
 public:
  static const char* const ClassName() { return "Float64Array"; }
};

//////

//XXX DataView

}

#endif
