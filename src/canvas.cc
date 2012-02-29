// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "v8_binding.h"
#include "canvas.h"

namespace v8_webgl {

#define PROTO_METHOD(name) AddCallback(proto, #name, Callback_##name, signature)

// WebGLRenderingContext getContext(DOMString type, hash);
static v8::Handle<v8::Value> Callback_getContext(const v8::Arguments& args) {
  Canvas* self = Canvas::ToNative(args.Holder());
  //XXX return existing WebGLRenderingContext or create and store one
  return v8::Undefined();
}

void Canvas::ConfigureConstructorTemplate(v8::Persistent<v8::FunctionTemplate> constructor) {
  v8::Handle<v8::ObjectTemplate> proto = constructor->PrototypeTemplate();
  v8::Local<v8::Signature> signature = v8::Signature::New(constructor);

//XXX need real JS constructor, Arguments are width, height

  PROTO_METHOD(getContext);
  //XXX add attributes (width, height etc.)?
}

}
