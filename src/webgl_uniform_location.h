// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_UNIFORM_LOCATION_H
#define V8WEBGL_WEBGL_UNIFORM_LOCATION_H

#include "webgl_object.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLUniformLocation : public WebGLObject<WebGLUniformLocation, GLint> {
 public:
  static const char* const ClassName() { return "WebGLUniformLocation"; }

  bool ValidateProgram(GLuint program_id) { return program_id == program_id_; }

 protected:
  WebGLUniformLocation(WebGLRenderingContext* context, GLuint program_id, GLint location_id)
      : WebGLObject<WebGLUniformLocation, GLint>(context, location_id, true)
      , program_id_(program_id) {}

 private:
  GLuint program_id_;

  friend class WebGLRenderingContext;
};

}

#endif
