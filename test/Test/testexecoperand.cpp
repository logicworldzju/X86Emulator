#include "testexecoperand.h"
#include <QtTest/QTest>
#include "cpu/executer/operand/execimmediateoperand.h"
#include "cpu/executer/operand/execgpregisteroperand.h"
#include "cpu/executer/operand/execsegmentregisteroperand.h"
#include "cpu/executer/operand/execmemoryoperand.h"
#include "memory/debugmemory.h"

TestExecOperand::TestExecOperand(QObject *parent) :
    QObject(parent)
{
}

void TestExecOperand::testExecOperandImmediate()
{
    ExecImmediateOperand operand(0xff,DATA_SIZE_BYTE);
    QCOMPARE(operand.getS8(),s8(-1));
    QCOMPARE(operand.getS16(),s16(-1));
    QCOMPARE(operand.getS32(),s32(-1));
    QCOMPARE(operand.getS64(),s64(-1));

    QCOMPARE(operand.getU8(),u8(0xff));
    QCOMPARE(operand.getU16(),u16(0xff));
    QCOMPARE(operand.getU32(),u32(0xff));
    QCOMPARE(operand.getU64(),u64(0xff));

}

void TestExecOperand::testExecOperandGPR()
{
    RegisterFile file;
    file.setGPR8BitsLow(RAX,0xff);

    ExecGPRegisterOperand operand(file,RAX,DATA_SIZE_BYTE,false);
    QCOMPARE(operand.getU16(),u16(0xff));
    QCOMPARE(operand.getS16(),s16(-1));

    operand.setU8(0xcc);
    QCOMPARE(file.getGPR8Bits(RAX),u8(0xcc));

}

void TestExecOperand::testExecOperandCR()
{
    RegisterFile file;
    file.setSR(CS,0x1234);

    ExecSegmentRegisterOperand operand(file,CS);
    QCOMPARE(file.getSR(CS),u16(0x1234));

    operand.setU16(0x4321);
    QCOMPARE(file.getSR(CS),u16(0x4321));
}

void TestExecOperand::testExecOperandMemory()
{
    DebugMemory memory;
    memory.startAccess(Memory::DEBUG_ACCESS);
    memory.set32Bits(0x1234,0x6767);
    memory.endAccess();
    ExecMemoryOperand operand(memory,0x1234,DATA_SIZE_DWORD);
    QCOMPARE(operand.getU8(),u8(0x67));
    operand.setU32(0x12334455);
    QCOMPARE(operand.getU32(),u32(0x12334455));
}
