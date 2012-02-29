#include <v8.h>
#include <v8_webgl.h>

class Factory : public v8_webgl::Factory {
 public:
  v8_webgl::GraphicContext* CreateGraphicContext() { return 0; }
  //  Logger* CreateLogger() { return 0; }
};

int main(int argc, char* argv[])
{
    v8::HandleScope handle_scope;

    v8::Handle<v8::ObjectTemplate> global = v8_webgl::Initialize(new Factory());
    v8::Persistent<v8::Context> context = v8::Context::New(NULL, global);

    v8::Context::Scope context_scope(context);

    v8::Handle<v8::String> source = v8::String::New("console.log('FRONT=' + WebGLRenderingContext.FRONT)");
    v8::Handle<v8::Script> script = v8::Script::Compile(source);

    v8::Handle<v8::Value> result = script->Run();

    context.Dispose();

    // Convert the result to an ASCII string and print it.
    v8::String::AsciiValue ascii(result);
    printf("%s\n", *ascii);
    return 0;
}
