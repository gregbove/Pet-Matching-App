#-------------------------------------------------
#
# Project created by QtCreator 2021-04-07T09:09:24
#
#-------------------------------------------------

QT       += core gui

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
    enteranimalscreennew.cpp

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
    enteranimalscreennew.h

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
    enteranimalscreennew.ui
