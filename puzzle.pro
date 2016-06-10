#-------------------------------------------------
#
# Project created by QtCreator 2016-05-15T11:31:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = puzzle
TEMPLATE = app


SOURCES += main.cpp\
        okno.cpp \
    config.cpp

HEADERS  += okno.h \
    logika.h \
    config.h

FORMS    += okno.ui \
    config.ui
