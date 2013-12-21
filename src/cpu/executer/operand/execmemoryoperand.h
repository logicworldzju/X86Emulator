#ifndef EXECREADMEMORYOPERAND_H
#define EXECREADMEMORYOPERAND_H
#include "execreadwriteoperand.h"
#include "memory/memory.h"
#include <assert.h>

class ExecMemoryOperand:public ExecReadWriteOperand
{
public:
    ExecMemoryOperand(Memory& memory,u32 base,u32 offset,
                          DataSize size)
        :_memory(memory),_address(base+offset),_base(base),_offset(offset)
    {
        _size=size;
    }
public:
    virtual void prepareReadSigned()
    {
        _memory.startAccess(Memory::CPU_DATA_ACCESS);
        switch(_size)
        {
        case DATA_SIZE_BYTE:
            _sValue=static_cast<s8>(_memory.get8Bits(_address));
            break;
        case DATA_SIZE_WORD:
            _sValue=static_cast<s16>(_memory.get16Bits(_address));
            break;
        case DATA_SIZE_DWORD:
            _sValue=static_cast<s32>(_memory.get32Bits(_address));
            break;
        case DATA_SIZE_6BYTES:
        {
            _sValue=static_cast<s48>(PACK_32_16_TO_48BITS(_memory.get32Bits(_address),
                                                          _memory.get16Bits(_address+4)));
            break;
        }
        case DATA_SIZE_QWORD:
            _sValue=static_cast<s64>(_memory.get64Bits(_address));
            break;
        default:
            assert(0);
        }
        _memory.endAccess();
    }
    virtual void prepareReadUnsigned()
    {
        _memory.startAccess(Memory::CPU_DATA_ACCESS);
        switch(_size)
        {
        case DATA_SIZE_BYTE:
            _uValue=_memory.get8Bits(_address);
            break;
        case DATA_SIZE_WORD:
            _uValue=_memory.get16Bits(_address);
            break;
        case DATA_SIZE_DWORD:
            _uValue=_memory.get32Bits(_address);
            break;
        case DATA_SIZE_6BYTES:
        {
            _uValue=static_cast<u48>(PACK_32_16_TO_48BITS(_memory.get32Bits(_address),
                                                          _memory.get16Bits(_address+4)));
            break;
        }
        case DATA_SIZE_QWORD:
            _uValue=_memory.get64Bits(_address);
            break;
//        case NOT_ASSIGNED:
//            _uValue=_address;
        default:
            assert(0);
        }
        _memory.endAccess();
    }
    virtual void setU8(u8 value)
    {
        _memory.startAccess(Memory::CPU_DATA_ACCESS);
        assert(_size==DATA_SIZE_BYTE);
        _memory.set8Bits(_address,value);
        _memory.endAccess();

    }
    virtual void setU16(u16 value)
    {
        _memory.startAccess(Memory::CPU_DATA_ACCESS);
        assert(_size==DATA_SIZE_WORD);
        _memory.set16Bits(_address,value);
        _memory.endAccess();
    }
    virtual void setU32(u32 value)
    {
        _memory.startAccess(Memory::CPU_DATA_ACCESS);
        assert(_size==DATA_SIZE_DWORD);
        _memory.set32Bits(_address,value);
        _memory.endAccess();
    }
    virtual void setU64(u64 value)
    {
        _memory.startAccess(Memory::CPU_DATA_ACCESS);
        assert(_size==DATA_SIZE_QWORD);
        _memory.set64Bits(_address,value);
        _memory.endAccess();
    }
    u32 getOffset()
    {
        return _offset;
    }
protected:
    Memory& _memory;
    u32 _address;
    u32 _base;
    u32 _offset;
};

#endif // EXECREADMEMORYOPERAND_H
