// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_CONSOLE_H
#define V8WEBGL_CONSOLE_H

#include "v8_binding.h"

namespace v8_webgl {

class Logger;

class Console : public V8Object<Console> {
 public:
  static const char* const ClassName() { return "Console"; }
  static void ConfigureConstructorTemplate(v8::Persistent<v8::FunctionTemplate> constructor);
  static void ConfigureTarget(v8::Handle<v8::ObjectTemplate> target);

  Logger* GetLogger() { return logger_; }

 protected:
  Console(Logger* logger);
  ~Console();

 private:
  Logger* logger_;

  friend class V8Object<Console>;
};

}

#endif
