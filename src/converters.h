// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_CONVERTERS_H
#define V8WEBGL_CONVERTERS_H

#include <v8.h>
#include <string>
#include <vector>

namespace v8_webgl {

inline v8::Handle<v8::Value> ThrowError(const char* msg) {
  return v8::ThrowException(v8::String::New(msg));
}

inline v8::Handle<v8::Value> ThrowObjectDisposed() {
  return v8::ThrowException(v8::Exception::ReferenceError(v8::String::New("Object has been disposed")));
}

inline v8::Handle<v8::Value> ThrowArgCount() {
  return v8::ThrowException(v8::Exception::TypeError(v8::String::New("Not enough arguments")));
}

inline v8::Handle<v8::Value> ThrowTypeError() {
  return v8::ThrowException(v8::Exception::TypeError(v8::String::New("Type error")));
}

inline v8::Handle<v8::Value> ThrowRangeError(const char* msg) {
  return v8::ThrowException(v8::Exception::RangeError(v8::String::New(msg)));
}

//////

template<typename T>
v8::Handle<v8::Value> ToV8(T value);

template<>
inline v8::Handle<v8::Value> ToV8<bool>(bool value) {
  return value ? v8::True() : v8::False();
}
template<>
inline v8::Handle<v8::Value> ToV8<int32_t>(int32_t value) {
  return v8::Integer::New(value);
}
template<>
inline v8::Handle<v8::Value> ToV8<uint32_t>(uint32_t value) {
  return v8::Integer::NewFromUnsigned(value);
}
template<>
inline v8::Handle<v8::Value> ToV8<double>(double value) {
  return v8::Number::New(value);
}
template<>
inline v8::Handle<v8::Value> ToV8<const char*>(const char* value) {
  return v8::String::New(value);
}
template<>
inline v8::Handle<v8::Value> ToV8<std::string>(std::string value) {
  return v8::String::New(value.data(), value.size());
}

template<typename T>
v8::Handle<v8::Array> ArrayToV8(T* values, uint32_t length) {
  v8::Local<v8::Array> array = v8::Array::New(length);
  for (uint32_t i = 0; i < length; i++)
    array->Set(ToV8(i), ToV8<T>(values[i]));
  return array;
}

template<typename T>
T FromV8(v8::Handle<v8::Value> value, bool* ok);

template<>
std::string FromV8<std::string>(v8::Handle<v8::Value> value, bool* ok);

template<>
inline bool FromV8<bool>(v8::Handle<v8::Value> value, bool* ok) {
  *ok = true;
  return value->BooleanValue();
}

template<>
double FromV8<double>(v8::Handle<v8::Value> value, bool* ok);

template<>
inline float FromV8<float>(v8::Handle<v8::Value> value, bool* ok) {
  return static_cast<float>(FromV8<double>(value, ok));
}

template<>
int32_t FromV8<int32_t>(v8::Handle<v8::Value> value, bool* ok);

template<>
uint32_t FromV8<uint32_t>(v8::Handle<v8::Value> value, bool* ok);


template<class T>
T* NativeFromV8(v8::Handle<v8::Value> value, bool* ok) {
  *ok = true;
  // Not an error if undefined/null
  if (value->IsUndefined() || value->IsNull())
    return NULL;

  if (!T::HasInstance(value)) {
    *ok = false;
    return NULL;
  }
  v8::Handle<v8::Object> object = value->ToObject();
  T* native = T::FromV8Object(object);
  if (!native) {
    *ok = false;
    ThrowObjectDisposed();
    return NULL;
  }
  return native;
}

template<class T>
std::vector<T> ArrayFromV8(v8::Handle<v8::Value> value, bool* ok) {
  *ok = true;

  if (value->IsUndefined() || value->IsNull())
    return std::vector<T>();
  if (!value->IsArray()){
    *ok = false;
    return std::vector<T>();
  }
  v8::Handle<v8::Array> array = v8::Handle<v8::Array>::Cast(value);
  uint32_t length = array->Length();
  std::vector<T> vector(length);
  for (uint32_t i = 0; i < length; i++) {
    v8::Local<v8::Value> entry = array->Get(i);
    vector[i] = FromV8<T>(entry, ok);
    if (!*ok)
      return std::vector<T>();
  }
  return vector;
}

}
#endif
