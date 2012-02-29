// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_CANVAS_H
#define V8WEBGL_CANVAS_H

#include "V8Binding.h"

namespace V8WebGL {

class Canvas : public V8Object<Canvas> {
public:
    static const char* const className() { return "Canvas"; }
    static void configureConstructorTemplate(v8::Persistent<v8::FunctionTemplate> constructor);
};

}

#endif
