// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_SHADER_H
#define V8WEBGL_WEBGL_SHADER_H

#include "webgl_object.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLShader : public WebGLObject<WebGLShader, GLuint> {
 public:
  static const char* const ClassName() { return "WebGLShader"; }

 protected:
  WebGLShader(WebGLRenderingContext* context, GLuint shader_id)
      : WebGLObject<WebGLShader, GLuint>(context, shader_id) {}

  friend class WebGLRenderingContext;
};

}

#endif
