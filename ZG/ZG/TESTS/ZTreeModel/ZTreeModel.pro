TEMPLATE = lib
CONFIG  += qt


HEADERS += ZTreeModel.h
HEADERS += ZTreeItem.h


SOURCES += ZTreeModel.cpp
SOURCES += ZTreeItem.cpp


TARGET = ztreemodel

#LIBS += -L../../../Lib -lastralite -lmycom
INCLUDEPATH += ../../../I
#DEFINES += OBJ_PACKAGE=\"YantarCore.Reestr\" OBJ_VERSION=1 

DESTDIR=../../../Lib

target.path = ../../../Bin

INSTALLS += target

head.path = ../../../I
head.files = ZTreeModel.h

INSTALLS += head

