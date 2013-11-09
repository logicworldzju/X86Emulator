#ifndef DEBUGMEMORY_H
#define DEBUGMEMORY_H
#include "memory.h"

class DebugMemory : public Memory
{
public:
    DebugMemory(u32 memorySize=(1<<16));
    ~DebugMemory();
    void resetStatisticMemoryCPUDataSet();
    void resetStatisticMemoryCPUDataGet();
    void resetStatisticMemoryInstGet();
    void resetStatisticMemoryDeviceDataSet();
    void resetStatisticMemoryDeviceDataGet();
    void resetStatisticMemory();

    const u32* getStatisticMemoryCPUDataSet()
    {
        return _statisticMemoryCPUDataSet;
    }
    const u32* getStatisticMemoryCPUDataGet()
    {
        return _statisticMemoryCPUDataGet;
    }
    const u32* getStatisticMemoryInstGet()
    {
        return _statisticMemoryInstGet;
    }
    const u32* getStatisticMemoryDeviceDataSet()
    {
        return _statisticMemoryDeviceDataSet;
    }
    const u32* getStatisticMemoryDeviceDataGet()
    {
        return _statisticMemoryDeviceDataGet;
    }
public:
    virtual u8 get8Bits(u32 address);
    virtual void set8Bits(u32 address, u8 value);
protected:
    u32* _statisticMemoryCPUDataGet;
    u32* _statisticMemoryCPUDataSet;
    u32* _statisticMemoryInstGet;
    u32* _statisticMemoryDeviceDataGet;
    u32* _statisticMemoryDeviceDataSet;
};

#endif // DEBUGMEMORY_H
