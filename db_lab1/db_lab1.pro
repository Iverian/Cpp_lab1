#-------------------------------------------------
#
# Project created by QtCreator 2016-10-11T17:05:05
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = db_lab1
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp\
        DbWrapper.cpp

HEADERS  += MainWindow.h\
			DbWrapper.h

FORMS    += MainWindow.ui
