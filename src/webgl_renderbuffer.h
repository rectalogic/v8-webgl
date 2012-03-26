// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_RENDERBUFFER_H
#define V8WEBGL_WEBGL_RENDERBUFFER_H

#include "webgl_object.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLRenderbuffer : public WebGLObject<WebGLRenderbuffer, GLuint> {
 public:
  static const char* const ClassName() { return "WebGLRenderbuffer"; }

 protected:
  WebGLRenderbuffer(WebGLRenderingContext* context, GLuint renderbuffer_id)
      : WebGLObject<WebGLRenderbuffer, GLuint>(context, renderbuffer_id) {}

  friend class WebGLRenderingContext;
};

}

#endif
