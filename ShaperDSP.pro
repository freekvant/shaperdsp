#-------------------------------------------------
#
# Project created by QtCreator 2013-01-28T10:20:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShaperDSP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    collect.cpp \
    limitparams.cpp

HEADERS  += mainwindow.h \
    collect.h \
    limitparams.h

FORMS    += mainwindow.ui \
    collect.ui \
    limitparams.ui
