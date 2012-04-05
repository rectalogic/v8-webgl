// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "v8_binding.h"

namespace v8_webgl {

V8ObjectBase::~V8ObjectBase() {
  if (!instance_.IsEmpty()) {
    instance_.ClearWeak();
    instance_->SetPointerInInternalField(0, 0);
    instance_.Dispose();
    instance_.Clear();
  }
}

void V8ObjectBase::SetInstance(v8::Handle<v8::Object> instance, bool weak) {
  instance_ = v8::Persistent<v8::Object>::New(instance);
  instance_->SetPointerInInternalField(0, this);
  if (weak) {
    // Since we aren't using object grouping API, mark independent
    // so our weak callback is called earlier.
    instance_.MarkIndependent();
    instance_.MakeWeak(this, WeakCallback);
  }
}

void V8ObjectBase::WeakCallback(v8::Persistent<v8::Value> value, void* data) {
  V8ObjectBase* object = static_cast<V8ObjectBase*>(data);
  delete object;
}

v8::Persistent<v8::FunctionTemplate> V8ObjectBase::CreateConstructorTemplate(const char* class_name, v8::InvocationCallback callback) {
  v8::Local<v8::FunctionTemplate> result = v8::FunctionTemplate::New(callback);
  v8::Persistent<v8::FunctionTemplate> constructor = v8::Persistent<v8::FunctionTemplate>::New(result);
  constructor->SetClassName(v8::String::New(class_name));
  constructor->ReadOnlyPrototype();
  v8::Local<v8::ObjectTemplate> instance = constructor->InstanceTemplate();
  instance->SetInternalFieldCount(1);
  return constructor;
}

}
