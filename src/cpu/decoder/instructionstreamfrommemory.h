#ifndef INSTRUCTIONSTREAMFROMMEMORY_H
#define INSTRUCTIONSTREAMFROMMEMORY_H

#include "instructionstream.h"
#include "memory/memory.h"

class InstructionStreamFromMemory : public InstructionStream
{
public:
    InstructionStreamFromMemory(Memory& memory,bool isDisasm)
        :_memory(memory),_isDisasm(isDisasm)
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
        if(_isDisasm)
            _memory.startAccess(Memory::DEBUG_ACCESS);
        else
            _memory.startAccess(Memory::INST_ACCESS);
        u8 ret=_memory.get8Bits(_ip);
        _memory.endAccess();
        _ip+=1;
        return ret;
    }
    virtual u16 get16Bits()
    {
        if(_isDisasm)
            _memory.startAccess(Memory::DEBUG_ACCESS);
        else
            _memory.startAccess(Memory::INST_ACCESS);
        u16 ret=_memory.get16Bits(_ip);
        _memory.endAccess();
        _ip+=2;
        return ret;
    }
    virtual u32 get32Bits()
    {
        if(_isDisasm)
            _memory.startAccess(Memory::DEBUG_ACCESS);
        else
            _memory.startAccess(Memory::INST_ACCESS);
        u32 ret=_memory.get32Bits(_ip);
        _memory.endAccess();
        _ip+=4;
        return ret;
    }
    virtual u64 get64Bits()
    {
        if(_isDisasm)
            _memory.startAccess(Memory::DEBUG_ACCESS);
        else
            _memory.startAccess(Memory::INST_ACCESS);
        u64 ret=_memory.get64Bits(_ip);
        _memory.endAccess();
        _ip+=8;
        return ret;
    }
protected:
    Memory& _memory;
    u32 _ip;
    bool _isDisasm;
};

#endif // INSTRUCTIONSTREAMFROMMEMORY_H
