// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <v8_webgl.h>
#include "canvas.h"
#include "console.h"
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

namespace v8_webgl {

static Factory* s_factory = 0;
static v8::Persistent<v8::ObjectTemplate> s_global;

v8::Persistent<v8::ObjectTemplate> Initialize(Factory* factory) {
  if (!s_global.IsEmpty())
    return s_global;

  s_factory = factory;

  v8::HandleScope scope;
  v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New();
  s_global = v8::Persistent<v8::ObjectTemplate>::New(global);

  Console::Initialize(s_global);
  Canvas::Initialize(s_global);
  WebGLActiveInfo::Initialize(s_global);
  WebGLBuffer::Initialize(s_global);
  WebGLFramebuffer::Initialize(s_global);
  WebGLProgram::Initialize(s_global);
  WebGLRenderbuffer::Initialize(s_global);
  WebGLRenderingContext::Initialize(s_global);
  WebGLShader::Initialize(s_global);
  WebGLTexture::Initialize(s_global);
  WebGLUniformLocation::Initialize(s_global);

  // Typed Array
  ArrayBuffer::Initialize(s_global);
  Int8Array::Initialize(s_global);
  Uint8Array::Initialize(s_global);
  Uint8ClampedArray::Initialize(s_global);
  Int16Array::Initialize(s_global);
  Uint16Array::Initialize(s_global);
  Int32Array::Initialize(s_global);
  Uint32Array::Initialize(s_global);
  Float32Array::Initialize(s_global);
  Float64Array::Initialize(s_global);

  return s_global;
}

void Uninitialize() {
  if (s_global.IsEmpty())
    return;
  s_global.Dispose();
  s_global.Clear();

  delete s_factory;
  s_factory = 0;

  Console::Uninitialize();
  Canvas::Uninitialize();
  WebGLActiveInfo::Uninitialize();
  WebGLBuffer::Uninitialize();
  WebGLFramebuffer::Uninitialize();
  WebGLProgram::Uninitialize();
  WebGLRenderbuffer::Uninitialize();
  WebGLRenderingContext::Uninitialize();
  WebGLShader::Uninitialize();
  WebGLTexture::Uninitialize();
  WebGLUniformLocation::Uninitialize();

  // Typed Array
  ArrayBuffer::Uninitialize();
  Int8Array::Uninitialize();
  Uint8Array::Uninitialize();
  Uint8ClampedArray::Uninitialize();
  Int16Array::Uninitialize();
  Uint16Array::Uninitialize();
  Int32Array::Uninitialize();
  Uint32Array::Uninitialize();
  Float32Array::Uninitialize();
  Float64Array::Uninitialize();

  // Run GC until everything is freed
  while (!v8::V8::IdleNotification()) {}

  v8::V8::Dispose();
}

Factory* GetFactory() {
  return s_factory;
}

}
