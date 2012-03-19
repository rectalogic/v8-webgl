// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_OBJECT_H
#define V8WEBGL_WEBGL_OBJECT_H

#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLObject {
 public:
  WebGLObject(WebGLRenderingContext* context, GLuint webgl_id)
      : context_id_(context->get_context_id())
      , webgl_id_(webgl_id) {}

  bool ValidateContext(WebGLRenderingContext* context) { return context->get_context_id() == context_id_; }
  GLuint get_webgl_id() { return webgl_id_; }

 private:
  unsigned long context_id_;
  GLuint webgl_id_;
};

}

#endif
