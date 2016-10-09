TEMPLATE = lib
CONFIG  += qt


HEADERS += ZTestModelGItem.h
HEADERS += ZModelDelegateGItem.h
#HEADERS += ZTestGraphicsItemsFactory.h
#HEADERS += IModelGraphicsItem.h
HEADERS += ZGTestItemView.h
HEADERS += ZArrow.h


SOURCES += ZTestModelGItem.cpp
SOURCES += ZModelDelegateGItem.cpp
SOURCES += ZProxyGraphicsItem.cpp
#SOURCES += ZTestGraphicsItemsFactory.cpp
SOURCES += ZGTestItemView.cpp
SOURCES += ZArrow.cpp


TARGET = zgtestitemview

LIBS += -L../../../Lib -lzgitemview
INCLUDEPATH += ../../../I
#DEFINES += OBJ_PACKAGE=\"YantarCore.Reestr\" OBJ_VERSION=1 

DESTDIR=../../../Lib

target.path = ../../../Bin

INSTALLS += target

head.path = ../../../I
head.files = ZGTestItemView.h

INSTALLS += head

