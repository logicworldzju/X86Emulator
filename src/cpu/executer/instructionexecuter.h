#ifndef INSTRUCTIONEXECUTER_H
#define INSTRUCTIONEXECUTER_H

#include "cpu/executer/operand/execgpregisteroperand.h"
#include "cpu/executer/operand/execimmediateoperand.h"
#include "cpu/executer/operand/execmemoryoperand.h"
#include "cpu/executer/operand/execsegmentregisteroperand.h"

#include "cpu/executer/operand/execoperands.h"

#include "cpu/instructionformat.h"

#include "cpu/register/registerfile.h"
#include "memory/memory.h"

class InstructionExecuter
{
public:
    InstructionExecuter();
	static void addressing(InstructionHighLevelFormat& highFormat,RegisterFile& registerFile,
						   Memory& memory,ExecOperands& operands);
	static void execute(InstructionHighLevelFormat& highFormat,RegisterFile& registerFile,
						Memory& memory,ExecOperands& operands);
private:
	static void addressingOneOperand(InstructionHighLevelFormat& highFormat,RegisterFile& registerFile,
									 Memory& memory,IFOperand& ifOperand,
									 ExecReadWriteOperand*& execOperand);
};

#endif // INSTRUCTIONEXECUTER_H
