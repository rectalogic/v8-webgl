// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_FRAMEBUFFER_H
#define V8WEBGL_WEBGL_FRAMEBUFFER_H

#include "v8_binding.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLFramebuffer : public V8Object<WebGLFramebuffer> {
 public:
  static const char* const ClassName() { return "WebGLFramebuffer"; }

  unsigned long get_context_id() { return context_id_; }

 protected:
  WebGLFramebuffer(WebGLRenderingContext* context)
      : V8Object<WebGLFramebuffer>()
      , context_id_(context->get_context_id()) {}

 private:
  unsigned long context_id_;
};

}

#endif
