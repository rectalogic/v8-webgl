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

 protected:
  ArrayBuffer(v8::Handle<v8::Object> instance, void* data, uint32_t data_length);
  ~ArrayBuffer();

 private:
  uint32_t data_length_;
  void* data_;
};

//////

//XXX use sizeof(TNative) to get bytes per el
template<class T, v8::ExternalArrayType TArrayType, typename TNative>
class TypedArray : public V8Object<T> {
};

//////

class Int8Array : public TypedArray<Int8Array, v8::kExternalByteArray, int8_t> {
  static const char* const ClassName() { return "Int8Array"; }
};

}

#endif
