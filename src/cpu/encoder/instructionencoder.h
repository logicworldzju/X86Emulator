#ifndef INSTRUCTIONENCODER_H
#define INSTRUCTIONENCODER_H

#include "../instructionformat.h"
#include <vector>

class InstructionEncoder
{
public:
    InstructionEncoder();
    static void encode(const InstructionLowLevelFormat& lowFormat,
                       std::vector<u8>& inst);
protected:
    static void writeImmToInst(DataSize size,DispImm imm,std::vector<u8>& inst);
    static void writeDispToInst(DataSize size,DispImm disp,std::vector<u8>& inst);
};

#endif // INSTRUCTIONENCODER_H
