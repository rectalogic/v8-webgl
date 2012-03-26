// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_BUFFER_H
#define V8WEBGL_WEBGL_BUFFER_H

#include "webgl_object.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLBuffer : public WebGLObject<WebGLBuffer, GLuint> {
 public:
  static const char* const ClassName() { return "WebGLBuffer"; }

 protected:
  WebGLBuffer(WebGLRenderingContext* context, GLuint buffer_id)
      : WebGLObject<WebGLBuffer, GLuint>(context, buffer_id) {}

  friend class WebGLRenderingContext;
};

}

#endif
