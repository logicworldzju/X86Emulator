#include "debugmemory.h"
#include <string.h>
#include <assert.h>

DebugMemory::DebugMemory(u32 memorySize)
    :Memory(memorySize)
{
    _statisticMemoryCPUDataGet = new u32[memorySize];
    _statisticMemoryCPUDataSet = new u32[memorySize];
    _statisticMemoryInstGet = new u32[memorySize];
    _statisticMemoryDeviceDataGet = new u32[memorySize];
    _statisticMemoryDeviceDataSet = new u32[memorySize];
    resetStatisticMemory();
}
DebugMemory::~DebugMemory()
{
    delete _statisticMemoryCPUDataGet;
    delete _statisticMemoryCPUDataSet;
    delete _statisticMemoryInstGet;
    delete _statisticMemoryDeviceDataGet;
    delete _statisticMemoryDeviceDataSet;
}
void DebugMemory::resetStatisticMemoryCPUDataSet()
{
    ::memset(_statisticMemoryCPUDataSet,0,sizeof(u32)*_memorySize);
}
void DebugMemory::resetStatisticMemoryCPUDataGet()
{
    ::memset(_statisticMemoryCPUDataGet,0,sizeof(u32)*_memorySize);
}
void DebugMemory::resetStatisticMemoryInstGet()
{
    ::memset(_statisticMemoryInstGet,0,sizeof(u32)*_memorySize);
}
void DebugMemory::resetStatisticMemoryDeviceDataSet()
{
    ::memset(_statisticMemoryDeviceDataSet,0,sizeof(u32)*_memorySize);
}
void DebugMemory::resetStatisticMemoryDeviceDataGet()
{
    ::memset(_statisticMemoryDeviceDataGet,0,sizeof(u32)*_memorySize);
}
void DebugMemory::resetStatisticMemory()
{
    resetStatisticMemoryCPUDataSet();
    resetStatisticMemoryCPUDataGet();
    resetStatisticMemoryInstGet();
    resetStatisticMemoryDeviceDataSet();
    resetStatisticMemoryDeviceDataGet();
}

u8 DebugMemory::get8Bits(u32 address)
{
    assert(address<_memorySize);
    assert(_accessMode!=NOT_ACCESS_MODE);
    switch(_accessMode)
    {
    case INST_ACCESS:
        _statisticMemoryInstGet[address]++;
        break;
    case CPU_DATA_ACCESS:
        _statisticMemoryCPUDataGet[address]++;
        break;
    case DEVICE_DATA_ACCESS:
        _statisticMemoryDeviceDataGet[address]++;
        break;
    default:
        //assert(0);
        break;
    }
    return Memory::get8Bits(address);
}

void DebugMemory::set8Bits(u32 address, u8 value)
{
    assert(address<_memorySize);
    assert(_accessMode!=NOT_ACCESS_MODE);
    assert(_accessMode!=INST_ACCESS);
    switch(_accessMode)
    {
    case CPU_DATA_ACCESS:
        _statisticMemoryCPUDataSet[address]++;
        break;
    case DEVICE_DATA_ACCESS:
        _statisticMemoryDeviceDataSet[address]++;
        break;
    case SYSTEM_INIT_ACCESS:
    case DEBUG_ACCESS:
        break;
    default:
        assert(0);
    }
    Memory::set8Bits(address,value);
}




