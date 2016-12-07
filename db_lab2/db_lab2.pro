#-------------------------------------------------
#
# Project created by QtCreator 2016-12-07T17:30:24
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = db_lab2
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
    AddDatabaseDialog.cpp \
    DoraTheExplorer.cpp

HEADERS  += \
    AddDatabaseDialog.h \
    DoraTheExplorer.h

FORMS    += \
    DoraTheExplorer.ui \
    AddDatabaseDialog.ui

RESOURCES += \
    resources.qrc
