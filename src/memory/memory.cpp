#include "memory.h"
#include <assert.h>
#include <string.h>

Memory::Memory(u32 memorySize)
{
    _memorySize = memorySize;
    _memory = new u8[memorySize];
    ::memset(_memory,0,memorySize);

    _accessMode=NOT_ACCESS_MODE;
}
Memory::~Memory()
{
    delete _memory;
}
u8 Memory::get8Bits(u32 address)
{
    assert(address<_memorySize);
    return _memory[address];
}

void Memory::set8Bits(u32 address, u8 value)
{
    assert(address<_memorySize);
    _memory[address]=value;
}

u16 Memory::get16Bits(u32 address)
{
    return (get8Bits(address+1)<<8)+(get8Bits(address)<<0);
}

void Memory::set16Bits(u32 address, u16 value)
{
    set8Bits(address,(u8)value);
    set8Bits(address+1,value>>8);
}

u32 Memory::get32Bits(u32 address)
{
    return (get16Bits(address+2)<<16)+(get16Bits(address)<<0);
}

void Memory::set32Bits(u32 address, u32 value)
{
    set16Bits(address,(u16)value);
    set16Bits(address+2,value>>16);
}

u64 Memory::get64Bits(u32 address)
{
    u64 result;
    result = get32Bits(address+4);
    result <<= 32;
    result += get32Bits(address);
    return result;
}

void Memory::set64Bits(u32 address, u64 value)
{
    set32Bits(address,(u32)value);
    set32Bits(address+4,value>>32);
}

void Memory::getBytes(u32 address, u32 length, u8 *buffer)
{
    for(u32 i=0; i<length; i++)
    {
        buffer[i]=get8Bits(address+i);
    }
}

void Memory::setBytes(u32 address, u32 length, const u8 *buffer)
{
    for(u32 i=0; i<length; i++)
    {
        set8Bits(address+i,buffer[i]);
    }
}

