// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "v8_binding.h"
#include "canvas.h"
#include "webgl_rendering_context.h"


namespace v8_webgl {


//XXX Canvas is weak - maybe should be strong with dispose method?
Canvas::Canvas(v8::Handle<v8::Object> instance)
    : V8Object<Canvas>(true, instance)
    , rendering_context_(0)
    , width_(0)
    , height_(0) {
}

Canvas::~Canvas() {
  delete rendering_context_;
}

//XXX need antialiasing flags
WebGLRenderingContext* Canvas::GetRenderingContext() {
  if (rendering_context_)
    return rendering_context_;
  // Context is not weak
  rendering_context_ = new WebGLRenderingContext(width_, height_);
  return rendering_context_;
}

void Canvas::set_width(int width) {
  if (width == width_)
    return;
  width_ = width;
  if (rendering_context_)
    rendering_context_->Resize(width_, height_);
}

void Canvas::set_height(int height) {
  if (height == height_)
    return;
  height_ = height;
  if (rendering_context_)
    rendering_context_->Resize(width_, height_);
}

// WebGLRenderingContext getContext(DOMString type, hash);
v8::Handle<v8::Value> Canvas::Callback_getContext(const v8::Arguments& args) {
  //XXX validate first arg is "experimental-webgl", handle optional second arg params
  return GetRenderingContext()->ToV8Object();
}

void Canvas::Setter_width(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo& info) {
  set_width(value->Int32Value());
}

v8::Handle<v8::Value> Canvas::Getter_width(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
  return v8::Integer::New(get_width());
}

void Canvas::Setter_height(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo& info) {
  set_height(value->Int32Value());
}

v8::Handle<v8::Value> Canvas::Getter_height(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
  return v8::Integer::New(get_height());
}

v8::Handle<v8::Value> Canvas::ConstructorCallback(const v8::Arguments& args) {
  new Canvas(args.This());
  return args.This();
}

void Canvas::ConfigureConstructorTemplate(v8::Persistent<v8::FunctionTemplate> constructor) {
  v8::Handle<v8::ObjectTemplate> proto = constructor->PrototypeTemplate();
  v8::Handle<v8::ObjectTemplate> instance = constructor->InstanceTemplate();
  v8::Local<v8::Signature> signature = v8::Signature::New(constructor);

#define PROTO_METHOD(name, argc) AddCallback(proto, #name, InvocationCallbackDispatcher<Canvas, argc, &Canvas::Callback_##name>, signature)

  PROTO_METHOD(getContext, 0); //XXX should be 1 args, "experimental-webgl" and optional options hash

#undef PROTO_METHOD

#define ACCESSOR(name) SetAccessor(instance, #name, AccessorGetterDispatcher<Canvas, &Canvas::Getter_##name>, AccessorSetterDispatcher<Canvas, &Canvas::Setter_##name>)

  ACCESSOR(width);
  ACCESSOR(height);

#undef ACCESSOR
}

}
