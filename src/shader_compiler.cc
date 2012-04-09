// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "shader_compiler.h"
#include "webgl_rendering_context.h"
#include <vector>

namespace v8_webgl {

ShaderCompiler::~ShaderCompiler() {
  DestroyCompilers();
}

void ShaderCompiler::Init(WebGLRenderingContext* context) {
  ShInitialize();
  ShInitBuiltInResources(&resources_);

  context->MakeCurrent();

  context->GetIntegerv(GL_MAX_VERTEX_ATTRIBS, &resources_.MaxVertexAttribs);
  context->GetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &resources_.MaxVertexUniformVectors);
  context->GetIntegerv(GL_MAX_VARYING_VECTORS, &resources_.MaxVaryingVectors);
  context->GetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &resources_.MaxVertexTextureImageUnits);
  context->GetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &resources_.MaxCombinedTextureImageUnits); 
  context->GetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &resources_.MaxTextureImageUnits);
  context->GetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &resources_.MaxFragmentUniformVectors);

  // Always set to 1 for OpenGL ES.
  resources_.MaxDrawBuffers = 1;
}

void ShaderCompiler::DestroyCompilers() {
  if (fragment_compiler_)
    ShDestruct(fragment_compiler_);
  fragment_compiler_ = 0;
  if (vertex_compiler_)
    ShDestruct(vertex_compiler_);
  vertex_compiler_ = 0;

  built_compilers_ = false;
}

bool ShaderCompiler::TranslateShaderSource(const char* shader_source, GLenum shader_type, std::string* translated_shader_source, std::string* shader_log) {
  if (!built_compilers_) {
    fragment_compiler_ = ShConstructCompiler(SH_FRAGMENT_SHADER, SH_WEBGL_SPEC, SH_GLSL_OUTPUT, &resources_);
    vertex_compiler_ = ShConstructCompiler(SH_VERTEX_SHADER, SH_WEBGL_SPEC, SH_GLSL_OUTPUT, &resources_);
    if (!fragment_compiler_ || !vertex_compiler_) {
      DestroyCompilers();
      return false;
    }

    built_compilers_ = true;
  }

  ShHandle compiler;
  if (shader_type == GL_VERTEX_SHADER)
    compiler = vertex_compiler_;
  else // GL_FRAGMENT_SHADER
    compiler = fragment_compiler_;

  const char* const shader_source_strings[] = { shader_source };

  bool is_valid = ShCompile(compiler, shader_source_strings, 1, SH_OBJECT_CODE);
  if (!is_valid) {
    int log_size = 0;
    ShGetInfo(compiler, SH_INFO_LOG_LENGTH, &log_size);
    if (log_size > 1) {
      std::vector<char> buffer(log_size);
      ShGetInfoLog(compiler, &buffer[0]);
      shader_log->assign(&buffer[0], log_size - 1);
    }
    return false;
  }

  int translated_source_length = 0;
  ShGetInfo(compiler, SH_OBJECT_CODE_LENGTH, &translated_source_length);
  if (translated_source_length > 1) {
    std::vector<char> buffer(translated_source_length);
    ShGetObjectCode(compiler, &buffer[0]);
    translated_shader_source->assign(&buffer[0], translated_source_length - 1);
  }
  return true;
}

}
