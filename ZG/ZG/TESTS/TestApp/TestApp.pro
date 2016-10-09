#TEMPLATE = app
HEADERS += MainWidget.h
SOURCES += MainWidget.cpp
SOURCES += main.cpp

CONFIG  += qt
CONFIG  += console
#QT      += xml sql



TARGET = GModelTestApp1

LIBS += -L../../../Lib -lzgitemview -lziconview -lztreemodel -lzgtestitemview 
INCLUDEPATH += ../../../I
#DEFINES += OBJ_PACKAGE=\"YantarCore.EngineCreator\" OBJ_VERSION=1 

target.path = ../../../Bin

scripts.files = run_GModelTestApp1.sh
scripts.path = ../../../Bin

INSTALLS += target scripts
