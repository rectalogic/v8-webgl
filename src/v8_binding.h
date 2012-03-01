// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_V8BINDING_H
#define V8WEBGL_V8BINDING_H

#include <v8.h>
#include <assert.h>

namespace v8_webgl {

class V8ObjectBase {
 protected:
  virtual ~V8ObjectBase() {}

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
  static bool IsConstructionAllowed() { return s_allow_construction; }
 private:
  static bool s_allow_construction;
};
template<class T>
bool ConstructorMode<T>::s_allow_construction = false;

//////

template<class T>
class V8Object : public V8ObjectBase {
 public:
  static void Initialize(v8::Handle<v8::ObjectTemplate> global) {
    if (!s_constructor_template.IsEmpty())
      return;
    v8::HandleScope scope;
    s_constructor_template = CreateConstructorTemplate(T::ClassName(), ConstructorCallback);
    T::ConfigureConstructorTemplate(s_constructor_template);
    T::ConfigureGlobal(global);
  }

  static void Uninitialize() {
    if (s_constructor_template.IsEmpty())
      return;
    s_constructor_template.Dispose();
    s_constructor_template.Clear();
  }

  // Subclasses can reimplement this if they don't want their constructor name exposed
  static void ConfigureGlobal(v8::Handle<v8::ObjectTemplate> global) {
    global->Set(v8::String::New(T::ClassName()), s_constructor_template);
  }

  inline static T* ToNative(v8::Handle<v8::Object> value) {
    return static_cast<T*>(value->GetPointerFromInternalField(0));
  }

  inline static bool HasInstance(v8::Handle<v8::Value> value){
    return s_constructor_template->HasInstance(value);
  }

  inline v8::Handle<v8::Object> ToV8() {
    return instance_;
  }

 protected:
  V8Object(v8::Local<v8::Object> instance = v8::Local<v8::Object>()) {
    // If no instance, construct a new one
    if (instance.IsEmpty()) {
      ConstructorMode<T> mode;
      instance = s_constructor_template->GetFunction()->NewInstance();
    }

    instance_ = v8::Persistent<v8::Object>::New(instance);
    instance_->SetPointerInInternalField(0, this);
    instance_.MakeWeak(this, WeakCallback);
  }

  ~V8Object() {
    //XXX is this right? instance_ won't be empty if Disposed - needs to be Cleared
    if (!instance_.IsEmpty()) {
      assert(instance_.IsNearDeath());
      instance_.ClearWeak();
      instance_->SetInternalField(0, v8::Undefined());
      instance_.Dispose();
      instance_.Clear();
    }
  }

  static v8::Handle<v8::Value> ConstructorCallback(const v8::Arguments& args) {
    v8::HandleScope scope;
    if (!ConstructorMode<T>::IsConstructionAllowed())
      return v8::ThrowException(v8::Exception::TypeError(v8::String::New("Illegal constructor")));

    return args.This();
  }

 private:
  static void WeakCallback(v8::Persistent<v8::Value> value, void* data) {
    value.Dispose();
    T* object = static_cast<T*>(data);
    assert(value == object->instance_);
    delete object;
  }

  static v8::Persistent<v8::FunctionTemplate> s_constructor_template;
  v8::Persistent<v8::Object> instance_;
};

template<class T>
v8::Persistent<v8::FunctionTemplate> V8Object<T>::s_constructor_template;

}

#endif
