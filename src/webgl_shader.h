// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_SHADER_H
#define V8WEBGL_WEBGL_SHADER_H

#include "v8_binding.h"
#include "webgl_object.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLShader : public V8Object<WebGLShader> {
 public:
  static const char* const ClassName() { return "WebGLShader"; }

  WebGLObject<GLuint>* get_webgl_object() { return &webgl_object_; }

 protected:
  WebGLShader(WebGLRenderingContext* context, GLuint shader_id)
      : V8Object<WebGLShader>()
      , webgl_object_(context, shader_id) {}

 private:
  WebGLObject<GLuint> webgl_object_;

  friend class WebGLRenderingContext;
};

}

#endif
