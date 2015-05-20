#-------------------------------------------------
#
# Project created by QtCreator 2015-05-14T15:23:45
#
#-------------------------------------------------
#CONFIG += console release
QT       += core gui opengl
TARGET = AnimationPersonnage
TEMPLATE = app
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lglew32
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

OBJECTS_DIR = obj
DESTDIR = release

SOURCES += \
src/main.cpp \
    src/Framework/GlCamera.cpp \
    src/Framework/GlFramework.cpp \
    src/Model/MD5Animation.cpp \
    src/Model/MD5Model.cpp \
    src/Shapes/Basis.cpp \
    src/Shapes/BasisPlan.cpp \
    src/Shapes/Cubes.cpp \
    src/Shapes/Cylinder.cpp \
    src/Shapes/Object3D.cpp \
    src/Shapes/ParametricShape.cpp \
    src/Shapes/Pyramid.cpp \
    src/Shapes/Shape.cpp \
    src/Shapes/Star.cpp \
    src/Tools/RandomNumberGenerator.cpp \
    src/AnimationPersonnage.cpp \
    src/Framework/GlWindow.cpp


HEADERS += \
    src/Framework/AbstractFramework.h \
    src/Framework/GlCamera.h \
    src/Framework/GlFramework.h \
    src/Model/MD5Animation.h \
    src/Model/MD5Model.h \
    src/Shapes/Basis.h \
    src/Shapes/BasisPlan.h \
    src/Shapes/Cubes.h \
    src/Shapes/Cylinder.h \
    src/Shapes/Object3D.h \
    src/Shapes/ParametricShape.h \
    src/Shapes/Pyramid.h \
    src/Shapes/Shape.h \
    src/Shapes/Star.h \
    src/Tools/MemDefns.h \
    src/Tools/RandomNumberGenerator.h \
    src/AnimationPersonnage.h \
    src/Framework/GlWindow.h



