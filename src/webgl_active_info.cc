// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "webgl_active_info.h"

namespace v8_webgl {

WebGLActiveInfo::WebGLActiveInfo(GLint size, GLenum type, const char* name)
    : V8Object<WebGLActiveInfo>(true) {
  v8::Handle<v8::Object> instance(ToV8Object());
  v8::PropertyAttribute attrs = static_cast<v8::PropertyAttribute>(v8::ReadOnly|v8::DontDelete);
  instance->Set(ToV8("size"), ToV8(size), attrs);
  instance->Set(ToV8("type"), ToV8(type), attrs);
  instance->Set(ToV8("name"), ToV8(name), attrs);
}


}
