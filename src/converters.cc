// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "converters.h"

namespace v8_webgl {

template<>
std::string FromV8<std::string>(v8::Handle<v8::Value> value, bool* ok) {
  *ok = true;

  v8::String::Utf8Value utf8_value(value);
  if (!*utf8_value) {
    *ok = false;
    return std::string();
  }
  return std::string(*utf8_value, utf8_value.length());
}

template<>
double FromV8<double>(v8::Handle<v8::Value> value, bool* ok) {
  *ok = true;

  v8::Local<v8::Number> num_value = value->ToNumber();
  if (num_value.IsEmpty()) {
    *ok = false;
    return 0;
  }
  return num_value->Value();
}

template<>
int32_t FromV8<int32_t>(v8::Handle<v8::Value> value, bool* ok) {
  *ok = true;

  v8::Local<v8::Int32> int_value = value->ToInt32();
  if (int_value.IsEmpty()) {
    *ok = false;
    return 0;
  }
  return int_value->Value();
}

template<>
uint32_t FromV8<uint32_t>(v8::Handle<v8::Value> value, bool* ok) {
  *ok = true;

  v8::Local<v8::Uint32> uint_value = value->ToUint32();
  if (uint_value.IsEmpty()) {
    *ok = false;
    return 0;
  }
  return uint_value->Value();
}

}
