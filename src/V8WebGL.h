// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_V8WEBGL_H
#define V8WEBGL_V8WEBGL_H

#include <v8.h>

namespace V8WebGL {

// Initialize v8-webgl and return the global object.
// This will be valid until uninitialize().
//XXX pass in ImageFactory, Console instance
//XXX need Console impl with virtual methods so user can subclass
//XXX also GraphicContext abstract class with makeCurrent
v8::Handle<v8::ObjectTemplate> initialize();

void uninitialize();

}

#endif
