// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "v8_binding.h"

namespace v8_webgl {

v8::Persistent<v8::FunctionTemplate> V8ObjectBase::CreateConstructorTemplate(const char* class_name, v8::InvocationCallback callback) {
  v8::Local<v8::FunctionTemplate> result = v8::FunctionTemplate::New(callback);
  v8::Persistent<v8::FunctionTemplate> constructor = v8::Persistent<v8::FunctionTemplate>::New(result);
  constructor->SetClassName(v8::String::New(class_name));
  constructor->ReadOnlyPrototype();
  v8::Local<v8::ObjectTemplate> instance = constructor->InstanceTemplate();
  instance->SetInternalFieldCount(1);
  return constructor;
}

double V8ToNumber(v8::Handle<v8::Value> value, bool& ok) {
  ok = true;
  v8::Local<v8::Number> numValue = value->ToNumber();
  if (numValue.IsEmpty()) {
    ok = false;
    return 0;
  }
  return numValue->Value();
}

int32_t V8ToInt32(v8::Handle<v8::Value> value, bool& ok) {
  ok = true;
  v8::Local<v8::Int32> intValue = value->ToInt32();
  if (intValue.IsEmpty()) {
    ok = false;
    return 0;
  }
  return intValue->Value();
}

uint32_t V8ToUint32(v8::Handle<v8::Value> value, bool& ok) {
  ok = true;
  v8::Local<v8::Uint32> uintValue = value->ToUint32();
  if (uintValue.IsEmpty()) {
    ok = false;
    return 0;
  }
  return uintValue->Value();
}

}
