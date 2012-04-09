// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_SHADER_H
#define V8WEBGL_WEBGL_SHADER_H

#include "webgl_object.h"
#include "webgl_rendering_context.h"
#include <string>

namespace v8_webgl {

class WebGLShader : public WebGLObject<WebGLShader, GLuint> {
 public:
  static const char* const ClassName() { return "WebGLShader"; }

  std::string source() { return source_; }
  void set_source(const std::string& source) { source_ = source; }

  std::string log() { return log_; }
  void set_log(const std::string& log) { log_ = log; }

  bool is_valid() { return is_valid_; }
  void set_is_valid(bool valid) { is_valid_ = valid; }

 protected:
  WebGLShader(WebGLRenderingContext* context, GLuint shader_id)
      : WebGLObject<WebGLShader, GLuint>(context, shader_id)
      , is_valid_(false) {}

  friend class WebGLRenderingContext;

 private:
  bool is_valid_;
  std::string source_;
  std::string log_;
};

}

#endif
