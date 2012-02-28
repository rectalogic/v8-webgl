// Copyright (c) 2012 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8WEBGL_V8BINDING_H
#define V8WEBGL_V8BINDING_H

#include <v8.h>

namespace V8WebGL {

class V8ObjectBase {
protected:
    inline static void addCallback(v8::Handle<v8::ObjectTemplate> proto, const char* name, v8::InvocationCallback callback, v8::Local<v8::Signature> signature) {
        proto->Set(v8::String::New(name),
                   v8::FunctionTemplate::New(callback, v8::Handle<v8::Value>(), signature),
                   v8::DontDelete);
    };

    static v8::Persistent<v8::FunctionTemplate> createConstructorTemplate(const char* className);
};

template<class T>
class V8Object : public V8ObjectBase {
public:
    static void initialize(v8::Handle<v8::ObjectTemplate> target) {
        if (!s_constructorTemplate.IsEmpty())
            return;
        v8::HandleScope scope;
        s_constructorTemplate = createConstructorTemplate(T::className());
        T::configureConstructorTemplate(s_constructorTemplate);
        T::configureTarget(target);
    }

    static void uninitialize() {
        if (s_constructorTemplate.IsEmpty())
            return;
        s_constructorTemplate.Dispose();
        s_constructorTemplate.Clear();
    }

    // Subclasses can reimplement this if they don't want their constructor exposed
    static void configureTarget(v8::Handle<v8::ObjectTemplate> target) {
        target->Set(v8::String::New(T::className()), s_constructorTemplate);
    }

    //XXX add static toNative(Handle), hmm need to distinguish type checking from actual null value
    //XXX add wrap(T*) - return JS wrapper for T, with weakref etc.

private:
    static v8::Persistent<v8::FunctionTemplate> s_constructorTemplate;
};

template<class T>
v8::Persistent<v8::FunctionTemplate> V8Object<T>::s_constructorTemplate;

}

#endif
