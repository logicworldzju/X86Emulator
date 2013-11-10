#ifndef EXECREADOPERAND_H
#define EXECREADOPERAND_H
#include "type.h"

class ExecReadOperand
{
public:
    ExecReadOperand()
    {
        _uValue=0;
        _sValue=0;
    }
    u8 getU8()
    {
        prepareReadUnsigned();
        return u8(_uValue);
    }
    u16 getU16()
    {
        prepareReadUnsigned();
        return u16(_uValue);
    }
    u32 getU32()
    {
        prepareReadUnsigned();
        return u32(_uValue);
    }
    u48 getU48()
    {
        prepareReadUnsigned();
        return u48(_uValue);
    }
    u64 getU64()
    {
        prepareReadUnsigned();
        return u64(_uValue);
    }
    s8 getS8()
    {
        prepareReadSigned();
        return s8(_sValue);
    }
    s16 getS16()
    {
        prepareReadSigned();
        return s16(_sValue);
    }
    s32 getS32()
    {
        prepareReadSigned();
        return s32(_sValue);
    }
    s48 getS48()
    {
        prepareReadUnsigned();
        return s48(_sValue);
    }
    s64 getS64()
    {
        prepareReadSigned();
        return s64(_sValue);
    }
public:
    virtual void prepareReadSigned()=0;
    virtual void prepareReadUnsigned()=0;
protected:
    u64 _uValue;
    s64 _sValue;
};

#endif // EXECREADOPERAND_H
