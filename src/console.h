// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_CONSOLE_H
#define V8WEBGL_CONSOLE_H

#include <v8.h>

namespace v8_webgl {

class Logger;

class Console {
 public:
  static void Initialize(v8::Handle<v8::ObjectTemplate> global);
  static void Uninitialize() {}
};

}

#endif
