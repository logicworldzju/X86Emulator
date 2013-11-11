#include "testioportlist.h"
#include <QtTest/QTest>
#include "io/ioportlist.h"
class IOPortTest:public IOPort
{
public:
    virtual void write2Port(u32 value,Memory& memory,
                            RegisterFile& registerFile)
    {
        memory.startAccess(Memory::DEVICE_DATA_ACCESS);
        memory.set32Bits(0x200,value);
        memory.endAccess();
    }
    virtual u32 readFromPort(Memory& memory,
                             RegisterFile& registerFile)
    {
        memory.startAccess(Memory::DEVICE_DATA_ACCESS);
        u32 ret=memory.get32Bits(0x200);
        memory.endAccess();
        return ret;
    }
};

TestIOPortList::TestIOPortList(QObject *parent) :
    QObject(parent)
{
}

void TestIOPortList::testAll()
{
    Memory memory;
    RegisterFile file;
    IOPortList list(memory,file);

    IOPortTest ioPortTest;
    list.add2PortList(0,&ioPortTest);

    QCOMPARE(list.readFromPort(0),0u);
    list.write2Port(0,0xcc);
    QCOMPARE(list.readFromPort(0),uint(0xcc));
}
