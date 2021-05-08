QT += core sql

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
    defaultcontroller.cpp \
    bnbcontroller.cpp \
    ../common/bnbresponse.cpp \
    ../common/bnbmodel.cpp \
    ../common/user.cpp \
    ../common/parent.cpp \
    ../common/shelterowner.cpp \
    ../common/administrator.cpp \
    ../common/shelter.cpp \
    ../common/bnbrequest.cpp \
    userscontroller.cpp \
    db.cpp \
    authcontroller.cpp

HEADERS += \
    defaultcontroller.h \
    bnbcontroller.h \
    ../common/bnbresponse.h \
    ../common/bnbmodel.h \
    ../common/user.cpp \
    ../common/parent.h \
    ../common/shelterowner.h \
    ../common/administrator.h \
    ../common/shelter.h \
    ../common/bnbrequest.cpp \
    userscontroller.h \
    db.h \
    authcontroller.h
