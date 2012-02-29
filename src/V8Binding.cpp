// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "V8Binding.h"

namespace V8WebGL {

v8::Persistent<v8::FunctionTemplate> V8ObjectBase::createConstructorTemplate(const char* className, v8::InvocationCallback callback)
{
    v8::Local<v8::FunctionTemplate> result = v8::FunctionTemplate::New(callback);
    v8::Persistent<v8::FunctionTemplate> constructor = v8::Persistent<v8::FunctionTemplate>::New(result);
    constructor->SetClassName(v8::String::New(className));
    constructor->ReadOnlyPrototype();
    v8::Local<v8::ObjectTemplate> instance = constructor->InstanceTemplate();
    instance->SetInternalFieldCount(1);
    return constructor;
}

}
