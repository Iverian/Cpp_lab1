#-------------------------------------------------
#
# Project created by QtCreator 2016-12-23T16:50:52
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zadolbalo
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        MainWindow.cpp \
    ModifyDialog.cpp \
    ShowDialog.cpp \
    Competition.cpp

HEADERS  += MainWindow.h \
    ModifyDialog.h \
    ShowDialog.h \
    Competition.h

FORMS    += MainWindow.ui \
    ModifyDialog.ui \
    ShowDialog.ui \
    Competition.ui
