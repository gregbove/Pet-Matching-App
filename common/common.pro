QT += core

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += main.cpp \
    administrator.cpp \
    attribute.cpp \
    bnbmodel.cpp \
    pet.cpp \
    petattribute.cpp \
    shelter.cpp \
    shelterowner.cpp \
    shelterownership.cpp \
    user.cpp \
    bnbresponse.cpp \
    jsonserializable.cpp \
    parent.cpp \
    bnbrequest.cpp

HEADERS += \
    administrator.h \
    attribute.h \
    bnbmodel.h \
    pet.h \
    petattribute.h \
    shelter.h \
    shelterowner.h \
    shelterownership.h \
    user.h \
    bnbresponse.h \
    jsonserializable.h \
    parent.h \
    bnbrequest.h
