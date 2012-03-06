// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_BUFFER_H
#define V8WEBGL_WEBGL_BUFFER_H

#include "v8_binding.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLBuffer : public V8Object<WebGLBuffer> {
 public:
  static const char* const ClassName() { return "WebGLBuffer"; }

  bool ValidateContext(WebGLRenderingContext* context) { return context->get_context_id() == context_id_; }
  uint32_t get_buffer_id() { return buffer_id_; }

 protected:
  WebGLBuffer(WebGLRenderingContext* context, uint32_t buffer_id)
      : V8Object<WebGLBuffer>()
      , context_id_(context->get_context_id())
      , buffer_id_(buffer_id) {}

 private:
  unsigned long context_id_;
  uint32_t buffer_id_;

  friend class WebGLRenderingContext;
};

}

#endif
