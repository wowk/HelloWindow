TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    GLObject.cpp \
    GLApplication.cpp \
    GL/src/glad.cpp \
    GLShader.cpp \
    Utils/FileUtil.cpp

HEADERS += \
    GL/include/glad/glad.h \
    GLObject.h \
    GLApplication.h \
    GLShader.h \
    GL/include/KHR/khrplatform.h \
    Utils/FileUtil.h

INCLUDEPATH += GL/include/

LIBS += -lGL -lGLU -lSDL2 -ldl

DISTFILES += \
    triangle.frag \
    triangle.vert
