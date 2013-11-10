#ifndef EXECIMMEDIATEOPERAND_H
#define EXECIMMEDIATEOPERAND_H

#include "execreadwriteoperand.h"

class ExecImmediateOperand : public ExecReadWriteOperand
{
public:
    ExecImmediateOperand(u64 value,DataSize size)
    {
        _size=size;
        switch(_size)
        {
        case DATA_SIZE_BYTE:
            _uValue=u8(value);
            _sValue=s8(value);
            break;
        case DATA_SIZE_WORD:
            _uValue=u16(value);
            _sValue=s16(value);
            break;
        case DATA_SIZE_DWORD:
            _uValue=u32(value);
            _sValue=s32(value);
            break;
        case DATA_SIZE_QWORD:
            _uValue=u64(value);
            _sValue=s64(value);
            break;
        default:
            break;
        }
    }
    virtual void prepareReadSigned()
    {}
    virtual void prepareReadUnsigned()
    {}
    virtual void setU8(u8 value)
    {
        assert(0);
    }
    virtual void setU16(u16 value)
    {
        assert(0);
    }
    virtual void setU32(u32 value)
    {
        assert(0);
    }
    virtual void setU64(u64 value)
    {
        assert(0);
    }
protected:
};

#endif // EXECIMMEDIATEOPERAND_H
