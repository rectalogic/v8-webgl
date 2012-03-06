// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_PROGRAM_H
#define V8WEBGL_WEBGL_PROGRAM_H

#include "v8_binding.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLProgram : public V8Object<WebGLProgram> {
 public:
  static const char* const ClassName() { return "WebGLProgram"; }

  unsigned long get_context_id() { return context_id_; }
  uint32_t get_program_id() { return program_id_; }

 protected:
  WebGLProgram(WebGLRenderingContext* context, uint32_t program_id)
      : V8Object<WebGLProgram>()
      , context_id_(context->get_context_id())
      , program_id_(program_id) {}

 private:
  unsigned long context_id_;
  uint32_t program_id_;

  friend class WebGLRenderingContext;
};

}

#endif
