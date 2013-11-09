#ifndef INSTRUCTIONSTREAM_H
#define INSTRUCTIONSTREAM_H
#include "type.h"
class InstructionStream
{
public:
    virtual u8 get8Bits();
    virtual u16 get16Bits();
    virtual u32 get32Bits();
    virtual u64 get64Bits();
};

#endif // INSTRUCTIONSTREAM_H
