#ifndef INSTRUCTIONEXECUTER_H
#define INSTRUCTIONEXECUTER_H

#include "operand/execgpregisteroperand.h"
#include "operand/execimmediateoperand.h"
#include "operand/execmemoryoperand.h"
#include "operand/execsegmentregisteroperand.h"

#include "operand/execoperands.h"

#include "../instructionformat.h"

#include "../register/registerfile.h"
#include "../../memory/memory.h"

#include "../../io/ioportlist.h"

class InstructionExecuter
{
public:
    InstructionExecuter();
	static void addressing(InstructionHighLevelFormat& highFormat,RegisterFile& registerFile,
						   Memory& memory,ExecOperands& operands);
	static void execute(InstructionHighLevelFormat& highFormat,RegisterFile& registerFile,
                        Memory& memory,IOPortList& ioPortList,ExecOperands& operands);
private:
    static ExecReadWriteOperand* addressingOneOperand(InstructionHighLevelFormat& highFormat, RegisterFile& registerFile,
                                     Memory& memory, IFOperand& ifOperand);
    static u32 calculateAddress16BitMode(RegisterFile& registerFile,IFOperand& ifOperand);
    static u32 calculateAddress3264BitMode(RegisterFile& registerFile,IFOperand& ifOperand);
    static u32 calculateAddressSIB(RegisterFile& registerFile,IFOperand& ifOperand);
};

#endif // INSTRUCTIONEXECUTER_H
