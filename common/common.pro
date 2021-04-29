QT += core network

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += main.cpp \
    administrator.cpp \
    attribute.cpp \
    attributepreference.cpp \
    bnbmodel.cpp \
    pet.cpp \
    petattribute.cpp \
    petmatch.cpp \
    petwatch.cpp \
    shelter.cpp \
    shelterowner.cpp \
    user.cpp \
    bnbresponse.cpp \
    jsonserializable.cpp \
    parent.cpp \
    bnbrequest.cpp \
    bnbclient.cpp

HEADERS += \
    administrator.h \
    attribute.h \
    attributepreference.h \
    bnbmodel.h \
    pet.h \
    petattribute.h \
    petmatch.h \
    petwatch.h \
    shelter.h \
    shelterowner.h \
    user.h \
    bnbresponse.h \
    jsonserializable.h \
    parent.h \
    bnbrequest.h \
    bnbclient.h
