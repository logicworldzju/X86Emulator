#ifndef INSTRUCTIONSTREAM_H
#define INSTRUCTIONSTREAM_H
#include "type.h"
#include <vector>
class InstructionStream
{
public:
    virtual u8 get8Bits()=0;
    virtual u16 get16Bits()=0;
    virtual u32 get32Bits()=0;
    virtual u64 get64Bits()=0;
    virtual void startReadOneInstruction()=0;
    virtual void endReadOneInstruction()=0;
    virtual std::vector<u8> readLastInstruction()=0;
};

#endif // INSTRUCTIONSTREAM_H
