// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "V8Binding.h"
#include "WebGLRenderingContext.h"

namespace V8WebGL {

// WebGLContextAttributes getContextAttributes();
static v8::Handle<v8::Value> getContextAttributesCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// boolean isContextLost();
static v8::Handle<v8::Value> isContextLostCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// DOMString[ ] getSupportedExtensions();
static v8::Handle<v8::Value> getSupportedExtensionsCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// object getExtension(DOMString name);
static v8::Handle<v8::Value> getExtensionCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void activeTexture(GLenum texture);
static v8::Handle<v8::Value> activeTextureCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void attachShader(WebGLProgram program, WebGLShader shader);
static v8::Handle<v8::Value> attachShaderCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void bindAttribLocation(WebGLProgram program, GLuint index, DOMString name);
static v8::Handle<v8::Value> bindAttribLocationCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void bindBuffer(GLenum target, WebGLBuffer buffer);
static v8::Handle<v8::Value> bindBufferCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void bindFramebuffer(GLenum target, WebGLFramebuffer framebuffer);
static v8::Handle<v8::Value> bindFramebufferCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void bindRenderbuffer(GLenum target, WebGLRenderbuffer renderbuffer);
static v8::Handle<v8::Value> bindRenderbufferCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void bindTexture(GLenum target, WebGLTexture texture);
static v8::Handle<v8::Value> bindTextureCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void blendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
static v8::Handle<v8::Value> blendColorCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void blendEquation(GLenum mode);
static v8::Handle<v8::Value> blendEquationCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void blendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
static v8::Handle<v8::Value> blendEquationSeparateCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void blendFunc(GLenum sfactor, GLenum dfactor);
static v8::Handle<v8::Value> blendFuncCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void blendFuncSeparate(GLenum srcRGB, GLenum dstRGB, 
//                        GLenum srcAlpha, GLenum dstAlpha);
static v8::Handle<v8::Value> blendFuncSeparateCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void bufferData(GLenum target, GLsizeiptr size, GLenum usage);
// void bufferData(GLenum target, ArrayBufferView data, GLenum usage);
// void bufferData(GLenum target, ArrayBuffer data, GLenum usage);
static v8::Handle<v8::Value> bufferDataCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void bufferSubData(GLenum target, GLintptr offset, ArrayBufferView data);
// void bufferSubData(GLenum target, GLintptr offset, ArrayBuffer data);
static v8::Handle<v8::Value> bufferSubDataCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// GLenum checkFramebufferStatus(GLenum target);
static v8::Handle<v8::Value> checkFramebufferStatusCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void clear(GLbitfield mask);
static v8::Handle<v8::Value> clearCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
static v8::Handle<v8::Value> clearColorCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void clearDepth(GLclampf depth);
static v8::Handle<v8::Value> clearDepthCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void clearStencil(GLint s);
static v8::Handle<v8::Value> clearStencilCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
static v8::Handle<v8::Value> colorMaskCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void compileShader(WebGLShader shader);
static v8::Handle<v8::Value> compileShaderCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void copyTexImage2D(GLenum target, GLint level, GLenum internalformat, 
//                     GLint x, GLint y, GLsizei width, GLsizei height, 
//                     GLint border);
static v8::Handle<v8::Value> copyTexImage2DCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void copyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, 
//                        GLint x, GLint y, GLsizei width, GLsizei height);
static v8::Handle<v8::Value> copyTexSubImage2DCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// WebGLBuffer createBuffer();
static v8::Handle<v8::Value> createBufferCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// WebGLFramebuffer createFramebuffer();
static v8::Handle<v8::Value> createFramebufferCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// WebGLProgram createProgram();
static v8::Handle<v8::Value> createProgramCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// WebGLRenderbuffer createRenderbuffer();
static v8::Handle<v8::Value> createRenderbufferCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// WebGLShader createShader(GLenum type);
static v8::Handle<v8::Value> createShaderCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// WebGLTexture createTexture();
static v8::Handle<v8::Value> createTextureCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void cullFace(GLenum mode);
static v8::Handle<v8::Value> cullFaceCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void deleteBuffer(WebGLBuffer buffer);
static v8::Handle<v8::Value> deleteBufferCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void deleteFramebuffer(WebGLFramebuffer framebuffer);
static v8::Handle<v8::Value> deleteFramebufferCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void deleteProgram(WebGLProgram program);
static v8::Handle<v8::Value> deleteProgramCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void deleteRenderbuffer(WebGLRenderbuffer renderbuffer);
static v8::Handle<v8::Value> deleteRenderbufferCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void deleteShader(WebGLShader shader);
static v8::Handle<v8::Value> deleteShaderCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void deleteTexture(WebGLTexture texture);
static v8::Handle<v8::Value> deleteTextureCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void depthFunc(GLenum func);
static v8::Handle<v8::Value> depthFuncCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void depthMask(GLboolean flag);
static v8::Handle<v8::Value> depthMaskCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void depthRange(GLclampf zNear, GLclampf zFar);
static v8::Handle<v8::Value> depthRangeCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void detachShader(WebGLProgram program, WebGLShader shader);
static v8::Handle<v8::Value> detachShaderCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void disable(GLenum cap);
static v8::Handle<v8::Value> disableCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void disableVertexAttribArray(GLuint index);
static v8::Handle<v8::Value> disableVertexAttribArrayCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void drawArrays(GLenum mode, GLint first, GLsizei count);
static v8::Handle<v8::Value> drawArraysCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void drawElements(GLenum mode, GLsizei count, GLenum type, GLintptr offset);
static v8::Handle<v8::Value> drawElementsCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void enable(GLenum cap);
static v8::Handle<v8::Value> enableCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void enableVertexAttribArray(GLuint index);
static v8::Handle<v8::Value> enableVertexAttribArrayCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void finish();
static v8::Handle<v8::Value> finishCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void flush();
static v8::Handle<v8::Value> flushCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void framebufferRenderbuffer(GLenum target, GLenum attachment, 
//                              GLenum renderbuffertarget, 
//                              WebGLRenderbuffer renderbuffer);
static v8::Handle<v8::Value> framebufferRenderbufferCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void framebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, 
//                           WebGLTexture texture, GLint level);
static v8::Handle<v8::Value> framebufferTexture2DCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void frontFace(GLenum mode);
static v8::Handle<v8::Value> frontFaceCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void generateMipmap(GLenum target);
static v8::Handle<v8::Value> generateMipmapCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// WebGLActiveInfo getActiveAttrib(WebGLProgram program, GLuint index);
static v8::Handle<v8::Value> getActiveAttribCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// WebGLActiveInfo getActiveUniform(WebGLProgram program, GLuint index);
static v8::Handle<v8::Value> getActiveUniformCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// WebGLShader[ ] getAttachedShaders(WebGLProgram program);
static v8::Handle<v8::Value> getAttachedShadersCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// GLint getAttribLocation(WebGLProgram program, DOMString name);
static v8::Handle<v8::Value> getAttribLocationCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// any getParameter(GLenum pname);
static v8::Handle<v8::Value> getParameterCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// any getBufferParameter(GLenum target, GLenum pname);
static v8::Handle<v8::Value> getBufferParameterCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// GLenum getError();
static v8::Handle<v8::Value> getErrorCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// any getFramebufferAttachmentParameter(GLenum target, GLenum attachment, 
//                                       GLenum pname);
static v8::Handle<v8::Value> getFramebufferAttachmentParameterCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// any getProgramParameter(WebGLProgram program, GLenum pname);
static v8::Handle<v8::Value> getProgramParameterCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// DOMString getProgramInfoLog(WebGLProgram program);
static v8::Handle<v8::Value> getProgramInfoLogCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// any getRenderbufferParameter(GLenum target, GLenum pname);
static v8::Handle<v8::Value> getRenderbufferParameterCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// any getShaderParameter(WebGLShader shader, GLenum pname);
static v8::Handle<v8::Value> getShaderParameterCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// DOMString getShaderInfoLog(WebGLShader shader);
static v8::Handle<v8::Value> getShaderInfoLogCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// DOMString getShaderSource(WebGLShader shader);
static v8::Handle<v8::Value> getShaderSourceCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// any getTexParameter(GLenum target, GLenum pname);
static v8::Handle<v8::Value> getTexParameterCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// any getUniform(WebGLProgram program, WebGLUniformLocation location);
static v8::Handle<v8::Value> getUniformCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// WebGLUniformLocation getUniformLocation(WebGLProgram program, DOMString name);
static v8::Handle<v8::Value> getUniformLocationCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// any getVertexAttrib(GLuint index, GLenum pname);
static v8::Handle<v8::Value> getVertexAttribCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// GLsizeiptr getVertexAttribOffset(GLuint index, GLenum pname);
static v8::Handle<v8::Value> getVertexAttribOffsetCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void hint(GLenum target, GLenum mode);
static v8::Handle<v8::Value> hintCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// GLboolean isBuffer(WebGLBuffer buffer);
static v8::Handle<v8::Value> isBufferCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// GLboolean isEnabled(GLenum cap);
static v8::Handle<v8::Value> isEnabledCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// GLboolean isFramebuffer(WebGLFramebuffer framebuffer);
static v8::Handle<v8::Value> isFramebufferCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// GLboolean isProgram(WebGLProgram program);
static v8::Handle<v8::Value> isProgramCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// GLboolean isRenderbuffer(WebGLRenderbuffer renderbuffer);
static v8::Handle<v8::Value> isRenderbufferCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// GLboolean isShader(WebGLShader shader);
static v8::Handle<v8::Value> isShaderCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// GLboolean isTexture(WebGLTexture texture);
static v8::Handle<v8::Value> isTextureCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void lineWidth(GLfloat width);
static v8::Handle<v8::Value> lineWidthCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void linkProgram(WebGLProgram program);
static v8::Handle<v8::Value> linkProgramCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void pixelStorei(GLenum pname, GLint param);
static v8::Handle<v8::Value> pixelStoreiCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void polygonOffset(GLfloat factor, GLfloat units);
static v8::Handle<v8::Value> polygonOffsetCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void readPixels(GLint x, GLint y, GLsizei width, GLsizei height, 
//                 GLenum format, GLenum type, ArrayBufferView pixels);
static v8::Handle<v8::Value> readPixelsCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void renderbufferStorage(GLenum target, GLenum internalformat, 
//                          GLsizei width, GLsizei height);
static v8::Handle<v8::Value> renderbufferStorageCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void sampleCoverage(GLclampf value, GLboolean invert);
static v8::Handle<v8::Value> sampleCoverageCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void scissor(GLint x, GLint y, GLsizei width, GLsizei height);
static v8::Handle<v8::Value> scissorCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void shaderSource(WebGLShader shader, DOMString source);
static v8::Handle<v8::Value> shaderSourceCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void stencilFunc(GLenum func, GLint ref, GLuint mask);
static v8::Handle<v8::Value> stencilFuncCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void stencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
static v8::Handle<v8::Value> stencilFuncSeparateCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void stencilMask(GLuint mask);
static v8::Handle<v8::Value> stencilMaskCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void stencilMaskSeparate(GLenum face, GLuint mask);
static v8::Handle<v8::Value> stencilMaskSeparateCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void stencilOp(GLenum fail, GLenum zfail, GLenum zpass);
static v8::Handle<v8::Value> stencilOpCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void stencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass);
static v8::Handle<v8::Value> stencilOpSeparateCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

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
static v8::Handle<v8::Value> texImage2DCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void texParameterf(GLenum target, GLenum pname, GLfloat param);
static v8::Handle<v8::Value> texParameterfCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void texParameteri(GLenum target, GLenum pname, GLint param);
static v8::Handle<v8::Value> texParameteriCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

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
static v8::Handle<v8::Value> texSubImage2DCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniform1f(WebGLUniformLocation location, GLfloat x);
static v8::Handle<v8::Value> uniform1fCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniform1fv(WebGLUniformLocation location, FloatArray v);
// void uniform1fv(WebGLUniformLocation location, sequence<float> v);
static v8::Handle<v8::Value> uniform1fvCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniform1i(WebGLUniformLocation location, GLint x);
static v8::Handle<v8::Value> uniform1iCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniform1iv(WebGLUniformLocation location, Int32Array v);
// void uniform1iv(WebGLUniformLocation location, sequence<long> v);
static v8::Handle<v8::Value> uniform1ivCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniform2f(WebGLUniformLocation location, GLfloat x, GLfloat y);
static v8::Handle<v8::Value> uniform2fCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniform2fv(WebGLUniformLocation location, FloatArray v);
// void uniform2fv(WebGLUniformLocation location, sequence<float> v);
static v8::Handle<v8::Value> uniform2fvCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniform2i(WebGLUniformLocation location, GLint x, GLint y);
static v8::Handle<v8::Value> uniform2iCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniform2iv(WebGLUniformLocation location, Int32Array v);
// void uniform2iv(WebGLUniformLocation location, sequence<long> v);
static v8::Handle<v8::Value> uniform2ivCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniform3f(WebGLUniformLocation location, GLfloat x, GLfloat y, GLfloat z);
static v8::Handle<v8::Value> uniform3fCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniform3fv(WebGLUniformLocation location, FloatArray v);
// void uniform3fv(WebGLUniformLocation location, sequence<float> v);
static v8::Handle<v8::Value> uniform3fvCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniform3i(WebGLUniformLocation location, GLint x, GLint y, GLint z);
static v8::Handle<v8::Value> uniform3iCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniform3iv(WebGLUniformLocation location, Int32Array v);
// void uniform3iv(WebGLUniformLocation location, sequence<long> v);
static v8::Handle<v8::Value> uniform3ivCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniform4f(WebGLUniformLocation location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
static v8::Handle<v8::Value> uniform4fCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniform4fv(WebGLUniformLocation location, FloatArray v);
// void uniform4fv(WebGLUniformLocation location, sequence<float> v);
static v8::Handle<v8::Value> uniform4fvCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniform4i(WebGLUniformLocation location, GLint x, GLint y, GLint z, GLint w);
static v8::Handle<v8::Value> uniform4iCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniform4iv(WebGLUniformLocation location, Int32Array v);
// void uniform4iv(WebGLUniformLocation location, sequence<long> v);
static v8::Handle<v8::Value> uniform4ivCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniformMatrix2fv(WebGLUniformLocation location, GLboolean transpose, 
//                       FloatArray value);
// void uniformMatrix2fv(WebGLUniformLocation location, GLboolean transpose, 
//                       sequence<float> value);
static v8::Handle<v8::Value> uniformMatrix2fvCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniformMatrix3fv(WebGLUniformLocation location, GLboolean transpose, 
//                       FloatArray value);
// void uniformMatrix3fv(WebGLUniformLocation location, GLboolean transpose, 
//                       sequence<float> value);
static v8::Handle<v8::Value> uniformMatrix3fvCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void uniformMatrix4fv(WebGLUniformLocation location, GLboolean transpose, 
//                       FloatArray value);
// void uniformMatrix4fv(WebGLUniformLocation location, GLboolean transpose, 
//                       sequence<float> value);
static v8::Handle<v8::Value> uniformMatrix4fvCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void useProgram(WebGLProgram program);
static v8::Handle<v8::Value> useProgramCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void validateProgram(WebGLProgram program);
static v8::Handle<v8::Value> validateProgramCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void vertexAttrib1f(GLuint indx, GLfloat x);
static v8::Handle<v8::Value> vertexAttrib1fCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void vertexAttrib1fv(GLuint indx, FloatArray values);
// void vertexAttrib1fv(GLuint indx, sequence<float> values);
static v8::Handle<v8::Value> vertexAttrib1fvCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void vertexAttrib2f(GLuint indx, GLfloat x, GLfloat y);
static v8::Handle<v8::Value> vertexAttrib2fCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void vertexAttrib2fv(GLuint indx, FloatArray values);
// void vertexAttrib2fv(GLuint indx, sequence<float> values);
static v8::Handle<v8::Value> vertexAttrib2fvCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void vertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z);
static v8::Handle<v8::Value> vertexAttrib3fCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void vertexAttrib3fv(GLuint indx, FloatArray values);
// void vertexAttrib3fv(GLuint indx, sequence<float> values);
static v8::Handle<v8::Value> vertexAttrib3fvCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void vertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
static v8::Handle<v8::Value> vertexAttrib4fCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void vertexAttrib4fv(GLuint indx, FloatArray values);
// void vertexAttrib4fv(GLuint indx, sequence<float> values);
static v8::Handle<v8::Value> vertexAttrib4fvCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void vertexAttribPointer(GLuint indx, GLint size, GLenum type, 
//                          GLboolean normalized, GLsizei stride, GLintptr offset);
static v8::Handle<v8::Value> vertexAttribPointerCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }

// void viewport(GLint x, GLint y, GLsizei width, GLsizei height);
static v8::Handle<v8::Value> viewportCallback(const v8::Arguments& args) { return v8::Handle<v8::Value>(); }


inline static void setConstant(const char* name, int value, v8::Handle<v8::ObjectTemplate> proto, v8::Handle<v8::FunctionTemplate> constructor)
{
    v8::Handle<v8::String> nameHandle = v8::String::New(name);
    v8::Handle<v8::Integer> valueHandle = v8::Integer::New(value);
    constructor->Set(nameHandle, valueHandle, v8::ReadOnly);
    proto->Set(nameHandle, valueHandle, v8::ReadOnly);
}

#define PROTO_METHOD(name) addCallback(proto, #name, name##Callback, signature)

#define CONSTANT(name, value) setConstant(#name, value, proto, constructor)

void WebGLRenderingContext::configureConstructorTemplate(v8::Persistent<v8::FunctionTemplate> constructor)
{
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
