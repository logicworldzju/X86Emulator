#-------------------------------------------------
#
# Project created by QtCreator 2013-11-05T13:38:54
#
#-------------------------------------------------

QT       += core gui
CONFIG += console
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = X86Emulator
TEMPLATE = app
DESTDIR = ..


SOURCES += main.cpp\
        gui/mainwindow.cpp \
    cpu/opcodetable.cpp \
    memory/memory.cpp \
    memory/debugmemory.cpp \
    cpu/decoder/instructiondecoder.cpp \
    cpu/encoder/instructionencoder.cpp \
    cpu/tostring/instructiontostring.cpp \
    bios/bios.cpp \
    cpu/executer/instructionexecuter.cpp \
    cpu/executer/execute.cpp \
    gui/video.cpp \
    cpu/debugcpu.cpp \
    cpu/cpu.cpp \
    gui/consoleimage.cpp \
    gui/consolewidget.cpp \
    gui/charactercode.cpp

HEADERS  += gui/mainwindow.h \
    cpu/instructionformat.h \
    cpu/opcodetable.h \
    memory/memory.h \
    type.h \
    memory/debugmemory.h \
    cpu/registerfile.h \
    cpu/gpregister.h \
    io/ioport.h \
    io/ioportlist.h \
    interrupt/interrupt.h \
    cpu/executer/operand/execreadoperand.h \
    cpu/executer/operand/execwriteoperand.h \
    cpu/executer/operand/execreadwriteoperand.h \
    cpu/executer/operand/execmemoryoperand.h \
    cpu/executer/operand/execgpregisteroperand.h \
    cpu/executer/operand/execsegmentregisteroperand.h \
    cpu/executer/operand/execimmediateoperand.h \
    cpu/instructionstream.h \
    cpu/instructionstreamfrommemory.h \
    cpu/register/registerfile.h \
    cpu/register/gpregister.h \
    cpu/register/flags.h \
    cpu/decoder/instructionstreamfrommemory.h \
    cpu/decoder/instructionstream.h \
    cpu/decoder/instructiondecoder.h \
    cpu/decoder/instructionstreamfromfile.h \
    cpu/cputype.h \
    cpu/encoder/instructionencoder.h \
    cpu/instructioncode.h \
    cpu/tostring/instructiontostring.h \
    bios/bios.h \
    cpu/executer/instructionexecuter.h \
    cpu/executer/execute.h \
    gui/video.h \
    cpu/debugcpu.h \
    cpu/cpu.h \
    gui/consoleimage.h \
    gui/consolewidget.h \
    gui/charactercode.h

FORMS    += gui/mainwindow.ui

















































