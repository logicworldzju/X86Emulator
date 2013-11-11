#include "testmemory.h"

TestMemory::TestMemory(QObject *parent) :
    QObject(parent)
{
}

void TestMemory::testGetSet()
{
    DebugMemory memory;

    memory.startAccess(Memory::CPU_DATA_ACCESS);

    //8 bits.
    for(u32 i=0; i<1024; i++)
    {
        memory.set8Bits(i,i%256);
    }
    for(u32 i=0; i<1024; i++)
    {
        QCOMPARE((memory.get8Bits(i)),u8(i%256));
    }

    //16 bits.

    for(u32 i=0; i<1024; i++)
    {
        memory.set16Bits(i*2,i);
    }
    for(u32 i=0; i<1024; i++)
    {
        QCOMPARE(memory.get16Bits(i*2),u16(i));
    }

    //32 bits
    for(u32 i=0; i<1024; i++)
    {
        memory.set32Bits(i*4,i);
    }
    for(u32 i=0; i<1024; i++)
    {
        QCOMPARE(memory.get32Bits(4*i),u32(i));
    }

    //64 bits
    for(u32 i=0; i<1024; i++)
    {
        memory.set64Bits(i*8,i);
    }
    for(u32 i=0; i<1024; i++)
    {
        QCOMPARE(memory.get64Bits(i*8),u64(i));
    }

    //16 bytes
    u8 data[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    for(u32 i=0; i<1024; i++)
    {
        memory.setBytes(i*16,sizeof(data),data);
    }
    for(u32 i=0; i<1024; i++)
    {
        u8 dataGet[16];
        memory.getBytes(i*16,sizeof(dataGet),dataGet);
        for(int i=0; i<16; i++)
        {
            QCOMPARE(dataGet[i],data[i]);
        }
    }
    memory.endAccess();
}

void TestMemory::testStaticstic()
{
    DebugMemory memory;
    memory.startAccess(Memory::CPU_DATA_ACCESS);
    memory.set8Bits(0,0);
    memory.set16Bits(0,0);
    memory.set32Bits(0,0);
    memory.set64Bits(0,0);
    memory.endAccess();
    const u32* cpuDataSet=memory.getStatisticMemoryCPUDataSet();
    QCOMPARE(cpuDataSet[0],4u);
    QCOMPARE(cpuDataSet[1],3u);
    QCOMPARE(cpuDataSet[2],2u);
    QCOMPARE(cpuDataSet[3],2u);
    QCOMPARE(cpuDataSet[4],1u);
    QCOMPARE(cpuDataSet[5],1u);
    QCOMPARE(cpuDataSet[6],1u);
    QCOMPARE(cpuDataSet[7],1u);
    QCOMPARE(cpuDataSet[8],0u);

    memory.startAccess(Memory::CPU_DATA_ACCESS);
    memory.get8Bits(0);
    memory.get16Bits(0);
    memory.get32Bits(0);
    memory.get64Bits(0);
    const u32* cpuDataGet=memory.getStatisticMemoryCPUDataGet();
    memory.endAccess();
    QCOMPARE(cpuDataGet[0],4u);
    QCOMPARE(cpuDataGet[1],3u);
    QCOMPARE(cpuDataGet[2],2u);
    QCOMPARE(cpuDataGet[3],2u);
    QCOMPARE(cpuDataGet[4],1u);
    QCOMPARE(cpuDataGet[5],1u);
    QCOMPARE(cpuDataGet[6],1u);
    QCOMPARE(cpuDataGet[7],1u);
    QCOMPARE(cpuDataGet[8],0u);
//    QCOMPARE(memory.get)
}
