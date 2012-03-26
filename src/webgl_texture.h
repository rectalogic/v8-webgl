// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_TEXTURE_H
#define V8WEBGL_WEBGL_TEXTURE_H

#include "webgl_object.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLTexture : public WebGLObject<WebGLTexture, GLuint> {
 public:
  static const char* const ClassName() { return "WebGLTexture"; }

 protected:
  WebGLTexture(WebGLRenderingContext* context, GLuint texture_id)
      : WebGLObject<WebGLTexture, GLuint>(context, texture_id) {}

  friend class WebGLRenderingContext;
};

}

#endif
