// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_RENDERING_CONTEXT_H
#define V8WEBGL_WEBGL_RENDERING_CONTEXT_H

#include "v8_binding.h"

namespace v8_webgl {
class Canvas;
class GraphicContext;

class WebGLRenderingContext : public V8Object<WebGLRenderingContext> {
 public:
  static const char* const ClassName() { return "WebGLRenderingContext"; }
  static void ConfigureConstructorTemplate(v8::Persistent<v8::FunctionTemplate> constructor);

  void Resize(int width, int height);

  ~WebGLRenderingContext();

 protected:
  WebGLRenderingContext(int width, int height);

 private:
  GraphicContext* graphic_context_;

  friend class Canvas;
};

}

#endif
