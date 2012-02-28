// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "V8WebGL.h"
#include "V8WebGLRenderingContext.h"

namespace V8WebGL {

static v8::Persistent<v8::ObjectTemplate> s_global = 0;

v8::Handle<v8::ObjectTemplate> initialize()
{
    if (s_global)
        return s_global;
    {
        HandleScope scope;
        v8::Local<v8::ObjectTemplate global = v8::ObjectTemplate::New();
        s_global = v8::Persistent<v8::ObjectTemplate>::New(global);

        WebGLRenderingContext::uninitialize(s_global);
        //XXX initialize webgl classes with global

        //XXX no JS constructors, add createCanvas() api to global? (or webvfx object in global)
    }
}

void uninitialize()
{
    if (!s_global)
        return;
    s_global.Dispose();

    WebGLRenderingContext::uninitialize();
    //XXX uninitialize webgl classes
}

}
