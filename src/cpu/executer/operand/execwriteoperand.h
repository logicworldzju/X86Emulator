#ifndef EXECWRITEOPERAND_H
#define EXECWRITEOPERAND_H

#include "../../../type.h"
#include "../../instructionformat.h"

class ExecWriteOperand
{
public:
	virtual ~ExecWriteOperand()
	{
	}
    virtual void setU8(u8 value)=0;
    virtual void setU16(u16 value)=0;
    virtual void setU32(u32 value)=0;
    virtual void setU64(u64 value)=0;
    DataSize getSize()
    {
        return _size;
    }
protected:
    DataSize _size;
};

#endif // EXECWRITEOPERAND_H
