// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "v8_binding.h"
#include "typed_array.h"


namespace v8_webgl {

ArrayBuffer::ArrayBuffer(v8::Handle<v8::Object> instance, void* data, uint32_t data_length)
    : V8Object<ArrayBuffer>(true, instance)
    , data_length_(data_length)
    , data_(data)
{
}

ArrayBuffer::~ArrayBuffer() {
  free(data_);
  v8::V8::AdjustAmountOfExternalAllocatedMemory(-data_length_);
}

// ArrayBuffer(unsigned long length)
v8::Handle<v8::Value> ArrayBuffer::ConstructorCallback(const v8::Arguments& args) {
  bool ok = true;
  uint32_t length = V8ToUint32(args[0], ok);
  if (!ok)
    return v8::Undefined();

  void* data = calloc(length, 1);
  if (!data)
    return ThrowError("Unable to allocate ArrayBuffer.");

  v8::Handle<v8::Object> self(args.This());

  self->Set(v8::String::New("byteLength"), args[0],
            static_cast<v8::PropertyAttribute>(v8::ReadOnly|v8::DontDelete));

  new ArrayBuffer(self, data, length);
  self->SetIndexedPropertiesToExternalArrayData(data, v8::kExternalUnsignedByteArray, length);

  v8::V8::AdjustAmountOfExternalAllocatedMemory(length);

  return self;
}

}
