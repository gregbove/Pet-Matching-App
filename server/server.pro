QT += core

TARGET = server
TEMPLATE = app

CONFIG += console c++14
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += -pthread

unix:!macx: LIBS += -L$$PWD/../libs/x64-linux/lib/ -lrestbed

INCLUDEPATH += $$PWD/../libs/x64-linux/include
DEPENDPATH += $$PWD/../libs/x64-linux/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../libs/x64-linux/lib/librestbed.a

SOURCES += main.cpp \
    defaultcontroller.cpp

HEADERS += \
    defaultcontroller.h
