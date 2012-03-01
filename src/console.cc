// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "v8_webgl_internal.h"
#include "v8_binding.h"
#include "console.h"
#include <string>
#include <iostream>

namespace v8_webgl {

#define PROTO_METHOD(name) AddCallback(proto, #name, Callback_##name, signature)

Console::Console(Logger* logger)
    : V8Object<Console>()
    , logger_(logger) {
}

Console::~Console() {
  delete logger_;
}

static v8::Handle<v8::Value> Log(const v8::Arguments& args, Logger::Level level) {
  v8::HandleScope scope;
  Console* self = Console::ToNative(args.Holder());
  v8::String::Utf8Value utf8(args[0]);
  std::string msg(*utf8);
  Logger* logger = self->GetLogger();
  if (logger)
    logger->Log(level, msg);
  else
    std::cerr << msg << std::endl;
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

void Console::ConfigureGlobal(v8::Handle<v8::ObjectTemplate> global) {
  Console* console = new Console(GetFactory()->CreateLogger());
  // Add a "console" instance
  global->Set(v8::String::New("console"), console->ToV8());
}

void Console::ConfigureConstructorTemplate(v8::Persistent<v8::FunctionTemplate> constructor) {
  v8::Handle<v8::ObjectTemplate> proto = constructor->PrototypeTemplate();
  v8::Local<v8::Signature> signature = v8::Signature::New(constructor);

  PROTO_METHOD(log);
  PROTO_METHOD(debug);
  PROTO_METHOD(info);
  PROTO_METHOD(warn);
  PROTO_METHOD(error);
}

}
