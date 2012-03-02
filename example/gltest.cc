#include <v8.h>
#include <v8_webgl.h>
#include <iostream>

class Factory : public v8_webgl::Factory, v8_webgl::Logger {
 private:
  class GraphicContext : public v8_webgl::GraphicContext {
    void Resize(int width, int height) {}
    void MakeCurrent() {}
  };

 public:
  void Log(Level level, std::string& msg) {
    std::cerr << msg << std::endl;
  }
  v8_webgl::GraphicContext* CreateGraphicContext(int width, int height) { return new GraphicContext(); }
  Logger* GetLogger() { return this; }
};

int main(int argc, char* argv[])
{
  {
    v8::HandleScope handle_scope;

    const char* kExposeGC = "--expose-gc";
    v8::V8::SetFlagsFromString(kExposeGC, strlen(kExposeGC));

    v8::Handle<v8::ObjectTemplate> global = v8_webgl::Initialize(new Factory());
    v8::Persistent<v8::Context> context = v8::Context::New(NULL, global);

    v8::Context::Scope context_scope(context);

    v8::Handle<v8::String> source = v8::String::New("var canvas = new Canvas(); canvas.width = canvas.height = 200; var gl = canvas.getContext(); console.log('canvas=' + canvas); console.log('context=' + gl); console.log('width=' + canvas.width); console.log('FRONT=' + WebGLRenderingContext.FRONT); canvas = null; /*gc();*/");
    v8::Handle<v8::Script> script = v8::Script::Compile(source);

    v8::Handle<v8::Value> result = script->Run();

    context.Dispose();

    // Convert the result to an ASCII string and print it.
    v8::String::AsciiValue ascii(result);
    printf("%s\n", *ascii);
  }

  v8_webgl::Uninitialize();
  return 0;
}
