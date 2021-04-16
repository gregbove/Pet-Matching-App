QT += core

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += main.cpp \
    bnbmodel.cpp \
    user.cpp \
    bnbresponse.cpp \
    jsonserializable.cpp

HEADERS += \
    bnbmodel.h \
    user.h \
    bnbresponse.h \
    jsonserializable.h
