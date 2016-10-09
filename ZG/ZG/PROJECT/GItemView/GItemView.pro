TEMPLATE = lib
CONFIG  += qt


HEADERS += ZGItemView.h
HEADERS += ZGraphicsView.h
HEADERS += ZG.h
HEADERS += ZGraphicsItem.h
HEADERS += TGraphicsItemsFactory.h
HEADERS += MyPersistents.h
HEADERS += MyPersistent2.h
HEADERS += ZItemsMap3.h


SOURCES += ZGItemView.cpp
SOURCES += ZGraphicsView.cpp
SOURCES += ZGraphicsItem.cpp
SOURCES += MyPersistents.cpp
SOURCES += MyPersistent2.cpp
SOURCES += ZItemsMap3.cpp

TARGET = zgitemview

#LIBS += -L../../../Lib -lastralite -lmycom
INCLUDEPATH += ../../../I
#DEFINES += OBJ_PACKAGE=\"YantarCore.Reestr\" OBJ_VERSION=1 

DESTDIR=../../../Lib

target.path = ../../../Bin

INSTALLS += target

head.path = ../../../I
head.files = ZG.h ZGItemView.h ZGraphicsItem.h TGraphicsItemsFactory.h ZItemsMap3.h

INSTALLS += head
