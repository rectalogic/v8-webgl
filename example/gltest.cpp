#include <v8.h>
#include "V8WebGL.h"

int main(int argc, char* argv[])
{
    v8::HandleScope handle_scope;

    v8::Handle<v8::ObjectTemplate> global = V8WebGL::initialize();
    v8::Persistent<v8::Context> context = v8::Context::New(0, global);
  
    v8::Context::Scope context_scope(context);

    v8::Handle<v8::String> source = v8::String::New("WebGLRenderingContext.FRONT");
    v8::Handle<v8::Script> script = v8::Script::Compile(source);
  
    v8::Handle<v8::Value> result = script->Run();
  
    context.Dispose();

    // Convert the result to an ASCII string and print it.
    v8::String::AsciiValue ascii(result);
    printf("%s\n", *ascii);
    return 0;
}
