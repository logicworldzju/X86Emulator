#include "testexecute.h"
#include <QDebug>
#include "cpu/executer/operand/execgpregisteroperand.h"
#include "cpu/executer/operand/execimmediateoperand.h"
#include "cpu/executer/operand/execmemoryoperand.h"
#include "cpu/executer/operand/execsegmentregisteroperand.h"

TestExecute::TestExecute(QObject *parent) :
    QObject(parent)
{
}

void TestExecute::testADD()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(0x11,DATA_SIZE_BYTE);
        executeADD(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);
        QCOMPARE(int(registerFile.getGPR16Bits(RAX)),0x11);
    }
    {
        fillRegisterFile(registerFile);
        //signed extent case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(0x81,DATA_SIZE_BYTE);
        executeADD(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);
        QCOMPARE(int(registerFile.getGPR16Bits(RAX)),0xff81);
    }
    {
        fillRegisterFile(registerFile);
        //flags case 1.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0x8123);
        ExecImmediateOperand src(0x8123,DATA_SIZE_WORD);
        executeADD(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);
        QCOMPARE(int(registerFile.getGPR16Bits(RAX)),0x0246);
        QCOMPARE(registerFile.getFlagsBits().CF,(unsigned int)(1));
        QCOMPARE(registerFile.getFlagsBits().PF,(unsigned int)(0));
        QCOMPARE(registerFile.getFlagsBits().AF,(unsigned int)(0));
        QCOMPARE(registerFile.getFlagsBits().ZF,(unsigned int)(0));
        QCOMPARE(registerFile.getFlagsBits().SF,(unsigned int)(0));
        QCOMPARE(registerFile.getFlagsBits().OF,(unsigned int)(1));
    }
    {
        fillRegisterFile(registerFile);
        //flags case 2.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0x7f23);
        ExecImmediateOperand src(0x8123,DATA_SIZE_WORD);
        executeADD(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);
        QCOMPARE(int(registerFile.getGPR16Bits(RAX)),0x0046);
        QCOMPARE(registerFile.getFlagsBits().CF,(unsigned int)(1));
        QCOMPARE(registerFile.getFlagsBits().PF,(unsigned int)(0));
        QCOMPARE(registerFile.getFlagsBits().AF,(unsigned int)(0));
        QCOMPARE(registerFile.getFlagsBits().ZF,(unsigned int)(0));
        QCOMPARE(registerFile.getFlagsBits().SF,(unsigned int)(0));
        QCOMPARE(registerFile.getFlagsBits().OF,(unsigned int)(0));
    }
    {
        fillRegisterFile(registerFile);
        //flags case 3.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0x4123);
        ExecImmediateOperand src(0x4123,DATA_SIZE_WORD);
        executeADD(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);
        QCOMPARE(int(registerFile.getGPR16Bits(RAX)),0x8246);
        QCOMPARE(registerFile.getFlagsBits().CF,(unsigned int)(0));
        QCOMPARE(registerFile.getFlagsBits().PF,(unsigned int)(0));
        QCOMPARE(registerFile.getFlagsBits().AF,(unsigned int)(0));
        QCOMPARE(registerFile.getFlagsBits().ZF,(unsigned int)(0));
        QCOMPARE(registerFile.getFlagsBits().SF,(unsigned int)(1));
        QCOMPARE(registerFile.getFlagsBits().OF,(unsigned int)(1));
    }
    {
        fillRegisterFile(registerFile);
        //flags case 4.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0x8000);
        ExecImmediateOperand src(0x8000,DATA_SIZE_WORD);
        executeADD(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);
        QCOMPARE(int(registerFile.getGPR16Bits(RAX)),0x0000);
        QCOMPARE(registerFile.getFlagsBits().CF,(unsigned int)(1));
        QCOMPARE(registerFile.getFlagsBits().PF,(unsigned int)(1));
        QCOMPARE(registerFile.getFlagsBits().AF,(unsigned int)(0));
        QCOMPARE(registerFile.getFlagsBits().ZF,(unsigned int)(1));
        QCOMPARE(registerFile.getFlagsBits().SF,(unsigned int)(0));
        QCOMPARE(registerFile.getFlagsBits().OF,(unsigned int)(1));
    }

}

void TestExecute::testPOP()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //16bits data and 16bits address case pop to rax.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        memory.startAccess(memory.DEBUG_ACCESS);
        memory.set16Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RSP),0x1234);
        memory.endAccess();
        executePOP(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);
        QCOMPARE(u32(registerFile.getGPR16Bits(RAX)),u32(0x1234));
        QCOMPARE(u32(registerFile.getGPR16Bits(RSP)),u32(0x4446));
    }
    {
        fillRegisterFile(registerFile);
        //16bits data and 16bits address case pop to ds

        ExecSegmentRegisterOperand dest(registerFile,DS);
        memory.startAccess(memory.DEBUG_ACCESS);
        memory.set16Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RSP),0x1234);
        memory.endAccess();
        executePOP(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);
        QCOMPARE(u32(registerFile.getSR(DS)),u32(0x1234));
        QCOMPARE(u32(registerFile.getSSR(DS)),u32(0x12340));
        QCOMPARE(u32(registerFile.getGPR16Bits(RSP)),u32(0x4446));
    }
    {
        fillRegisterFile(registerFile);
        //32bits data and 16bits address case pop to ds
        ExecGPRegisterOperand dest(registerFile,RDX,DATA_SIZE_DWORD,false);

        memory.startAccess(memory.DEBUG_ACCESS);
        memory.set32Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RSP),0x12345678);
        memory.endAccess();
        executePOP(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(registerFile.getGPR32Bits(RDX)),u32(0x12345678));
        QCOMPARE(u32(registerFile.getGPR16Bits(RSP)),u32(0x4448));
    }
}

void TestExecute::testPUSH()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //16bits data and 16bits address case push from rax.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0x1234);

        executePUSH(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(registerFile.getGPR16Bits(RSP)),u32(0x4442));

        memory.startAccess(memory.DEBUG_ACCESS);
        QCOMPARE((u32)memory.get16Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RSP)),
                 u32(0x1234));
        memory.endAccess();

    }
    {
        fillRegisterFile(registerFile);
        //16bits data and 16bits address case push from es.
        ExecSegmentRegisterOperand dest(registerFile,ES);

        executePUSH(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(registerFile.getGPR16Bits(RSP)),u32(0x4442));

        memory.startAccess(memory.DEBUG_ACCESS);
        QCOMPARE((u32)memory.get16Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RSP)),
                 u32(0x0000));
        memory.endAccess();

    }
    {
        fillRegisterFile(registerFile);
        //32bits data and 16bits address case push from es.
        ExecGPRegisterOperand dest(registerFile,RBX,DATA_SIZE_DWORD,false);

        executePUSH(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(registerFile.getGPR16Bits(RSP)),u32(0x4440));

        memory.startAccess(memory.DEBUG_ACCESS);
        QCOMPARE((u32)memory.get32Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RSP)),
                 u32(0x33333333));
        memory.endAccess();

    }
}

void TestExecute::testOR()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(0x11,DATA_SIZE_BYTE);
        executeOR(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);
        QCOMPARE(int(registerFile.getGPR16Bits(RAX)),0x11);
    }
    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RSP,DATA_SIZE_DWORD,false);
        ExecImmediateOperand src(0x81,DATA_SIZE_BYTE);
        executeOR(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);
        QCOMPARE(u32(registerFile.getGPR32Bits(RSP)),u32(0xffffffc5));
    }
}

void TestExecute::testAND()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(0x11,DATA_SIZE_BYTE);
        executeAND(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);
        QCOMPARE(int(registerFile.getGPR16Bits(RAX)),0x0);
    }
    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RDI,DATA_SIZE_DWORD,false);
        ExecImmediateOperand src(0x81,DATA_SIZE_BYTE);
        executeAND(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);
        QCOMPARE(u32(registerFile.getGPR32Bits(RDI)),u32(0x77777701));
    }
}

void TestExecute::testXOR()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(0x11,DATA_SIZE_BYTE);
        executeXOR(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);
        QCOMPARE(int(registerFile.getGPR16Bits(RAX)),0x11);
    }
    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RDI,DATA_SIZE_DWORD,false);
        ExecImmediateOperand src(0x81,DATA_SIZE_BYTE);
        executeXOR(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);
        QCOMPARE(u32(registerFile.getGPR32Bits(RDI)),u32(0x888888f6));
    }
}

void TestExecute::testADC()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffee);
        ExecImmediateOperand src(0x11,DATA_SIZE_WORD);

        executeADC(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().PF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().AF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().ZF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().SF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
    {
        fillRegisterFile(registerFile);
        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0x7fee);
        ExecImmediateOperand src(0x7f11,DATA_SIZE_WORD);

        executeADC(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0xff00);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().PF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().AF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().ZF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().SF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)1);
    }
}

void TestExecute::testSBB()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffee);
        ExecImmediateOperand src(0x11,DATA_SIZE_WORD);

        executeSBB(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0xffdc);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().PF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().AF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().ZF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().SF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
    {
        fillRegisterFile(registerFile);
        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0x7f11);
        ExecImmediateOperand src(0x7fee,DATA_SIZE_WORD);

        executeSBB(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0xff22);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().PF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().AF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().ZF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().SF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
    {
        fillRegisterFile(registerFile);
        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0x4000);
        ExecImmediateOperand src(0xc000,DATA_SIZE_WORD);

        executeSBB(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0x7fff);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().PF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().AF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().ZF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().SF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
}

void TestExecute::testSUB()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
//        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffee);
        ExecImmediateOperand src(0x11,DATA_SIZE_WORD);

        executeSUB(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0xffdd);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().PF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().AF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().ZF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().SF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
    {
        fillRegisterFile(registerFile);
//        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0x7f11);
        ExecImmediateOperand src(0x7fee,DATA_SIZE_WORD);

        executeSUB(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0xff23);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().PF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().AF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().ZF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().SF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
    {
        fillRegisterFile(registerFile);
//        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0x4000);
        ExecImmediateOperand src(0xc000,DATA_SIZE_WORD);

        executeSUB(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0x8000);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().PF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().AF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().ZF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().SF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)1);
    }
}

void TestExecute::testCMP()
{

}

void TestExecute::testINC()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
//        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffee);

        executeINC(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0xffef);
//        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().PF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().AF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().ZF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().SF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
}

void TestExecute::testDEC()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
//        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffee);

        executeDEC(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0xffed);
//        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().PF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().AF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().ZF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().SF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
}

void TestExecute::testNOT()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffee);

        executeNOT(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0x0011);
    }
}

void TestExecute::testNEG()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffee);

        executeNEG(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0x0012);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().PF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().AF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().ZF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().SF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
}

void TestExecute::testROL()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(1,DATA_SIZE_BYTE);
        dest.setU16(0xffee);

        executeROL(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0xffdd);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(4,DATA_SIZE_BYTE);
        dest.setU16(0xffee);

        executeROL(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0xfeef);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)1);
//        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
}

void TestExecute::testROR()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(1,DATA_SIZE_BYTE);
        dest.setU16(0xffee);

        executeROR(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0x7ff7);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)1);
    }
    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(4,DATA_SIZE_BYTE);
        dest.setU16(0xffee);

        executeROR(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0xeffe);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)1);
//        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
}

void TestExecute::testRCL()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(1,DATA_SIZE_BYTE);
        dest.setU16(0xffee);

        executeRCL(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0xffdd);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
    {
        fillRegisterFile(registerFile);
        registerFile.getFlagsBits().CF=0;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(4,DATA_SIZE_BYTE);
        dest.setU16(0xffee);

        executeRCL(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0xfee7);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)1);
//        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
}

void TestExecute::testRCR()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(1,DATA_SIZE_BYTE);
        dest.setU16(0xffee);

        executeRCR(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0xfff7);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
    {
        fillRegisterFile(registerFile);
        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(4,DATA_SIZE_BYTE);
        dest.setU16(0xffee);

        executeRCR(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0xdffe);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)1);
//        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
}

void TestExecute::testSHR()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(1,DATA_SIZE_BYTE);
        dest.setU16(0xffee);

        executeSHR(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0x7ff7);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)1);
    }
    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(4,DATA_SIZE_BYTE);
        dest.setU16(0xffee);

        executeSHR(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0x0ffe);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)1);
//        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
}

void TestExecute::testSHL_SAL()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(1,DATA_SIZE_BYTE);
        dest.setU16(0xffee);

        executeSHL_SAL(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0xffdc);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(4,DATA_SIZE_BYTE);
        dest.setU16(0xffee);

        executeSHL_SAL(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0xfee0);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)1);
//        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
}

void TestExecute::testSAR()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(1,DATA_SIZE_BYTE);
        dest.setU16(0xffee);

        executeSAR(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0xfff7);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecImmediateOperand src(4,DATA_SIZE_BYTE);
        dest.setU16(0xffee);

        executeSAR(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(dest.getU16()),(u32)0xfffe);
        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)1);
//        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
    }
}

void TestExecute::testJx()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecImmediateOperand dest(1,DATA_SIZE_BYTE);

        executeJBE(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(registerFile.getIP()),(u32)0x1235);
    }
    {
        fillRegisterFile(registerFile);
        registerFile.setIP(0x1122ffff);
        registerFile.getFlagsBits().ZF=1;
        //normal case.
        ExecImmediateOperand dest(1,DATA_SIZE_BYTE);

        executeJBE(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(registerFile.getIP()),(u32)0x00000000);
    }
}

void TestExecute::testJRCXZ()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        registerFile.setGPR16Bits(RCX,0);
        //normal case.
        ExecImmediateOperand dest(1,DATA_SIZE_BYTE);

        executeJRCXZ(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(registerFile.getIP()),(u32)0x1234);
    }
    {
        fillRegisterFile(registerFile);
        registerFile.setIP(0x1122ffff);
//        registerFile.getFlagsBits().ZF=1;
        registerFile.setGPR32Bits(RCX,0);
        //normal case.
        ExecImmediateOperand dest(1,DATA_SIZE_BYTE);

        executeJRCXZ(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(registerFile.getIP()),(u32)0x00000000);
    }
}

void TestExecute::testLOOP()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        registerFile.setGPR16Bits(RCX,0);
        //normal case.
        ExecImmediateOperand dest(1,DATA_SIZE_BYTE);

        executeLOOP(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(registerFile.getIP()),(u32)0x1235);
    }
    {
        fillRegisterFile(registerFile);
        registerFile.setIP(0x1122ffff);
//        registerFile.getFlagsBits().ZF=1;
        registerFile.setGPR32Bits(RCX,1);
        //normal case.
        ExecImmediateOperand dest(1,DATA_SIZE_BYTE);

        executeLOOP(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(registerFile.getIP()),(u32)0x1122ffff);
    }
}
class IOPortTestINOUT:public IOPort
{
public:
    u32 readFromPort(Memory &memory, RegisterFile &registerFile)
    {
        (void)memory;(void)registerFile;
        return 0x12345678;
    }
    void write2Port(u32 value, Memory &memory, RegisterFile &registerFile)
    {
        (void)memory;(void)registerFile;
        writeValue=value;
    }
    u32 writeValue;
};
void TestExecute::testIN()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);
    IOPortTestINOUT ioPort;
    ioPortList.add2PortList(1,&ioPort);

    {
        fillRegisterFile(registerFile);
//        registerFile.setGPR16Bits(RCX,0);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_DWORD,false);
        ExecImmediateOperand src(1,DATA_SIZE_BYTE);

        executeIN(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(registerFile.getGPR32Bits(RAX)),(u32)0x12345678);
    }
//    std::cout<<registerFile.toString();
}

void TestExecute::testOUT()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);
    IOPortTestINOUT ioPort;
    ioPortList.add2PortList(1,&ioPort);

    {
        fillRegisterFile(registerFile);
//        registerFile.setGPR16Bits(RCX,0);
        //normal case.
        ExecImmediateOperand dest(1,DATA_SIZE_BYTE);
        ExecGPRegisterOperand src(registerFile,RAX,DATA_SIZE_DWORD,false);
        src.setU32(0x87654321);

        executeOUT(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(ioPort.writeValue),(u32)0x87654321);
    }
    {
        fillRegisterFile(registerFile);
//        registerFile.setGPR16Bits(RCX,0);
        //normal case.
        ExecImmediateOperand dest(1,DATA_SIZE_BYTE);
        ExecGPRegisterOperand src(registerFile,RAX,DATA_SIZE_WORD,false);
        src.setU16(0x4321);

        executeOUT(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(ioPort.writeValue),(u32)0x4321);
    }
}

void TestExecute::testIMUL3()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecGPRegisterOperand src(registerFile,RAX,DATA_SIZE_WORD,false);
        src.setU16(0x1234);
        ExecImmediateOperand src2(0xff,DATA_SIZE_BYTE);

        executeIMUL3(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,&src2,registerFile,memory,ioPortList);

        QCOMPARE(u16(registerFile.getGPR16Bits(RAX)),(u16)(-0x1234));
        QCOMPARE(u32(registerFile.getFlagsBits().OF),u32(0));
    }
    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecGPRegisterOperand src(registerFile,RAX,DATA_SIZE_WORD,false);
        src.setU16(0x1234);
        ExecImmediateOperand src2(0xff,DATA_SIZE_WORD);

        executeIMUL3(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,&src2,registerFile,memory,ioPortList);

        QCOMPARE(u16(registerFile.getGPR16Bits(RAX)),(u16)(0x21CC));
        QCOMPARE(u32(registerFile.getFlagsBits().OF),u32(1));
    }
}

void TestExecute::testIMUL1()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffff);

        executeIMUL1(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u16(registerFile.getGPR16Bits(RAX)),(u16)(1));
        QCOMPARE(u16(registerFile.getGPR16Bits(RDX)),(u16)(0));
        QCOMPARE(u32(registerFile.getFlagsBits().OF),u32(0));
    }
    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0x12);

        executeIMUL1(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u16(registerFile.getGPR16Bits(RAX)),(u16)(0x144));
        QCOMPARE(u16(registerFile.getGPR16Bits(RDX)),(u16)(0));
        QCOMPARE(u32(registerFile.getFlagsBits().OF),u32(0));
    }
}

void TestExecute::testMUL()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffff);

        executeMUL1(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u16(registerFile.getGPR16Bits(RAX)),(u16)(0x0001));
        QCOMPARE(u16(registerFile.getGPR16Bits(RDX)),(u16)(0xFFFE));
        QCOMPARE(u32(registerFile.getFlagsBits().OF),u32(1));
    }
    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0x12);

        executeMUL1(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u16(registerFile.getGPR16Bits(RAX)),(u16)(0x144));
        QCOMPARE(u16(registerFile.getGPR16Bits(RDX)),(u16)(0));
        QCOMPARE(u32(registerFile.getFlagsBits().OF),u32(0));
    }
}

void TestExecute::testIDIV()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        registerFile.setGPR16Bits(RAX,0x1122);
        registerFile.setGPR16Bits(RDX,0x3344);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RBX,DATA_SIZE_WORD,false);
        dest.setU16(0xffff);

        executeIDIV1(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u16(registerFile.getGPR16Bits(RAX)),(u16)(-0x1122));
        QCOMPARE(u16(registerFile.getGPR16Bits(RDX)),(u16)(0x0));
    }

}

void TestExecute::testDIV()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        registerFile.setGPR16Bits(RAX,0x1122);
        registerFile.setGPR16Bits(RDX,0x3344);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RBX,DATA_SIZE_WORD,false);
        dest.setU16(0xffff);

        executeDIV1(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u16(registerFile.getGPR16Bits(RAX)),(u16)(0x3344));
        QCOMPARE(u16(registerFile.getGPR16Bits(RDX)),(u16)(0x4466));
    }
}

void TestExecute::testXCHG()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RBX,DATA_SIZE_WORD,false);
        ExecGPRegisterOperand src(registerFile,RAX,DATA_SIZE_WORD,false);

        executeXCHG(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u16(registerFile.getGPR16Bits(RAX)),(u16)(0x3333));
        QCOMPARE(u16(registerFile.getGPR16Bits(RBX)),(u16)(0x0000));
    }
}

void TestExecute::testMove()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RBX,DATA_SIZE_WORD,false);
        ExecGPRegisterOperand src(registerFile,RAX,DATA_SIZE_WORD,false);

        executeXCHG(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u16(registerFile.getGPR16Bits(RBX)),(u16)(0x0000));
    }
}

void TestExecute::testLEA()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RBX,DATA_SIZE_WORD,false);
//        ExecGPRegisterOperand src(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecMemoryOperand src(memory,0x100,0x1234,DATA_SIZE_DWORD);

        executeLEA(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u16(registerFile.getGPR16Bits(RBX)),(u16)(0x1234));
    }
}

void TestExecute::testCBW()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        registerFile.setGPR8Bits(RAX,0xf0);
        //normal case.
        executeCBW_CWDE_CDQE(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,NULL,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u16(registerFile.getGPR16Bits(RAX)),(u16)(0xfff0));
    }
}

void TestExecute::testCWD()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        registerFile.setGPR16Bits(RAX,0xff00);
        //normal case.
        executeCWD_CDQ_CQO(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,NULL,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u16(registerFile.getGPR16Bits(RDX)),(u16)(0xffff));
    }
}

void TestExecute::testSAHF()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        registerFile.setGPR16Bits(RAX,0xf000);
        //normal case.
        executeSAHF(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,NULL,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(registerFile.getFlagsBits().CF,(unsigned int)(0));
        QCOMPARE(registerFile.getFlagsBits().PF,(unsigned int)(0));
        QCOMPARE(registerFile.getFlagsBits().AF,(unsigned int)(1));
        QCOMPARE(registerFile.getFlagsBits().ZF,(unsigned int)(1));
        QCOMPARE(registerFile.getFlagsBits().SF,(unsigned int)(1));
    }
}

void TestExecute::testLAHF()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);
    {
        fillRegisterFile(registerFile);

        registerFile.getFlagsBits().CF=(unsigned int)(0);
        registerFile.getFlagsBits().PF=(unsigned int)(0);
        registerFile.getFlagsBits().AF=(unsigned int)(1);
        registerFile.getFlagsBits().ZF=(unsigned int)(1);
        registerFile.getFlagsBits().SF=(unsigned int)(1);
        //        registerFile.setGPR16Bits(RAX,0xf000);
        //normal case.
        executeLAHF(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,NULL,NULL,NULL,registerFile,memory,ioPortList);
        QCOMPARE(registerFile.getFlags8Bits(),u8(0xd0));
        QCOMPARE((u32)registerFile.getGPR8BitsHigh(RAX),u32(0xD0));
    }
}

void TestExecute::testLDS()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RBX,DATA_SIZE_WORD,false);
//        ExecGPRegisterOperand src(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecMemoryOperand src(memory,0x100,0x1234,DATA_SIZE_DWORD);
        src.setU32(0x12345678);

        executeLDS(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u16(registerFile.getGPR16Bits(RBX)),(u16)(0x5678));
        QCOMPARE(u16(registerFile.getSR(DS)),u16(0x1234));
        QCOMPARE(u32(registerFile.getSSR(DS)),u32(0x12340));
    }
}

void TestExecute::testLES()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RSI,DATA_SIZE_WORD,false);
//        ExecGPRegisterOperand src(registerFile,RAX,DATA_SIZE_WORD,false);
        ExecMemoryOperand src(memory,0x100,0x1234,DATA_SIZE_DWORD);
        src.setU32(0x12345678);

        executeLES(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u16(registerFile.getGPR16Bits(RSI)),(u16)(0x5678));
        QCOMPARE(u16(registerFile.getSR(ES)),u16(0x1234));
        QCOMPARE(u32(registerFile.getSSR(ES)),u32(0x12340));
    }
}

void TestExecute::testXLAT()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        registerFile.setGPR8BitsLow(RAX,(u8)0x10);
        registerFile.setGPR32Bits(RBX,0x1234);
        registerFile.setSR(DS,1);
        registerFile.setSSR(DS,1<<4);
        //normal case.
        ExecMemoryOperand src(memory,0x20,0x1234,DATA_SIZE_DWORD);
        src.setU32(0x12345678);


        executeXLAT(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,NULL,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u16(registerFile.getGPR8Bits(RAX)),(u16)(0x78));
    }
}

void TestExecute::testCMC()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.

        executeCMC(ENV_16_BITS,EFFECTIVE_32_BITS,EFFECTIVE_16_BITS,DS,NULL,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(registerFile.getFlagsBits().CF),u32(1));

    }
}

void TestExecute::testINT()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        memory.startAccess(memory.DEBUG_ACCESS);
        memory.set32Bits(1*4,0x12348765);
        memory.endAccess();
        //normal case.

        ExecImmediateOperand dest(1,DATA_SIZE_BYTE);

        executeINT(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(registerFile.getSR(CS)),u32(0x1234));
        QCOMPARE(u32(registerFile.getSSR(CS)),u32(0x1234<<4));
        QCOMPARE(u32(registerFile.getIP()),u32(0x8765));
        QCOMPARE(u32(registerFile.getGPR32Bits(RSP)),u32(0x4444443e));

        memory.startAccess(memory.DEBUG_ACCESS);

        QCOMPARE(u48(memory.get64Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RSP))),
                 u48(0x000011111234L));
        memory.endAccess();
//        QCOMPARE(u32(registerFile.getFlagsBits().CF),u32(1));
    }
}

void TestExecute::testIRET()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        memory.startAccess(memory.DEBUG_ACCESS);
        memory.set32Bits(1*4,0x12348765);
        memory.endAccess();
        //normal case.

        ExecImmediateOperand dest(1,DATA_SIZE_BYTE);

        executeINT(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(registerFile.getSR(CS)),u32(0x1234));
        QCOMPARE(u32(registerFile.getSSR(CS)),u32(0x1234<<4));
        QCOMPARE(u32(registerFile.getIP()),u32(0x8765));
        QCOMPARE(u32(registerFile.getGPR32Bits(RSP)),u32(0x4444443e));

        memory.startAccess(memory.DEBUG_ACCESS);

        QCOMPARE(u48(memory.get64Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RSP))),
                 u48(0x000011111234L));
        memory.endAccess();

        executeIRET_IRETD_IRETQ(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,NULL,NULL,NULL,registerFile,memory,ioPortList);
        QCOMPARE(u32(registerFile.getFlags16Bits()),u32(0));
        QCOMPARE(u32(registerFile.getIP()),u32(0x1234));
        QCOMPARE(u16(registerFile.getSR(CS)),(u16)0x1111);
        QCOMPARE(u32(registerFile.getSSR(CS)),(u32)0x11110);
//        QCOMPARE(u32(registerFile.getFlagsBits().CF),u32(1));
    }
}

void TestExecute::testPUSHF()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        registerFile.getFlagsBits().CF=1;
        //normal case.

        executePUSHFDQ(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,NULL,NULL,NULL,registerFile,memory,ioPortList);

//        QCOMPARE(u32(registerFile.getFlagsBits().CF),u32(1));

        memory.startAccess(memory.DEBUG_ACCESS);
        QCOMPARE(u32(memory.get16Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RSP))),
                 u32(1));
        memory.endAccess();

    }
}

void TestExecute::testPOPF()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        registerFile.getFlagsBits().CF=1;
        //normal case.

        executePUSHFDQ(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,NULL,NULL,NULL,registerFile,memory,ioPortList);

//        QCOMPARE(u32(registerFile.getFlagsBits().CF),u32(1));

        memory.startAccess(memory.DEBUG_ACCESS);
        QCOMPARE(u32(memory.get16Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RSP))),
                 u32(1));
        memory.endAccess();

        registerFile.getFlagsBits().CF=0;

        executePOPFDQ(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,NULL,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u16(registerFile.getFlags16Bits()),u16(1));
    }
}

void TestExecute::testCALLNEAR_Jz()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.

        ExecImmediateOperand src(1,DATA_SIZE_BYTE);

        executeCALLNEAR_Jz(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&src,NULL,NULL,registerFile,memory,ioPortList);

//        QCOMPARE(u32(registerFile.getFlagsBits().CF),u32(1));

        memory.startAccess(memory.DEBUG_ACCESS);
        QCOMPARE(u32(memory.get16Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RSP))),
                 u32(0x1234));
        memory.endAccess();
        QCOMPARE(u32(registerFile.getIP()),u32(0x1235));
    }
}

void TestExecute::testCALLNEAR_Ev()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.

        ExecImmediateOperand src(1,DATA_SIZE_BYTE);

        executeCALLNEAR_Ev(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&src,NULL,NULL,registerFile,memory,ioPortList);

//        QCOMPARE(u32(registerFile.getFlagsBits().CF),u32(1));

        memory.startAccess(memory.DEBUG_ACCESS);
        QCOMPARE(u32(memory.get16Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RSP))),
                 u32(0x1234));
        memory.endAccess();
        QCOMPARE(u32(registerFile.getIP()),u32(0x1));
    }
}

void TestExecute::testCALLFAR()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.

        ExecImmediateOperand src(1,DATA_SIZE_DWORD);

        executeCALLFAR_Ap(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&src,NULL,NULL,registerFile,memory,ioPortList);

//        QCOMPARE(u32(registerFile.getFlagsBits().CF),u32(1));

        memory.startAccess(memory.DEBUG_ACCESS);
        QCOMPARE(u32(memory.get32Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RSP))),
                 u32(0x11111234));
        memory.endAccess();
        QCOMPARE(u16(registerFile.getSR(CS)),u16(0));
        QCOMPARE(u32(registerFile.getIP()),u32(0x1));
    }
}

void TestExecute::testRETNEAR()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.

        ExecImmediateOperand src(1,DATA_SIZE_BYTE);

        executeCALLNEAR_Ev(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&src,NULL,NULL,registerFile,memory,ioPortList);

//        QCOMPARE(u32(registerFile.getFlagsBits().CF),u32(1));

        memory.startAccess(memory.DEBUG_ACCESS);
        QCOMPARE(u32(memory.get16Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RSP))),
                 u32(0x1234));
        memory.endAccess();
        QCOMPARE(u32(registerFile.getIP()),u32(0x1));
        QCOMPARE(u32(registerFile.getGPR16Bits(RSP)),u32(0x4442));

        executeRETNEAR(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&src,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(registerFile.getIP()),u32(0x1234));
        QCOMPARE(u32(registerFile.getGPR16Bits(RSP)),u32(0x4445));
    }
}

void TestExecute::testRETFAR()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.

        ExecImmediateOperand src(1,DATA_SIZE_DWORD);

        executeCALLFAR_Ap(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&src,NULL,NULL,registerFile,memory,ioPortList);

//        QCOMPARE(u32(registerFile.getFlagsBits().CF),u32(1));

        memory.startAccess(memory.DEBUG_ACCESS);
        QCOMPARE(u32(memory.get32Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RSP))),
                 u32(0x11111234));
        memory.endAccess();
        QCOMPARE(u16(registerFile.getSR(CS)),u16(0));
        QCOMPARE(u32(registerFile.getIP()),u32(0x1));
        QCOMPARE(u32(registerFile.getGPR16Bits(RSP)),u32(0x4440));

        executeRETFAR(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&src,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(registerFile.getIP()),u32(0x1234));
        QCOMPARE(u32(registerFile.getSR(CS)),u32(0x1111));
        QCOMPARE(u32(registerFile.getGPR16Bits(RSP)),u32(0x4445));


    }
}

void TestExecute::testJMPNEAR_J()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.

        ExecImmediateOperand src(1,DATA_SIZE_BYTE);

        executeJMPNEAR_J(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&src,NULL,NULL,registerFile,memory,ioPortList);

//        QCOMPARE(u32(registerFile.getFlagsBits().CF),u32(1));

//        memory.startAccess(memory.DEBUG_ACCESS);
//        QCOMPARE(u32(memory.get16Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RSP))),
//                 u32(0x1234));
//        memory.endAccess();
        QCOMPARE(u32(registerFile.getIP()),u32(0x1235));
    }
}

void TestExecute::testJMPNEAR_Ev()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.

        ExecImmediateOperand src(1,DATA_SIZE_BYTE);

        executeJMPNEAR_Ev(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&src,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(registerFile.getIP()),u32(0x1));
    }
}

void TestExecute::testJMPFAR()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        //normal case.

        ExecImmediateOperand src(1,DATA_SIZE_DWORD);

        executeJMPFAR_p(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&src,NULL,NULL,registerFile,memory,ioPortList);

//        QCOMPARE(u32(registerFile.getFlagsBits().CF),u32(1));

        QCOMPARE(u16(registerFile.getSR(CS)),u16(0));
        QCOMPARE(u32(registerFile.getIP()),u32(0x1));
    }
}

void TestExecute::testENTER()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        memory.startAccess(memory.DEBUG_ACCESS);
        memory.set16Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RBP)-2,0xcc);
        memory.endAccess();
        //normal case.

        ExecImmediateOperand dest(1,DATA_SIZE_DWORD);
        ExecImmediateOperand src(2,DATA_SIZE_DWORD);

        executeENTER(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

//        QCOMPARE(u32(registerFile.getFlagsBits().CF),u32(1));

//        QCOMPARE(u16(registerFile.getSR(CS)),u16(0));
//        QCOMPARE(u32(registerFile.getIP()),u32(0x1));
        QCOMPARE(u32(registerFile.getGPR16Bits(RBP)),u32(0x4444-2));
        QCOMPARE(u32(registerFile.getGPR16Bits(RSP)),u32(0x4444-2-2*2-1));

        memory.startAccess(memory.DEBUG_ACCESS);
        QCOMPARE(u32(memory.get16Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RBP))),
                 u32(0x5555));
        QCOMPARE(u32(memory.get16Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RBP)-2)),
                 u32(0xcc));
        QCOMPARE(u32(memory.get16Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RBP)-4)),
                 u32(0x4444-2));
        memory.endAccess();
    }
}

void TestExecute::testLEAVE()
{
    RegisterFile registerFile;

    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
        memory.startAccess(memory.DEBUG_ACCESS);
        memory.set16Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RBP)-2,0xcc);
        memory.endAccess();
        //normal case.

        ExecImmediateOperand dest(1,DATA_SIZE_DWORD);
        ExecImmediateOperand src(2,DATA_SIZE_DWORD);

        executeENTER(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

//        QCOMPARE(u32(registerFile.getFlagsBits().CF),u32(1));

//        QCOMPARE(u16(registerFile.getSR(CS)),u16(0));
//        QCOMPARE(u32(registerFile.getIP()),u32(0x1));
        QCOMPARE(u32(registerFile.getGPR16Bits(RBP)),u32(0x4444-2));
        QCOMPARE(u32(registerFile.getGPR16Bits(RSP)),u32(0x4444-2-2*2-1));

        memory.startAccess(memory.DEBUG_ACCESS);
        QCOMPARE(u32(memory.get16Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RBP))),
                 u32(0x5555));
        QCOMPARE(u32(memory.get16Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RBP)-2)),
                 u32(0xcc));
        QCOMPARE(u32(memory.get16Bits(registerFile.getSSR(SS)+registerFile.getGPR16Bits(RBP)-4)),
                 u32(0x4444-2));
        memory.endAccess();


        executeLEAVE(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,NULL,NULL,NULL,registerFile,memory,ioPortList);

        QCOMPARE(u32(registerFile.getGPR16Bits(RBP)),u32(0x5555));
        QCOMPARE(u32(registerFile.getGPR16Bits(RSP)),u32(0x4444));

    }
}

void TestExecute::testCMPS()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
//        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffee);
        ExecImmediateOperand src(0x11,DATA_SIZE_WORD);

        executeCMPS(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().PF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().AF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().ZF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().SF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
        QCOMPARE((u32)registerFile.getGPR16Bits(RDI),(u32)0x7779);
        QCOMPARE((u32)registerFile.getGPR16Bits(RSI),(u32)0x6668);
    }
    {
        fillRegisterFile(registerFile);
        registerFile.getFlagsBits().DF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffee);
        ExecImmediateOperand src(0x11,DATA_SIZE_WORD);

        executeCMPS(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().PF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().AF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().ZF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().SF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);
        QCOMPARE((u32)registerFile.getGPR16Bits(RDI),(u32)0x7775);
        QCOMPARE((u32)registerFile.getGPR16Bits(RSI),(u32)0x6664);
    }
}

void TestExecute::testMOVE()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
//        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffee);
        ExecImmediateOperand src(0x11,DATA_SIZE_WORD);

        executeMOVS(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE((u32)dest.getU16(),(u32)0x11);
        QCOMPARE((u32)registerFile.getGPR16Bits(RDI),(u32)0x7779);
        QCOMPARE((u32)registerFile.getGPR16Bits(RSI),(u32)0x6668);
    }
    {
        fillRegisterFile(registerFile);
        registerFile.getFlagsBits().DF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffee);
        ExecImmediateOperand src(0x11,DATA_SIZE_WORD);

        executeMOVS(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE((u32)dest.getU16(),(u32)0x11);
        QCOMPARE((u32)registerFile.getGPR16Bits(RDI),(u32)0x7775);
        QCOMPARE((u32)registerFile.getGPR16Bits(RSI),(u32)0x6664);
    }
}

void TestExecute::testLODS()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
//        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffee);
        ExecImmediateOperand src(0x11,DATA_SIZE_WORD);

        executeLODS(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE((u32)dest.getU16(),(u32)0x11);
        QCOMPARE((u32)registerFile.getGPR16Bits(RDI),(u32)0x7777);
        QCOMPARE((u32)registerFile.getGPR16Bits(RSI),(u32)0x6668);
    }
    {
        fillRegisterFile(registerFile);
        registerFile.getFlagsBits().DF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffee);
        ExecImmediateOperand src(0x11,DATA_SIZE_WORD);

        executeLODS(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE((u32)dest.getU16(),(u32)0x11);
        QCOMPARE((u32)registerFile.getGPR16Bits(RDI),(u32)0x7777);
        QCOMPARE((u32)registerFile.getGPR16Bits(RSI),(u32)0x6664);
    }
}

void TestExecute::testSTOS()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
//        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffee);
        ExecImmediateOperand src(0x11,DATA_SIZE_WORD);

        executeSTOS(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE((u32)dest.getU16(),(u32)0x11);
        QCOMPARE((u32)registerFile.getGPR16Bits(RDI),(u32)0x7779);
        QCOMPARE((u32)registerFile.getGPR16Bits(RSI),(u32)0x6666);
    }
    {
        fillRegisterFile(registerFile);
        registerFile.getFlagsBits().DF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffee);
        ExecImmediateOperand src(0x11,DATA_SIZE_WORD);

        executeSTOS(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE((u32)dest.getU16(),(u32)0x11);
        QCOMPARE((u32)registerFile.getGPR16Bits(RDI),(u32)0x7775);
        QCOMPARE((u32)registerFile.getGPR16Bits(RSI),(u32)0x6666);
    }
}

void TestExecute::testSCAS()
{
    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);

    {
        fillRegisterFile(registerFile);
//        registerFile.getFlagsBits().CF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffee);
        ExecImmediateOperand src(0xffee,DATA_SIZE_WORD);

        executeSCAS(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().PF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().AF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().ZF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().SF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);

        QCOMPARE((u32)registerFile.getGPR16Bits(RDI),(u32)0x7779);
        QCOMPARE((u32)registerFile.getGPR16Bits(RSI),(u32)0x6666);
    }
    {
        fillRegisterFile(registerFile);
        registerFile.getFlagsBits().DF=1;
        //normal case.
        ExecGPRegisterOperand dest(registerFile,RAX,DATA_SIZE_WORD,false);
        dest.setU16(0xffee);
        ExecImmediateOperand src(0x11,DATA_SIZE_WORD);

        executeSCAS(ENV_16_BITS,EFFECTIVE_16_BITS,EFFECTIVE_16_BITS,DS,&dest,&src,NULL,registerFile,memory,ioPortList);

        QCOMPARE((u32)registerFile.getFlagsBits().CF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().PF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().AF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().ZF,(u32)0);
        QCOMPARE((u32)registerFile.getFlagsBits().SF,(u32)1);
        QCOMPARE((u32)registerFile.getFlagsBits().OF,(u32)0);

        QCOMPARE((u32)registerFile.getGPR16Bits(RDI),(u32)0x7775);
        QCOMPARE((u32)registerFile.getGPR16Bits(RSI),(u32)0x6666);
    }
}


void TestExecute::fillRegisterFile(RegisterFile &registerFile)
{
    registerFile.setFlags32Bits(0);
    //RAX=0,RCX,RDX,RBX,RSP,RBP,RSI,RDI,R8,R9,R10,R11,R12,R13,R14,R15
    registerFile.setGPR64Bits(RAX,0x0000000000000000L);
    registerFile.setGPR64Bits(RCX,0x1111111111111111L);
    registerFile.setGPR64Bits(RDX,0x2222222222222222L);
    registerFile.setGPR64Bits(RBX,0x3333333333333333L);
    registerFile.setGPR64Bits(RSP,0x4444444444444444L);
    registerFile.setGPR64Bits(RBP,0x5555555555555555L);
    registerFile.setGPR64Bits(RSI,0x6666666666666666L);
    registerFile.setGPR64Bits(RDI,0x7777777777777777L);
    registerFile.setGPR64Bits(R8,0x8888888888888888L);
    registerFile.setGPR64Bits(R9,0x9999999999999999L);
    registerFile.setGPR64Bits(R10,0xaaaaaaaaaaaaaaaaL);
    registerFile.setGPR64Bits(R11,0xbbbbbbbbbbbbbbbbL);
    registerFile.setGPR64Bits(R12,0xccccccccccccccccL);
    registerFile.setGPR64Bits(R13,0xddddddddddddddddL);
    registerFile.setGPR64Bits(R14,0xeeeeeeeeeeeeeeeeL);
    registerFile.setGPR64Bits(R15,0xffffffffffffffffL);
//    registerFile.setGPR64Bits(R15,0xfffL);

    registerFile.setIP(0x1234);

    //ES=0,CS,SS,DS,FS,GS
    registerFile.setSR(ES,0x0000);registerFile.setSSR(ES,0x0000<<4);
    registerFile.setSR(CS,0x1111);registerFile.setSSR(CS,0x1111<<4);
    registerFile.setSR(SS,0x2222);registerFile.setSSR(SS,0x2222<<4);
    registerFile.setSR(DS,0x3333);registerFile.setSSR(DS,0x3333<<4);
    registerFile.setSR(FS,0x4444);registerFile.setSSR(FS,0x4444<<4);
    registerFile.setSR(GS,0x5555);registerFile.setSSR(GS,0x5555<<4);
}
