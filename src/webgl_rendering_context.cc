// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "v8_webgl_internal.h"
#include "v8_binding.h"
#include "webgl_active_info.h"
#include "webgl_buffer.h"
#include "webgl_framebuffer.h"
#include "webgl_program.h"
#include "webgl_renderbuffer.h"
#include "webgl_rendering_context.h"
#include "webgl_shader.h"
#include "webgl_texture.h"
#include "webgl_uniform_location.h"


namespace v8_webgl {

unsigned long WebGLRenderingContext::s_context_counter = 0;

#define PROTO_METHOD(name) AddCallback(proto, #name, Callback_##name, signature)
#define CONSTANT(name, value) SetConstant(#name, value, proto, constructor)

#define CHECK_ARGS(num) \
  if (args.Length() < num) \
    return ThrowArgCount();

#define CONVERT_ARG(num, converter) \
  converter(args[num], ok); \
  if (!ok) return v8::Undefined();

#define VALIDATE_CONTEXT(object) \
  if (!object->ValidateContext(context)) \
    return ThrowInvalidContext();

#define CALLBACK_PREAMBLE() \
  WebGLRenderingContext* context = WebGLRenderingContext::ToNative(args.Holder()); \
  if (!context) \
    return ThrowObjectDisposed(); \
  context->MakeCurrent(); \
  bool ok = true; \
  (void)ok;

static inline v8::Handle<v8::Value> ThrowInvalidContext() {
  return v8::ThrowException(v8::Exception::TypeError(v8::String::New("Object not created with this WebGLRenderingContext")));
}

// Only Canvas creates us - so make ourself not weak
WebGLRenderingContext::WebGLRenderingContext(int width, int height)
    : V8Object<WebGLRenderingContext>(v8::Local<v8::Object>(), false)
    , graphic_context_(GetFactory()->CreateGraphicContext(width, height))
    , context_id_(s_context_counter++) {
}

WebGLRenderingContext::~WebGLRenderingContext() {
  delete graphic_context_;
}
WebGLActiveInfo* WebGLRenderingContext::CreateActiveInfo() {
  return new WebGLActiveInfo(this);
}
WebGLBuffer* WebGLRenderingContext::CreateBuffer(uint32_t buffer_id) {
  return new WebGLBuffer(this, buffer_id);
}
WebGLFramebuffer* WebGLRenderingContext::CreateFramebuffer(uint32_t framebuffer_id) {
  return new WebGLFramebuffer(this, framebuffer_id);
}
WebGLProgram* WebGLRenderingContext::CreateProgram(uint32_t program_id) {
  return new WebGLProgram(this, program_id);
}
WebGLRenderbuffer* WebGLRenderingContext::CreateRenderbuffer(uint32_t renderbuffer_id) {
  return new WebGLRenderbuffer(this, renderbuffer_id);
}
WebGLShader* WebGLRenderingContext::CreateShader(uint32_t shader_id) {
  return new WebGLShader(this, shader_id);
}
WebGLTexture* WebGLRenderingContext::CreateTexture(uint32_t texture_id) {
  return new WebGLTexture(this, texture_id);
}
WebGLUniformLocation* WebGLRenderingContext::CreateUniformLocation() {
  return new WebGLUniformLocation(this);
}

//////

// WebGLContextAttributes getContextAttributes();
static v8::Handle<v8::Value> Callback_getContextAttributes(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  /*XXX finish*/
  return v8::Undefined();
}

// boolean isContextLost();
static v8::Handle<v8::Value> Callback_isContextLost(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  return BooleanToV8(false);
}

// DOMString[ ] getSupportedExtensions();
static v8::Handle<v8::Value> Callback_getSupportedExtensions(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// object getExtension(DOMString name);
static v8::Handle<v8::Value> Callback_getExtension(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void activeTexture(GLenum texture);
static v8::Handle<v8::Value> Callback_activeTexture(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  uint32_t texture = CONVERT_ARG(0, V8ToUint32);
  glActiveTexture(texture);
  return v8::Undefined();
}

// void attachShader(WebGLProgram program, WebGLShader shader);
static v8::Handle<v8::Value> Callback_attachShader(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void bindAttribLocation(WebGLProgram program, GLuint index, DOMString name);
static v8::Handle<v8::Value> Callback_bindAttribLocation(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void bindBuffer(GLenum target, WebGLBuffer buffer);
static v8::Handle<v8::Value> Callback_bindBuffer(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void bindFramebuffer(GLenum target, WebGLFramebuffer framebuffer);
static v8::Handle<v8::Value> Callback_bindFramebuffer(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void bindRenderbuffer(GLenum target, WebGLRenderbuffer renderbuffer);
static v8::Handle<v8::Value> Callback_bindRenderbuffer(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void bindTexture(GLenum target, WebGLTexture texture);
static v8::Handle<v8::Value> Callback_bindTexture(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void blendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
static v8::Handle<v8::Value> Callback_blendColor(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(4);
  float red = CONVERT_ARG(0, V8ToFloat);
  float green = CONVERT_ARG(1, V8ToFloat);
  float blue = CONVERT_ARG(2, V8ToFloat);
  float alpha = CONVERT_ARG(3, V8ToFloat);
  glBlendColor(red, green, blue, alpha);
  return v8::Undefined();
 }

// void blendEquation(GLenum mode);
static v8::Handle<v8::Value> Callback_blendEquation(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  uint32_t mode = CONVERT_ARG(0, V8ToUint32);
  glBlendEquation(mode);
  return v8::Undefined();
}

// void blendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
static v8::Handle<v8::Value> Callback_blendEquationSeparate(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(2);
  uint32_t modeRGB = CONVERT_ARG(0, V8ToUint32);
  uint32_t modeAlpha = CONVERT_ARG(1, V8ToUint32);
  glBlendEquationSeparate(modeRGB, modeAlpha);
  return v8::Undefined();
}

// void blendFunc(GLenum sfactor, GLenum dfactor);
static v8::Handle<v8::Value> Callback_blendFunc(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(2);
  uint32_t sfactor = CONVERT_ARG(0, V8ToUint32);
  uint32_t dfactor = CONVERT_ARG(1, V8ToUint32);
  glBlendFunc(sfactor, dfactor);
  return v8::Undefined();
}

// void blendFuncSeparate(GLenum srcRGB, GLenum dstRGB, 
//                        GLenum srcAlpha, GLenum dstAlpha);
static v8::Handle<v8::Value> Callback_blendFuncSeparate(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(4);
  uint32_t srcRGB = CONVERT_ARG(0, V8ToUint32);
  uint32_t dstRGB = CONVERT_ARG(1, V8ToUint32);
  uint32_t srcAlpha = CONVERT_ARG(2, V8ToUint32);
  uint32_t dstAlpha = CONVERT_ARG(3, V8ToUint32);
  glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
  return v8::Undefined();
}

// void bufferData(GLenum target, GLsizeiptr size, GLenum usage);
// void bufferData(GLenum target, ArrayBufferView data, GLenum usage);
// void bufferData(GLenum target, ArrayBuffer data, GLenum usage);
static v8::Handle<v8::Value> Callback_bufferData(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void bufferSubData(GLenum target, GLintptr offset, ArrayBufferView data);
// void bufferSubData(GLenum target, GLintptr offset, ArrayBuffer data);
static v8::Handle<v8::Value> Callback_bufferSubData(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// GLenum checkFramebufferStatus(GLenum target);
static v8::Handle<v8::Value> Callback_checkFramebufferStatus(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  uint32_t target = CONVERT_ARG(0, V8ToUint32);
  return Uint32ToV8(glCheckFramebufferStatus(target));
}

// void clear(GLbitfield mask);
static v8::Handle<v8::Value> Callback_clear(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  uint32_t mask = CONVERT_ARG(0, V8ToUint32);
  glClear(mask);
  return v8::Undefined();
}

// void clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
static v8::Handle<v8::Value> Callback_clearColor(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(4);
  float red = CONVERT_ARG(0, V8ToFloat);
  float green = CONVERT_ARG(1, V8ToFloat);
  float blue = CONVERT_ARG(2, V8ToFloat);
  float alpha = CONVERT_ARG(3, V8ToFloat);
  glClearColor(red, green, blue, alpha);
  return v8::Undefined();
}

// void clearDepth(GLclampf depth);
static v8::Handle<v8::Value> Callback_clearDepth(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  float depth = CONVERT_ARG(0, V8ToFloat);
  glClearDepth(depth);
  return v8::Undefined();
}

// void clearStencil(GLint s);
static v8::Handle<v8::Value> Callback_clearStencil(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  int32_t s = CONVERT_ARG(0, V8ToInt32);
  glClearStencil(s);
  return v8::Undefined();
}

// void colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
static v8::Handle<v8::Value> Callback_colorMask(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(4);
  bool red = CONVERT_ARG(0, V8ToBoolean);
  bool green = CONVERT_ARG(1, V8ToBoolean);
  bool blue = CONVERT_ARG(2, V8ToBoolean);
  bool alpha = CONVERT_ARG(3, V8ToBoolean);
  glColorMask(red, green, blue, alpha);
  return v8::Undefined();
}

// void compileShader(WebGLShader shader);
static v8::Handle<v8::Value> Callback_compileShader(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void copyTexImage2D(GLenum target, GLint level, GLenum internalformat, 
//                     GLint x, GLint y, GLsizei width, GLsizei height, 
//                     GLint border);
static v8::Handle<v8::Value> Callback_copyTexImage2D(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(8);
  uint32_t target = CONVERT_ARG(0, V8ToUint32);
  int32_t level = CONVERT_ARG(1, V8ToInt32);
  uint32_t internalformat = CONVERT_ARG(2, V8ToUint32);
  int32_t x = CONVERT_ARG(3, V8ToInt32);
  int32_t y = CONVERT_ARG(4, V8ToInt32);
  int32_t width = CONVERT_ARG(5, V8ToInt32);
  int32_t height = CONVERT_ARG(6, V8ToInt32);
  int32_t border = CONVERT_ARG(7, V8ToInt32);
  glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
  return v8::Undefined();
}

// void copyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, 
//                        GLint x, GLint y, GLsizei width, GLsizei height);
static v8::Handle<v8::Value> Callback_copyTexSubImage2D(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(8);
  uint32_t target = CONVERT_ARG(0, V8ToUint32);
  int32_t level = CONVERT_ARG(1, V8ToInt32);
  int32_t xoffset = CONVERT_ARG(2, V8ToInt32);
  int32_t yoffset = CONVERT_ARG(3, V8ToInt32);
  int32_t x = CONVERT_ARG(4, V8ToInt32);
  int32_t y = CONVERT_ARG(5, V8ToInt32);
  int32_t width = CONVERT_ARG(6, V8ToInt32);
  int32_t height = CONVERT_ARG(7, V8ToInt32);
  glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
  return v8::Undefined();
}

// WebGLBuffer createBuffer();
static v8::Handle<v8::Value> Callback_createBuffer(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  GLuint buffer_id = 0;
  glGenBuffers(1, &buffer_id);
  WebGLBuffer* buffer = context->CreateBuffer(buffer_id);
  return buffer->ToV8();
}

// WebGLFramebuffer createFramebuffer();
static v8::Handle<v8::Value> Callback_createFramebuffer(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  GLuint framebuffer_id = 0;
  //XXX glGenFramebuffersEXT etc.
  glGenFramebuffers(1, &framebuffer_id);
  WebGLFramebuffer* framebuffer = context->CreateFramebuffer(framebuffer_id);
  return framebuffer->ToV8();
}

// WebGLProgram createProgram();
static v8::Handle<v8::Value> Callback_createProgram(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  GLuint program_id = glCreateProgram();
  WebGLProgram* program = context->CreateProgram(program_id);
  return program->ToV8();
}

// WebGLRenderbuffer createRenderbuffer();
static v8::Handle<v8::Value> Callback_createRenderbuffer(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  GLuint renderbuffer_id = 0;
  //XXX glGenRenderbuffersEXT etc.
  glGenRenderbuffers(1, &renderbuffer_id);
  WebGLRenderbuffer* renderbuffer = context->CreateRenderbuffer(renderbuffer_id);
  return renderbuffer->ToV8();
}

// WebGLShader createShader(GLenum type);
static v8::Handle<v8::Value> Callback_createShader(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  uint32_t type = CONVERT_ARG(0, V8ToUint32);
  GLuint shader_id = glCreateShader(type);
  WebGLShader* shader = context->CreateShader(shader_id);
  return shader->ToV8();
}

// WebGLTexture createTexture();
static v8::Handle<v8::Value> Callback_createTexture(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  GLuint texture_id = 0;
  glGenTextures(1, &texture_id);
  WebGLTexture* texture = context->CreateTexture(texture_id);
  return texture->ToV8();
}

// void cullFace(GLenum mode);
static v8::Handle<v8::Value> Callback_cullFace(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  uint32_t mode = CONVERT_ARG(0, V8ToUint32);
  glCullFace(mode);
  return v8::Undefined();
}

// void deleteBuffer(WebGLBuffer buffer);
static v8::Handle<v8::Value> Callback_deleteBuffer(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  WebGLBuffer* buffer = CONVERT_ARG(0, V8ToNative<WebGLBuffer>);
  VALIDATE_CONTEXT(buffer);
  GLuint buffer_id = buffer->get_buffer_id();
  glDeleteBuffers(1, &buffer_id);
  return v8::Undefined();
}

// void deleteFramebuffer(WebGLFramebuffer framebuffer);
static v8::Handle<v8::Value> Callback_deleteFramebuffer(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  WebGLFramebuffer* framebuffer = CONVERT_ARG(0, V8ToNative<WebGLFramebuffer>);
  VALIDATE_CONTEXT(framebuffer);
  GLuint framebuffer_id = framebuffer->get_framebuffer_id();
  //XXX glDeleteFramebuffersEXT etc.
  glDeleteFramebuffers(1, &framebuffer_id);
  return v8::Undefined();
}

// void deleteProgram(WebGLProgram program);
static v8::Handle<v8::Value> Callback_deleteProgram(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  WebGLProgram* program = CONVERT_ARG(0, V8ToNative<WebGLProgram>);
  VALIDATE_CONTEXT(program);
  glDeleteProgram(program->get_program_id());
  return v8::Undefined();
}

// void deleteRenderbuffer(WebGLRenderbuffer renderbuffer);
static v8::Handle<v8::Value> Callback_deleteRenderbuffer(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  WebGLRenderbuffer* renderbuffer = CONVERT_ARG(0, V8ToNative<WebGLRenderbuffer>);
  VALIDATE_CONTEXT(renderbuffer);
  GLuint renderbuffer_id = renderbuffer->get_renderbuffer_id();
  //XXX glDeleteRenderbuffersEXT etc.
  glDeleteRenderbuffers(1, &renderbuffer_id);
  return v8::Undefined();
}

// void deleteShader(WebGLShader shader);
static v8::Handle<v8::Value> Callback_deleteShader(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  WebGLShader* shader = CONVERT_ARG(0, V8ToNative<WebGLShader>);
  VALIDATE_CONTEXT(shader);
  glDeleteShader(shader->get_shader_id());
  return v8::Undefined();
}

// void deleteTexture(WebGLTexture texture);
static v8::Handle<v8::Value> Callback_deleteTexture(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  WebGLTexture* texture = CONVERT_ARG(0, V8ToNative<WebGLTexture>);
  VALIDATE_CONTEXT(texture);
  GLuint texture_id = texture->get_texture_id();
  glDeleteTextures(1, &texture_id);
  return v8::Undefined();
}

// void depthFunc(GLenum func);
static v8::Handle<v8::Value> Callback_depthFunc(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  uint32_t func = CONVERT_ARG(0, V8ToUint32);
  glDepthFunc(func);
  return v8::Undefined();
}

// void depthMask(GLboolean flag);
static v8::Handle<v8::Value> Callback_depthMask(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  GLboolean flag = CONVERT_ARG(0, V8ToBoolean);
  glDepthMask(flag);
  return v8::Undefined();
}

// void depthRange(GLclampf zNear, GLclampf zFar);
static v8::Handle<v8::Value> Callback_depthRange(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void detachShader(WebGLProgram program, WebGLShader shader);
static v8::Handle<v8::Value> Callback_detachShader(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void disable(GLenum cap);
static v8::Handle<v8::Value> Callback_disable(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  uint32_t cap = CONVERT_ARG(0, V8ToUint32);
  glDisable(cap);
  return v8::Undefined();
}

// void disableVertexAttribArray(GLuint index);
static v8::Handle<v8::Value> Callback_disableVertexAttribArray(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  uint32_t index = CONVERT_ARG(0, V8ToUint32);
  glDisableVertexAttribArray(index);
  return v8::Undefined();
}

// void drawArrays(GLenum mode, GLint first, GLsizei count);
static v8::Handle<v8::Value> Callback_drawArrays(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void drawElements(GLenum mode, GLsizei count, GLenum type, GLintptr offset);
static v8::Handle<v8::Value> Callback_drawElements(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void enable(GLenum cap);
static v8::Handle<v8::Value> Callback_enable(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  uint32_t cap = CONVERT_ARG(0, V8ToUint32);
  glEnable(cap);
  return v8::Undefined();
}

// void enableVertexAttribArray(GLuint index);
static v8::Handle<v8::Value> Callback_enableVertexAttribArray(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  uint32_t index = CONVERT_ARG(0, V8ToUint32);
  glEnableVertexAttribArray(index);
  return v8::Undefined();
}

// void finish();
static v8::Handle<v8::Value> Callback_finish(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  glFinish();
  return v8::Undefined();
}

// void flush();
static v8::Handle<v8::Value> Callback_flush(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  glFlush();
  return v8::Undefined();
}

// void framebufferRenderbuffer(GLenum target, GLenum attachment, 
//                              GLenum renderbuffertarget, 
//                              WebGLRenderbuffer renderbuffer);
static v8::Handle<v8::Value> Callback_framebufferRenderbuffer(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void framebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, 
//                           WebGLTexture texture, GLint level);
static v8::Handle<v8::Value> Callback_framebufferTexture2D(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void frontFace(GLenum mode);
static v8::Handle<v8::Value> Callback_frontFace(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  uint32_t mode = CONVERT_ARG(0, V8ToUint32);
  glFrontFace(mode);
  return v8::Undefined();
}

// void generateMipmap(GLenum target);
static v8::Handle<v8::Value> Callback_generateMipmap(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  uint32_t target = CONVERT_ARG(0, V8ToUint32);
  //XXX glGenerateMipmapEXT etc.
  glGenerateMipmap(target);
  return v8::Undefined();
}

// WebGLActiveInfo getActiveAttrib(WebGLProgram program, GLuint index);
static v8::Handle<v8::Value> Callback_getActiveAttrib(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// WebGLActiveInfo getActiveUniform(WebGLProgram program, GLuint index);
static v8::Handle<v8::Value> Callback_getActiveUniform(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// WebGLShader[ ] getAttachedShaders(WebGLProgram program);
static v8::Handle<v8::Value> Callback_getAttachedShaders(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// GLint getAttribLocation(WebGLProgram program, DOMString name);
static v8::Handle<v8::Value> Callback_getAttribLocation(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// any getParameter(GLenum pname);
static v8::Handle<v8::Value> Callback_getParameter(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// any getBufferParameter(GLenum target, GLenum pname);
static v8::Handle<v8::Value> Callback_getBufferParameter(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// GLenum getError();
static v8::Handle<v8::Value> Callback_getError(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  GLenum error = glGetError();
  return Uint32ToV8(error);
}

// any getFramebufferAttachmentParameter(GLenum target, GLenum attachment, 
//                                       GLenum pname);
static v8::Handle<v8::Value> Callback_getFramebufferAttachmentParameter(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// any getProgramParameter(WebGLProgram program, GLenum pname);
static v8::Handle<v8::Value> Callback_getProgramParameter(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// DOMString getProgramInfoLog(WebGLProgram program);
static v8::Handle<v8::Value> Callback_getProgramInfoLog(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// any getRenderbufferParameter(GLenum target, GLenum pname);
static v8::Handle<v8::Value> Callback_getRenderbufferParameter(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// any getShaderParameter(WebGLShader shader, GLenum pname);
static v8::Handle<v8::Value> Callback_getShaderParameter(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// DOMString getShaderInfoLog(WebGLShader shader);
static v8::Handle<v8::Value> Callback_getShaderInfoLog(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// DOMString getShaderSource(WebGLShader shader);
static v8::Handle<v8::Value> Callback_getShaderSource(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// any getTexParameter(GLenum target, GLenum pname);
static v8::Handle<v8::Value> Callback_getTexParameter(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// any getUniform(WebGLProgram program, WebGLUniformLocation location);
static v8::Handle<v8::Value> Callback_getUniform(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// WebGLUniformLocation getUniformLocation(WebGLProgram program, DOMString name);
static v8::Handle<v8::Value> Callback_getUniformLocation(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// any getVertexAttrib(GLuint index, GLenum pname);
static v8::Handle<v8::Value> Callback_getVertexAttrib(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// GLsizeiptr getVertexAttribOffset(GLuint index, GLenum pname);
static v8::Handle<v8::Value> Callback_getVertexAttribOffset(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void hint(GLenum target, GLenum mode);
static v8::Handle<v8::Value> Callback_hint(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// GLboolean isBuffer(WebGLBuffer buffer);
static v8::Handle<v8::Value> Callback_isBuffer(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// GLboolean isEnabled(GLenum cap);
static v8::Handle<v8::Value> Callback_isEnabled(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  uint32_t cap = CONVERT_ARG(0, V8ToUint32);
  glIsEnabled(cap);
  return v8::Undefined();
}

// GLboolean isFramebuffer(WebGLFramebuffer framebuffer);
static v8::Handle<v8::Value> Callback_isFramebuffer(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// GLboolean isProgram(WebGLProgram program);
static v8::Handle<v8::Value> Callback_isProgram(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// GLboolean isRenderbuffer(WebGLRenderbuffer renderbuffer);
static v8::Handle<v8::Value> Callback_isRenderbuffer(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// GLboolean isShader(WebGLShader shader);
static v8::Handle<v8::Value> Callback_isShader(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// GLboolean isTexture(WebGLTexture texture);
static v8::Handle<v8::Value> Callback_isTexture(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void lineWidth(GLfloat width);
static v8::Handle<v8::Value> Callback_lineWidth(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void linkProgram(WebGLProgram program);
static v8::Handle<v8::Value> Callback_linkProgram(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void pixelStorei(GLenum pname, GLint param);
static v8::Handle<v8::Value> Callback_pixelStorei(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void polygonOffset(GLfloat factor, GLfloat units);
static v8::Handle<v8::Value> Callback_polygonOffset(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void readPixels(GLint x, GLint y, GLsizei width, GLsizei height, 
//                 GLenum format, GLenum type, ArrayBufferView pixels);
static v8::Handle<v8::Value> Callback_readPixels(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void renderbufferStorage(GLenum target, GLenum internalformat, 
//                          GLsizei width, GLsizei height);
static v8::Handle<v8::Value> Callback_renderbufferStorage(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void sampleCoverage(GLclampf value, GLboolean invert);
static v8::Handle<v8::Value> Callback_sampleCoverage(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void scissor(GLint x, GLint y, GLsizei width, GLsizei height);
static v8::Handle<v8::Value> Callback_scissor(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void shaderSource(WebGLShader shader, DOMString source);
static v8::Handle<v8::Value> Callback_shaderSource(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void stencilFunc(GLenum func, GLint ref, GLuint mask);
static v8::Handle<v8::Value> Callback_stencilFunc(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void stencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
static v8::Handle<v8::Value> Callback_stencilFuncSeparate(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void stencilMask(GLuint mask);
static v8::Handle<v8::Value> Callback_stencilMask(const v8::Arguments& args) {
  CALLBACK_PREAMBLE();
  CHECK_ARGS(1);
  uint32_t mask = CONVERT_ARG(0, V8ToUint32);
  glStencilMask(mask);
  return v8::Undefined();
}

// void stencilMaskSeparate(GLenum face, GLuint mask);
static v8::Handle<v8::Value> Callback_stencilMaskSeparate(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void stencilOp(GLenum fail, GLenum zfail, GLenum zpass);
static v8::Handle<v8::Value> Callback_stencilOp(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void stencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass);
static v8::Handle<v8::Value> Callback_stencilOpSeparate(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void texImage2D(GLenum target, GLint level, GLenum internalformat, 
//                 GLsizei width, GLsizei height, GLint border, GLenum format, 
//                 GLenum type, ArrayBufferView pixels);
// void texImage2D(GLenum target, GLint level, GLenum internalformat,
//                 GLenum format, GLenum type, ImageData pixels);
// void texImage2D(GLenum target, GLint level, GLenum internalformat,
//                 GLenum format, GLenum type, HTMLImageElement image) raises (DOMException);
// void texImage2D(GLenum target, GLint level, GLenum internalformat,
//                 GLenum format, GLenum type, HTMLCanvasElement canvas) raises (DOMException);
// void texImage2D(GLenum target, GLint level, GLenum internalformat,
//                 GLenum format, GLenum type, HTMLVideoElement video) raises (DOMException);
static v8::Handle<v8::Value> Callback_texImage2D(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void texParameterf(GLenum target, GLenum pname, GLfloat param);
static v8::Handle<v8::Value> Callback_texParameterf(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void texParameteri(GLenum target, GLenum pname, GLint param);
static v8::Handle<v8::Value> Callback_texParameteri(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, 
//                    GLsizei width, GLsizei height, 
//                    GLenum format, GLenum type, ArrayBufferView pixels);
// void texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, 
//                    GLenum format, GLenum type, ImageData pixels);
// void texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, 
//                    GLenum format, GLenum type, HTMLImageElement image) raises (DOMException);
// void texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, 
//                    GLenum format, GLenum type, HTMLCanvasElement canvas) raises (DOMException);
// void texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, 
//                    GLenum format, GLenum type, HTMLVideoElement video) raises (DOMException);
static v8::Handle<v8::Value> Callback_texSubImage2D(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform1f(WebGLUniformLocation location, GLfloat x);
static v8::Handle<v8::Value> Callback_uniform1f(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform1fv(WebGLUniformLocation location, FloatArray v);
// void uniform1fv(WebGLUniformLocation location, sequence<float> v);
static v8::Handle<v8::Value> Callback_uniform1fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform1i(WebGLUniformLocation location, GLint x);
static v8::Handle<v8::Value> Callback_uniform1i(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform1iv(WebGLUniformLocation location, Int32Array v);
// void uniform1iv(WebGLUniformLocation location, sequence<long> v);
static v8::Handle<v8::Value> Callback_uniform1iv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform2f(WebGLUniformLocation location, GLfloat x, GLfloat y);
static v8::Handle<v8::Value> Callback_uniform2f(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform2fv(WebGLUniformLocation location, FloatArray v);
// void uniform2fv(WebGLUniformLocation location, sequence<float> v);
static v8::Handle<v8::Value> Callback_uniform2fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform2i(WebGLUniformLocation location, GLint x, GLint y);
static v8::Handle<v8::Value> Callback_uniform2i(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform2iv(WebGLUniformLocation location, Int32Array v);
// void uniform2iv(WebGLUniformLocation location, sequence<long> v);
static v8::Handle<v8::Value> Callback_uniform2iv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform3f(WebGLUniformLocation location, GLfloat x, GLfloat y, GLfloat z);
static v8::Handle<v8::Value> Callback_uniform3f(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform3fv(WebGLUniformLocation location, FloatArray v);
// void uniform3fv(WebGLUniformLocation location, sequence<float> v);
static v8::Handle<v8::Value> Callback_uniform3fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform3i(WebGLUniformLocation location, GLint x, GLint y, GLint z);
static v8::Handle<v8::Value> Callback_uniform3i(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform3iv(WebGLUniformLocation location, Int32Array v);
// void uniform3iv(WebGLUniformLocation location, sequence<long> v);
static v8::Handle<v8::Value> Callback_uniform3iv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform4f(WebGLUniformLocation location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
static v8::Handle<v8::Value> Callback_uniform4f(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform4fv(WebGLUniformLocation location, FloatArray v);
// void uniform4fv(WebGLUniformLocation location, sequence<float> v);
static v8::Handle<v8::Value> Callback_uniform4fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform4i(WebGLUniformLocation location, GLint x, GLint y, GLint z, GLint w);
static v8::Handle<v8::Value> Callback_uniform4i(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform4iv(WebGLUniformLocation location, Int32Array v);
// void uniform4iv(WebGLUniformLocation location, sequence<long> v);
static v8::Handle<v8::Value> Callback_uniform4iv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniformMatrix2fv(WebGLUniformLocation location, GLboolean transpose, 
//                       FloatArray value);
// void uniformMatrix2fv(WebGLUniformLocation location, GLboolean transpose, 
//                       sequence<float> value);
static v8::Handle<v8::Value> Callback_uniformMatrix2fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniformMatrix3fv(WebGLUniformLocation location, GLboolean transpose, 
//                       FloatArray value);
// void uniformMatrix3fv(WebGLUniformLocation location, GLboolean transpose, 
//                       sequence<float> value);
static v8::Handle<v8::Value> Callback_uniformMatrix3fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniformMatrix4fv(WebGLUniformLocation location, GLboolean transpose, 
//                       FloatArray value);
// void uniformMatrix4fv(WebGLUniformLocation location, GLboolean transpose, 
//                       sequence<float> value);
static v8::Handle<v8::Value> Callback_uniformMatrix4fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void useProgram(WebGLProgram program);
static v8::Handle<v8::Value> Callback_useProgram(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void validateProgram(WebGLProgram program);
static v8::Handle<v8::Value> Callback_validateProgram(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void vertexAttrib1f(GLuint indx, GLfloat x);
static v8::Handle<v8::Value> Callback_vertexAttrib1f(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void vertexAttrib1fv(GLuint indx, FloatArray values);
// void vertexAttrib1fv(GLuint indx, sequence<float> values);
static v8::Handle<v8::Value> Callback_vertexAttrib1fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void vertexAttrib2f(GLuint indx, GLfloat x, GLfloat y);
static v8::Handle<v8::Value> Callback_vertexAttrib2f(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void vertexAttrib2fv(GLuint indx, FloatArray values);
// void vertexAttrib2fv(GLuint indx, sequence<float> values);
static v8::Handle<v8::Value> Callback_vertexAttrib2fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void vertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z);
static v8::Handle<v8::Value> Callback_vertexAttrib3f(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void vertexAttrib3fv(GLuint indx, FloatArray values);
// void vertexAttrib3fv(GLuint indx, sequence<float> values);
static v8::Handle<v8::Value> Callback_vertexAttrib3fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void vertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
static v8::Handle<v8::Value> Callback_vertexAttrib4f(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void vertexAttrib4fv(GLuint indx, FloatArray values);
// void vertexAttrib4fv(GLuint indx, sequence<float> values);
static v8::Handle<v8::Value> Callback_vertexAttrib4fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void vertexAttribPointer(GLuint indx, GLint size, GLenum type, 
//                          GLboolean normalized, GLsizei stride, GLintptr offset);
static v8::Handle<v8::Value> Callback_vertexAttribPointer(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void viewport(GLint x, GLint y, GLsizei width, GLsizei height);
static v8::Handle<v8::Value> Callback_viewport(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

//////

inline static void SetConstant(const char* name, int value, v8::Handle<v8::ObjectTemplate> proto, v8::Handle<v8::FunctionTemplate> constructor) {
  v8::Handle<v8::String> name_handle = v8::String::New(name);
  v8::Handle<v8::Integer> value_handle = v8::Integer::New(value);
  constructor->Set(name_handle, value_handle, v8::ReadOnly);
  proto->Set(name_handle, value_handle, v8::ReadOnly);
}

void WebGLRenderingContext::ConfigureConstructorTemplate(v8::Persistent<v8::FunctionTemplate> constructor) {
  v8::Handle<v8::ObjectTemplate> proto = constructor->PrototypeTemplate();
  v8::Local<v8::Signature> signature = v8::Signature::New(constructor);

  PROTO_METHOD(getContextAttributes);
  PROTO_METHOD(isContextLost);
  PROTO_METHOD(getSupportedExtensions);
  PROTO_METHOD(getExtension);
  PROTO_METHOD(activeTexture);
  PROTO_METHOD(attachShader);
  PROTO_METHOD(bindAttribLocation);
  PROTO_METHOD(bindBuffer);
  PROTO_METHOD(bindFramebuffer);
  PROTO_METHOD(bindRenderbuffer);
  PROTO_METHOD(bindTexture);
  PROTO_METHOD(blendColor);
  PROTO_METHOD(blendEquation);
  PROTO_METHOD(blendEquationSeparate);
  PROTO_METHOD(blendFunc);
  PROTO_METHOD(blendFuncSeparate);
  PROTO_METHOD(bufferData);
  PROTO_METHOD(bufferSubData);
  PROTO_METHOD(checkFramebufferStatus);
  PROTO_METHOD(clear);
  PROTO_METHOD(clearColor);
  PROTO_METHOD(clearDepth);
  PROTO_METHOD(clearStencil);
  PROTO_METHOD(colorMask);
  PROTO_METHOD(compileShader);
  PROTO_METHOD(copyTexImage2D);
  PROTO_METHOD(copyTexSubImage2D);
  PROTO_METHOD(createBuffer);
  PROTO_METHOD(createFramebuffer);
  PROTO_METHOD(createProgram);
  PROTO_METHOD(createRenderbuffer);
  PROTO_METHOD(createShader);
  PROTO_METHOD(createTexture);
  PROTO_METHOD(cullFace);
  PROTO_METHOD(deleteBuffer);
  PROTO_METHOD(deleteFramebuffer);
  PROTO_METHOD(deleteProgram);
  PROTO_METHOD(deleteRenderbuffer);
  PROTO_METHOD(deleteShader);
  PROTO_METHOD(deleteTexture);
  PROTO_METHOD(depthFunc);
  PROTO_METHOD(depthMask);
  PROTO_METHOD(depthRange);
  PROTO_METHOD(detachShader);
  PROTO_METHOD(disable);
  PROTO_METHOD(disableVertexAttribArray);
  PROTO_METHOD(drawArrays);
  PROTO_METHOD(drawElements);
  PROTO_METHOD(enable);
  PROTO_METHOD(enableVertexAttribArray);
  PROTO_METHOD(finish);
  PROTO_METHOD(flush);
  PROTO_METHOD(framebufferRenderbuffer);
  PROTO_METHOD(framebufferTexture2D);
  PROTO_METHOD(frontFace);
  PROTO_METHOD(generateMipmap);
  PROTO_METHOD(getActiveAttrib);
  PROTO_METHOD(getActiveUniform);
  PROTO_METHOD(getAttachedShaders);
  PROTO_METHOD(getAttribLocation);
  PROTO_METHOD(getParameter);
  PROTO_METHOD(getBufferParameter);
  PROTO_METHOD(getError);
  PROTO_METHOD(getFramebufferAttachmentParameter);
  PROTO_METHOD(getProgramParameter);
  PROTO_METHOD(getProgramInfoLog);
  PROTO_METHOD(getRenderbufferParameter);
  PROTO_METHOD(getShaderParameter);
  PROTO_METHOD(getShaderInfoLog);
  PROTO_METHOD(getShaderSource);
  PROTO_METHOD(getTexParameter);
  PROTO_METHOD(getUniform);
  PROTO_METHOD(getUniformLocation);
  PROTO_METHOD(getVertexAttrib);
  PROTO_METHOD(getVertexAttribOffset);
  PROTO_METHOD(hint);
  PROTO_METHOD(isBuffer);
  PROTO_METHOD(isEnabled);
  PROTO_METHOD(isFramebuffer);
  PROTO_METHOD(isProgram);
  PROTO_METHOD(isRenderbuffer);
  PROTO_METHOD(isShader);
  PROTO_METHOD(isTexture);
  PROTO_METHOD(lineWidth);
  PROTO_METHOD(linkProgram);
  PROTO_METHOD(pixelStorei);
  PROTO_METHOD(polygonOffset);
  PROTO_METHOD(readPixels);
  PROTO_METHOD(renderbufferStorage);
  PROTO_METHOD(sampleCoverage);
  PROTO_METHOD(scissor);
  PROTO_METHOD(shaderSource);
  PROTO_METHOD(stencilFunc);
  PROTO_METHOD(stencilFuncSeparate);
  PROTO_METHOD(stencilMask);
  PROTO_METHOD(stencilMaskSeparate);
  PROTO_METHOD(stencilOp);
  PROTO_METHOD(stencilOpSeparate);
  PROTO_METHOD(texImage2D);
  PROTO_METHOD(texParameterf);
  PROTO_METHOD(texParameteri);
  PROTO_METHOD(texSubImage2D);
  PROTO_METHOD(uniform1f);
  PROTO_METHOD(uniform1fv);
  PROTO_METHOD(uniform1i);
  PROTO_METHOD(uniform1iv);
  PROTO_METHOD(uniform2f);
  PROTO_METHOD(uniform2fv);
  PROTO_METHOD(uniform2i);
  PROTO_METHOD(uniform2iv);
  PROTO_METHOD(uniform3f);
  PROTO_METHOD(uniform3fv);
  PROTO_METHOD(uniform3i);
  PROTO_METHOD(uniform3iv);
  PROTO_METHOD(uniform4f);
  PROTO_METHOD(uniform4fv);
  PROTO_METHOD(uniform4i);
  PROTO_METHOD(uniform4iv);
  PROTO_METHOD(uniformMatrix2fv);
  PROTO_METHOD(uniformMatrix3fv);
  PROTO_METHOD(uniformMatrix4fv);
  PROTO_METHOD(useProgram);
  PROTO_METHOD(validateProgram);
  PROTO_METHOD(vertexAttrib1f);
  PROTO_METHOD(vertexAttrib1fv);
  PROTO_METHOD(vertexAttrib2f);
  PROTO_METHOD(vertexAttrib2fv);
  PROTO_METHOD(vertexAttrib3f);
  PROTO_METHOD(vertexAttrib3fv);
  PROTO_METHOD(vertexAttrib4f);
  PROTO_METHOD(vertexAttrib4fv);
  PROTO_METHOD(vertexAttribPointer);
  PROTO_METHOD(viewport);

  // ClearBufferMask
  CONSTANT(DEPTH_BUFFER_BIT, 0x00000100);
  CONSTANT(STENCIL_BUFFER_BIT, 0x00000400);
  CONSTANT(COLOR_BUFFER_BIT, 0x00004000);

  // BeginMode
  CONSTANT(POINTS, 0x0000);
  CONSTANT(LINES, 0x0001);
  CONSTANT(LINE_LOOP, 0x0002);
  CONSTANT(LINE_STRIP, 0x0003);
  CONSTANT(TRIANGLES, 0x0004);
  CONSTANT(TRIANGLE_STRIP, 0x0005);
  CONSTANT(TRIANGLE_FAN, 0x0006);

  // BlendingFactorDest
  CONSTANT(ZERO, 0);
  CONSTANT(ONE, 1);
  CONSTANT(SRC_COLOR, 0x0300);
  CONSTANT(ONE_MINUS_SRC_COLOR, 0x0301);
  CONSTANT(SRC_ALPHA, 0x0302);
  CONSTANT(ONE_MINUS_SRC_ALPHA, 0x0303);
  CONSTANT(DST_ALPHA, 0x0304);
  CONSTANT(ONE_MINUS_DST_ALPHA, 0x0305);

  // BlendingFactorSrc
  CONSTANT(DST_COLOR, 0x0306);
  CONSTANT(ONE_MINUS_DST_COLOR, 0x0307);
  CONSTANT(SRC_ALPHA_SATURATE, 0x0308);

  // BlendEquationSeparate
  CONSTANT(FUNC_ADD, 0x8006);
  CONSTANT(BLEND_EQUATION, 0x8009);
  CONSTANT(BLEND_EQUATION_RGB, 0x8009);   // same as BLEND_EQUATION
  CONSTANT(BLEND_EQUATION_ALPHA, 0x883D);

  // BlendSubtract
  CONSTANT(FUNC_SUBTRACT, 0x800A);
  CONSTANT(FUNC_REVERSE_SUBTRACT, 0x800B);

  // Separate Blend Functions
  CONSTANT(BLEND_DST_RGB, 0x80C8);
  CONSTANT(BLEND_SRC_RGB, 0x80C9);
  CONSTANT(BLEND_DST_ALPHA, 0x80CA);
  CONSTANT(BLEND_SRC_ALPHA, 0x80CB);
  CONSTANT(CONSTANT_COLOR, 0x8001);
  CONSTANT(ONE_MINUS_CONSTANT_COLOR, 0x8002);
  CONSTANT(CONSTANT_ALPHA, 0x8003);
  CONSTANT(ONE_MINUS_CONSTANT_ALPHA, 0x8004);
  CONSTANT(BLEND_COLOR, 0x8005);

  // Buffer Objects
  CONSTANT(ARRAY_BUFFER, 0x8892);
  CONSTANT(ELEMENT_ARRAY_BUFFER, 0x8893);
  CONSTANT(ARRAY_BUFFER_BINDING, 0x8894);
  CONSTANT(ELEMENT_ARRAY_BUFFER_BINDING, 0x8895);

  CONSTANT(STREAM_DRAW, 0x88E0);
  CONSTANT(STATIC_DRAW, 0x88E4);
  CONSTANT(DYNAMIC_DRAW, 0x88E8);

  CONSTANT(BUFFER_SIZE, 0x8764);
  CONSTANT(BUFFER_USAGE, 0x8765);

  CONSTANT(CURRENT_VERTEX_ATTRIB, 0x8626);

  // CullFaceMode
  CONSTANT(FRONT, 0x0404);
  CONSTANT(BACK, 0x0405);
  CONSTANT(FRONT_AND_BACK, 0x0408);

  // EnableCap
  CONSTANT(TEXTURE_2D, 0x0DE1);
  CONSTANT(CULL_FACE, 0x0B44);
  CONSTANT(BLEND, 0x0BE2);
  CONSTANT(DITHER, 0x0BD0);
  CONSTANT(STENCIL_TEST, 0x0B90);
  CONSTANT(DEPTH_TEST, 0x0B71);
  CONSTANT(SCISSOR_TEST, 0x0C11);
  CONSTANT(POLYGON_OFFSET_FILL, 0x8037);
  CONSTANT(SAMPLE_ALPHA_TO_COVERAGE, 0x809E);
  CONSTANT(SAMPLE_COVERAGE, 0x80A0);

  // ErrorCode
  CONSTANT(NO_ERROR, 0);
  CONSTANT(INVALID_ENUM, 0x0500);
  CONSTANT(INVALID_VALUE, 0x0501);
  CONSTANT(INVALID_OPERATION, 0x0502);
  CONSTANT(OUT_OF_MEMORY, 0x0505);

  // FrontFaceDirection
  CONSTANT(CW, 0x0900);
  CONSTANT(CCW, 0x0901);

  // GetPName
  CONSTANT(LINE_WIDTH, 0x0B21);
  CONSTANT(ALIASED_POINT_SIZE_RANGE, 0x846D);
  CONSTANT(ALIASED_LINE_WIDTH_RANGE, 0x846E);
  CONSTANT(CULL_FACE_MODE, 0x0B45);
  CONSTANT(FRONT_FACE, 0x0B46);
  CONSTANT(DEPTH_RANGE, 0x0B70);
  CONSTANT(DEPTH_WRITEMASK, 0x0B72);
  CONSTANT(DEPTH_CLEAR_VALUE, 0x0B73);
  CONSTANT(DEPTH_FUNC, 0x0B74);
  CONSTANT(STENCIL_CLEAR_VALUE, 0x0B91);
  CONSTANT(STENCIL_FUNC, 0x0B92);
  CONSTANT(STENCIL_FAIL, 0x0B94);
  CONSTANT(STENCIL_PASS_DEPTH_FAIL, 0x0B95);
  CONSTANT(STENCIL_PASS_DEPTH_PASS, 0x0B96);
  CONSTANT(STENCIL_REF, 0x0B97);
  CONSTANT(STENCIL_VALUE_MASK, 0x0B93);
  CONSTANT(STENCIL_WRITEMASK, 0x0B98);
  CONSTANT(STENCIL_BACK_FUNC, 0x8800);
  CONSTANT(STENCIL_BACK_FAIL, 0x8801);
  CONSTANT(STENCIL_BACK_PASS_DEPTH_FAIL, 0x8802);
  CONSTANT(STENCIL_BACK_PASS_DEPTH_PASS, 0x8803);
  CONSTANT(STENCIL_BACK_REF, 0x8CA3);
  CONSTANT(STENCIL_BACK_VALUE_MASK, 0x8CA4);
  CONSTANT(STENCIL_BACK_WRITEMASK, 0x8CA5);
  CONSTANT(VIEWPORT, 0x0BA2);
  CONSTANT(SCISSOR_BOX, 0x0C10);
  CONSTANT(COLOR_CLEAR_VALUE, 0x0C22);
  CONSTANT(COLOR_WRITEMASK, 0x0C23);
  CONSTANT(UNPACK_ALIGNMENT, 0x0CF5);
  CONSTANT(PACK_ALIGNMENT, 0x0D05);
  CONSTANT(MAX_TEXTURE_SIZE, 0x0D33);
  CONSTANT(MAX_VIEWPORT_DIMS, 0x0D3A);
  CONSTANT(SUBPIXEL_BITS, 0x0D50);
  CONSTANT(RED_BITS, 0x0D52);
  CONSTANT(GREEN_BITS, 0x0D53);
  CONSTANT(BLUE_BITS, 0x0D54);
  CONSTANT(ALPHA_BITS, 0x0D55);
  CONSTANT(DEPTH_BITS, 0x0D56);
  CONSTANT(STENCIL_BITS, 0x0D57);
  CONSTANT(POLYGON_OFFSET_UNITS, 0x2A00);
  CONSTANT(POLYGON_OFFSET_FACTOR, 0x8038);
  CONSTANT(TEXTURE_BINDING_2D, 0x8069);
  CONSTANT(SAMPLE_BUFFERS, 0x80A8);
  CONSTANT(SAMPLES, 0x80A9);
  CONSTANT(SAMPLE_COVERAGE_VALUE, 0x80AA);
  CONSTANT(SAMPLE_COVERAGE_INVERT, 0x80AB);

  // GetTextureParameter
  CONSTANT(NUM_COMPRESSED_TEXTURE_FORMATS, 0x86A2);
  CONSTANT(COMPRESSED_TEXTURE_FORMATS, 0x86A3);

  // HintMode
  CONSTANT(DONT_CARE, 0x1100);
  CONSTANT(FASTEST, 0x1101);
  CONSTANT(NICEST, 0x1102);

  // HintTarget
  CONSTANT(GENERATE_MIPMAP_HINT, 0x8192);

  // DataType
  CONSTANT(BYTE, 0x1400);
  CONSTANT(UNSIGNED_BYTE, 0x1401);
  CONSTANT(SHORT, 0x1402);
  CONSTANT(UNSIGNED_SHORT, 0x1403);
  CONSTANT(INT, 0x1404);
  CONSTANT(UNSIGNED_INT, 0x1405);
  CONSTANT(FLOAT, 0x1406);

  // PixelFormat
  CONSTANT(DEPTH_COMPONENT, 0x1902);
  CONSTANT(ALPHA, 0x1906);
  CONSTANT(RGB, 0x1907);
  CONSTANT(RGBA, 0x1908);
  CONSTANT(LUMINANCE, 0x1909);
  CONSTANT(LUMINANCE_ALPHA, 0x190A);

  // PixelType
  CONSTANT(UNSIGNED_SHORT_4_4_4_4, 0x8033);
  CONSTANT(UNSIGNED_SHORT_5_5_5_1, 0x8034);
  CONSTANT(UNSIGNED_SHORT_5_6_5, 0x8363);

  // Shaders
  CONSTANT(FRAGMENT_SHADER, 0x8B30);
  CONSTANT(VERTEX_SHADER, 0x8B31);
  CONSTANT(MAX_VERTEX_ATTRIBS, 0x8869);
  CONSTANT(MAX_VERTEX_UNIFORM_VECTORS, 0x8DFB);
  CONSTANT(MAX_VARYING_VECTORS, 0x8DFC);
  CONSTANT(MAX_COMBINED_TEXTURE_IMAGE_UNITS, 0x8B4D);
  CONSTANT(MAX_VERTEX_TEXTURE_IMAGE_UNITS, 0x8B4C);
  CONSTANT(MAX_TEXTURE_IMAGE_UNITS, 0x8872);
  CONSTANT(MAX_FRAGMENT_UNIFORM_VECTORS, 0x8DFD);
  CONSTANT(SHADER_TYPE, 0x8B4F);
  CONSTANT(DELETE_STATUS, 0x8B80);
  CONSTANT(LINK_STATUS, 0x8B82);
  CONSTANT(VALIDATE_STATUS, 0x8B83);
  CONSTANT(ATTACHED_SHADERS, 0x8B85);
  CONSTANT(ACTIVE_UNIFORMS, 0x8B86);
  CONSTANT(ACTIVE_UNIFORM_MAX_LENGTH, 0x8B87);
  CONSTANT(ACTIVE_ATTRIBUTES, 0x8B89);
  CONSTANT(ACTIVE_ATTRIBUTE_MAX_LENGTH, 0x8B8A);
  CONSTANT(SHADING_LANGUAGE_VERSION, 0x8B8C);
  CONSTANT(CURRENT_PROGRAM, 0x8B8D);

  // StencilFunction
  CONSTANT(NEVER, 0x0200);
  CONSTANT(LESS, 0x0201);
  CONSTANT(EQUAL, 0x0202);
  CONSTANT(LEQUAL, 0x0203);
  CONSTANT(GREATER, 0x0204);
  CONSTANT(NOTEQUAL, 0x0205);
  CONSTANT(GEQUAL, 0x0206);
  CONSTANT(ALWAYS, 0x0207);

  // StencilOp
  CONSTANT(KEEP, 0x1E00);
  CONSTANT(REPLACE, 0x1E01);
  CONSTANT(INCR, 0x1E02);
  CONSTANT(DECR, 0x1E03);
  CONSTANT(INVERT, 0x150A);
  CONSTANT(INCR_WRAP, 0x8507);
  CONSTANT(DECR_WRAP, 0x8508);

  // StringName
  CONSTANT(VENDOR, 0x1F00);
  CONSTANT(RENDERER, 0x1F01);
  CONSTANT(VERSION, 0x1F02);

  // TextureMagFilter
  CONSTANT(NEAREST, 0x2600);
  CONSTANT(LINEAR, 0x2601);

  // TextureMinFilter
  CONSTANT(NEAREST_MIPMAP_NEAREST, 0x2700);
  CONSTANT(LINEAR_MIPMAP_NEAREST, 0x2701);
  CONSTANT(NEAREST_MIPMAP_LINEAR, 0x2702);
  CONSTANT(LINEAR_MIPMAP_LINEAR, 0x2703);

  // TextureParameterName
  CONSTANT(TEXTURE_MAG_FILTER, 0x2800);
  CONSTANT(TEXTURE_MIN_FILTER, 0x2801);
  CONSTANT(TEXTURE_WRAP_S, 0x2802);
  CONSTANT(TEXTURE_WRAP_T, 0x2803);

  // TextureTarget
  CONSTANT(TEXTURE, 0x1702);
  CONSTANT(TEXTURE_CUBE_MAP, 0x8513);
  CONSTANT(TEXTURE_BINDING_CUBE_MAP, 0x8514);
  CONSTANT(TEXTURE_CUBE_MAP_POSITIVE_X, 0x8515);
  CONSTANT(TEXTURE_CUBE_MAP_NEGATIVE_X, 0x8516);
  CONSTANT(TEXTURE_CUBE_MAP_POSITIVE_Y, 0x8517);
  CONSTANT(TEXTURE_CUBE_MAP_NEGATIVE_Y, 0x8518);
  CONSTANT(TEXTURE_CUBE_MAP_POSITIVE_Z, 0x8519);
  CONSTANT(TEXTURE_CUBE_MAP_NEGATIVE_Z, 0x851A);
  CONSTANT(MAX_CUBE_MAP_TEXTURE_SIZE, 0x851C);

  // TextureUnit
  CONSTANT(TEXTURE0, 0x84C0);
  CONSTANT(TEXTURE1, 0x84C1);
  CONSTANT(TEXTURE2, 0x84C2);
  CONSTANT(TEXTURE3, 0x84C3);
  CONSTANT(TEXTURE4, 0x84C4);
  CONSTANT(TEXTURE5, 0x84C5);
  CONSTANT(TEXTURE6, 0x84C6);
  CONSTANT(TEXTURE7, 0x84C7);
  CONSTANT(TEXTURE8, 0x84C8);
  CONSTANT(TEXTURE9, 0x84C9);
  CONSTANT(TEXTURE10, 0x84CA);
  CONSTANT(TEXTURE11, 0x84CB);
  CONSTANT(TEXTURE12, 0x84CC);
  CONSTANT(TEXTURE13, 0x84CD);
  CONSTANT(TEXTURE14, 0x84CE);
  CONSTANT(TEXTURE15, 0x84CF);
  CONSTANT(TEXTURE16, 0x84D0);
  CONSTANT(TEXTURE17, 0x84D1);
  CONSTANT(TEXTURE18, 0x84D2);
  CONSTANT(TEXTURE19, 0x84D3);
  CONSTANT(TEXTURE20, 0x84D4);
  CONSTANT(TEXTURE21, 0x84D5);
  CONSTANT(TEXTURE22, 0x84D6);
  CONSTANT(TEXTURE23, 0x84D7);
  CONSTANT(TEXTURE24, 0x84D8);
  CONSTANT(TEXTURE25, 0x84D9);
  CONSTANT(TEXTURE26, 0x84DA);
  CONSTANT(TEXTURE27, 0x84DB);
  CONSTANT(TEXTURE28, 0x84DC);
  CONSTANT(TEXTURE29, 0x84DD);
  CONSTANT(TEXTURE30, 0x84DE);
  CONSTANT(TEXTURE31, 0x84DF);
  CONSTANT(ACTIVE_TEXTURE, 0x84E0);

  // TextureWrapMode
  CONSTANT(REPEAT, 0x2901);
  CONSTANT(CLAMP_TO_EDGE, 0x812F);
  CONSTANT(MIRRORED_REPEAT, 0x8370);

  // Uniform Types
  CONSTANT(FLOAT_VEC2, 0x8B50);
  CONSTANT(FLOAT_VEC3, 0x8B51);
  CONSTANT(FLOAT_VEC4, 0x8B52);
  CONSTANT(INT_VEC2, 0x8B53);
  CONSTANT(INT_VEC3, 0x8B54);
  CONSTANT(INT_VEC4, 0x8B55);
  CONSTANT(BOOL, 0x8B56);
  CONSTANT(BOOL_VEC2, 0x8B57);
  CONSTANT(BOOL_VEC3, 0x8B58);
  CONSTANT(BOOL_VEC4, 0x8B59);
  CONSTANT(FLOAT_MAT2, 0x8B5A);
  CONSTANT(FLOAT_MAT3, 0x8B5B);
  CONSTANT(FLOAT_MAT4, 0x8B5C);
  CONSTANT(SAMPLER_2D, 0x8B5E);
  CONSTANT(SAMPLER_CUBE, 0x8B60);

  // Vertex Arrays
  CONSTANT(VERTEX_ATTRIB_ARRAY_ENABLED, 0x8622);
  CONSTANT(VERTEX_ATTRIB_ARRAY_SIZE, 0x8623);
  CONSTANT(VERTEX_ATTRIB_ARRAY_STRIDE, 0x8624);
  CONSTANT(VERTEX_ATTRIB_ARRAY_TYPE, 0x8625);
  CONSTANT(VERTEX_ATTRIB_ARRAY_NORMALIZED, 0x886A);
  CONSTANT(VERTEX_ATTRIB_ARRAY_POINTER, 0x8645);
  CONSTANT(VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, 0x889F);

  // Shader Source
  CONSTANT(COMPILE_STATUS, 0x8B81);
  CONSTANT(INFO_LOG_LENGTH, 0x8B84);
  CONSTANT(SHADER_SOURCE_LENGTH, 0x8B88);

  // Shader Precision-Specified Types
  CONSTANT(LOW_FLOAT, 0x8DF0);
  CONSTANT(MEDIUM_FLOAT, 0x8DF1);
  CONSTANT(HIGH_FLOAT, 0x8DF2);
  CONSTANT(LOW_INT, 0x8DF3);
  CONSTANT(MEDIUM_INT, 0x8DF4);
  CONSTANT(HIGH_INT, 0x8DF5);

  // Framebuffer Object.
  CONSTANT(FRAMEBUFFER, 0x8D40);
  CONSTANT(RENDERBUFFER, 0x8D41);

  CONSTANT(RGBA4, 0x8056);
  CONSTANT(RGB5_A1, 0x8057);
  CONSTANT(RGB565, 0x8D62);
  CONSTANT(DEPTH_COMPONENT16, 0x81A5);
  CONSTANT(STENCIL_INDEX, 0x1901);
  CONSTANT(STENCIL_INDEX8, 0x8D48);
  CONSTANT(DEPTH_STENCIL, 0x84F9);

  CONSTANT(RENDERBUFFER_WIDTH, 0x8D42);
  CONSTANT(RENDERBUFFER_HEIGHT, 0x8D43);
  CONSTANT(RENDERBUFFER_INTERNAL_FORMAT, 0x8D44);
  CONSTANT(RENDERBUFFER_RED_SIZE, 0x8D50);
  CONSTANT(RENDERBUFFER_GREEN_SIZE, 0x8D51);
  CONSTANT(RENDERBUFFER_BLUE_SIZE, 0x8D52);
  CONSTANT(RENDERBUFFER_ALPHA_SIZE, 0x8D53);
  CONSTANT(RENDERBUFFER_DEPTH_SIZE, 0x8D54);
  CONSTANT(RENDERBUFFER_STENCIL_SIZE, 0x8D55);

  CONSTANT(FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, 0x8CD0);
  CONSTANT(FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, 0x8CD1);
  CONSTANT(FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL, 0x8CD2);
  CONSTANT(FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE, 0x8CD3);

  CONSTANT(COLOR_ATTACHMENT0, 0x8CE0);
  CONSTANT(DEPTH_ATTACHMENT, 0x8D00);
  CONSTANT(STENCIL_ATTACHMENT, 0x8D20);
  CONSTANT(DEPTH_STENCIL_ATTACHMENT, 0x821A);

  CONSTANT(NONE, 0);

  CONSTANT(FRAMEBUFFER_COMPLETE, 0x8CD5);
  CONSTANT(FRAMEBUFFER_INCOMPLETE_ATTACHMENT, 0x8CD6);
  CONSTANT(FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT, 0x8CD7);
  CONSTANT(FRAMEBUFFER_INCOMPLETE_DIMENSIONS, 0x8CD9);
  CONSTANT(FRAMEBUFFER_UNSUPPORTED, 0x8CDD);

  CONSTANT(FRAMEBUFFER_BINDING, 0x8CA6);
  CONSTANT(RENDERBUFFER_BINDING, 0x8CA7);
  CONSTANT(MAX_RENDERBUFFER_SIZE, 0x84E8);

  CONSTANT(INVALID_FRAMEBUFFER_OPERATION, 0x0506);

  // WebGL-specific enums
  CONSTANT(UNPACK_FLIP_Y_WEBGL, 0x9240);
  CONSTANT(UNPACK_PREMULTIPLY_ALPHA_WEBGL, 0x9241);
  CONSTANT(CONTEXT_LOST_WEBGL, 0x9242);
  CONSTANT(UNPACK_COLORSPACE_CONVERSION_WEBGL, 0x9243);
  CONSTANT(BROWSER_DEFAULT_WEBGL, 0x9244);

  //XXX add attributes (canvas, drawingBufferWidth etc.)?
}

}
