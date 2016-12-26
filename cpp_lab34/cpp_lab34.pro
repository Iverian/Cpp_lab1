#-------------------------------------------------
#
# Project created by QtCreator 2016-11-22T20:21:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cpp_lab34
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        TextEditor.cpp \
    FileEdit.cpp \
    Highlighter.cpp

HEADERS  += \
    FileEdit.h \
    properties.h \
    TextEditor.h \
    Highlighter.h

FORMS    += \
    TextEditor.ui

RESOURCES += \
    texteditorres.qrc
