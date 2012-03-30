// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_OBJECT_H
#define V8WEBGL_WEBGL_OBJECT_H

#include "v8_binding.h"
#include "webgl_rendering_context.h"

namespace v8_webgl {

class WebGLObjectInterface {
 public:
  virtual ~WebGLObjectInterface() {}
  virtual bool ValidateContext(WebGLRenderingContext* context) = 0;
};

//////

template<class V, typename T>
class WebGLObject : public V8Object<V>, public WebGLObjectInterface {
 public:
  WebGLObject(WebGLRenderingContext* context, T webgl_id, bool weak = false)
      : V8Object<V>(weak)
      , context_id_(context->get_context_id())
      , webgl_id_(webgl_id) {}

  bool ValidateContext(WebGLRenderingContext* context) { return context->get_context_id() == context_id_; }
  T get_webgl_id() { return webgl_id_; }

 private:
  unsigned long context_id_;
  T webgl_id_;
};

}

#endif
