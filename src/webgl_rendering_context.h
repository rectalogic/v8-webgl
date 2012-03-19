// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_WEBGL_RENDERING_CONTEXT_H
#define V8WEBGL_WEBGL_RENDERING_CONTEXT_H

#include <v8_webgl.h>
#include "v8_binding.h"
#include <map>

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

namespace v8_webgl {
class GraphicContext;
class Canvas;
class WebGLActiveInfo;
class WebGLBuffer;
class WebGLFramebuffer;
class WebGLProgram;
class WebGLRenderbuffer;
class WebGLShader;
class WebGLTexture;
class WebGLUniformLocation;

class WebGLRenderingContext : public V8Object<WebGLRenderingContext> {
 public:
  static const char* const ClassName() { return "WebGLRenderingContext"; }
  static void ConfigureConstructorTemplate(v8::Persistent<v8::FunctionTemplate> constructor);

  void MakeCurrent() {
    graphic_context_->MakeCurrent();
  }

  void Resize(int width, int height) {
    graphic_context_->Resize(width, height);
  }

  WebGLActiveInfo* CreateActiveInfo();
  WebGLBuffer* CreateBuffer(GLuint buffer_id);
  WebGLFramebuffer* CreateFramebuffer(GLuint framebuffer_id);
  WebGLProgram* CreateProgram(GLuint program_id);
  WebGLRenderbuffer* CreateRenderbuffer(GLuint renderbuffer_id);
  WebGLShader* CreateShader(GLuint shader_id);
  WebGLTexture* CreateTexture(GLuint texture_id);
  WebGLUniformLocation* CreateUniformLocation();

  void DeleteBuffer(WebGLBuffer* buffer);
  void DeleteFramebuffer(WebGLFramebuffer* framebuffer);
  void DeleteProgram(WebGLProgram* program);
  void DeleteRenderbuffer(WebGLRenderbuffer* renderbuffer);
  void DeleteShader(WebGLShader* shader);
  void DeleteTexture(WebGLTexture* texture);

  WebGLBuffer* IdToBuffer(GLuint buffer_id) {
    return IdToObject(buffer_map_, buffer_id);
  }
  WebGLFramebuffer* IdToFramebuffer(GLuint framebuffer_id) {
    return IdToObject(framebuffer_map_, framebuffer_id);
  }
  WebGLProgram* IdToProgram(GLuint program_id) {
    return IdToObject(program_map_, program_id);
  }
  WebGLRenderbuffer* IdToRenderbuffer(GLuint renderbuffer_id) {
    return IdToObject(renderbuffer_map_, renderbuffer_id);
  }
  WebGLShader* IdToShader(GLuint shader_id) {
    return IdToObject(shader_map_, shader_id);
  }
  WebGLTexture* IdToTexture(GLuint texture_id) {
    return IdToObject(texture_map_, texture_id);
  }

  unsigned long get_context_id() { return context_id_; }

 protected:
  WebGLRenderingContext(int width, int height);
  ~WebGLRenderingContext();

 private:
  GraphicContext* graphic_context_;
  unsigned long context_id_;

  std::map<GLuint, WebGLBuffer*> buffer_map_;
  std::map<GLuint, WebGLFramebuffer*> framebuffer_map_;
  std::map<GLuint, WebGLProgram*> program_map_;
  std::map<GLuint, WebGLRenderbuffer*> renderbuffer_map_;
  std::map<GLuint, WebGLShader*> shader_map_;
  std::map<GLuint, WebGLTexture*> texture_map_;

  template<class T>
  void DeleteMapObjects(std::map<GLuint, T*>& map) {
    typename std::map<GLuint, T*>::iterator it;
    for (it = map.begin(); it != map.end(); it++)
      delete it->second;
  }

  template<class T>
  T* IdToObject(std::map<GLuint, T*>& map, GLuint id) {
    typename std::map<GLuint, T*>::iterator it;
    it = map.find(id);
    if (it == map.end())
      return 0;
    return it->second;
  }

  static unsigned long s_context_counter;

  friend class Canvas;
};

}

#endif
