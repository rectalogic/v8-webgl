// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_RENDERING_CONTEXT_H
#define V8WEBGL_WEBGL_RENDERING_CONTEXT_H

#include <v8_webgl.h>
#include "v8_binding.h"

namespace v8_webgl {
class GraphicContext;
class Canvas;
class WebGLActiveInfo;
class WebGLBuffer;
class WebGLFramebuffer;
class WebGLProgram;
class WebGLRenderbuffer;
class WebGLShader;
class WebGLTexture;
class WebGLUniformLocation;

class WebGLRenderingContext : public V8Object<WebGLRenderingContext> {
 public:
  static const char* const ClassName() { return "WebGLRenderingContext"; }
  static void ConfigureConstructorTemplate(v8::Persistent<v8::FunctionTemplate> constructor);

  void MakeCurrent() {
    graphic_context_->MakeCurrent();
  }

  void Resize(int width, int height) {
    graphic_context_->Resize(width, height);
  }

  WebGLActiveInfo* CreateActiveInfo();
  WebGLBuffer* CreateBuffer(uint32_t buffer_id);
  WebGLFramebuffer* CreateFramebuffer(uint32_t framebuffer_id);
  WebGLProgram* CreateProgram(uint32_t program_id);
  WebGLRenderbuffer* CreateRenderbuffer();
  WebGLShader* CreateShader();
  WebGLTexture* CreateTexture();
  WebGLUniformLocation* CreateUniformLocation();

  unsigned long get_context_id() { return context_id_; }

 protected:
  WebGLRenderingContext(int width, int height);
  ~WebGLRenderingContext();

 private:
  GraphicContext* graphic_context_;
  unsigned long context_id_;

  static unsigned long s_context_counter;

  friend class Canvas;
  friend class V8Object<WebGLRenderingContext>;
};

}

#endif
