// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_CANVAS_H
#define V8WEBGL_CANVAS_H

#include "v8_binding.h"

namespace v8_webgl {

class Canvas : public V8Object<Canvas> {
public:
  static const char* const ClassName() { return "Canvas"; }
  static void ConfigureConstructorTemplate(v8::Persistent<v8::FunctionTemplate> constructor);
private:
  // Always allow construction
  static ConstructorMode<Canvas> s_mode;
};

}

#endif
