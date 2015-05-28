#-------------------------------------------------
#
# Project created by QtCreator 2015-05-28T22:35:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = humanPop
TEMPLATE = app


SOURCES += main.cpp\
    Map.cpp \
    SimulationSystem.cpp \
    Agent.cpp \
    Cell.cpp \
    Mainwindow.cpp \
    Resource.cpp

HEADERS  += \
    Map.h \
    SimulationSystem.h \
    Agent.h \
    Mainwindow.h \
    Cell.h \
    Resource.h

FORMS    += mainwindow.ui

DISTFILES += \
    map.txt
