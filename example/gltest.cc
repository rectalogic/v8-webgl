#include <v8.h>
#include <v8_webgl.h>
#include <iostream>
#include <QApplication>
#include <QGLWidget>

class GraphicContext : public v8_webgl::GraphicContext {
 public:
  //XXX configure antialiasing etc.
  GraphicContext(int width, int height)
      : gl_widget_(new QGLWidget()) {
    gl_widget_->resize(width, height);
    gl_widget_->setVisible(true);
  }
  ~GraphicContext() {
    delete gl_widget_;
  }
  void Resize(int width, int height) {
    gl_widget_->resize(width, height);
  }
  void MakeCurrent() {
    //XXX optimize this
    gl_widget_->makeCurrent();
  }
 private:
  QGLWidget* gl_widget_;
};

class Factory : public v8_webgl::Factory, v8_webgl::Logger {
 public:
  void Log(Level level, std::string& msg) {
    std::cerr << msg << std::endl;
  }
  v8_webgl::GraphicContext* CreateGraphicContext(int width, int height) {
    return new GraphicContext(width, height);
  }
  Logger* GetLogger() { return this; }
};

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  {
    v8::HandleScope handle_scope;

    const char* kExposeGC = "--expose-gc";
    v8::V8::SetFlagsFromString(kExposeGC, strlen(kExposeGC));

    v8::Handle<v8::ObjectTemplate> global = v8_webgl::Initialize(new Factory());
    v8::Persistent<v8::Context> context = v8::Context::New(NULL, global);

    v8::Context::Scope context_scope(context);

    v8::Handle<v8::String> source =
        v8::String::New
        (
"function shaderProgram(gl, vs, fs) {"
"    var prog = gl.createProgram();"
"    var addshader = function(type, source) {"
"        var s = gl.createShader((type == 'vertex') ?"
"            gl.VERTEX_SHADER : gl.FRAGMENT_SHADER);"
"        gl.shaderSource(s, source);"
"        gl.compileShader(s);"
"        if (!gl.getShaderParameter(s, gl.COMPILE_STATUS)) {"
"            throw 'Could not compile '+type+"
"                ' shader: '+ gl.getShaderInfoLog(s);"
"        }"
"        gl.attachShader(prog, s);"
"    };"
"    addshader('vertex', vs);"
"    addshader('fragment', fs);"
"    gl.linkProgram(prog);"
"    if (!gl.getProgramParameter(prog, gl.LINK_STATUS)) {"
"        throw 'Could not link the shader program!';"
"    }"
"    return prog;"
"}"
""
"function attributeSetFloats(gl, prog, attr_name, rsize, arr) {"
"    gl.bindBuffer(gl.ARRAY_BUFFER, gl.createBuffer());"
"    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(arr), gl.STATIC_DRAW);"
"    var attr = gl.getAttribLocation(prog, attr_name);"
"    gl.enableVertexAttribArray(attr);"
"    gl.vertexAttribPointer(attr, rsize, gl.FLOAT, false, 0, 0);"
"}"
""
"function draw() {"
"    var gl;"
"    try {"
"        var canvas = new Canvas();"
"        canvas.width = 640;"
"        canvas.height = 480;"
"        gl = canvas.getContext('experimental-webgl', {antialias:true});"
"        if (!gl) { throw 'x'; }"
"    } catch (err) {"
"        throw 'Your web browser does not support WebGL!';"
"    }"
"    gl.clearColor(0.8, 0.8, 0.8, 1);"
"    gl.clear(gl.COLOR_BUFFER_BIT);"
""
"    var prog = shaderProgram(gl,"
"        'precision mediump float;'+"
"        'attribute vec3 pos;'+"
"        'void main() {'+"
"        '   gl_Position = vec4(pos, 2.0);'+"
"        '}',"
"        'precision mediump float;'+"
"        'void main() {'+"
"        '   gl_FragColor = vec4(0.5, 0.5, 1.0, 1.0);'+"
"        '}'"
"    );"
"    gl.useProgram(prog);"
""
"    attributeSetFloats(gl, prog, 'pos', 3, ["
"        -1, 0, 0,"
"        0, 1, 0,"
"        0, -1, 0,"
"        1, 0, 0"
"    ]);"
"    "
"    gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);"
"}"
""
"console.log('initialized');"
"draw();"
         );
    v8::Handle<v8::Script> script = v8::Script::Compile(source);

    v8::Handle<v8::Value> result = script->Run();

    app.exec();
    context.Dispose();

    // Convert the result to an ASCII string and print it.
    v8::String::AsciiValue ascii(result);
    printf("%s\n", *ascii);
  }

  v8_webgl::Uninitialize();
  return 0;
}
