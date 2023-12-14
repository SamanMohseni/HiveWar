#-------------------------------------------------
#
# Project created by QtCreator 2016-05-29T05:00:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HiveWar
TEMPLATE = app


SOURCES += main.cpp \
    Map.cpp \
    Server.cpp \
    AI.cpp \
    GameManager.cpp \
    GameWindow.cpp \
    Hexagon.cpp \
    MainMenu.cpp \
    SinglePlayer.cpp \
    AllGameObjects.cpp \
    Buttons.cpp \
    FileManager.cpp \
    DesireMap.cpp \
    GameManagerProxy.cpp \
    MapEditor.cpp \
    MultiPlay.cpp \
    FixedPositionObject.cpp

HEADERS  += \
    Map.h \
    AI.h \
    GameManager.h \
    GameWindow.h \
    Hexagon.h \
    MainMenu.h \
    Server.h \
    SinglePlayer.h \
    SystemInfo.h \
    AllGameObjects.h \
    Buttons.h \
    FileManager.h \
    DesireMap.h \
    Desire.h \
    GameManagerProxy.h \
    MapEditor.h \
    MultiPlay.h \
    FixedPositionObject.h

FORMS    +=

RESOURCES += \
    resources.qrc
