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
    cpu/opcodetable.cpp \
    memory/memory.cpp \
    memory/debugmemory.cpp \
    cpu/decoder/instructiondecoder.cpp \
    cpu/encoder/instructionencoder.cpp

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
    cpu/instructioncode.h

FORMS    += gui/mainwindow.ui















































