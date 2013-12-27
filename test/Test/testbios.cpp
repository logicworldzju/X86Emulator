#include "testbios.h"
#include "bios/bios.h"
#include "memory/debugmemory.h"

TestBIOS::TestBIOS(QObject *parent) :
    QObject(parent)
{
}

void TestBIOS::test()
{
    DebugMemory memory;
    BIOS bios(memory,"../../src/bios/bios.bin");
    memory.startAccess(memory.DEBUG_ACCESS);

    QCOMPARE(memory.get8Bits(0xf0000),u8(0xe6));
    QCOMPARE(memory.get8Bits(0xf0001),u8(0x00));
    QCOMPARE(memory.get8Bits(0xf0002),u8(0xcf));

    QCOMPARE(memory.get8Bits(0xffff0),u8(0xea));
    QCOMPARE(memory.get8Bits(0xffff1),u8(0xb4));
    QCOMPARE(memory.get8Bits(0xffff2),u8(0x04));
    memory.endAccess();
}
