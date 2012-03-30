// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "typed_array.h"
#include "webgl_active_info.h"
#include "webgl_buffer.h"
#include "webgl_framebuffer.h"
#include "webgl_program.h"
#include "webgl_renderbuffer.h"
#include "webgl_rendering_context.h"
#include "webgl_shader.h"
#include "webgl_texture.h"
#include "webgl_uniform_location.h"

#include <string>
#include <vector>
#include <sstream>

namespace v8_webgl {

// Emulate GLES2 constants
#ifndef GL_MAX_FRAGMENT_UNIFORM_VECTORS
#define GL_MAX_FRAGMENT_UNIFORM_VECTORS 0x8DFD
#endif
#ifndef GL_MAX_VERTEX_UNIFORM_VECTORS
#define GL_MAX_VERTEX_UNIFORM_VECTORS 0x8DFB
#endif
#ifndef GL_MAX_VARYING_VECTORS
#define GL_MAX_VARYING_VECTORS 0x8DFC
#endif
#ifndef GL_RGB565
#define GL_RGB565 0x8D62
#endif

// WebGL specific
#define GL_UNPACK_FLIP_Y_WEBGL 0x9240
#define GL_UNPACK_PREMULTIPLY_ALPHA_WEBGL 0x9241
#define GL_UNPACK_COLORSPACE_CONVERSION_WEBGL 0x9243

static WebGLRenderingContext* CallbackContext(const v8::Arguments& args) {
  WebGLRenderingContext* context = WebGLRenderingContext::ToNative(args.Holder());
  if (!context)
    return NULL;
  context->MakeCurrent();
  return context;
}

//////

// WebGLContextAttributes getContextAttributes();
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getContextAttributes(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  /*XXX finish, need to add WebGLContextAttributes class*/
  return v8::Undefined();
}

// boolean isContextLost();
v8::Handle<v8::Value> WebGLRenderingContext::Callback_isContextLost(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  return TypeToV8<bool>(false);
}

// DOMString[ ] getSupportedExtensions();
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getSupportedExtensions(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// object getExtension(DOMString name);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getExtension(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void activeTexture(GLenum texture);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_activeTexture(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLenum texture = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  glActiveTexture(texture);
  return v8::Undefined();
}

// void attachShader(WebGLProgram program, WebGLShader shader);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_attachShader(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  WebGLProgram* program = V8ToNative<WebGLProgram>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->RequireObject(program)) return v8::Undefined();
  if (!context->ValidateObject(program)) return v8::Undefined();
  GLuint program_id = program ? program->get_webgl_id() : 0;
  WebGLShader* shader = V8ToNative<WebGLShader>(args[1], ok); if (!ok) return v8::Undefined();
  if (!context->RequireObject(shader)) return v8::Undefined();
  if (!context->ValidateObject(shader)) return v8::Undefined();
  GLuint shader_id = shader ? shader->get_webgl_id() : 0;
  glAttachShader(program_id, shader_id);
  return v8::Undefined();
}

// void bindAttribLocation(WebGLProgram program, GLuint index, DOMString name);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_bindAttribLocation(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 3) return ThrowArgCount();
  WebGLProgram* program = V8ToNative<WebGLProgram>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->RequireObject(program)) return v8::Undefined();
  if (!context->ValidateObject(program)) return v8::Undefined();
  GLuint program_id = program ? program->get_webgl_id() : 0;
  GLuint index = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  std::string name = V8ToType<std::string>(args[2], ok); if (!ok) return v8::Undefined();
  glBindAttribLocation(program_id, index, name.c_str());
  return v8::Undefined();
}

// void bindBuffer(GLenum target, WebGLBuffer buffer);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_bindBuffer(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  switch (target) {
    case GL_ARRAY_BUFFER:
    case GL_ELEMENT_ARRAY_BUFFER:
      break;
    default:
      context->set_gl_error(GL_INVALID_ENUM);
      return v8::Undefined();
  }
  WebGLBuffer* buffer = V8ToNative<WebGLBuffer>(args[1], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateObject(buffer)) return v8::Undefined();
  GLuint buffer_id = buffer ? buffer->get_webgl_id() : 0;
  glBindBuffer(target, buffer_id);
  return v8::Undefined();
}

// void bindFramebuffer(GLenum target, WebGLFramebuffer framebuffer);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_bindFramebuffer(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  if (target != GL_FRAMEBUFFER) {
    context->set_gl_error(GL_INVALID_ENUM);
    return v8::Undefined();
  }
  WebGLFramebuffer* framebuffer = V8ToNative<WebGLFramebuffer>(args[1], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateObject(framebuffer)) return v8::Undefined();
  GLuint framebuffer_id = framebuffer ? framebuffer->get_webgl_id() : 0;
  //XXX glBindFramebufferEXT
  glBindFramebuffer(target, framebuffer_id);
  return v8::Undefined();
}

// void bindRenderbuffer(GLenum target, WebGLRenderbuffer renderbuffer);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_bindRenderbuffer(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  if (target != GL_RENDERBUFFER) {
    context->set_gl_error(GL_INVALID_ENUM);
    return v8::Undefined();
  }
  WebGLRenderbuffer* renderbuffer = V8ToNative<WebGLRenderbuffer>(args[1], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateObject(renderbuffer)) return v8::Undefined();
  GLuint renderbuffer_id = renderbuffer ? renderbuffer->get_webgl_id() : 0;
  //XXX glBindRenderbufferEXT
  glBindRenderbuffer(target, renderbuffer_id);
  return v8::Undefined();
}

// void bindTexture(GLenum target, WebGLTexture texture);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_bindTexture(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  switch (target) {
    case GL_TEXTURE_2D:
    case GL_TEXTURE_CUBE_MAP:
      break;
    default:
      context->set_gl_error(GL_INVALID_ENUM);
      return v8::Undefined();
  }
  WebGLTexture* texture = V8ToNative<WebGLTexture>(args[1], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateObject(texture)) return v8::Undefined();
  GLuint texture_id = texture ? texture->get_webgl_id() : 0;
  glBindTexture(target, texture_id);
  return v8::Undefined();
}

// void blendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_blendColor(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 4) return ThrowArgCount();
  GLclampf red = V8ToType<float>(args[0], ok); if (!ok) return v8::Undefined();
  GLclampf green = V8ToType<float>(args[1], ok); if (!ok) return v8::Undefined();
  GLclampf blue = V8ToType<float>(args[2], ok); if (!ok) return v8::Undefined();
  GLclampf alpha = V8ToType<float>(args[3], ok); if (!ok) return v8::Undefined();
  glBlendColor(red, green, blue, alpha);
  return v8::Undefined();
 }

// void blendEquation(GLenum mode);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_blendEquation(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLenum mode = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateBlendEquation("blendEquation", mode))
    return v8::Undefined();
  glBlendEquation(mode);
  return v8::Undefined();
}

// void blendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_blendEquationSeparate(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  GLenum modeRGB = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateBlendEquation("blendEquationSeparate", modeRGB))
    return v8::Undefined();
  GLenum modeAlpha = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateBlendEquation("blendEquationSeparate", modeAlpha))
    return v8::Undefined();
  glBlendEquationSeparate(modeRGB, modeAlpha);
  return v8::Undefined();
}

// void blendFunc(GLenum sfactor, GLenum dfactor);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_blendFunc(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  GLenum sfactor = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  GLenum dfactor = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateBlendFuncFactors("blendFunc", sfactor, dfactor))
    return v8::Undefined();
  glBlendFunc(sfactor, dfactor);
  return v8::Undefined();
}

// void blendFuncSeparate(GLenum srcRGB, GLenum dstRGB, 
//                        GLenum srcAlpha, GLenum dstAlpha);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_blendFuncSeparate(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 4) return ThrowArgCount();
  GLenum srcRGB = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  GLenum dstRGB = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateBlendFuncFactors("blendFuncSeparate", srcRGB, dstRGB))
    return v8::Undefined();
  GLenum srcAlpha = V8ToType<uint32_t>(args[2], ok); if (!ok) return v8::Undefined();
  GLenum dstAlpha = V8ToType<uint32_t>(args[3], ok); if (!ok) return v8::Undefined();
  glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
  return v8::Undefined();
}

// void bufferData(GLenum target, GLsizeiptr size, GLenum usage);
// void bufferData(GLenum target, ArrayBufferView data, GLenum usage);
// void bufferData(GLenum target, ArrayBuffer data, GLenum usage);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_bufferData(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 3) return ThrowArgCount();
  if (args[1]->IsNull()) {
    context->set_gl_error(GL_INVALID_VALUE);
    return v8::Undefined();
  }
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  void* data = NULL;
  GLsizeiptr size = 0;
  uint32_t length = 0;
  if (TypedArrayToData(args[1], data, length, ok))
    size = length;
  else {
    if (!ok)
      return v8::Undefined();
    size = V8ToType<int32_t>(args[1], ok); if (!ok) return v8::Undefined();
  }
  GLenum usage = V8ToType<uint32_t>(args[2], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateBufferDataParameters("bufferData", target, usage))
    return v8::Undefined();
  glBufferData(target, size, data, usage);
  return v8::Undefined();
}

// void bufferSubData(GLenum target, GLintptr offset, ArrayBufferView data);
// void bufferSubData(GLenum target, GLintptr offset, ArrayBuffer data);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_bufferSubData(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 3) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateBufferDataParameters("bufferSubData", target, GL_STATIC_DRAW))
    return v8::Undefined();
  GLintptr offset = V8ToType<int32_t>(args[1], ok); if (!ok) return v8::Undefined();
  void* data = NULL;
  GLsizeiptr size = 0;
  uint32_t length = 0;
  if (TypedArrayToData(args[2], data, length, ok))
    size = length;
  else
    return v8::Undefined();

  glBufferSubData(target, offset, size, data);
  return v8::Undefined();
}

// GLenum checkFramebufferStatus(GLenum target);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_checkFramebufferStatus(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  if (target != GL_FRAMEBUFFER) {
    context->set_gl_error(GL_INVALID_ENUM);
    return TypeToV8<uint32_t>(0);
  }
  return TypeToV8<uint32_t>(glCheckFramebufferStatus(target));
}

// void clear(GLbitfield mask);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_clear(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLbitfield mask = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  if (mask & ~(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)) {
    context->set_gl_error(GL_INVALID_VALUE);
    return v8::Undefined();
  }
  glClear(mask);
  return v8::Undefined();
}

// void clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_clearColor(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 4) return ThrowArgCount();
  GLclampf red = V8ToType<float>(args[0], ok); if (!ok) return v8::Undefined();
  GLclampf green = V8ToType<float>(args[1], ok); if (!ok) return v8::Undefined();
  GLclampf blue = V8ToType<float>(args[2], ok); if (!ok) return v8::Undefined();
  GLclampf alpha = V8ToType<float>(args[3], ok); if (!ok) return v8::Undefined();
  glClearColor(red, green, blue, alpha);
  return v8::Undefined();
}

// void clearDepth(GLclampf depth);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_clearDepth(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLclampf depth = V8ToType<float>(args[0], ok); if (!ok) return v8::Undefined();
  glClearDepth(depth);
  return v8::Undefined();
}

// void clearStencil(GLint s);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_clearStencil(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLint s = V8ToType<int32_t>(args[0], ok); if (!ok) return v8::Undefined();
  glClearStencil(s);
  return v8::Undefined();
}

// void colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_colorMask(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 4) return ThrowArgCount();
  GLboolean red = V8ToType<bool>(args[0], ok); if (!ok) return v8::Undefined();
  GLboolean green = V8ToType<bool>(args[1], ok); if (!ok) return v8::Undefined();
  GLboolean blue = V8ToType<bool>(args[2], ok); if (!ok) return v8::Undefined();
  GLboolean alpha = V8ToType<bool>(args[3], ok); if (!ok) return v8::Undefined();
  glColorMask(red, green, blue, alpha);
  return v8::Undefined();
}

//XXX need to use ANGLE to translate shader source - see GraphicsContext3D::compileShader
// void compileShader(WebGLShader shader);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_compileShader(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  WebGLShader* shader = V8ToNative<WebGLShader>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->RequireObject(shader)) return v8::Undefined();
  if (!context->ValidateObject(shader)) return v8::Undefined();
  GLuint shader_id = shader ? shader->get_webgl_id() : 0;
  glCompileShader(shader_id);
  return v8::Undefined();
}

// void copyTexImage2D(GLenum target, GLint level, GLenum internalformat, 
//                     GLint x, GLint y, GLsizei width, GLsizei height, 
//                     GLint border);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_copyTexImage2D(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 8) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  GLint level = V8ToType<int32_t>(args[1], ok); if (!ok) return v8::Undefined();
  GLenum internalformat = V8ToType<uint32_t>(args[2], ok); if (!ok) return v8::Undefined();
  GLint x = V8ToType<int32_t>(args[3], ok); if (!ok) return v8::Undefined();
  GLint y = V8ToType<int32_t>(args[4], ok); if (!ok) return v8::Undefined();
  GLsizei width = V8ToType<int32_t>(args[5], ok); if (!ok) return v8::Undefined();
  GLsizei height = V8ToType<int32_t>(args[6], ok); if (!ok) return v8::Undefined();
  GLint border = V8ToType<int32_t>(args[7], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateTexFuncParameters("copyTexImage2D", target, level, internalformat, width, height, border, internalformat, GL_UNSIGNED_BYTE))
    return v8::Undefined();
  glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
  return v8::Undefined();
}

// void copyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, 
//                        GLint x, GLint y, GLsizei width, GLsizei height);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_copyTexSubImage2D(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 8) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  GLint level = V8ToType<int32_t>(args[1], ok); if (!ok) return v8::Undefined();
  GLint xoffset = V8ToType<int32_t>(args[2], ok); if (!ok) return v8::Undefined();
  GLint yoffset = V8ToType<int32_t>(args[3], ok); if (!ok) return v8::Undefined();
  GLint x = V8ToType<int32_t>(args[4], ok); if (!ok) return v8::Undefined();
  GLint y = V8ToType<int32_t>(args[5], ok); if (!ok) return v8::Undefined();
  GLsizei width = V8ToType<int32_t>(args[6], ok); if (!ok) return v8::Undefined();
  GLsizei height = V8ToType<int32_t>(args[7], ok); if (!ok) return v8::Undefined();
  glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
  return v8::Undefined();
}

// WebGLBuffer createBuffer();
v8::Handle<v8::Value> WebGLRenderingContext::Callback_createBuffer(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  GLuint buffer_id = 0;
  glGenBuffers(1, &buffer_id);
  WebGLBuffer* buffer = context->CreateBuffer(buffer_id);
  return buffer->ToV8();
}

// WebGLFramebuffer createFramebuffer();
v8::Handle<v8::Value> WebGLRenderingContext::Callback_createFramebuffer(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  GLuint framebuffer_id = 0;
  //XXX glGenFramebuffersEXT etc.
  glGenFramebuffers(1, &framebuffer_id);
  WebGLFramebuffer* framebuffer = context->CreateFramebuffer(framebuffer_id);
  return framebuffer->ToV8();
}

// WebGLProgram createProgram();
v8::Handle<v8::Value> WebGLRenderingContext::Callback_createProgram(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  GLuint program_id = glCreateProgram();
  WebGLProgram* program = context->CreateProgram(program_id);
  return program->ToV8();
}

// WebGLRenderbuffer createRenderbuffer();
v8::Handle<v8::Value> WebGLRenderingContext::Callback_createRenderbuffer(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  GLuint renderbuffer_id = 0;
  //XXX glGenRenderbuffersEXT etc.
  glGenRenderbuffers(1, &renderbuffer_id);
  WebGLRenderbuffer* renderbuffer = context->CreateRenderbuffer(renderbuffer_id);
  return renderbuffer->ToV8();
}

// WebGLShader createShader(GLenum type);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_createShader(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLenum type = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  GLuint shader_id = glCreateShader(type);
  WebGLShader* shader = context->CreateShader(shader_id);
  return shader->ToV8();
}

// WebGLTexture createTexture();
v8::Handle<v8::Value> WebGLRenderingContext::Callback_createTexture(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  GLuint texture_id = 0;
  glGenTextures(1, &texture_id);
  WebGLTexture* texture = context->CreateTexture(texture_id);
  return texture->ToV8();
}

// void cullFace(GLenum mode);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_cullFace(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLenum mode = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  glCullFace(mode);
  return v8::Undefined();
}

// void deleteBuffer(WebGLBuffer buffer);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_deleteBuffer(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  WebGLBuffer* buffer = V8ToNative<WebGLBuffer>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateObject(buffer)) return v8::Undefined();
  GLuint buffer_id = buffer ? buffer->get_webgl_id() : 0;
  glDeleteBuffers(1, &buffer_id);
  context->DeleteBuffer(buffer);
  return v8::Undefined();
}

// void deleteFramebuffer(WebGLFramebuffer framebuffer);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_deleteFramebuffer(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  WebGLFramebuffer* framebuffer = V8ToNative<WebGLFramebuffer>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateObject(framebuffer)) return v8::Undefined();
  GLuint framebuffer_id = framebuffer ? framebuffer->get_webgl_id() : 0;
  //XXX glDeleteFramebuffersEXT etc.
  glDeleteFramebuffers(1, &framebuffer_id);
  context->DeleteFramebuffer(framebuffer);
  return v8::Undefined();
}

// void deleteProgram(WebGLProgram program);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_deleteProgram(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  WebGLProgram* program = V8ToNative<WebGLProgram>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateObject(program)) return v8::Undefined();
  GLuint program_id = program ? program->get_webgl_id() : 0;
  glDeleteProgram(program_id);
  context->DeleteProgram(program);
  return v8::Undefined();
}

// void deleteRenderbuffer(WebGLRenderbuffer renderbuffer);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_deleteRenderbuffer(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  WebGLRenderbuffer* renderbuffer = V8ToNative<WebGLRenderbuffer>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateObject(renderbuffer)) return v8::Undefined();
  GLuint renderbuffer_id = renderbuffer ? renderbuffer->get_webgl_id() : 0;
  //XXX glDeleteRenderbuffersEXT etc.
  glDeleteRenderbuffers(1, &renderbuffer_id);
  context->DeleteRenderbuffer(renderbuffer);
  return v8::Undefined();
}

// void deleteShader(WebGLShader shader);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_deleteShader(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  WebGLShader* shader = V8ToNative<WebGLShader>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateObject(shader)) return v8::Undefined();
  GLuint shader_id = shader ? shader->get_webgl_id() : 0;
  glDeleteShader(shader_id);
  context->DeleteShader(shader);
  return v8::Undefined();
}

// void deleteTexture(WebGLTexture texture);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_deleteTexture(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  WebGLTexture* texture = V8ToNative<WebGLTexture>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateObject(texture)) return v8::Undefined();
  GLuint texture_id = texture ? texture->get_webgl_id() : 0;
  glDeleteTextures(1, &texture_id);
  context->DeleteTexture(texture);
  return v8::Undefined();
}

// void depthFunc(GLenum func);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_depthFunc(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLenum func = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  glDepthFunc(func);
  return v8::Undefined();
}

// void depthMask(GLboolean flag);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_depthMask(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLboolean flag = V8ToType<bool>(args[0], ok); if (!ok) return v8::Undefined();
  glDepthMask(flag);
  return v8::Undefined();
}

// void depthRange(GLclampf zNear, GLclampf zFar);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_depthRange(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  GLclampf zNear = V8ToType<float>(args[0], ok); if (!ok) return v8::Undefined();
  GLclampf zFar = V8ToType<float>(args[1], ok); if (!ok) return v8::Undefined();
  glDepthRange(zNear, zFar);
  return v8::Undefined();
}

// void detachShader(WebGLProgram program, WebGLShader shader);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_detachShader(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  WebGLProgram* program = V8ToNative<WebGLProgram>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->RequireObject(program)) return v8::Undefined();
  if (!context->ValidateObject(program)) return v8::Undefined();
  GLuint program_id = program ? program->get_webgl_id() : 0;
  WebGLShader* shader = V8ToNative<WebGLShader>(args[1], ok); if (!ok) return v8::Undefined();
  if (!context->RequireObject(shader)) return v8::Undefined();
  if (!context->ValidateObject(shader)) return v8::Undefined();
  GLuint shader_id = shader ? shader->get_webgl_id() : 0;
  glDetachShader(program_id, shader_id);
  return v8::Undefined();
}

// void disable(GLenum cap);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_disable(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLenum cap = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateCapability("disable", cap))
    return v8::Undefined();
  glDisable(cap);
  return v8::Undefined();
}

// void disableVertexAttribArray(GLuint index);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_disableVertexAttribArray(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLuint index = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  glDisableVertexAttribArray(index);
  return v8::Undefined();
}

// void drawArrays(GLenum mode, GLint first, GLsizei count);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_drawArrays(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 3) return ThrowArgCount();
  GLenum mode = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateDrawMode("drawArrays", mode))
    return v8::Undefined();
  GLint first = V8ToType<int32_t>(args[1], ok); if (!ok) return v8::Undefined();
  GLsizei count = V8ToType<int32_t>(args[2], ok); if (!ok) return v8::Undefined();
  glDrawArrays(mode, first, count);
  return v8::Undefined();
}

// void drawElements(GLenum mode, GLsizei count, GLenum type, GLintptr offset);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_drawElements(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 4) return ThrowArgCount();
  GLenum mode = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateDrawMode("drawElements", mode))
    return v8::Undefined();
  GLsizei count = V8ToType<int32_t>(args[1], ok); if (!ok) return v8::Undefined();
  GLenum type = V8ToType<uint32_t>(args[2], ok); if (!ok) return v8::Undefined();
  GLintptr offset = V8ToType<int32_t>(args[3], ok); if (!ok) return v8::Undefined();
  glDrawElements(mode, count, type, reinterpret_cast<GLvoid*>(static_cast<intptr_t>(offset)));
  return v8::Undefined();
}

// void enable(GLenum cap);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_enable(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLenum cap = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateCapability("enable", cap))
    return v8::Undefined();
  glEnable(cap);
  return v8::Undefined();
}

// void enableVertexAttribArray(GLuint index);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_enableVertexAttribArray(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLuint index = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  glEnableVertexAttribArray(index);
  return v8::Undefined();
}

// void finish();
v8::Handle<v8::Value> WebGLRenderingContext::Callback_finish(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  glFinish();
  return v8::Undefined();
}

// void flush();
v8::Handle<v8::Value> WebGLRenderingContext::Callback_flush(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  glFlush();
  return v8::Undefined();
}

// void framebufferRenderbuffer(GLenum target, GLenum attachment, 
//                              GLenum renderbuffertarget, 
//                              WebGLRenderbuffer renderbuffer);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_framebufferRenderbuffer(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 4) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  GLenum attachment = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateFramebufferFuncParameters("framebufferRenderbuffer", target, attachment))
    return v8::Undefined();
  GLenum renderbuffertarget = V8ToType<uint32_t>(args[2], ok); if (!ok) return v8::Undefined();
  if (renderbuffertarget != GL_RENDERBUFFER) {
    context->set_gl_error(GL_INVALID_ENUM);
    return v8::Undefined();
  }
  WebGLRenderbuffer* renderbuffer = V8ToNative<WebGLRenderbuffer>(args[3], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateObject(renderbuffer)) return v8::Undefined();
  GLuint renderbuffer_id = renderbuffer ? renderbuffer->get_webgl_id() : 0;
  //XXX glFramebufferRenderbufferEXT
  glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer_id);
  return v8::Undefined();
}

// void framebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, 
//                           WebGLTexture texture, GLint level);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_framebufferTexture2D(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 5) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  GLenum attachment = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateFramebufferFuncParameters("framebufferTexture2D", target, attachment))
    return v8::Undefined();
  GLenum textarget = V8ToType<uint32_t>(args[2], ok); if (!ok) return v8::Undefined();
  WebGLTexture* texture = V8ToNative<WebGLTexture>(args[3], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateObject(texture)) return v8::Undefined();
  GLuint texture_id = texture ? texture->get_webgl_id() : 0;
  GLint level = V8ToType<int32_t>(args[4], ok); if (!ok) return v8::Undefined();
  //XXX glFramebufferTexture2DEXT
  glFramebufferTexture2D(target, attachment, textarget, texture_id, level);
  return v8::Undefined();
}

// void frontFace(GLenum mode);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_frontFace(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLenum mode = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  glFrontFace(mode);
  return v8::Undefined();
}

// void generateMipmap(GLenum target);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_generateMipmap(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  //XXX glGenerateMipmapEXT etc.
  glGenerateMipmap(target);
  return v8::Undefined();
}

// WebGLActiveInfo getActiveAttrib(WebGLProgram program, GLuint index);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getActiveAttrib(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// WebGLActiveInfo getActiveUniform(WebGLProgram program, GLuint index);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getActiveUniform(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// WebGLShader[ ] getAttachedShaders(WebGLProgram program);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getAttachedShaders(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

//XXX should return -1 (webkit) or 0 (firefox) on error, not Undefined - should preamble define a fail: label that can return whatever is needed?
// GLint getAttribLocation(WebGLProgram program, DOMString name);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getAttribLocation(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  WebGLProgram* program = V8ToNative<WebGLProgram>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->RequireObject(program)) return v8::Undefined();
  if (!context->ValidateObject(program)) return v8::Undefined();
  GLuint program_id = program ? program->get_webgl_id() : 0;
  std::string name = V8ToType<std::string>(args[1], ok); if (!ok) return v8::Undefined();
  GLint location = glGetAttribLocation(program_id, name.c_str());
  return TypeToV8<int32_t>(location);
}

// any getParameter(GLenum pname);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getParameter(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLenum pname = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  switch (pname) {
    case GL_ACTIVE_TEXTURE:
    case GL_BLEND_DST_ALPHA:
    case GL_BLEND_DST_RGB:
    case GL_BLEND_EQUATION_ALPHA:
    case GL_BLEND_EQUATION_RGB:
    case GL_BLEND_SRC_ALPHA:
    case GL_BLEND_SRC_RGB:
    case GL_CULL_FACE_MODE:
    case GL_DEPTH_FUNC:
    case GL_FRONT_FACE:
    case GL_GENERATE_MIPMAP_HINT:
    case GL_STENCIL_BACK_FAIL:
    case GL_STENCIL_BACK_FUNC:
    case GL_STENCIL_BACK_PASS_DEPTH_FAIL:
    case GL_STENCIL_BACK_PASS_DEPTH_PASS:
    case GL_STENCIL_BACK_VALUE_MASK:
    case GL_STENCIL_BACK_WRITEMASK:
    case GL_STENCIL_FAIL:
    case GL_STENCIL_FUNC:
    case GL_STENCIL_PASS_DEPTH_FAIL:
    case GL_STENCIL_PASS_DEPTH_PASS:
    case GL_STENCIL_VALUE_MASK:
    case GL_STENCIL_WRITEMASK: {
      GLint value = 0;
      glGetIntegerv(pname, &value);
      return TypeToV8<uint32_t>(static_cast<uint32_t>(value));
    }

    case GL_ALIASED_LINE_WIDTH_RANGE:
    case GL_ALIASED_POINT_SIZE_RANGE:
    case GL_DEPTH_RANGE: {
      GLfloat value[2] = {0};
      glGetFloatv(pname, value);
      return Float32Array::Create(value, 2);
    }

    case GL_BLEND_COLOR:
    case GL_COLOR_CLEAR_VALUE: {
      GLfloat value[4] = {0};
      glGetFloatv(pname, value);
      return Float32Array::Create(value, 4);
    }

    case GL_MAX_VIEWPORT_DIMS: {
      GLint value[2] = {0};
      glGetIntegerv(pname, value);
      return Int32Array::Create(value, 2);
    }

    case GL_SCISSOR_BOX:
    case GL_VIEWPORT: {
      GLint value[4] = {0};
      glGetIntegerv(pname, value);
      return Int32Array::Create(value, 4);
    }

    // Emulate GLES2 queries for desktop GL

    case GL_MAX_FRAGMENT_UNIFORM_VECTORS: {
      GLint value = 0;
      glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &value);
      return TypeToV8<int32_t>(value / 4);
    }
    case GL_MAX_VERTEX_UNIFORM_VECTORS: {
      GLint value = 0;
      glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &value);
      return TypeToV8<int32_t>(value / 4);
    }
    case GL_MAX_VARYING_VECTORS: {
      GLint value = 0;
      glGetIntegerv(GL_MAX_VARYING_FLOATS, &value);
      return TypeToV8<int32_t>(value / 4);
    }

    case GL_ALPHA_BITS:
    case GL_BLUE_BITS:
    case GL_DEPTH_BITS:
    case GL_GREEN_BITS:
    case GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS:
    case GL_MAX_CUBE_MAP_TEXTURE_SIZE:
    case GL_MAX_RENDERBUFFER_SIZE:
    case GL_MAX_TEXTURE_IMAGE_UNITS:
    case GL_MAX_TEXTURE_SIZE:
    case GL_MAX_VERTEX_ATTRIBS:
    case GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS:
#if 0
    case GL_NUM_SHADER_BINARY_FORMATS:
      //XXX not sure about this
#endif
    case GL_PACK_ALIGNMENT:
    case GL_RED_BITS:
    case GL_SAMPLE_BUFFERS:
    case GL_SAMPLES:
    case GL_STENCIL_BACK_REF:
    case GL_STENCIL_BITS:
    case GL_STENCIL_CLEAR_VALUE:
    case GL_STENCIL_REF:
    case GL_SUBPIXEL_BITS:
    case GL_UNPACK_ALIGNMENT: {
      GLint value = 0;
      glGetIntegerv(pname, &value);
      return TypeToV8<int32_t>(value);
    }

    case GL_COLOR_WRITEMASK: {
      GLboolean value[4] = {0};
      glGetBooleanv(pname, value);
      bool bool_value[4];
      for (int i = 0; i < 4; i++)
        bool_value[i] = static_cast<bool>(value[i]);
      return ArrayToV8<bool>(bool_value, 4);
    }

    case GL_BLEND:
    case GL_CULL_FACE:
    case GL_DEPTH_TEST:
    case GL_DEPTH_WRITEMASK:
    case GL_DITHER:
    case GL_POLYGON_OFFSET_FILL:
    case GL_SAMPLE_COVERAGE_INVERT:
    case GL_SCISSOR_TEST:
    case GL_STENCIL_TEST: {
      GLboolean value = 0;
      glGetBooleanv(pname, &value);
      return TypeToV8<bool>(static_cast<bool>(value));
    }

    case GL_DEPTH_CLEAR_VALUE:
    case GL_LINE_WIDTH:
    case GL_POLYGON_OFFSET_FACTOR:
    case GL_POLYGON_OFFSET_UNITS:
    case GL_SAMPLE_COVERAGE_VALUE: {
      GLfloat value = 0;
      glGetFloatv(pname, &value);
      return TypeToV8<double>(value);
    }

    case GL_ARRAY_BUFFER_BINDING:
    case GL_ELEMENT_ARRAY_BUFFER_BINDING: {
      GLint buffer_id = 0;
      glGetIntegerv(pname, &buffer_id);
      WebGLBuffer* buffer = context->IdToBuffer(buffer_id);
      return ToV8OrNull(buffer);
    }

    case GL_COMPRESSED_TEXTURE_FORMATS:
      // XXX needed for WEBGL_compressed_texture_s3tc extension
      return Uint32Array::Create(0, NULL);

    case GL_CURRENT_PROGRAM: {
      GLint program_id = 0;
      glGetIntegerv(pname, &program_id);
      WebGLProgram* program = context->IdToProgram(program_id);
      return ToV8OrNull(program);
    }

    case GL_FRAMEBUFFER_BINDING:
    case GL_RENDERBUFFER_BINDING: {
      GLint framebuffer_id = 0;
      glGetIntegerv(pname, &framebuffer_id);
      WebGLFramebuffer* framebuffer = context->IdToFramebuffer(framebuffer_id);
      return ToV8OrNull(framebuffer);
    }

    case GL_RENDERER:
      return TypeToV8<const char*>("v8-webgl");

    case GL_SHADING_LANGUAGE_VERSION: {
      std::string version = std::string("WebGL GLSL ES 1.0 (") + std::string(reinterpret_cast<const char*>(glGetString(pname))) + std::string(")");
      return TypeToV8<const char*>(version.c_str());
    }

    case GL_TEXTURE_BINDING_2D:
    case GL_TEXTURE_BINDING_CUBE_MAP: {
      GLint texture_id = 0;
      glGetIntegerv(pname, &texture_id);
      WebGLTexture* texture = context->IdToTexture(texture_id);
      return ToV8OrNull(texture);
    }

#if 0
    case GL_UNPACK_FLIP_Y_WEBGL:
    case GL_UNPACK_PREMULTIPLY_ALPHA_WEBGL:
    case GL_UNPACK_COLORSPACE_CONVERSION_WEBGL:
      //XXX these are WebGL specific - need to track and store them in our context
#endif

    case GL_VENDOR:
      return TypeToV8<const char*>("rectalogic");

    case GL_VERSION: {
      std::string version = std::string("WebGL 1.0 (") + std::string(reinterpret_cast<const char*>(glGetString(pname))) + std::string(")");
      return TypeToV8<const char*>(version.c_str());
    }

#if 0
    case GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES:
      //XXX used with OES_standard_derivatives extension

    case GL_UNMASKED_RENDERER_WEBGL:
    case GL_UNMASKED_VENDOR_WEBGL:
      //XXX used with WEBGL_debug_renderer_info extension

    case GL_VERTEX_ARRAY_BINDING_OES:
      //XXX used with OES_vertex_array_object extension
#endif

    default: {
      context->set_gl_error(GL_INVALID_ENUM);
      std::stringstream ss;
      ss << "getParameter: Unrecognized parameter name: " << pname;
      Log(Logger::kWarn, ss.str());
      return v8::Undefined();
    }
  }
}

// any getBufferParameter(GLenum target, GLenum pname);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getBufferParameter(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  if (target != GL_ARRAY_BUFFER && target != GL_ELEMENT_ARRAY_BUFFER) {
    context->set_gl_error(GL_INVALID_ENUM);
    return v8::Null();
  }
  GLenum pname = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  if (pname != GL_BUFFER_SIZE && pname != GL_BUFFER_USAGE) {
    context->set_gl_error(GL_INVALID_ENUM);
    return v8::Null();
  }
  GLint value = 0;
  glGetBufferParameteriv(target, pname, &value);
  if (pname == GL_BUFFER_SIZE)
    return TypeToV8<int32_t>(value);
  return TypeToV8<uint32_t>(static_cast<uint32_t>(value));
}

// GLenum getError();
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getError(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  GLenum error = context->get_gl_error();
  return TypeToV8<uint32_t>(error);
}

// any getFramebufferAttachmentParameter(GLenum target, GLenum attachment, 
//                                       GLenum pname);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getFramebufferAttachmentParameter(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 3) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  GLenum attachment = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateFramebufferFuncParameters("getFramebufferAttachmentParameter", target, attachment))
    return v8::Null();
  GLenum pname = V8ToType<uint32_t>(args[2], ok); if (!ok) return v8::Undefined();
  GLint value = 0;
  //XXX glGetFramebufferAttachmentParameterivEXT etc.
  glGetFramebufferAttachmentParameteriv(target, attachment, pname, &value);

  switch (pname) {
    case GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME: {
      GLint type = 0;
      glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &type);
      switch (type) {
        case GL_RENDERBUFFER: {
          WebGLRenderbuffer* renderbuffer = context->IdToRenderbuffer(value);
          return ToV8OrNull(renderbuffer);
        }
        case GL_TEXTURE: {
          WebGLTexture* texture = context->IdToTexture(value);
          return ToV8OrNull(texture);
        }
        default:
          context->set_gl_error(GL_INVALID_ENUM);
          return v8::Null();
      }
    }
    case GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE:
      return TypeToV8<uint32_t>(value);
    case GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL:
    case GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE:
      return TypeToV8<int32_t>(value);
    default:
      context->set_gl_error(GL_INVALID_ENUM);
      return v8::Null();
  }
}

// any getProgramParameter(WebGLProgram program, GLenum pname);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getProgramParameter(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  WebGLProgram* program = V8ToNative<WebGLProgram>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->RequireObject(program)) return v8::Undefined();
  if (!context->ValidateObject(program)) return v8::Undefined();
  GLuint program_id = program ? program->get_webgl_id() : 0;
  GLenum pname = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  GLint value = 0;
  glGetProgramiv(program_id, pname, &value);

  switch (pname) {
    case GL_DELETE_STATUS:
    case GL_VALIDATE_STATUS:
    case GL_LINK_STATUS:
      return TypeToV8<bool>(static_cast<bool>(value));
    case GL_ATTACHED_SHADERS:
    case GL_ACTIVE_ATTRIBUTES:
    case GL_ACTIVE_UNIFORMS:
      return TypeToV8<int32_t>(value);
    default:
      context->set_gl_error(GL_INVALID_ENUM);
      return v8::Null();
  }
}

//XXX should use log from ANGLE
// DOMString getProgramInfoLog(WebGLProgram program);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getProgramInfoLog(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// any getRenderbufferParameter(GLenum target, GLenum pname);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getRenderbufferParameter(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  if (target != GL_RENDERBUFFER) {
    context->set_gl_error(GL_INVALID_ENUM);
    return v8::Null();
  }
  GLenum pname = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  GLint value = 0;
  //XXX glGetRenderbufferParameterivEXT
  glGetRenderbufferParameteriv(target, pname, &value);
  switch (pname) {
    case GL_RENDERBUFFER_INTERNAL_FORMAT:
      return TypeToV8<uint32_t>(static_cast<uint32_t>(value));
    case GL_RENDERBUFFER_WIDTH:
    case GL_RENDERBUFFER_HEIGHT:
    case GL_RENDERBUFFER_RED_SIZE:
    case GL_RENDERBUFFER_GREEN_SIZE:
    case GL_RENDERBUFFER_BLUE_SIZE:
    case GL_RENDERBUFFER_ALPHA_SIZE:
    case GL_RENDERBUFFER_DEPTH_SIZE:
    case GL_RENDERBUFFER_STENCIL_SIZE:
      return TypeToV8<int32_t>(value);
    default:
      context->set_gl_error(GL_INVALID_ENUM);
      return v8::Null();
  }
}

// any getShaderParameter(WebGLShader shader, GLenum pname);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getShaderParameter(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  WebGLShader* shader = V8ToNative<WebGLShader>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->RequireObject(shader)) return v8::Undefined();
  if (!context->ValidateObject(shader)) return v8::Undefined();
  GLuint shader_id = shader ? shader->get_webgl_id() : 0;
  GLenum pname = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  GLint value = 0;
  glGetShaderiv(shader_id, pname, &value);
  switch (pname) {
    case GL_DELETE_STATUS:
    case GL_COMPILE_STATUS:
      return TypeToV8<bool>(static_cast<bool>(value));
    case GL_SHADER_TYPE:
      return TypeToV8<uint32_t>(value);
    default:
      context->set_gl_error(GL_INVALID_ENUM);
      return v8::Null();
  }
}

// DOMString getShaderInfoLog(WebGLShader shader);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getShaderInfoLog(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// DOMString getShaderSource(WebGLShader shader);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getShaderSource(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// any getTexParameter(GLenum target, GLenum pname);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getTexParameter(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateTextureBinding("getTextParameter", target, false))
    return v8::Null();
  GLenum pname = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  switch (pname) {
    case GL_TEXTURE_MAG_FILTER:
    case GL_TEXTURE_MIN_FILTER:
    case GL_TEXTURE_WRAP_S:
    case GL_TEXTURE_WRAP_T:
      break;
    default:
      context->set_gl_error(GL_INVALID_ENUM);
      return v8::Null();
  }
  GLint value = 0;
  glGetTexParameteriv(target, pname, &value);
  return TypeToV8<uint32_t>(static_cast<uint32_t>(value));
}

static bool UniformTypeToBaseLength(GLenum uniform_type, GLenum& uniform_base_type, uint32_t& length) {
  switch (uniform_type) {
    case GL_BOOL:
      uniform_base_type = GL_BOOL;
      length = 1;
      break;
    case GL_BOOL_VEC2:
      uniform_base_type = GL_BOOL;
      length = 2;
      break;
    case GL_BOOL_VEC3:
      uniform_base_type = GL_BOOL;
      length = 3;
      break;
    case GL_BOOL_VEC4:
      uniform_base_type = GL_BOOL;
      length = 4;
      break;
    case GL_INT:
      uniform_base_type = GL_INT;
      length = 1;
      break;
    case GL_INT_VEC2:
      uniform_base_type = GL_INT;
      length = 2;
      break;
    case GL_INT_VEC3:
      uniform_base_type = GL_INT;
      length = 3;
      break;
    case GL_INT_VEC4:
      uniform_base_type = GL_INT;
      length = 4;
      break;
    case GL_FLOAT:
      uniform_base_type = GL_FLOAT;
      length = 1;
      break;
    case GL_FLOAT_VEC2:
      uniform_base_type = GL_FLOAT;
      length = 2;
      break;
    case GL_FLOAT_VEC3:
      uniform_base_type = GL_FLOAT;
      length = 3;
      break;
    case GL_FLOAT_VEC4:
      uniform_base_type = GL_FLOAT;
      length = 4;
      break;
    case GL_FLOAT_MAT2:
      uniform_base_type = GL_FLOAT;
      length = 4;
      break;
    case GL_FLOAT_MAT3:
      uniform_base_type = GL_FLOAT;
      length = 9;
      break;
    case GL_FLOAT_MAT4:
      uniform_base_type = GL_FLOAT;
      length = 16;
      break;
    case GL_SAMPLER_2D:
    case GL_SAMPLER_CUBE:
      uniform_base_type = GL_INT;
      length = 1;
      break;
    default:
      return false;
  }
  return true;
}

// any getUniform(WebGLProgram program, WebGLUniformLocation location);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getUniform(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  WebGLProgram* program = V8ToNative<WebGLProgram>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->RequireObject(program)) return v8::Undefined();
  if (!context->ValidateObject(program)) return v8::Undefined();
  GLuint program_id = program ? program->get_webgl_id() : 0;
  WebGLUniformLocation* location = V8ToNative<WebGLUniformLocation>(args[1], ok); if (!ok) return v8::Undefined();
  if (!context->RequireObject(location)) return v8::Undefined();
  if (!context->ValidateLocationProgram(location, program_id)) return v8::Undefined();
  //XXX need to catch std::bad_alloc from string/vector

  GLint location_id = location ? location->get_webgl_id() : 0;
  GLint active_uniforms = 0;
  glGetProgramiv(program_id, GL_ACTIVE_UNIFORMS, &active_uniforms);
  GLint max_name_length = 0;
  glGetProgramiv(program_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_length);
  std::vector<char> name_vec(max_name_length);
  std::string array_ending("[0]");
  // Search for our location_id
  for (GLint i = 0; i < active_uniforms; i++) {
    GLsizei name_length = 0;
    GLint uniform_size = 0;
    GLenum uniform_type = 0;
    glGetActiveUniform(program_id, i, max_name_length, &name_length,
                       &uniform_size, &uniform_type, &name_vec[0]);
    std::string uniform_name(&name_vec[0], name_length);

    // Strip "[0]" from name ending, if it's an array
    if (uniform_size > 1 && uniform_name.length() > array_ending.length()
        && uniform_name.compare(uniform_name.length() - array_ending.length(),
                                array_ending.length(), array_ending) == 0) {
      uniform_name.resize(uniform_name.length() - 3);
    }

    // For arrays, iterate through each element appending "[index]" to the name
    // and checking location
    for (GLint index = 0; index < uniform_size; index++) {
      std::string name(uniform_name);
      if (uniform_size > 1 && index >= 1) {
        std::stringstream ss(name);
        ss << "[" << index << "]";
        name = ss.str();
      }
      // Look the name up again
      GLint uniform_location_id = glGetUniformLocation(program_id, name.c_str());
      if (uniform_location_id == location_id) {
        GLenum uniform_base_type = 0;
        uint32_t length = 0;
        if (!UniformTypeToBaseLength(uniform_type, uniform_base_type, length)) {
          context->set_gl_error(GL_INVALID_VALUE);
          return v8::Null();
        }

        switch (uniform_base_type) {
          case GL_FLOAT: {
            GLfloat value[16] = {0};
            glGetUniformfv(program_id, location_id, value);
            if (length == 1)
              return TypeToV8<double>(value[0]);
            return Float32Array::Create(value, length);
          }
          case GL_INT: {
            GLint value[4] = {0};
            glGetUniformiv(program_id, location_id, value);
            if (length == 1)
              return TypeToV8<int32_t>(value[0]);
            return Int32Array::Create(value, length);
          }
          case GL_BOOL: {
            GLint value[4] = {0};
            glGetUniformiv(program_id, location_id, value);
            if (length > 1) {
              bool bool_value[4] = {0};
              for (uint32_t j = 0; j < length; j++)
                bool_value[j] = static_cast<bool>(value[j]);
              return ArrayToV8<bool>(bool_value, length);
            }
            return TypeToV8<bool>(static_cast<bool>(value[0]));
          }
        }
      }
    }
  }

  context->set_gl_error(GL_INVALID_VALUE);
  return v8::Null();
}

// WebGLUniformLocation getUniformLocation(WebGLProgram program, DOMString name);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getUniformLocation(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  WebGLProgram* program = V8ToNative<WebGLProgram>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->RequireObject(program)) return v8::Undefined();
  if (!context->ValidateObject(program)) return v8::Undefined();
  GLuint program_id = program ? program->get_webgl_id() : 0;
  std::string name = V8ToType<std::string>(args[1], ok); if (!ok) return v8::Undefined();
  GLint location_id = glGetUniformLocation(program_id, name.c_str());
  WebGLUniformLocation* location = context->CreateUniformLocation(program_id, location_id);
  return location->ToV8();
}

// any getVertexAttrib(GLuint index, GLenum pname);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getVertexAttrib(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  GLuint index = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  GLenum pname = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  switch (pname) {
    case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING: {
      GLint value = 0;
      glGetVertexAttribiv(index, pname, &value);
      WebGLBuffer* buffer = context->IdToBuffer(value);
      return ToV8OrNull(buffer);
    }
    case GL_VERTEX_ATTRIB_ARRAY_ENABLED:
    case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED: {
      GLint value = 0;
      glGetVertexAttribiv(index, pname, &value);
      return TypeToV8<bool>(static_cast<bool>(value));
    }
    case GL_VERTEX_ATTRIB_ARRAY_SIZE:
    case GL_VERTEX_ATTRIB_ARRAY_STRIDE: {
      GLint value = 0;
      glGetVertexAttribiv(index, pname, &value);
      return TypeToV8<int32_t>(value);
    }
    case GL_VERTEX_ATTRIB_ARRAY_TYPE: {
      GLint value = 0;
      glGetVertexAttribiv(index, pname, &value);
      return TypeToV8<uint32_t>(static_cast<uint32_t>(value));
    }
    case GL_CURRENT_VERTEX_ATTRIB: {
      GLfloat value[4] = {0};
      glGetVertexAttribfv(index, pname, value);
      return Float32Array::Create(value, 4);
    }
    default:
      context->set_gl_error(GL_INVALID_ENUM);
      return v8::Null();
  }
}

// GLsizeiptr getVertexAttribOffset(GLuint index, GLenum pname);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_getVertexAttribOffset(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  GLuint index = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  GLenum pname = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  GLvoid* pointer = 0;
  glGetVertexAttribPointerv(index, pname, &pointer);
  return TypeToV8<int32_t>(static_cast<GLsizeiptr>(reinterpret_cast<intptr_t>(pointer)));
}

// void hint(GLenum target, GLenum mode);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_hint(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  //XXX nedd to handle GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES when we support extensions
  if (target != GL_GENERATE_MIPMAP_HINT) {
    context->set_gl_error(GL_INVALID_ENUM);
    return v8::Undefined();
  }
  GLenum mode = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  glHint(target, mode);
  return v8::Undefined();
}

// GLboolean isBuffer(WebGLBuffer buffer);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_isBuffer(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  WebGLBuffer* buffer = V8ToNative<WebGLBuffer>(args[0], ok); if (!ok) return v8::Undefined();
  if (!buffer)
    return TypeToV8<bool>(false);
  GLuint buffer_id = buffer ? buffer->get_webgl_id() : 0;
  return TypeToV8<bool>(glIsBuffer(buffer_id));
}

// GLboolean isEnabled(GLenum cap);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_isEnabled(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLenum cap = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateCapability("isEnabled", cap))
    return TypeToV8<bool>(false);
  glIsEnabled(cap);
  return v8::Undefined();
}

// GLboolean isFramebuffer(WebGLFramebuffer framebuffer);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_isFramebuffer(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  WebGLFramebuffer* framebuffer = V8ToNative<WebGLFramebuffer>(args[0], ok); if (!ok) return v8::Undefined();
  if (!framebuffer)
    return TypeToV8<bool>(false);
  GLuint framebuffer_id = framebuffer ? framebuffer->get_webgl_id() : 0;
  return TypeToV8<bool>(glIsFramebuffer(framebuffer_id));
}

// GLboolean isProgram(WebGLProgram program);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_isProgram(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  WebGLProgram* program = V8ToNative<WebGLProgram>(args[0], ok); if (!ok) return v8::Undefined();
  if (!program)
    return TypeToV8<bool>(false);
  GLuint program_id = program ? program->get_webgl_id() : 0;
  return TypeToV8<bool>(glIsProgram(program_id));
}

// GLboolean isRenderbuffer(WebGLRenderbuffer renderbuffer);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_isRenderbuffer(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  WebGLRenderbuffer* renderbuffer = V8ToNative<WebGLRenderbuffer>(args[0], ok); if (!ok) return v8::Undefined();
  if (!renderbuffer)
    return TypeToV8<bool>(false);
  GLuint renderbuffer_id = renderbuffer ? renderbuffer->get_webgl_id() : 0;
  return TypeToV8<bool>(glIsRenderbuffer(renderbuffer_id));
}

// GLboolean isShader(WebGLShader shader);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_isShader(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  WebGLShader* shader = V8ToNative<WebGLShader>(args[0], ok); if (!ok) return v8::Undefined();
  if (!shader)
    return TypeToV8<bool>(false);
  GLuint shader_id = shader ? shader->get_webgl_id() : 0;
  return TypeToV8<bool>(glIsShader(shader_id));
}

// GLboolean isTexture(WebGLTexture texture);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_isTexture(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  WebGLTexture* texture = V8ToNative<WebGLTexture>(args[0], ok); if (!ok) return v8::Undefined();
  if (!texture)
    return TypeToV8<bool>(false);
  GLuint texture_id = texture ? texture->get_webgl_id() : 0;
  return TypeToV8<bool>(glIsTexture(texture_id));
}

// void lineWidth(GLfloat width);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_lineWidth(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLfloat width = V8ToType<float>(args[0], ok); if (!ok) return v8::Undefined();
  glLineWidth(width);
  return v8::Undefined();
}

// void linkProgram(WebGLProgram program);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_linkProgram(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  WebGLProgram* program = V8ToNative<WebGLProgram>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->RequireObject(program)) return v8::Undefined();
  if (!context->ValidateObject(program)) return v8::Undefined();
  GLuint program_id = program ? program->get_webgl_id() : 0;
  glLinkProgram(program_id);
  return v8::Undefined();
}

//XXX this needs to deal with custom WebGL attrs like UNPACK_FLIP_Y_WEBGL
// void pixelStorei(GLenum pname, GLint param);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_pixelStorei(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void polygonOffset(GLfloat factor, GLfloat units);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_polygonOffset(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  GLfloat factor = V8ToType<float>(args[0], ok); if (!ok) return v8::Undefined();
  GLfloat units = V8ToType<float>(args[1], ok); if (!ok) return v8::Undefined();
  glPolygonOffset(factor, units);
  return v8::Undefined();
}

// void readPixels(GLint x, GLint y, GLsizei width, GLsizei height, 
//                 GLenum format, GLenum type, ArrayBufferView pixels);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_readPixels(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 7) return ThrowArgCount();
  GLint x = V8ToType<int32_t>(args[0], ok); if (!ok) return v8::Undefined();
  GLint y = V8ToType<int32_t>(args[1], ok); if (!ok) return v8::Undefined();
  GLsizei width = V8ToType<int32_t>(args[2], ok); if (!ok) return v8::Undefined();
  GLsizei height = V8ToType<int32_t>(args[3], ok); if (!ok) return v8::Undefined();
  GLenum format = V8ToType<uint32_t>(args[4], ok); if (!ok) return v8::Undefined();
  GLenum type = V8ToType<uint32_t>(args[5], ok); if (!ok) return v8::Undefined();
  if (format != GL_RGBA || type != GL_UNSIGNED_BYTE) {
    context->set_gl_error(GL_INVALID_OPERATION);
    return v8::Undefined();
  }
  Uint8Array* array = V8ToNative<Uint8Array>(args[6], ok); if (!ok) return v8::Undefined();
  if (!context->RequireObject(array)) return v8::Undefined();

  GLint alignment = 4;
  glGetIntegerv(GL_PACK_ALIGNMENT, &alignment);
  // GL_RGBA is 4 bytes per pixel
  uint32_t row_bytes = width * 4;
  if (row_bytes % alignment != 0)
    row_bytes = row_bytes + (alignment - (row_bytes % alignment));

  uint32_t length_required = row_bytes * height;
  uint32_t length = array->GetArrayLength();
  if (length < length_required) {
    context->set_gl_error(GL_INVALID_OPERATION);
    return v8::Undefined();
  }

  void* data = array->GetArrayData();
  glReadPixels(x, y, width, height, format, type, data);

  return v8::Undefined();
}

// void renderbufferStorage(GLenum target, GLenum internalformat, 
//                          GLsizei width, GLsizei height);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_renderbufferStorage(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 4) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  GLenum internalformat = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  GLsizei width = V8ToType<int32_t>(args[2], ok); if (!ok) return v8::Undefined();
  GLsizei height = V8ToType<int32_t>(args[3], ok); if (!ok) return v8::Undefined();
  if (target != GL_RENDERBUFFER) {
    context->set_gl_error(GL_INVALID_ENUM);
    return v8::Undefined();
  }
  //XXX some of these formats may not be supported on desktop GL - so we convert them (see GraphicsContext3DOpenGL.cpp:renderbufferStorage
  //XXX this means getRenderbufferParameter will return the wrong value - we should really stash the original value in the bound WebGLRenderbuffer
  //XXX http://www.khronos.org/webgl/public-mailing-list/archives/1010/msg00123.html
  switch (internalformat) {
    case GL_DEPTH_STENCIL:
      internalformat = GL_DEPTH24_STENCIL8;
      break;
    case GL_DEPTH_COMPONENT16:
      internalformat = GL_DEPTH_COMPONENT;
      break;
    case GL_RGBA4:
    case GL_RGB5_A1:
      internalformat = GL_RGBA;
      break;
    case GL_RGB565:
      internalformat = GL_RGB;
      break;
    case GL_STENCIL_INDEX8:
      break;
    default:
      context->set_gl_error(GL_INVALID_ENUM);
      return v8::Undefined();
  }

  glRenderbufferStorage(target, internalformat, width, height);
  return v8::Undefined();
}

// void sampleCoverage(GLclampf value, GLboolean invert);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_sampleCoverage(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  GLclampf value = V8ToType<float>(args[0], ok); if (!ok) return v8::Undefined();
  GLboolean invert = V8ToType<bool>(args[1], ok); if (!ok) return v8::Undefined();
  glSampleCoverage(value, invert);
  return v8::Undefined();
}

// void scissor(GLint x, GLint y, GLsizei width, GLsizei height);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_scissor(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 4) return ThrowArgCount();
  GLint x = V8ToType<int32_t>(args[0], ok); if (!ok) return v8::Undefined();
  GLint y = V8ToType<int32_t>(args[1], ok); if (!ok) return v8::Undefined();
  GLsizei width = V8ToType<int32_t>(args[2], ok); if (!ok) return v8::Undefined();
  GLsizei height = V8ToType<int32_t>(args[3], ok); if (!ok) return v8::Undefined();
  glScissor(x, y, width, height);
  return v8::Undefined();
}

//XXX stash this in shader for use with ANGLE when compiling?
// void shaderSource(WebGLShader shader, DOMString source);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_shaderSource(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void stencilFunc(GLenum func, GLint ref, GLuint mask);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_stencilFunc(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 3) return ThrowArgCount();
  GLenum func = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateStencilFunc("stencilFunc", func))
    return v8::Undefined();
  GLint ref = V8ToType<int32_t>(args[1], ok); if (!ok) return v8::Undefined();
  GLuint mask = V8ToType<uint32_t>(args[2], ok); if (!ok) return v8::Undefined();
  glStencilFunc(func, ref, mask);
  return v8::Undefined();
}

// void stencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_stencilFuncSeparate(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 4) return ThrowArgCount();
  GLenum face = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  switch (face) {
    case GL_FRONT_AND_BACK:
    case GL_FRONT:
    case GL_BACK:
      break;
    default:
      context->set_gl_error(GL_INVALID_ENUM);
      return v8::Undefined();
  }
  GLenum func = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateStencilFunc("stencilFuncSeparate", func))
    return v8::Undefined();
  GLint ref = V8ToType<int32_t>(args[2], ok); if (!ok) return v8::Undefined();
  GLuint mask = V8ToType<uint32_t>(args[3], ok); if (!ok) return v8::Undefined();
  glStencilFuncSeparate(face, func, ref, mask);
  return v8::Undefined();
}

// void stencilMask(GLuint mask);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_stencilMask(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 1) return ThrowArgCount();
  GLuint mask = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  glStencilMask(mask);
  return v8::Undefined();
}

// void stencilMaskSeparate(GLenum face, GLuint mask);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_stencilMaskSeparate(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 2) return ThrowArgCount();
  GLenum face = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  switch (face) {
    case GL_FRONT_AND_BACK:
    case GL_FRONT:
    case GL_BACK:
      break;
    default:
      context->set_gl_error(GL_INVALID_ENUM);
      return v8::Undefined();
  }
  GLuint mask = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  glStencilMaskSeparate(face, mask);
  return v8::Undefined();
}

// void stencilOp(GLenum fail, GLenum zfail, GLenum zpass);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_stencilOp(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 3) return ThrowArgCount();
  GLenum fail = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  GLenum zfail = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  GLenum zpass = V8ToType<uint32_t>(args[2], ok); if (!ok) return v8::Undefined();
  glStencilOp(fail, zfail, zpass);
  return v8::Undefined();
}

// void stencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_stencilOpSeparate(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 4) return ThrowArgCount();
  GLenum face = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  GLenum fail = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  GLenum zfail = V8ToType<uint32_t>(args[2], ok); if (!ok) return v8::Undefined();
  GLenum zpass = V8ToType<uint32_t>(args[3], ok); if (!ok) return v8::Undefined();
  glStencilOpSeparate(face, fail, zfail, zpass);
  return v8::Undefined();
}

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
v8::Handle<v8::Value> WebGLRenderingContext::Callback_texImage2D(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void texParameterf(GLenum target, GLenum pname, GLfloat param);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_texParameterf(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 3) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateTextureBinding("texParameterf", target, false))
    return v8::Undefined();
  GLenum pname = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  GLfloat param = V8ToType<float>(args[2], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateTexParameter("texParameterf", pname, static_cast<GLint>(param)))
    return v8::Undefined();
  glTexParameterf(target, pname, param);
  return v8::Undefined();
}

// void texParameteri(GLenum target, GLenum pname, GLint param);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_texParameteri(const v8::Arguments& args) {
  bool ok = true;
  WebGLRenderingContext* context = CallbackContext(args); if (!context) return ThrowObjectDisposed();
  if (args.Length() < 3) return ThrowArgCount();
  GLenum target = V8ToType<uint32_t>(args[0], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateTextureBinding("texParameteri", target, false))
    return v8::Undefined();
  GLenum pname = V8ToType<uint32_t>(args[1], ok); if (!ok) return v8::Undefined();
  GLint param = V8ToType<int32_t>(args[2], ok); if (!ok) return v8::Undefined();
  if (!context->ValidateTexParameter("texParameteri", pname, param))
    return v8::Undefined();
  glTexParameteri(target, pname, param);
  return v8::Undefined();
}

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
v8::Handle<v8::Value> WebGLRenderingContext::Callback_texSubImage2D(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform1f(WebGLUniformLocation location, GLfloat x);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniform1f(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform1fv(WebGLUniformLocation location, FloatArray v);
// void uniform1fv(WebGLUniformLocation location, sequence<float> v);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniform1fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform1i(WebGLUniformLocation location, GLint x);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniform1i(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform1iv(WebGLUniformLocation location, Int32Array v);
// void uniform1iv(WebGLUniformLocation location, sequence<long> v);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniform1iv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform2f(WebGLUniformLocation location, GLfloat x, GLfloat y);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniform2f(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform2fv(WebGLUniformLocation location, FloatArray v);
// void uniform2fv(WebGLUniformLocation location, sequence<float> v);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniform2fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform2i(WebGLUniformLocation location, GLint x, GLint y);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniform2i(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform2iv(WebGLUniformLocation location, Int32Array v);
// void uniform2iv(WebGLUniformLocation location, sequence<long> v);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniform2iv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform3f(WebGLUniformLocation location, GLfloat x, GLfloat y, GLfloat z);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniform3f(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform3fv(WebGLUniformLocation location, FloatArray v);
// void uniform3fv(WebGLUniformLocation location, sequence<float> v);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniform3fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform3i(WebGLUniformLocation location, GLint x, GLint y, GLint z);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniform3i(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform3iv(WebGLUniformLocation location, Int32Array v);
// void uniform3iv(WebGLUniformLocation location, sequence<long> v);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniform3iv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform4f(WebGLUniformLocation location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniform4f(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform4fv(WebGLUniformLocation location, FloatArray v);
// void uniform4fv(WebGLUniformLocation location, sequence<float> v);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniform4fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform4i(WebGLUniformLocation location, GLint x, GLint y, GLint z, GLint w);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniform4i(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniform4iv(WebGLUniformLocation location, Int32Array v);
// void uniform4iv(WebGLUniformLocation location, sequence<long> v);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniform4iv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniformMatrix2fv(WebGLUniformLocation location, GLboolean transpose, 
//                       FloatArray value);
// void uniformMatrix2fv(WebGLUniformLocation location, GLboolean transpose, 
//                       sequence<float> value);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniformMatrix2fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniformMatrix3fv(WebGLUniformLocation location, GLboolean transpose, 
//                       FloatArray value);
// void uniformMatrix3fv(WebGLUniformLocation location, GLboolean transpose, 
//                       sequence<float> value);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniformMatrix3fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void uniformMatrix4fv(WebGLUniformLocation location, GLboolean transpose, 
//                       FloatArray value);
// void uniformMatrix4fv(WebGLUniformLocation location, GLboolean transpose, 
//                       sequence<float> value);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_uniformMatrix4fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void useProgram(WebGLProgram program);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_useProgram(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void validateProgram(WebGLProgram program);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_validateProgram(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void vertexAttrib1f(GLuint indx, GLfloat x);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_vertexAttrib1f(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void vertexAttrib1fv(GLuint indx, FloatArray values);
// void vertexAttrib1fv(GLuint indx, sequence<float> values);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_vertexAttrib1fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void vertexAttrib2f(GLuint indx, GLfloat x, GLfloat y);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_vertexAttrib2f(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void vertexAttrib2fv(GLuint indx, FloatArray values);
// void vertexAttrib2fv(GLuint indx, sequence<float> values);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_vertexAttrib2fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void vertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_vertexAttrib3f(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void vertexAttrib3fv(GLuint indx, FloatArray values);
// void vertexAttrib3fv(GLuint indx, sequence<float> values);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_vertexAttrib3fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void vertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_vertexAttrib4f(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void vertexAttrib4fv(GLuint indx, FloatArray values);
// void vertexAttrib4fv(GLuint indx, sequence<float> values);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_vertexAttrib4fv(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void vertexAttribPointer(GLuint indx, GLint size, GLenum type, 
//                          GLboolean normalized, GLsizei stride, GLintptr offset);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_vertexAttribPointer(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

// void viewport(GLint x, GLint y, GLsizei width, GLsizei height);
v8::Handle<v8::Value> WebGLRenderingContext::Callback_viewport(const v8::Arguments& args) { return v8::Undefined(); /*XXX finish*/ }

}
