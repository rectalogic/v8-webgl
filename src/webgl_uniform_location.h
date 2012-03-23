// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_UNIFORM_LOCATION_H
#define V8WEBGL_WEBGL_UNIFORM_LOCATION_H

#include "v8_binding.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLUniformLocation : public V8Object<WebGLUniformLocation> {
 public:
  static const char* const ClassName() { return "WebGLUniformLocation"; }

  WebGLObject<GLint>* get_webgl_object() { return &webgl_object_; }

 protected:
  WebGLUniformLocation(WebGLRenderingContext* context, GLint location_id)
      : V8Object<WebGLUniformLocation>(true)
      , webgl_object_(context, location_id) {}

 private:
  WebGLObject<GLint> webgl_object_;

  friend class WebGLRenderingContext;
};

}

#endif
