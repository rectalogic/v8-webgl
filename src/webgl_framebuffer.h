// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_FRAMEBUFFER_H
#define V8WEBGL_WEBGL_FRAMEBUFFER_H

#include "webgl_object.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLFramebuffer : public WebGLObject<WebGLFramebuffer, GLuint> {
 public:
  static const char* const ClassName() { return "WebGLFramebuffer"; }

 protected:
  WebGLFramebuffer(WebGLRenderingContext* context, GLuint framebuffer_id)
      : WebGLObject<WebGLFramebuffer, GLuint>(context, framebuffer_id) {}

  friend class WebGLRenderingContext;
};

}

#endif
