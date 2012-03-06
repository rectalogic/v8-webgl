// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_SHADER_H
#define V8WEBGL_WEBGL_SHADER_H

#include "v8_binding.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLShader : public V8Object<WebGLShader> {
 public:
  static const char* const ClassName() { return "WebGLShader"; }

  bool ValidateContext(WebGLRenderingContext* context) { return context->get_context_id() == context_id_; }
  uint32_t get_shader_id() { return shader_id_; }

 protected:
  WebGLShader(WebGLRenderingContext* context, uint32_t shader_id)
      : V8Object<WebGLShader>()
      , context_id_(context->get_context_id())
      , shader_id_(shader_id) {}

 private:
  unsigned long context_id_;
  uint32_t shader_id_;

  friend class WebGLRenderingContext;
};

}

#endif
