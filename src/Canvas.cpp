// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "V8Binding.h"
#include "Canvas.h"

namespace V8WebGL {

// WebGLRenderingContext getContext(DOMString type, hash);
static v8::Handle<v8::Value> getContextCallback(const v8::Arguments& args)
{
    //XXX check args.Length()?
    Canvas* self = Canvas::toNative(args.Holder());
    //XXX return existing WebGLRenderingContext or create and store one
    return v8::Handle<v8::Value>();
}

#define PROTO_METHOD(name) addCallback(proto, #name, name##Callback, signature)


void Canvas::configureConstructorTemplate(v8::Persistent<v8::FunctionTemplate> constructor)
{
    v8::Handle<v8::ObjectTemplate> proto = constructor->PrototypeTemplate();
    v8::Local<v8::Signature> signature = v8::Signature::New(constructor);

//XXX need real JS constructor, Arguments are width, height

    PROTO_METHOD(getContext);
    //XXX add attributes (width, height etc.)?
}

}
