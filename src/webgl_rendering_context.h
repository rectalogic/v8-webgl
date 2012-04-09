// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_RENDERING_CONTEXT_H
#define V8WEBGL_WEBGL_RENDERING_CONTEXT_H

#include <v8_webgl.h>
#include "v8_binding.h"
#include "shader_compiler.h"
#include <map>

#include "gl.h"

namespace v8_webgl {
class GraphicContext;
class Canvas;
class WebGLObjectInterface;
class WebGLActiveInfo;
class WebGLBuffer;
class WebGLFramebuffer;
class WebGLProgram;
class WebGLRenderbuffer;
class WebGLShader;
class WebGLTexture;
class WebGLUniformLocation;
template<typename T> class UVAHelper;
template<typename T> class UniformHelper;
template<typename T> class UniformMatrixHelper;
template<typename T> class VertexAttribHelper;

class WebGLRenderingContext : public V8Object<WebGLRenderingContext> {
 public:
  static const char* const ClassName() { return "WebGLRenderingContext"; }
  static void ConfigureConstructorTemplate(v8::Persistent<v8::FunctionTemplate> constructor);

  inline void MakeCurrent() {
    graphic_context_->MakeCurrent();
  }

  inline void Resize(int width, int height) {
    graphic_context_->Resize(width, height);
  }

  unsigned long get_context_id() { return context_id_; }

 protected:
  WebGLRenderingContext(int width, int height);
  ~WebGLRenderingContext();

 private:
  GraphicContext* graphic_context_;
  unsigned long context_id_;
  GLenum gl_error_;
  ShaderCompiler shader_compiler_;

  std::map<GLuint, WebGLBuffer*> buffer_map_;
  std::map<GLuint, WebGLFramebuffer*> framebuffer_map_;
  std::map<GLuint, WebGLProgram*> program_map_;
  std::map<GLuint, WebGLRenderbuffer*> renderbuffer_map_;
  std::map<GLuint, WebGLShader*> shader_map_;
  std::map<GLuint, WebGLTexture*> texture_map_;

  template<class T>
  void DeleteMapObjects(std::map<GLuint, T*>& map) {
    typename std::map<GLuint, T*>::iterator it;
    for (it = map.begin(); it != map.end(); it++)
      delete it->second;
  }

  template<class T>
  T* IdToObject(std::map<GLuint, T*>& map, GLuint id) {
    typename std::map<GLuint, T*>::iterator it;
    it = map.find(id);
    if (it == map.end())
      return 0;
    return it->second;
  }

  // Wraps an InvocationCallback member function, making the context current first.
  template<v8::Handle<v8::Value> (WebGLRenderingContext::*InvocationCallbackMember)(v8::Arguments const&)>
  inline v8::Handle<v8::Value> MakeCurrentCallback(v8::Arguments const& args) {
    MakeCurrent();
    return ((*this).*(InvocationCallbackMember))(args);
  }

  WebGLActiveInfo* CreateActiveInfo(GLint size, GLenum type, const char* name);
  WebGLBuffer* CreateBuffer(GLuint buffer_id);
  WebGLFramebuffer* CreateFramebuffer(GLuint framebuffer_id);
  WebGLProgram* CreateProgram(GLuint program_id);
  WebGLRenderbuffer* CreateRenderbuffer(GLuint renderbuffer_id);
  WebGLShader* CreateShader(GLuint shader_id);
  WebGLTexture* CreateTexture(GLuint texture_id);
  WebGLUniformLocation* CreateUniformLocation(GLuint program_id, GLint location_id);

  void DeleteBuffer(WebGLBuffer* buffer);
  void DeleteFramebuffer(WebGLFramebuffer* framebuffer);
  void DeleteProgram(WebGLProgram* program);
  void DeleteRenderbuffer(WebGLRenderbuffer* renderbuffer);
  void DeleteShader(WebGLShader* shader);
  void DeleteTexture(WebGLTexture* texture);

  WebGLBuffer* IdToBuffer(GLuint buffer_id) {
    return IdToObject(buffer_map_, buffer_id);
  }
  WebGLFramebuffer* IdToFramebuffer(GLuint framebuffer_id) {
    return IdToObject(framebuffer_map_, framebuffer_id);
  }
  WebGLProgram* IdToProgram(GLuint program_id) {
    return IdToObject(program_map_, program_id);
  }
  WebGLRenderbuffer* IdToRenderbuffer(GLuint renderbuffer_id) {
    return IdToObject(renderbuffer_map_, renderbuffer_id);
  }
  WebGLShader* IdToShader(GLuint shader_id) {
    return IdToObject(shader_map_, shader_id);
  }
  WebGLTexture* IdToTexture(GLuint texture_id) {
    return IdToObject(texture_map_, texture_id);
  }

  void set_gl_error(GLenum error);
  GLenum gl_error();

  static bool TypedArrayToData(v8::Handle<v8::Value> value, void** data, uint32_t* length, bool* ok);
  static void Log(Logger::Level level, const char *fmt, ...);

  static v8::Handle<v8::Value> ToV8OrNull(V8ObjectBase* object) {
    return object ? static_cast<v8::Handle<v8::Value> >(object->ToV8Object()) : static_cast<v8::Handle<v8::Value> >(v8::Null());
  }

  bool ValidateObject(WebGLObjectInterface* object);
  bool ValidateLocationProgram(WebGLUniformLocation* location, GLuint program_id);
  bool RequireObject(const void* object) {
    if (!object) {
      set_gl_error(GL_INVALID_VALUE);
      return false;
    }
    return true;
  }
  WebGLUniformLocation* UniformLocationFromV8(v8::Handle<v8::Value> value);

  bool ValidateBlendEquation(const char* function, GLenum mode);
  bool ValidateBlendFuncFactors(const char* function, GLenum src, GLenum dst);
  bool ValidateTextureBinding(const char* function, GLenum target, bool use_six_enums);
  bool ValidateTexFuncParameters(const char* function, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type);
  bool ValidateCapability(const char* function, GLenum cap);
  bool ValidateDrawMode(const char* function, GLenum mode);
  bool ValidateFramebufferFuncParameters(const char* function, GLenum target, GLenum attachment);
  bool ValidateStencilFunc(const char* function, GLenum func);
  bool ValidateBufferDataParameters(const char* function, GLenum target, GLenum usage);
  bool ValidateTexParameter(const char* function, GLenum pname, GLint param);

  // Use instead of glGetIntegerv
  void GetIntegerv(GLenum pname, GLint* value);

  static unsigned long s_context_counter;

  template<typename> friend class UVAHelper;
  template<typename> friend class UniformHelper;
  template<typename> friend class UniformMatrixHelper;
  template<typename> friend class VertexAttribHelper;

  friend class Canvas;
  friend class ShaderCompiler;

#define CALLBACK(name) v8::Handle<v8::Value> Callback_##name(const v8::Arguments& args)
  CALLBACK(getContextAttributes);
  CALLBACK(isContextLost);
  CALLBACK(getSupportedExtensions);
  CALLBACK(getExtension);
  CALLBACK(activeTexture);
  CALLBACK(attachShader);
  CALLBACK(bindAttribLocation);
  CALLBACK(bindBuffer);
  CALLBACK(bindFramebuffer);
  CALLBACK(bindRenderbuffer);
  CALLBACK(bindTexture);
  CALLBACK(blendColor);
  CALLBACK(blendEquation);
  CALLBACK(blendEquationSeparate);
  CALLBACK(blendFunc);
  CALLBACK(blendFuncSeparate);
  CALLBACK(bufferData);
  CALLBACK(bufferSubData);
  CALLBACK(checkFramebufferStatus);
  CALLBACK(clear);
  CALLBACK(clearColor);
  CALLBACK(clearDepth);
  CALLBACK(clearStencil);
  CALLBACK(colorMask);
  CALLBACK(compileShader);
  CALLBACK(copyTexImage2D);
  CALLBACK(copyTexSubImage2D);
  CALLBACK(createBuffer);
  CALLBACK(createFramebuffer);
  CALLBACK(createProgram);
  CALLBACK(createRenderbuffer);
  CALLBACK(createShader);
  CALLBACK(createTexture);
  CALLBACK(cullFace);
  CALLBACK(deleteBuffer);
  CALLBACK(deleteFramebuffer);
  CALLBACK(deleteProgram);
  CALLBACK(deleteRenderbuffer);
  CALLBACK(deleteShader);
  CALLBACK(deleteTexture);
  CALLBACK(depthFunc);
  CALLBACK(depthMask);
  CALLBACK(depthRange);
  CALLBACK(detachShader);
  CALLBACK(disable);
  CALLBACK(disableVertexAttribArray);
  CALLBACK(drawArrays);
  CALLBACK(drawElements);
  CALLBACK(enable);
  CALLBACK(enableVertexAttribArray);
  CALLBACK(finish);
  CALLBACK(flush);
  CALLBACK(framebufferRenderbuffer);
  CALLBACK(framebufferTexture2D);
  CALLBACK(frontFace);
  CALLBACK(generateMipmap);
  CALLBACK(getActiveAttrib);
  CALLBACK(getActiveUniform);
  CALLBACK(getAttachedShaders);
  CALLBACK(getAttribLocation);
  CALLBACK(getParameter);
  CALLBACK(getBufferParameter);
  CALLBACK(getError);
  CALLBACK(getFramebufferAttachmentParameter);
  CALLBACK(getProgramParameter);
  CALLBACK(getProgramInfoLog);
  CALLBACK(getRenderbufferParameter);
  CALLBACK(getShaderParameter);
  CALLBACK(getShaderInfoLog);
  CALLBACK(getShaderSource);
  CALLBACK(getTexParameter);
  CALLBACK(getUniform);
  CALLBACK(getUniformLocation);
  CALLBACK(getVertexAttrib);
  CALLBACK(getVertexAttribOffset);
  CALLBACK(hint);
  CALLBACK(isBuffer);
  CALLBACK(isEnabled);
  CALLBACK(isFramebuffer);
  CALLBACK(isProgram);
  CALLBACK(isRenderbuffer);
  CALLBACK(isShader);
  CALLBACK(isTexture);
  CALLBACK(lineWidth);
  CALLBACK(linkProgram);
  CALLBACK(pixelStorei);
  CALLBACK(polygonOffset);
  CALLBACK(readPixels);
  CALLBACK(renderbufferStorage);
  CALLBACK(sampleCoverage);
  CALLBACK(scissor);
  CALLBACK(shaderSource);
  CALLBACK(stencilFunc);
  CALLBACK(stencilFuncSeparate);
  CALLBACK(stencilMask);
  CALLBACK(stencilMaskSeparate);
  CALLBACK(stencilOp);
  CALLBACK(stencilOpSeparate);
  CALLBACK(texImage2D);
  CALLBACK(texParameterf);
  CALLBACK(texParameteri);
  CALLBACK(texSubImage2D);
  CALLBACK(uniform1f);
  CALLBACK(uniform1fv);
  CALLBACK(uniform1i);
  CALLBACK(uniform1iv);
  CALLBACK(uniform2f);
  CALLBACK(uniform2fv);
  CALLBACK(uniform2i);
  CALLBACK(uniform2iv);
  CALLBACK(uniform3f);
  CALLBACK(uniform3fv);
  CALLBACK(uniform3i);
  CALLBACK(uniform3iv);
  CALLBACK(uniform4f);
  CALLBACK(uniform4fv);
  CALLBACK(uniform4i);
  CALLBACK(uniform4iv);
  CALLBACK(uniformMatrix2fv);
  CALLBACK(uniformMatrix3fv);
  CALLBACK(uniformMatrix4fv);
  CALLBACK(useProgram);
  CALLBACK(validateProgram);
  CALLBACK(vertexAttrib1f);
  CALLBACK(vertexAttrib1fv);
  CALLBACK(vertexAttrib2f);
  CALLBACK(vertexAttrib2fv);
  CALLBACK(vertexAttrib3f);
  CALLBACK(vertexAttrib3fv);
  CALLBACK(vertexAttrib4f);
  CALLBACK(vertexAttrib4fv);
  CALLBACK(vertexAttribPointer);
  CALLBACK(viewport);
#undef CALLBACK
};

}

#endif
