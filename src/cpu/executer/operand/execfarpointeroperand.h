#ifndef EXECFARPOINTEROPERAND_H
#define EXECFARPOINTEROPERAND_H
#include "execreadwriteoperand.h"

class ExecFarPointerOperand :public ExecReadWriteOperand
{
public:
    ExecFarPointerOperand(u16 selector,u32 disp,IFOperand::IFOperandSize size)
        :_selector(selector),_disp(disp),_size(size)
    {
    }
    virtual void prepareReadSigned()
    {
        assert(0);
    }
    virtual void prepareReadUnsigned()
    {
//        assert(0);
        _uValue = _selector;
        _uValue<<=32;
        _uValue|=_disp;
    }
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
    u16 getSelector()
    {
        return _selector;
    }
    u32 getDisp()
    {
        return _disp;
    }
protected:
    u16 _selector;
    u32 _disp;
};

#endif // EXECFARPOINTEROPERAND_H
