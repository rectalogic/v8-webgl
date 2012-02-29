// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_V8_WEBGL_H
#define V8WEBGL_V8_WEBGL_H

#include <v8.h>
#include <string>

namespace v8_webgl {

class GraphicContext {
 public:
  //XXX need flags for antialising, also windowed or FBO
  virtual ~GraphicContext() {}
  virtual void Resize(int width, int height) = 0;
  virtual void MakeCurrent() = 0;
};

class Logger {
 public:
  enum Level { kLog, kInfo, kWarn, kError };
  virtual ~Logger() {}
  virtual void Log(Level level, std::string& msg) = 0;
};

class Factory {
 public:
  virtual ~Factory() {}
  virtual GraphicContext* CreateGraphicContext() = 0;
  virtual Logger* CreateLogger() { return 0; }
  //XXX image method - pass in string name - don't want to return data though, want to upload to gpu (and need to know size, format etc.)
};

// Initialize v8-webgl and return the global object.
// This will be valid until uninitialize().
// Factory will be destroyed when Unintialized
v8::Persistent<v8::ObjectTemplate> Initialize(Factory* factory);

void Uninitialize();

}

#endif
