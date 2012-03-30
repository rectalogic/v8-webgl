// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "v8_binding.h"
#include "typed_array.h"


namespace v8_webgl {

ArrayBuffer::ArrayBuffer(void* data, uint32_t data_length, v8::Handle<v8::Object> instance)
    : V8Object<ArrayBuffer>(true, instance)
    , data_length_(data_length)
    , data_(data)
{
}

ArrayBuffer::~ArrayBuffer() {
  free(data_);
  v8::V8::AdjustAmountOfExternalAllocatedMemory(-data_length_);
}

v8::Handle<v8::Object> ArrayBuffer::Create(uint32_t length) {
  v8::Handle<v8::Value> argv[1] = { TypeToV8<uint32_t>(length) };
  return V8Object<ArrayBuffer>::Create(1, argv);
}

// ArrayBuffer(unsigned long length)
v8::Handle<v8::Value> ArrayBuffer::ConstructorCallback(const v8::Arguments& args) {
  uint32_t length = 0;
  void* data = NULL;
  if (args.Length() >= 1) {
    bool ok = true;
    length = FromV8<uint32_t>(args[0], ok);
    if (!ok)
      return v8::Undefined();

    data = calloc(length, 1);
    if (!data)
      return ThrowError("Unable to allocate ArrayBuffer.");
  }

  v8::Handle<v8::Object> self(args.This());

  SetProperty(self, "byteLength", TypeToV8<uint32_t>(length));

  //XXX need ArrayBuffer slice(long begin, optional long end)

  new ArrayBuffer(data, length, self);
  self->SetIndexedPropertiesToExternalArrayData(data, v8::kExternalUnsignedByteArray, length);

  v8::V8::AdjustAmountOfExternalAllocatedMemory(length);

  return self;
}

}
