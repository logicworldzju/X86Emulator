#ifndef INSTRUCTIONSTREAMFROMMEMORY_H
#define INSTRUCTIONSTREAMFROMMEMORY_H

#include "instructionstream.h"
#include "memory/memory.h"

class InstructionStreamFromMemory : public InstructionStream
{
public:
    InstructionStreamFromMemory(Memory& memory)
        :_memory(memory)
    {
    }
    void setIP(u32 ip)
    {
        _ip=ip;
    }
    u32 getIP()
    {
        return _ip;
    }
public:
    virtual u8 get8Bits()
    {
        _memory.startAccess(Memory::INST_ACCESS);
        u8 ret=_memory.get8Bits(_ip);
        _memory.endAccess();
        _ip+=1;
        return ret;
    }
    virtual u16 get16Bits()
    {
        _memory.startAccess(Memory::INST_ACCESS);
        u16 ret=_memory.get16Bits(_ip);
        _memory.endAccess();
        _ip+=2;
        return ret;
    }
    virtual u32 get32Bits()
    {
        _memory.startAccess(Memory::INST_ACCESS);
        u32 ret=_memory.get32Bits(_ip);
        _memory.endAccess();
        _ip+=4;
        return ret;
    }
    virtual u64 get64Bits()
    {
        _memory.startAccess(Memory::INST_ACCESS);
        u64 ret=_memory.get64Bits(_ip);
        _memory.endAccess();
        _ip+=8;
        return ret;
    }
protected:
    Memory& _memory;
    u32 _ip;
};

#endif // INSTRUCTIONSTREAMFROMMEMORY_H
