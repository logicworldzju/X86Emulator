#-------------------------------------------------
#
# Project created by QtCreator 2013-11-05T13:38:54
#
#-------------------------------------------------

QT       += core gui

TARGET = X86Emulator
TEMPLATE = app


SOURCES += main.cpp\
        gui/mainwindow.cpp \
    cpu/opcodetable.cpp

HEADERS  += gui/mainwindow.h \
    cpu/instructionformat.h \
    cpu/opcodetable.h

FORMS    += gui/mainwindow.ui



