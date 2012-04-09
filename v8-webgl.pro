#XXX fix this - where should we get v8 from?
V8_DIR = ../v8
ANGLE_DIR = angleproject

TEMPLATE = app

HEADERS += include/v8_webgl.h
HEADERS += src/canvas.h
HEADERS += src/console.h
HEADERS += src/converters.h
HEADERS += src/gl.h
HEADERS += src/shader_compiler.h
HEADERS += src/typed_array.h
HEADERS += src/v8_binding.h
HEADERS += src/v8_webgl_internal.h
HEADERS += src/webgl_active_info.h
HEADERS += src/webgl_buffer.h
HEADERS += src/webgl_framebuffer.h
HEADERS += src/webgl_object.h
HEADERS += src/webgl_program.h
HEADERS += src/webgl_renderbuffer.h
HEADERS += src/webgl_rendering_context.h
HEADERS += src/webgl_shader.h
HEADERS += src/webgl_texture.h
HEADERS += src/webgl_uniform_location.h

ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/BaseTypes.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/BuiltInFunctionEmulator.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/Common.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/ConstantUnion.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/debug.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/DetectRecursion.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/ExtensionBehavior.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/ForLoopUnroll.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/glslang.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/glslang_tab.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/InfoSink.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/InitializeDll.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/InitializeGlobals.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/Initialize.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/InitializeParseContext.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/intermediate.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/localintermediate.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/MMap.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/MapLongVariableNames.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/osinclude.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/preprocessor/atom.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/preprocessor/compile.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/preprocessor/cpp.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/preprocessor/length_limits.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/preprocessor/memory.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/preprocessor/parser.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/preprocessor/preprocess.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/preprocessor/scanner.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/preprocessor/slglobals.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/preprocessor/symbols.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/preprocessor/tokens.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/OutputESSL.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/OutputGLSL.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/OutputGLSLBase.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/OutputHLSL.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/ParseHelper.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/PoolAlloc.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/QualifierAlive.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/RemoveTree.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/SearchSymbol.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/ShHandle.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/SymbolTable.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/TranslatorESSL.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/TranslatorGLSL.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/TranslatorHLSL.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/Types.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/UnfoldSelect.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/util.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/ValidateLimitations.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/VariableInfo.h
ANGLE_HEADERS += $$ANGLE_DIR/src/compiler/VersionGLSL.h

HEADERS += $$ANGLE_HEADERS

SOURCES += example/gltest.cc
SOURCES += src/canvas.cc
SOURCES += src/console.cc
SOURCES += src/converters.cc
SOURCES += src/shader_compiler.cc
SOURCES += src/typed_array.cc
SOURCES += src/v8_binding.cc
SOURCES += src/v8_webgl.cc
SOURCES += src/webgl_active_info.cc
SOURCES += src/webgl_rendering_context.cc
SOURCES += src/webgl_rendering_context_callbacks.cc

ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/BuiltInFunctionEmulator.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/CodeGenGLSL.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/Compiler.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/debug.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/DetectRecursion.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/ForLoopUnroll.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/glslang_lex.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/glslang_tab.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/InfoSink.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/Initialize.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/InitializeDll.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/Intermediate.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/intermOut.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/IntermTraverse.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/MapLongVariableNames.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/ossource_posix.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/OutputESSL.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/OutputGLSL.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/OutputGLSLBase.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/OutputHLSL.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/parseConst.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/ParseHelper.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/PoolAlloc.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/QualifierAlive.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/RemoveTree.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/SearchSymbol.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/ShaderLang.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/SymbolTable.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/TranslatorESSL.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/TranslatorGLSL.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/TranslatorHLSL.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/UnfoldSelect.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/util.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/ValidateLimitations.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/VariableInfo.cpp
ANGLE_SOURCES += $$ANGLE_DIR/src/compiler/VersionGLSL.cpp

SOURCES += $$ANGLE_DIR/src/compiler/preprocessor/atom.c
SOURCES += $$ANGLE_DIR/src/compiler/preprocessor/cpp.c
SOURCES += $$ANGLE_DIR/src/compiler/preprocessor/cppstruct.c
SOURCES += $$ANGLE_DIR/src/compiler/preprocessor/memory.c
SOURCES += $$ANGLE_DIR/src/compiler/preprocessor/scanner.c
SOURCES += $$ANGLE_DIR/src/compiler/preprocessor/symbols.c
SOURCES += $$ANGLE_DIR/src/compiler/preprocessor/tokens.c

*g++* {
    ANGLE_CFLAGS += -Wno-unused-variable
    ANGLE_CFLAGS += -Wno-missing-noreturn
    ANGLE_CFLAGS += -Wno-unused-function
    ANGLE_CFLAGS += -Wno-reorder
    ANGLE_CFLAGS += -Wno-unused-parameter
    ANGLE_CFLAGS += -Wno-switch

    angle_cxx.commands = $$QMAKE_CXX -c $(CXXFLAGS) $$ANGLE_CFLAGS $(INCPATH) ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT}
    angle_cxx.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_BASE}$$QMAKE_EXT_OBJ
    anglc_cxx.dependency_type = TYPE_C
    angle_cxx.depends = $$ANGLE_HEADERS
    angle_cxx.input = ANGLE_SOURCES
    QMAKE_EXTRA_COMPILERS += angle_cxx
} else {
    SOURCES += $$ANGLE_SOURCES
}

INCLUDEPATH += $$V8_DIR/include
INCLUDEPATH += $$ANGLE_DIR/src
INCLUDEPATH += $$ANGLE_DIR/include
INCLUDEPATH += src
INCLUDEPATH += include

LIBS += -L$$V8_DIR -lv8_g

QT += opengl
TARGET = gltest

CONFIG += console
mac:CONFIG -= app_bundle
CONFIG += warn_on debug_and_release
CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/build/debug
} else {
    DESTDIR = $$PWD/build/release
}
OBJECTS_DIR = $$DESTDIR/.obj/$$TARGET
MOC_DIR = $$DESTDIR/.moc/$$TARGET
RCC_DIR = $$DESTDIR/.rcc/$$TARGET
UI_DIR = $$DESTDIR/.ui/$$TARGET
