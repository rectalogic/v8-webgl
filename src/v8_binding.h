// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_V8BINDING_H
#define V8WEBGL_V8BINDING_H

#include <v8.h>

namespace v8_webgl {

class V8ObjectBase {
protected:
  inline static void AddCallback(v8::Handle<v8::ObjectTemplate> proto, const char* name, v8::InvocationCallback callback, v8::Local<v8::Signature> signature) {
    proto->Set(v8::String::New(name),
               v8::FunctionTemplate::New(callback, v8::Handle<v8::Value>(), signature),
               v8::DontDelete);
  };

  static v8::Persistent<v8::FunctionTemplate> CreateConstructorTemplate(const char* class_name, v8::InvocationCallback callback);
};

//////

template<class T>
class ConstructorMode {
public:
  ConstructorMode() { s_allow_construction = true; }
  ~ConstructorMode() { s_allow_construction = false; }
  static bool AllowConstruction() { return s_allow_construction; }
private:
  static bool s_allow_construction;
};
template<class T>
bool ConstructorMode<T>::s_allow_construction = false;

//////

template<class T>
class V8Object : public V8ObjectBase {
public:
  static void Initialize(v8::Handle<v8::ObjectTemplate> target) {
    if (!s_constructor_template.IsEmpty())
      return;
    v8::HandleScope scope;
    s_constructor_template = CreateConstructorTemplate(T::ClassName(), ConstructorCallback);
    T::ConfigureConstructorTemplate(s_constructor_template);
    T::ConfigureTarget(target);
  }

  static void Uninitialize() {
    if (s_constructor_template.IsEmpty())
      return;
    s_constructor_template.Dispose();
    s_constructor_template.Clear();
  }

  // Subclasses can reimplement this if they don't want their constructor exposed
  static void ConfigureTarget(v8::Handle<v8::ObjectTemplate> target) {
    target->Set(v8::String::New(T::ClassName()), s_constructor_template);
  }

  inline static T* ToNative(v8::Handle<v8::Object> value) {
    v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(value->GetInternalField(0));
    return static_cast<T*>(wrap->Value());
  }
//XXX add toV8() that returns JS object (class member, persistent and weak)

  inline static bool HasInstance(v8::Handle<v8::Value> value){
    return s_constructor_template->HasInstance(value);
  }

  //XXX add static toNative(Handle), hmm need to distinguish type checking from actual null value
  //XXX add wrap(T*) - return JS wrapper for T, with weakref etc.

protected:
  //XXX constructor that takes default empty instance, if empty then create new instance from template, if not empty then persist that one. Either way, make weak with callback to delete this
  V8Object(v8::Local<v8::Object> instance=v8::Local<v8::Object>()) {
    if (instance.IsEmpty()) {
      ConstructorMode<T> mode;
      instance = s_constructor_template->GetFunction()->NewInstance();
    }
    //XXX
  }

private:
  static v8::Persistent<v8::FunctionTemplate> s_constructor_template;

  static v8::Handle<v8::Value> ConstructorCallback(const v8::Arguments& args) {
    if (!ConstructorMode<T>::AllowConstruction())
      return v8::ThrowException(v8::Exception::TypeError(v8::String::New("Illegal constructor")));

    return args.This();
  }
};

template<class T>
v8::Persistent<v8::FunctionTemplate> V8Object<T>::s_constructor_template;

}

#endif
