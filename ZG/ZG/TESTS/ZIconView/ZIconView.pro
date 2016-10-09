TEMPLATE = lib
CONFIG  += qt


RESOURCES = ZIconView.qrc


HEADERS += ZIconView.h
#HEADERS += ZIconGraphicsItemsFactory.h
HEADERS += ZImageGraphicsItem.h
HEADERS += ZLightingCoursor.h
HEADERS += ZGraphicsView.h


SOURCES += ZIconView.cpp
#SOURCES += ZIconGraphicsItemsFactory.cpp
SOURCES += ZImageGraphicsItem.cpp
SOURCES += ZLightingCoursor.cpp
SOURCES += ZGraphicsView.cpp


TARGET = ziconview

LIBS += -L../../../Lib -lzgitemview
INCLUDEPATH += ../../../I
#DEFINES += OBJ_PACKAGE=\"YantarCore.Reestr\" OBJ_VERSION=1 

DESTDIR=../../../Lib

target.path = ../../../Bin

INSTALLS += target

head.path = ../../../I
head.files = ZIconView.h

INSTALLS += head

