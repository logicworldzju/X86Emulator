#include "testdiskette.h"
#include "io/diskette.h"
#include "cpu/debugcpu.h"
#include "memory/debugmemory.h"

TestDiskette::TestDiskette(QObject *parent) :
    QObject(parent)
{
}

void TestDiskette::test()
{

    DebugCPU cpu;
    DebugMemory memory;
    RegisterFile& registerFile=cpu.getRegisterFile();

    Diskette diskette("images/DOS.IMG","images/NP.IMA");
    {
        //00h
        registerFile.setGPR8BitsLow(RDX,0);

        registerFile.setGPR8BitsHigh(RAX,0);
        diskette.write2Port(0,memory,registerFile);

        QCOMPARE((int)registerFile.getGPR8BitsHigh(RAX),0);
        QCOMPARE((int)registerFile.getFlagsBits().CF,0);
    }
    {
        //01h
        registerFile.setGPR8BitsLow(RDX,1);

        registerFile.setGPR8BitsHigh(RAX,1);
        diskette.write2Port(0,memory,registerFile);

        QCOMPARE((int)registerFile.getGPR8BitsHigh(RAX),0);
        QCOMPARE((int)registerFile.getFlagsBits().CF,0);
    }

    {
        //02h
        registerFile.setGPR8BitsLow(RAX,0x1);//al
        registerFile.setGPR8BitsHigh(RCX,79);//ch
        registerFile.setGPR8BitsLow(RCX,18);//cl
        registerFile.setGPR8BitsHigh(RDX,1);//dh
        registerFile.setGPR8BitsLow(RDX,0);//dl

        registerFile.setSR(ES,0x100);
        registerFile.setSSR(ES,0x1000);
        registerFile.setGPR16Bits(RBX,0x3000);

        registerFile.setGPR8BitsHigh(RAX,2);
        diskette.write2Port(0,memory,registerFile);

        memory.startAccess(memory.DEBUG_ACCESS);
        QCOMPARE(int(memory.get16Bits(0x4000+510)),int(0x006a));
        memory.endAccess();
    }
    {
        //03h
        //write
        registerFile.setGPR8BitsLow(RAX,0x1);//al
        registerFile.setGPR8BitsHigh(RCX,78);//ch
        registerFile.setGPR8BitsLow(RCX,18);//cl
        registerFile.setGPR8BitsHigh(RDX,1);//dh
        registerFile.setGPR8BitsLow(RDX,0);//dl

        registerFile.setSR(ES,0x100);
        registerFile.setSSR(ES,0x1000);
        registerFile.setGPR16Bits(RBX,0x3000);

        registerFile.setGPR8BitsHigh(RAX,3);
        diskette.write2Port(0,memory,registerFile);

//        memory.startAccess(memory.DEBUG_ACCESS);
//        QCOMPARE(int(memory.get16Bits(0x4000+510)),int(0x006a));
//        memory.endAccess();

        //read&verify

        registerFile.setGPR8BitsLow(RAX,0x1);//al
        registerFile.setGPR8BitsHigh(RCX,78);//ch
        registerFile.setGPR8BitsLow(RCX,18);//cl
        registerFile.setGPR8BitsHigh(RDX,1);//dh
        registerFile.setGPR8BitsLow(RDX,0);//dl

        registerFile.setSR(ES,0x100);
        registerFile.setSSR(ES,0x1000);
        registerFile.setGPR16Bits(RBX,0x2000);

        registerFile.setGPR8BitsHigh(RAX,2);
        diskette.write2Port(0,memory,registerFile);

        memory.startAccess(memory.DEBUG_ACCESS);
        QCOMPARE(int(memory.get16Bits(0x3000+510)),int(0x006a));
        memory.endAccess();
    }
    {
        //04h
        registerFile.setGPR8BitsLow(RAX,0x1);//al
        registerFile.setGPR8BitsHigh(RCX,78);//ch
        registerFile.setGPR8BitsLow(RCX,18);//cl
        registerFile.setGPR8BitsHigh(RDX,1);//dh
        registerFile.setGPR8BitsLow(RDX,0);//dl

        registerFile.setSR(ES,0x100);
        registerFile.setSSR(ES,0x1000);
        registerFile.setGPR16Bits(RBX,0x2000);

        registerFile.setGPR8BitsHigh(RAX,4);
        diskette.write2Port(0,memory,registerFile);

        QCOMPARE((int)registerFile.getGPR8BitsHigh(RAX),0);
        QCOMPARE((int)registerFile.getGPR8BitsLow(RAX),1);
        QCOMPARE((int)registerFile.getFlagsBits().CF,0);
    }
    {
        //05h
        registerFile.setGPR8BitsLow(RAX,0x1);//al
        registerFile.setGPR8BitsHigh(RCX,78);//ch
//        registerFile.setGPR8BitsLow(RCX,18);//cl
        registerFile.setGPR8BitsHigh(RDX,1);//dh
        registerFile.setGPR8BitsLow(RDX,0);//dl

        registerFile.setSR(ES,0x100);
        registerFile.setSSR(ES,0x1000);
        registerFile.setGPR16Bits(RBX,0x2000);

        registerFile.setGPR8BitsHigh(RAX,5);
        diskette.write2Port(0,memory,registerFile);

        QCOMPARE((int)registerFile.getGPR8BitsHigh(RAX),0);
        QCOMPARE((int)registerFile.getGPR8BitsLow(RAX),1);
        QCOMPARE((int)registerFile.getFlagsBits().CF,0);
    }
    {
        //08h
        registerFile.setGPR8BitsLow(RDX,0);//dl

        registerFile.setGPR8BitsHigh(RAX,8);
        diskette.write2Port(0,memory,registerFile);

        QCOMPARE(int(registerFile.getGPR8BitsLow(RBX)),0x4);
        QCOMPARE(int(registerFile.getGPR8BitsHigh(RCX)),79);
        QCOMPARE(int(registerFile.getGPR8BitsLow(RCX)),18);
        QCOMPARE(int(registerFile.getGPR8BitsHigh(RDX)),1);
        QCOMPARE(int(registerFile.getGPR8BitsLow(RDX)),2);
        QCOMPARE(int(registerFile.getGPR16Bits(RDI)),0);
        QCOMPARE(int(registerFile.getSR(ES)),int(0xf000));
        QCOMPARE(int(registerFile.getSSR(ES)),int(0xf0000));
        QCOMPARE(int(registerFile.getFlagsBits().CF),int(0));
    }
    {
        //15h
        registerFile.setGPR8BitsLow(RDX,0);//dl

        registerFile.setGPR8BitsHigh(RAX,0x15);
        diskette.write2Port(0,memory,registerFile);

        QCOMPARE(int(registerFile.getGPR8BitsHigh(RAX)),int(1));
        QCOMPARE(int(registerFile.getFlagsBits().CF),int(0));

        registerFile.setGPR8BitsLow(RDX,80);//dl

        registerFile.setGPR8BitsHigh(RAX,0x15);
        diskette.write2Port(0,memory,registerFile);

        QCOMPARE(int(registerFile.getGPR8BitsHigh(RAX)),int(0));
        QCOMPARE(int(registerFile.getFlagsBits().CF),int(0));
    }
    {
        //16h
        registerFile.setGPR8BitsLow(RDX,0);//dl

        registerFile.setGPR8BitsHigh(RAX,0x16);
        diskette.write2Port(0,memory,registerFile);
    }
    {
        //17h
        registerFile.setGPR8BitsLow(RDX,0);//dl

        registerFile.setGPR8BitsHigh(RAX,0x17);
        diskette.write2Port(0,memory,registerFile);
    }
    {
        //18h
        registerFile.setGPR8BitsLow(RDX,0);//dl

        registerFile.setGPR8BitsHigh(RAX,0x18);
        diskette.write2Port(0,memory,registerFile);
    }
}
