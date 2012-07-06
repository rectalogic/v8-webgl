# Overview

v8-webgl is an implementation of the [WebGL 1.0 API](http://www.khronos.org/webgl/)
for the Google [v8 JavaScript engine](http://code.google.com/p/v8/).

It uses [ANGLE](http://code.google.com/p/angleproject/)
to translate shaders from WebGL to desktop GLSL.

It was created to be used as a visual effects engine for video rendering.
e.g. to build a plugin for a framework like [MLT](http://www.mltframework.org/).
Decompressed video frames could be uploaded as WebGL textures and
rendered offscreen with visual effects applied.

## WIP

v8-webgl is currently a work in progress and incomplete.
It needs a hook for the API user to get image data into a WebGL texture.
Currently the texSubImage2D methods are not implemented.

It also needs to support rendering to an offscreen FBO - e.g.
bindFramebuffer to a null FBO should bind to the offscreen FBO.

It also needs a mechanism to load external JS files, and import
files into a JS file.

## License

Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file.
