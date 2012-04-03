// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "webgl_active_info.h"

namespace v8_webgl {

WebGLActiveInfo::WebGLActiveInfo(GLint size, GLenum type, const char* name)
    : V8Object<WebGLActiveInfo>(true) {
  v8::Handle<v8::Object> instance(ToV8());
  v8::PropertyAttribute attrs = static_cast<v8::PropertyAttribute>(v8::ReadOnly|v8::DontDelete);
  instance->Set(TypeToV8("size"), TypeToV8(size), attrs);
  instance->Set(TypeToV8("type"), TypeToV8(type), attrs);
  instance->Set(TypeToV8("name"), TypeToV8(name), attrs);
}


}
