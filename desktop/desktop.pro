#-------------------------------------------------
#
# Project created by QtCreator 2021-04-07T09:09:24
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = desktop
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        appstartwidget.cpp \
    userhomescreen.cpp \
    ownerhomescreen.cpp \
    adminhomescreen.cpp \
    createaccountscreen.cpp \
    enteranimalscreen.cpp \
    userpreferencesscreen.cpp \
    usersearchscreen.cpp \
    enteranimalscreengeneral.cpp \
    enteranimalscreennew.cpp \
    userpreferencesscreen2.cpp \
    adminparentsscreen.cpp \
    ../common/administrator.cpp \
    ../common/attribute.cpp \
    ../common/attributepreference.cpp \
    ../common/bnbmodel.cpp \
    ../common/pet.cpp \
    ../common/petadoption.cpp \
    ../common/petattribute.cpp \
    ../common/petmatch.cpp \
    ../common/petwatch.cpp \
    ../common/shelter.cpp \
    ../common/shelterowner.cpp \
    ../common/user.cpp \
    ../common/bnbresponse.cpp \
    ../common/jsonserializable.cpp \
    ../common/parent.cpp \
    ../common/bnbrequest.cpp \
    ../common/bnbclient.cpp \
    owneranimalsscreen.cpp


HEADERS += \
        appstartwidget.h \
    userhomescreen.h \
    ownerhomescreen.h \
    adminhomescreen.h \
    createaccountscreen.h \
    enteranimalscreen.h \
    userpreferencesscreen.h \
    usersearchscreen.h \
    enteranimalscreengeneral.h \
    enteranimalscreennew.h \
    userpreferencesscreen2.h \
    adminparentsscreen.h \
    ../common/administrator.h \
    ../common/attribute.h \
    ../common/attributepreference.h \
    ../common/bnbmodel.h \
    ../common/pet.h \
    ../common/petadoption.h \
    ../common/petattribute.h \
    ../common/petmatch.h \
    ../common/petwatch.h \
    ../common/shelter.h \
    ../common/shelterowner.h \
    ../common/user.h \
    ../common/bnbresponse.h \
    ../common/jsonserializable.h \
    ../common/parent.h \
    ../common/bnbrequest.h \
    ../common/bnbclient.h \
    owneranimalsscreen.h

FORMS += \
        appstartwidget.ui \
    userhomescreen.ui \
    ownerhomescreen.ui \
    adminhomescreen.ui \
    createaccountscreen.ui \
    enteranimalscreen.ui \
    userpreferencesscreen.ui \
    usersearchscreen.ui \
    enteranimalscreengeneral.ui \
    enteranimalscreennew.ui \
    userpreferencesscreen2.ui \
    adminparentsscreen.ui \
    owneranimalsscreen.ui
