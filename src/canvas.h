// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_CANVAS_H
#define V8WEBGL_CANVAS_H

#include "v8_binding.h"

namespace v8_webgl {
class WebGLRenderingContext;

class Canvas : public V8Object<Canvas> {
 public:
  static const char* const ClassName() { return "Canvas"; }
  static void ConfigureConstructorTemplate(v8::Persistent<v8::FunctionTemplate> constructor);
  static v8::Handle<v8::Value> ConstructorCallback(const v8::Arguments& args);

  WebGLRenderingContext* GetRenderingContext(/*XXX antialias flags*/);
  int get_width() { return width_; }
  int get_height() { return height_; }
  void set_width(int width);
  void set_height(int height);

  ~Canvas();

 protected:
  Canvas(v8::Local<v8::Object> instance);

 private:
  WebGLRenderingContext* rendering_context_;
  int width_;
  int height_;
};

}

#endif
