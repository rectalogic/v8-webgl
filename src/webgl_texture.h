// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_TEXTURE_H
#define V8WEBGL_WEBGL_TEXTURE_H

#include "v8_binding.h"
#include "webgl_object.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLTexture : public V8Object<WebGLTexture> {
 public:
  static const char* const ClassName() { return "WebGLTexture"; }

  WebGLObject* get_webgl_object() { return &webgl_object_; }

 protected:
  WebGLTexture(WebGLRenderingContext* context, uint32_t texture_id)
      : V8Object<WebGLTexture>()
      , webgl_object_(context, texture_id) {}

 private:
  WebGLObject webgl_object_;

  friend class WebGLRenderingContext;
};

}

#endif
