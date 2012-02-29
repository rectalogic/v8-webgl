// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "v8_webgl.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

static v8::Persistent<v8::ObjectTemplate> s_global;

v8::Handle<v8::ObjectTemplate> Initialize() {
  if (!s_global.IsEmpty())
    return s_global;

  v8::HandleScope scope;
  v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New();
  s_global = v8::Persistent<v8::ObjectTemplate>::New(global);

  WebGLRenderingContext::Initialize(s_global);
  //XXX initialize webgl classes with global

  //XXX no JS constructors, add createCanvas() api to global? (or webvfx object in global)
  return s_global;
}

void Uninitialize() {
  if (s_global.IsEmpty())
    return;
  s_global.Dispose();
  s_global.Clear();

  WebGLRenderingContext::Uninitialize();
  //XXX uninitialize webgl classes
}

}
