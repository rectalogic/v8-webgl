// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_ACTIVE_INFO_H
#define V8WEBGL_WEBGL_ACTIVE_INFO_H

#include "v8_binding.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLActiveInfo : public V8Object<WebGLActiveInfo> {
 public:
  static const char* const ClassName() { return "WebGLActiveInfo"; }

 protected:
  WebGLActiveInfo(GLint size, GLenum type, const char* name);

  friend class WebGLRenderingContext;
};

}

#endif
