# -------------------------------------------------
# Project created by QtCreator 2013-11-10T20:25:10
# -------------------------------------------------
QT += testlib
QT -= gui
TARGET = tst_testtest
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
INCLUDEPATH += ../../src
SOURCES += ../../src/memory/memory.cpp \
    ../../src/memory/debugmemory.cpp \
    ../../src/cpu/opcodetable.cpp \
    ../../src/cpu/decoder/instructiondecoder.cpp \
    ../../src/cpu/tostring/instructiontostring.cpp \
    ../../src/cpu/encoder/instructionencoder.cpp \
    testmemory.cpp \
    main.cpp \
    testioportlist.cpp \
    testinstructionstream.cpp \
    testregisterfile.cpp \
    testexecoperand.cpp \
    testdecoderencoder.cpp \
    ../../src/cpu/executer/instructionexecuter.cpp \
    ../../src/cpu/executer/execute.cpp \
    testexecute.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
HEADERS += ../../src/memory/memory.h \
    ../../src/memory/debugmemory.h \
    ../../src/io/ioportlist.h \
    ../../src/io/ioport.h \
    ../../src/interrupt/interrupt.h \
    ../../src/cpu/opcodetable.h \
    ../../src/cpu/instructionformat.h \
    ../../src/cpu/cputype.h \
    ../../src/cpu/decoder/instructionstreamfrommemory.h \
    ../../src/cpu/decoder/instructionstreamfromfile.h \
    ../../src/cpu/decoder/instructionstream.h \
    ../../src/cpu/decoder/instructiondecoder.h \
    ../../src/cpu/executer/operand/execwriteoperand.h \
    ../../src/cpu/executer/operand/execsegmentregisteroperand.h \
    ../../src/cpu/executer/operand/execreadwriteoperand.h \
    ../../src/cpu/executer/operand/execreadoperand.h \
    ../../src/cpu/executer/operand/execmemoryoperand.h \
    ../../src/cpu/executer/operand/execimmediateoperand.h \
    ../../src/cpu/executer/operand/execgpregisteroperand.h \
    ../../src/cpu/register/registerfile.h \
    ../../src/cpu/register/gpregister.h \
    ../../src/cpu/register/flags.h \
    ../../src/type.h \
    ../../src/cpu/tostring/instructiontostring.h \
    ../../src/cpu/encoder/instructionencoder.h \
    testmemory.h \
    testioportlist.h \
    testinstructionstream.h \
    testregisterfile.h \
    testexecoperand.h \
    testdecoderencoder.h \
    ../../src/cpu/executer/instructionexecuter.h \
    ../../src/cpu/executer/operand/execoperands.h \
    ../../src/cpu/executer/execute.h \
    testexecute.h
