#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = LsystemDrawer
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/lsystem.cpp \
    src/lsystemexamples.cpp

HEADERS  += src/mainwindow.h \
    src/lsystem.h \
    src/lsystemexamples.h

FORMS    += ui/mainwindow.ui

win32:QMAKE_CXXFLAGS += -W3
!win32:QMAKE_CXXFLAGS += -Wall
