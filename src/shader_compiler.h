// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_SHADER_COMPILER_H
#define V8WEBGL_SHADER_COMPILER_H

#include "gl.h"
#include <GLSLANG/ShaderLang.h>
#include <string>

namespace v8_webgl {
class WebGLRenderingContext;

class ShaderCompiler {
 public:
  ShaderCompiler()
      : built_compilers_(false)
      , fragment_compiler_(0)
      , vertex_compiler_(0) {}
  ~ShaderCompiler();

  void Init(WebGLRenderingContext* context);
  bool TranslateShaderSource(const char* shader_source, GLenum shader_type,
                             std::string* translated_shader_source, std::string* shader_log);

 private:
  ShaderCompiler(const ShaderCompiler&);
  ShaderCompiler& operator = (const ShaderCompiler&);

  void DestroyCompilers();

  ShBuiltInResources resources_;
  bool built_compilers_;
  ShHandle fragment_compiler_;
  ShHandle vertex_compiler_;
};

}

#endif
