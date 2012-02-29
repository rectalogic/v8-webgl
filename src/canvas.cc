// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "v8_binding.h"
#include "canvas.h"

namespace v8_webgl {

#define PROTO_METHOD(name) AddCallback(proto, #name, Callback_##name, signature)

Canvas::Canvas(v8::Local<v8::Object> instance, int width, int height)
    : V8Object<Canvas>(instance) {
  //XXX create GLContext of given size
  //XXX need ability to resize too
}

// WebGLRenderingContext getContext(DOMString type, hash);
static v8::Handle<v8::Value> Callback_getContext(const v8::Arguments& args) {
  v8::HandleScope scope;
  Canvas* self = Canvas::ToNative(args.Holder());
  //XXX return existing WebGLRenderingContext or create and store one
  return v8::Undefined();
}

v8::Handle<v8::Value> Canvas::ConstructorCallback(const v8::Arguments& args) {
  v8::HandleScope scope;
  //XXX get width/height and options from args, construct canvas with them
  Canvas* canvas = new Canvas(args.This(), 0, 0 /*XXX width, height */);
  return args.This();
}

void Canvas::ConfigureConstructorTemplate(v8::Persistent<v8::FunctionTemplate> constructor) {
  v8::Handle<v8::ObjectTemplate> proto = constructor->PrototypeTemplate();
  v8::Local<v8::Signature> signature = v8::Signature::New(constructor);

  PROTO_METHOD(getContext);
  //XXX add attributes (width, height etc.)?
}

}
