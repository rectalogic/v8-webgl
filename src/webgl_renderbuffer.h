// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_RENDERBUFFER_H
#define V8WEBGL_WEBGL_RENDERBUFFER_H

#include "v8_binding.h"
#include "webgl_object.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLRenderbuffer : public V8Object<WebGLRenderbuffer> {
 public:
  static const char* const ClassName() { return "WebGLRenderbuffer"; }

  WebGLObject* get_webgl_object() { return &webgl_object_; }

 protected:
  WebGLRenderbuffer(WebGLRenderingContext* context, uint32_t renderbuffer_id)
      : V8Object<WebGLRenderbuffer>()
      , webgl_object_(context, renderbuffer_id) {}

 private:
  WebGLObject webgl_object_;

  friend class WebGLRenderingContext;
};

}

#endif
