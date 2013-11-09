#ifndef EXECWRITEOPERAND_H
#define EXECWRITEOPERAND_H

#include "type.h"
#include "cpu/instructionformat.h"

class ExecWriteOperand
{
public:
    virtual void setU8(u8 value)=0;
    virtual void setU16(u16 value)=0;
    virtual void setU32(u32 value)=0;
    virtual void setU64(u64 value)=0;
    IFOperand::IFOperandSize getSize()
    {
        return _size;
    }
protected:
    IFOperand::IFOperandSize _size;
};

#endif // EXECWRITEOPERAND_H
