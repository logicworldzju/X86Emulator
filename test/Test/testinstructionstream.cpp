#include "testinstructionstream.h"
#include <QtTest/QTest>
#include "cpu/decoder/instructionstreamfromfile.h"
#include "cpu/decoder/instructionstreamfrommemory.h"
#include "memory/debugmemory.h"
TestInstructionStream::TestInstructionStream(QObject *parent) :
    QObject(parent)
{
}

void TestInstructionStream::testStreamFromFile()
{
    InstructionStreamFromFile fromFile("../asm/1.com");
    fromFile.startReadOneInstruction();
    fromFile.get8Bits();
    fromFile.get16Bits();
    fromFile.get32Bits();
    fromFile.get64Bits();
    fromFile.endReadOneInstruction();
    QCOMPARE(fromFile.readLastInstruction().size(),15u);
}

void TestInstructionStream::testStreamFromMemory()
{
    DebugMemory debugMemory;
    InstructionStreamFromMemory fromMemory(debugMemory);
    fromMemory.setIP(1<<20);
    fromMemory.startReadOneInstruction();
    fromMemory.get8Bits();
    fromMemory.get16Bits();
    fromMemory.get32Bits();
    fromMemory.get64Bits();
    fromMemory.endReadOneInstruction();
    QCOMPARE(fromMemory.readLastInstruction().size(),15u);
}
