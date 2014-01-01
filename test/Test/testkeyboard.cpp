#include "gui/consolewidget.h"
#include "memory/debugmemory.h"
#include "cpu/debugcpu.h"
#include "bios/bios.h"
#include "io/ioportlist.h"
#include "interrupt/interrupt.h"
#include "io/keyboard.h"
#include "testkeyboard.h"

TestKeyboard::TestKeyboard(QObject *parent) :
    QObject(parent)
{
}

void TestKeyboard::test()
{
    DebugCPU cpu;
    DebugMemory memory;
    IOPortList ioPortList(memory,cpu.getRegisterFile());



    KeyBoard key;

    ConsoleWidget w(NULL,memory.getVideoMemoryAddress());

    QObject::connect(&w,SIGNAL(keyStatusChange(u16,bool)),&key,SLOT(keyStatusGet(u16,bool)));
    QObject::connect(&w,SIGNAL(toggleKeyChange(bool,bool,bool,bool,bool,bool)),&key,SLOT(toggleKeyGet(bool,bool,bool,bool,bool,bool)));

    ioPortList.add2PortList(0x0016,&key.keyio);
    cpu.getRegisterFile().setGPR8BitsHigh(RAX,0x05);
    cpu.getRegisterFile().setGPR16Bits(RCX,0x2C7A);
    ioPortList.write2Port(0x16,0);
//    QCOMPARE(int(ioPortList.readFromPort(0x16)),int(0x2C7A));
    bool isGetIt;
    QCOMPARE(int(key.keyio.getFirstNonblock(isGetIt)),int(0x2C7A));

    cpu.getRegisterFile().setGPR8BitsHigh(RAX,0x01);
    ioPortList.write2Port(0x16,0);
    QCOMPARE(int(cpu.getRegisterFile().getGPR16Bits(RAX)),int(0x2C7A));
    QCOMPARE(int(cpu.getRegisterFile().getFlagsBits().ZF),0);
    cpu.getRegisterFile().setGPR8BitsHigh(RAX,0x10);
    ioPortList.write2Port(0x16,0);
    QCOMPARE(int(cpu.getRegisterFile().getGPR16Bits(RAX)),0x2C7A);


    emit w.keyStatusChange(0x3920,true);
    emit w.keyStatusChange(0x3920,false);
    cpu.getRegisterFile().setGPR8BitsHigh(RAX,0x10);
    ioPortList.write2Port(0x16,0);
    QCOMPARE(int(cpu.getRegisterFile().getGPR16Bits(RAX)),0x3920);

    emit w.keyStatusChange(0x5200,true);
    emit w.keyStatusChange(0x5200,false);
    cpu.getRegisterFile().setGPR8BitsHigh(RAX,0x12);
    ioPortList.write2Port(0x16,0);
    QCOMPARE(int(cpu.getRegisterFile().getGPR16Bits(RAX)),128);

    emit w.keyStatusChange(0x5200,true);
    emit w.keyStatusChange(0x5200,false);
    cpu.getRegisterFile().setGPR8BitsHigh(RAX,0x12);
    ioPortList.write2Port(0x16,0);
    QCOMPARE(int(cpu.getRegisterFile().getGPR16Bits(RAX)),0);

    key.keyio.getToggleKey(1,1,1,0,0,0);
    cpu.getRegisterFile().setGPR8BitsHigh(RAX,0x12);
    ioPortList.write2Port(0x16,0);
    QCOMPARE(int(cpu.getRegisterFile().getGPR16Bits(RAX)),782);


    emit w.toggleKeyChange(0,1,0,1,1,0);
    cpu.getRegisterFile().setGPR8BitsHigh(RAX,0x12);
    ioPortList.write2Port(0x16,0);
    QCOMPARE(int(cpu.getRegisterFile().getGPR16Bits(RAX)),24932);
}
