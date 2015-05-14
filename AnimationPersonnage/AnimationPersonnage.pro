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

SOURCES += main.cpp
OBJECTS_DIR = obj
DESTDIR = release



