// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "v8_webgl_internal.h"
#include "v8_binding.h"
#include "console.h"
#include <string>

namespace v8_webgl {

#define ADD_METHOD(target, name) target->Set(v8::String::New(#name), v8::FunctionTemplate::New(Callback_##name))

static v8::Handle<v8::Value> Log(const v8::Arguments& args, Logger::Level level) {
  Logger* logger = GetFactory()->GetLogger();
  if (logger) {
    v8::HandleScope scope;
    v8::String::Utf8Value utf8(args[0]);
    std::string msg(*utf8);
    logger->Log(level, msg);
  }
  return v8::Undefined();
}

// void log(DOMString type)
static v8::Handle<v8::Value> Callback_log(const v8::Arguments& args) {
  return Log(args, Logger::kLog);
}
// void debug(DOMString type)
static v8::Handle<v8::Value> Callback_debug(const v8::Arguments& args) {
  return Log(args, Logger::kLog);
}
// void info(DOMString type)
static v8::Handle<v8::Value> Callback_info(const v8::Arguments& args) {
  return Log(args, Logger::kInfo);
}
// void warn(DOMString type)
static v8::Handle<v8::Value> Callback_warn(const v8::Arguments& args) {
  return Log(args, Logger::kWarn);
}
// void error(DOMString type)
static v8::Handle<v8::Value> Callback_error(const v8::Arguments& args) {
  return Log(args, Logger::kError);
}

void Console::Initialize(v8::Handle<v8::ObjectTemplate> global) {
  v8::Handle<v8::ObjectTemplate> console = v8::ObjectTemplate::New();
  ADD_METHOD(console, log);
  ADD_METHOD(console, debug);
  ADD_METHOD(console, info);
  ADD_METHOD(console, warn);
  ADD_METHOD(console, error);
  global->Set(v8::String::New("console"), console);
}

}
