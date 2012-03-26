// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "v8_webgl_internal.h"
#include "v8_binding.h"
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

namespace v8_webgl {

unsigned long WebGLRenderingContext::s_context_counter = 0;

#define PROTO_METHOD(name) AddCallback(proto, #name, WebGLRenderingContext::Callback_##name, signature)
#define CONSTANT(name, value) AddConstant(#name, TypeToV8<int32_t>(value), proto, constructor)
#define WEBGL_ID(object)                                        \
  object ? object->get_webgl_object()->get_webgl_id() : 0


WebGLRenderingContext::WebGLRenderingContext(int width, int height)
    : V8Object<WebGLRenderingContext>()
    , graphic_context_(GetFactory()->CreateGraphicContext(width, height))
    , context_id_(s_context_counter++)
    , gl_error_(GL_NONE) {
}

WebGLRenderingContext::~WebGLRenderingContext() {
  DeleteMapObjects(buffer_map_);
  DeleteMapObjects(framebuffer_map_);
  DeleteMapObjects(program_map_);
  DeleteMapObjects(renderbuffer_map_);
  DeleteMapObjects(shader_map_);
  DeleteMapObjects(texture_map_);

  delete graphic_context_;
}

WebGLActiveInfo* WebGLRenderingContext::CreateActiveInfo() {
  return new WebGLActiveInfo(this);
}

WebGLBuffer* WebGLRenderingContext::CreateBuffer(GLuint buffer_id) {
  WebGLBuffer* buffer = new WebGLBuffer(this, buffer_id);
  buffer_map_[buffer_id] = buffer;
  return buffer;
}

WebGLFramebuffer* WebGLRenderingContext::CreateFramebuffer(GLuint framebuffer_id) {
  WebGLFramebuffer* framebuffer = new WebGLFramebuffer(this, framebuffer_id);
  framebuffer_map_[framebuffer_id] = framebuffer;
  return framebuffer;
}

WebGLProgram* WebGLRenderingContext::CreateProgram(GLuint program_id) {
  WebGLProgram* program = new WebGLProgram(this, program_id);
  program_map_[program_id] = program;
  return program;
}

WebGLRenderbuffer* WebGLRenderingContext::CreateRenderbuffer(GLuint renderbuffer_id) {
  WebGLRenderbuffer* renderbuffer = new WebGLRenderbuffer(this, renderbuffer_id);
  renderbuffer_map_[renderbuffer_id] = renderbuffer;
  return renderbuffer;
}

WebGLShader* WebGLRenderingContext::CreateShader(GLuint shader_id) {
  WebGLShader* shader = new WebGLShader(this, shader_id);
  shader_map_[shader_id] = shader;
  return shader;
}

WebGLTexture* WebGLRenderingContext::CreateTexture(GLuint texture_id) {
  WebGLTexture* texture = new WebGLTexture(this, texture_id);
  texture_map_[texture_id] = texture;
  return texture;
}

WebGLUniformLocation* WebGLRenderingContext::CreateUniformLocation(GLuint program_id, GLint location_id) {
  return new WebGLUniformLocation(this, program_id, location_id);
}

void WebGLRenderingContext::DeleteBuffer(WebGLBuffer* buffer) {
  buffer_map_.erase(WEBGL_ID(buffer));
  delete buffer;
}

void WebGLRenderingContext::DeleteFramebuffer(WebGLFramebuffer* framebuffer) {
  framebuffer_map_.erase(WEBGL_ID(framebuffer));
  delete framebuffer;
}

void WebGLRenderingContext::DeleteProgram(WebGLProgram* program) {
  program_map_.erase(WEBGL_ID(program));
  delete program;
}

void WebGLRenderingContext::DeleteRenderbuffer(WebGLRenderbuffer* renderbuffer) {
  renderbuffer_map_.erase(WEBGL_ID(renderbuffer));
  delete renderbuffer;
}

void WebGLRenderingContext::DeleteShader(WebGLShader* shader) {
  shader_map_.erase(WEBGL_ID(shader));
  delete shader;
}

void WebGLRenderingContext::DeleteTexture(WebGLTexture* texture) {
  texture_map_.erase(WEBGL_ID(texture));
  delete texture;
}

void WebGLRenderingContext::set_gl_error(GLenum error) {
  if (gl_error_ == GL_NONE)
    gl_error_ = error;
}

GLenum WebGLRenderingContext::get_gl_error() {
  if (gl_error_ != GL_NONE) {
    GLenum err = gl_error_;
    gl_error_ = GL_NONE;
    return err;
  }
  return glGetError();
}

bool WebGLRenderingContext::TypedArrayToData(v8::Handle<v8::Value> value, void*& data, uint32_t& length, bool& ok) {
  ok = true;
  if (ArrayBufferView::HasInstance(value) || ArrayBuffer::HasInstance(value)) {
    v8::Handle<v8::Object> object = value->ToObject();
    ArrayDataInterface* array_data = dynamic_cast<ArrayDataInterface*>(V8ObjectBase::ToNative(object));
    if (!array_data) {
      ThrowObjectDisposed();
      length = 0;
      data = NULL;
      ok = false;
      return false;
    }

    length = array_data->GetArrayLength();
    data = array_data->GetArrayData();
    return true;
  }
  length = 0;
  data = NULL;
  return false;
}

void WebGLRenderingContext::Log(Logger::Level level, std::string msg) {
  Logger* logger = GetFactory()->GetLogger();
  if (logger)
    logger->Log(level, msg);
}

bool WebGLRenderingContext::ValidateBlendEquation(const char* function, GLenum mode) {
  switch (mode) {
    case GL_FUNC_ADD:
    case GL_FUNC_SUBTRACT:
    case GL_FUNC_REVERSE_SUBTRACT:
      return true;
    default:
      Log(Logger::kWarn, std::string(function) + ": invalid mode.");
      set_gl_error(GL_INVALID_ENUM);
      return false;
  }
}

bool WebGLRenderingContext::ValidateBlendFuncFactors(const char* function, GLenum src, GLenum dst) {
  if (((src == GL_CONSTANT_COLOR || src == GL_ONE_MINUS_CONSTANT_COLOR)
       && (dst == GL_CONSTANT_ALPHA || dst == GL_ONE_MINUS_CONSTANT_ALPHA))
      || ((dst == GL_CONSTANT_COLOR || dst == GL_ONE_MINUS_CONSTANT_COLOR)
          && (src == GL_CONSTANT_ALPHA || src == GL_ONE_MINUS_CONSTANT_ALPHA))) {
    Log(Logger::kWarn, std::string(function) + ": invalid blend factors.");
    set_gl_error(GL_INVALID_OPERATION);
    return false;
  }
  return true;
}

bool WebGLRenderingContext::ValidateTextureBinding(const char* function, GLenum target) {
  switch (target) {
    case GL_TEXTURE_2D:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
      break;
    default:
      Log(Logger::kWarn, std::string(function) + ": invalid target.");
      set_gl_error(GL_INVALID_ENUM);
      return false;
  }
  return true;
}

bool WebGLRenderingContext::ValidateTexFuncParameters(const char* function, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type) {
  switch (format) {
    case GL_ALPHA:
    case GL_LUMINANCE:
    case GL_LUMINANCE_ALPHA:
    case GL_RGB:
    case GL_RGBA:
      break;
    default:
      Log(Logger::kWarn, std::string(function) + ": invalid format.");
      set_gl_error(GL_INVALID_ENUM);
      return false;
  }

  switch (type) {
    case GL_UNSIGNED_BYTE:
    case GL_UNSIGNED_SHORT_5_6_5:
    case GL_UNSIGNED_SHORT_4_4_4_4:
    case GL_UNSIGNED_SHORT_5_5_5_1:
      break;
    default:
      Log(Logger::kWarn, std::string(function) + ": invalid type.");
      set_gl_error(GL_INVALID_ENUM);
      return false;
  }

  switch (format) {
    case GL_ALPHA:
    case GL_LUMINANCE:
    case GL_LUMINANCE_ALPHA:
      if (type != GL_UNSIGNED_BYTE) {
        Log(Logger::kWarn, std::string(function) + ": invalid type for format.");
        set_gl_error(GL_INVALID_OPERATION);
        return false;
      }
      break;
    case GL_RGB:
      if (type != GL_UNSIGNED_BYTE && type != GL_UNSIGNED_SHORT_5_6_5) {
        Log(Logger::kWarn, std::string(function) + ": invalid type for format.");
        set_gl_error(GL_INVALID_OPERATION);
        return false;
      }
      break;
    case GL_RGBA:
      if (type != GL_UNSIGNED_BYTE
          && type != GL_UNSIGNED_SHORT_4_4_4_4
          && type != GL_UNSIGNED_SHORT_5_5_5_1) {
        Log(Logger::kWarn, std::string(function) + ": invalid type for format.");
        set_gl_error(GL_INVALID_OPERATION);
        return false;
      }
      break;
  }

  if (level < 0) {
    Log(Logger::kWarn, std::string(function) + ": invalid level.");
    set_gl_error(GL_INVALID_VALUE);
    return false;
  }

  if (width < 0 || height < 0) {
    Log(Logger::kWarn, std::string(function) + ": invalid width/height.");
    set_gl_error(GL_INVALID_VALUE);
    return false;
  }

  if (!ValidateTextureBinding(function, target))
    return false;

  if (format != internalformat) {
    Log(Logger::kWarn, std::string(function) + ": invalid format.");
    set_gl_error(GL_INVALID_OPERATION);
    return false;
  }

  if (border) {
    Log(Logger::kWarn, std::string(function) + ": invalid border.");
    set_gl_error(GL_INVALID_VALUE);
    return false;
  }
  return true;
}

bool WebGLRenderingContext::ValidateCapability(const char* function, GLenum cap) {
  switch (cap) {
    case GL_BLEND:
    case GL_CULL_FACE:
    case GL_DEPTH_TEST:
    case GL_DITHER:
    case GL_POLYGON_OFFSET_FILL:
    case GL_SAMPLE_ALPHA_TO_COVERAGE:
    case GL_SAMPLE_COVERAGE:
    case GL_SCISSOR_TEST:
    case GL_STENCIL_TEST:
      return true;
    default:
      Log(Logger::kWarn, std::string(function) + ": invalid capability.");
      set_gl_error(GL_INVALID_ENUM);
      return false;
  }
}

bool WebGLRenderingContext::ValidateDrawMode(const char* function, GLenum mode) {
  switch (mode) {
    case GL_POINTS:
    case GL_LINE_STRIP:
    case GL_LINE_LOOP:
    case GL_LINES:
    case GL_TRIANGLE_STRIP:
    case GL_TRIANGLE_FAN:
    case GL_TRIANGLES:
      return true;
    default:
      Log(Logger::kWarn, std::string(function) + ": invalid mode.");
      set_gl_error(GL_INVALID_ENUM);
      return false;
  }
}

bool WebGLRenderingContext::ValidateFramebufferFuncParameters(const char* function, GLenum target, GLenum attachment) {
  if (target != GL_FRAMEBUFFER) {
    Log(Logger::kWarn, std::string(function) + ": invalid target.");
    set_gl_error(GL_INVALID_ENUM);
    return false;
  }
  switch (attachment) {
    case GL_COLOR_ATTACHMENT0:
    case GL_DEPTH_ATTACHMENT:
    case GL_STENCIL_ATTACHMENT:
    case GL_DEPTH_STENCIL_ATTACHMENT:
      return true;
    default:
      Log(Logger::kWarn, std::string(function) + ": invalid attachment.");
      set_gl_error(GL_INVALID_ENUM);
      return false;
  }
}

bool WebGLRenderingContext::ValidateStencilFunc(const char* function, GLenum func) {
  switch (func) {
    case GL_NEVER:
    case GL_LESS:
    case GL_LEQUAL:
    case GL_GREATER:
    case GL_GEQUAL:
    case GL_EQUAL:
    case GL_NOTEQUAL:
    case GL_ALWAYS:
      return true;
    default:
      Log(Logger::kWarn, std::string(function) + ": invalid function.");
      set_gl_error(GL_INVALID_ENUM);
      return false;
  }
}

bool WebGLRenderingContext::ValidateBufferDataParameters(const char* function, GLenum target, GLenum usage) {
  switch (target) {
    case GL_ELEMENT_ARRAY_BUFFER:
    case GL_ARRAY_BUFFER:
      break;
    default:
      Log(Logger::kWarn, std::string(function) + ": invalid target.");
      set_gl_error(GL_INVALID_ENUM);
      return false;
  }
  switch (usage) {
    case GL_STREAM_DRAW:
    case GL_STATIC_DRAW:
    case GL_DYNAMIC_DRAW:
      break;
    default:
      Log(Logger::kWarn, std::string(function) + ": invalid usage.");
      set_gl_error(GL_INVALID_ENUM);
      return false;
  }
  return true;
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
