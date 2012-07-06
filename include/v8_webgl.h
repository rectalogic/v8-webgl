// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_V8_WEBGL_H
#define V8WEBGL_V8_WEBGL_H

#include <v8.h>
#include <string>

//XXX caller needs to use v8::Locker to "do anything" in v8 from another thread - i.e. if we use one isolate, then all access from multiple threads must be locked
//XXX also GL context can be used from only one thread at a time - may need to expose thread switching API so we can optimize making GL context current? (e.g. can't stash current context, need to link it to it's thread)

namespace v8_webgl {

class GraphicContext {
 public:
  //XXX need flags for antialising, also windowed or FBO
  virtual ~GraphicContext() {}
  virtual void Resize(int width, int height) = 0;
  virtual void MakeCurrent() = 0;
};

//////

class Logger {
 public:
  enum Level { kLog, kInfo, kWarn, kError };
  virtual ~Logger() {}
  virtual void Log(Level level, std::string& msg) = 0;
};

//////

class Factory {
 public:
  virtual ~Factory() {}
  virtual GraphicContext* CreateGraphicContext(int width, int height) = 0;
  // Logger instance, return 0 to disable logging via console.
  // Logger instance should live for as long as Factory.
  virtual Logger* GetLogger() { return 0; }
  //XXX image method - pass in string name - don't want to return data though, want to upload to gpu (and need to know size, format etc.)
};

//////

// Initialize v8-webgl and return the global object template.
// This will be valid until uninitialize().
// Factory will be destroyed when Unintialized.
v8::Persistent<v8::ObjectTemplate> Initialize(Factory* factory);

void Uninitialize();

}

#endif
