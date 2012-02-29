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

}
