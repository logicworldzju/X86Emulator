#ifndef EXECREADMEMORYOPERAND_H
#define EXECREADMEMORYOPERAND_H
#include "execreadwriteoperand.h"
#include "memory/memory.h"
#include <assert.h>

class ExecReadMemoryOperand:public ExecReadWriteOperand
{
public:
    ExecReadMemoryOperand(Memory& memory,u32 address,
                          IFOperand::IFOperandSize size)
        :_memory(memory),_address(address),_size(size)
    {
    }
public:
    virtual void prepareReadSigned()
    {
        _memory.startAccess(Memory::CPU_DATA_ACCESS);
        switch(_size)
        {
        case IFOperand::BYTE:
            _sValue=static_cast<s8>(_memory.get8Bits(_address));
            break;
        case IFOperand::WORD:
            _sValue=static_cast<s16>(_memory.get16Bits(_address));
            break;
        case IFOperand::DWORD:
            _sValue=static_cast<s32>(_memory.get32Bits(_address));
            break;
        case IFOperand::QWORD:
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
        case IFOperand::BYTE:
            _uValue=_memory.get8Bits(_address);
            break;
        case IFOperand::WORD:
            _uValue=_memory.get16Bits(_address);
            break;
        case IFOperand::DWORD:
            _uValue=_memory.get32Bits(_address);
            break;
        case IFOperand::QWORD:
            _uValue=_memory.get64Bits(_address);
            break;
        case IFOperand::NOT_ASSIGNED:
            _uValue=_address;
        default:
            assert(0);
        }
        _memory.endAccess();
    }
    virtual void setU8(u8 value)
    {
        _memory.startAccess(Memory::CPU_DATA_ACCESS);
        assert(value==IFOperand::BYTE);
        _memory.set8Bits(_address,value);
        _memory.endAccess();

    }
    virtual void setU16(u16 value)
    {
        _memory.startAccess(Memory::CPU_DATA_ACCESS);
        assert(value==IFOperand::WORD);
        _memory.set16Bits(_address,value);
        _memory.endAccess();
    }
    virtual void setU32(u32 value)
    {
        _memory.startAccess(Memory::CPU_DATA_ACCESS);
        assert(value==IFOperand::DWORD);
        _memory.set32Bits(_address,value);
        _memory.endAccess();
    }
    virtual void setU64(u64 value)
    {
        _memory.startAccess(Memory::CPU_DATA_ACCESS);
        assert(value==IFOperand::QWORD);
        _memory.set64Bits(_address,value);
        _memory.endAccess();
    }
    u32 getAddress()
    {
        return _address;
    }
protected:
    Memory& _memory;
    u32 _address;
};

#endif // EXECREADMEMORYOPERAND_H
