// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_BUFFER_H
#define V8WEBGL_WEBGL_BUFFER_H

#include "v8_binding.h"
#include "webgl_object.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLBuffer : public V8Object<WebGLBuffer> {
 public:
  static const char* const ClassName() { return "WebGLBuffer"; }

  WebGLObject<GLuint>* get_webgl_object() { return &webgl_object_; }

 protected:
  WebGLBuffer(WebGLRenderingContext* context, GLuint buffer_id)
      : V8Object<WebGLBuffer>()
      , webgl_object_(context, buffer_id) {}

 private:
  WebGLObject<GLuint> webgl_object_;

  friend class WebGLRenderingContext;
};

}

#endif
