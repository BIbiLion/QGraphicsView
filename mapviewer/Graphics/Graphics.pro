#-------------------------------------------------
#
# Project created by QtCreator 2015-06-28T18:45:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graphics
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myscene.cpp \
    myview.cpp

HEADERS  += mainwindow.h \
    myscene.h \
    myview.h

FORMS    += mainwindow.ui

RESOURCES += \
    graphics.qrc
