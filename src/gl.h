// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_GL_H
#define V8WEBGL_GL_H

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

// Emulate GLES2 constants
#ifndef GL_MAX_FRAGMENT_UNIFORM_VECTORS
#define GL_MAX_FRAGMENT_UNIFORM_VECTORS 0x8DFD
#endif
#ifndef GL_MAX_VERTEX_UNIFORM_VECTORS
#define GL_MAX_VERTEX_UNIFORM_VECTORS 0x8DFB
#endif
#ifndef GL_MAX_VARYING_VECTORS
#define GL_MAX_VARYING_VECTORS 0x8DFC
#endif
#ifndef GL_RGB565
#define GL_RGB565 0x8D62
#endif

// WebGL specific
#define GL_UNPACK_FLIP_Y_WEBGL 0x9240
#define GL_UNPACK_PREMULTIPLY_ALPHA_WEBGL 0x9241
#define GL_UNPACK_COLORSPACE_CONVERSION_WEBGL 0x9243

#endif
