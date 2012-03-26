// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_PROGRAM_H
#define V8WEBGL_WEBGL_PROGRAM_H

#include "webgl_object.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLProgram : public WebGLObject<WebGLProgram, GLuint> {
 public:
  static const char* const ClassName() { return "WebGLProgram"; }

 protected:
  WebGLProgram(WebGLRenderingContext* context, GLuint program_id)
      : WebGLObject<WebGLProgram, GLuint>(context, program_id) {}

  friend class WebGLRenderingContext;
};

}

#endif
