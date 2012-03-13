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

std::string V8ToString(v8::Handle<v8::Value> value, bool& ok) {
  ok = true;
  v8::String::Utf8Value utf8_value(value);
  if (!*utf8_value) {
    ok = false;
    return std::string();
  }
  return std::string(*utf8_value, utf8_value.length());
}

double V8ToNumber(v8::Handle<v8::Value> value, bool& ok) {
  ok = true;
  v8::Local<v8::Number> num_value = value->ToNumber();
  if (num_value.IsEmpty()) {
    ok = false;
    return 0;
  }
  return num_value->Value();
}

int32_t V8ToInt32(v8::Handle<v8::Value> value, bool& ok) {
  ok = true;
  v8::Local<v8::Int32> int_value = value->ToInt32();
  if (int_value.IsEmpty()) {
    ok = false;
    return 0;
  }
  return int_value->Value();
}

uint32_t V8ToUint32(v8::Handle<v8::Value> value, bool& ok) {
  ok = true;
  v8::Local<v8::Uint32> uint_value = value->ToUint32();
  if (uint_value.IsEmpty()) {
    ok = false;
    return 0;
  }
  return uint_value->Value();
}

}
