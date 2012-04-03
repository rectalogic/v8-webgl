TEMPLATE = app

SOURCES += example/gltest.cc
SOURCES += src/canvas.cc
SOURCES += src/console.cc
SOURCES += src/typed_array.cc
SOURCES += src/v8_binding.cc
SOURCES += src/v8_webgl.cc
SOURCES += src/webgl_active_info.cc
SOURCES += src/webgl_rendering_context.cc
SOURCES += src/webgl_rendering_context_callbacks.cc

QT += opengl
TARGET = gltest

INCLUDEPATH += ../v8/include
INCLUDEPATH += src
INCLUDEPATH += include

LIBS += -L../v8 -lv8_g

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
