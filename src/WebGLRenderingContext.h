// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_RENDERING_CONTEXT_H
#define V8WEBGL_WEBGL_RENDERING_CONTEXT_H

#include "V8Binding.h"

namespace V8WebGL {

class WebGLRenderingContext : public V8Object<WebGLRenderingContext> {
public:
    static const char* const className() { return "WebGLRenderingContext"; }
    static void configureConstructorTemplate(v8::Handle<v8::ObjectTemplate> target, v8::Persistent<v8::FunctionTemplate> constructor);
};

}

#endif
