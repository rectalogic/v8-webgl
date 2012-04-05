// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_V8BINDING_H
#define V8WEBGL_V8BINDING_H

#include <v8.h>
#include "converters.h"

namespace v8_webgl {

// InvocationCallback that does arg length checking and exception handling,
// and invokes the callback instance member function on the wrapped native.
template<class T, int Arity, v8::Handle<v8::Value> (T::*InvocationCallbackMember)(v8::Arguments const&)>
static v8::Handle<v8::Value> InvocationCallbackDispatcher(v8::Arguments const& args) {
  if (args.Length() < Arity)
    return ThrowArgCount();
  T* object = T::FromV8Object(args.Holder());
  if (!object)
    return ThrowObjectDisposed();
  try {
    return ((*object).*(InvocationCallbackMember))(args);
  } catch (std::exception const& e) {
    return v8::ThrowException(v8::String::New(e.what()));
  } catch (...) {
    return v8::ThrowException(v8::String::New("Caught unknown native exception."));
  }
}

template<v8::InvocationCallback CB>
static v8::Handle<v8::Value> InvocationCallbackCatcher(v8::Arguments const& args) {
  try {
    return CB(args);
  } catch (std::exception const& e) {
    return v8::ThrowException(v8::String::New(e.what()));
  } catch (...) {
    return v8::ThrowException(v8::String::New("Caught unknown native exception."));
  }
}

template<class T, v8::Handle<v8::Value> (T::*AccessorGetterMember)(v8::Local<v8::String>, const v8::AccessorInfo&)>
static v8::Handle<v8::Value> AccessorGetterDispatcher(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
  T* object = T::FromV8Object(info.Holder());
  if (!object)
    return ThrowObjectDisposed();
  try {
    return ((*object).*(AccessorGetterMember))(property, info);
  } catch (std::exception const& e) {
    return v8::ThrowException(v8::String::New(e.what()));
  } catch (...) {
    return v8::ThrowException(v8::String::New("Caught unknown native exception."));
  }
}

template<class T, void (T::*AccessorSetterMember)(v8::Local<v8::String>, v8::Local<v8::Value>, const v8::AccessorInfo&)>
static void AccessorSetterDispatcher(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo& info) {
  T* object = T::FromV8Object(info.Holder());
  if (!object) {
    ThrowObjectDisposed();
    return;
  }
  try {
    ((*object).*(AccessorSetterMember))(property, value, info);
  } catch (std::exception const& e) {
    v8::ThrowException(v8::String::New(e.what()));
  } catch (...) {
    v8::ThrowException(v8::String::New("Caught unknown native exception."));
  }
}

//////

class V8ObjectBase {
 public:
  inline static V8ObjectBase* FromV8Object(v8::Handle<v8::Object> value) {
    return static_cast<V8ObjectBase*>(value->GetPointerFromInternalField(0));
  }

  inline v8::Handle<v8::Object> ToV8Object() {
    return instance_;
  }

 protected:
  V8ObjectBase() {}
  virtual ~V8ObjectBase();

  inline static void AddCallback(v8::Handle<v8::ObjectTemplate> proto, const char* name, v8::InvocationCallback callback, v8::Local<v8::Signature> signature) {
    proto->Set(v8::String::New(name),
               v8::FunctionTemplate::New(callback, v8::Handle<v8::Value>(), signature),
               v8::DontDelete);
  };

  inline static void AddConstant(const char* name, v8::Handle<v8::Value> value, v8::Handle<v8::ObjectTemplate> proto, v8::Handle<v8::FunctionTemplate> constructor) {
    v8::Handle<v8::String> name_handle(v8::String::New(name));
    constructor->Set(name_handle, value, static_cast<v8::PropertyAttribute>(v8::ReadOnly|v8::DontDelete));
    proto->Set(name_handle, value, static_cast<v8::PropertyAttribute>(v8::ReadOnly|v8::DontDelete));
  };

  inline static void SetProperty(v8::Handle<v8::Object> self, const char* name, v8::Handle<v8::Value> value) {
    self->Set(ToV8(name), value,
              static_cast<v8::PropertyAttribute>(v8::ReadOnly|v8::DontDelete));
  }

  inline static void SetAccessor(v8::Handle<v8::ObjectTemplate> instance, const char* name, v8::AccessorGetter getter, v8::AccessorSetter setter) {
    instance->SetAccessor(v8::String::New(name), getter, setter);
  }

  static v8::Persistent<v8::FunctionTemplate> CreateConstructorTemplate(const char* class_name, v8::InvocationCallback callback);

  void SetInstance(v8::Handle<v8::Object> instance, bool weak = false);

 private:
  V8ObjectBase(const V8ObjectBase&);
  V8ObjectBase& operator = (const V8ObjectBase&);

  v8::Persistent<v8::Object> instance_;

  static void WeakCallback(v8::Persistent<v8::Value> value, void* data);
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
    s_constructor_template =
        CreateConstructorTemplate(T::ClassName(), InvocationCallbackCatcher<T::ConstructorCallback>);
    T::ConfigureConstructorTemplate(s_constructor_template);
    T::ConfigureGlobal(global);
  }

  static void Uninitialize() {
    if (s_constructor_template.IsEmpty())
      return;
    s_constructor_template.Dispose();
    s_constructor_template.Clear();
  }

  inline static T* FromV8Object(v8::Handle<v8::Object> value) {
    return static_cast<T*>(V8ObjectBase::FromV8Object(value));
  }

  inline static bool HasInstance(v8::Handle<v8::Value> value){
    return s_constructor_template->HasInstance(value);
  }

  inline static void Reparent(v8::Handle<v8::FunctionTemplate> child) {
    child->Inherit(s_constructor_template);
  }

 protected:
  V8Object(bool weak = false, v8::Handle<v8::Object> instance = v8::Local<v8::Object>()) {
    // If no instance, construct a new one
    if (instance.IsEmpty()) {
      ConstructorMode<T> mode;
      instance = Create();
    }
    SetInstance(instance, weak);
  }

  static v8::Handle<v8::Object> Create(int argc = 0, v8::Handle<v8::Value> argv[] = NULL) {
    return s_constructor_template->GetFunction()->NewInstance(argc, argv);
  }

  // Subclasses should reimplement
  static void ConfigureConstructorTemplate(v8::Persistent<v8::FunctionTemplate> /* constructor */) {}

  // Subclasses can reimplement this if they don't want their constructor name exposed
  static void ConfigureGlobal(v8::Handle<v8::ObjectTemplate> global) {
    global->Set(v8::String::New(T::ClassName()), s_constructor_template);
  }

  static v8::Handle<v8::Value> ConstructorCallback(const v8::Arguments& args) {
    if (!ConstructorMode<T>::IsConstructionAllowed())
      return v8::ThrowException(v8::Exception::TypeError(v8::String::New("Illegal constructor")));

    return args.This();
  }

 private:
  static v8::Persistent<v8::FunctionTemplate> s_constructor_template;
};

template<class T>
v8::Persistent<v8::FunctionTemplate> V8Object<T>::s_constructor_template;

}

#endif
