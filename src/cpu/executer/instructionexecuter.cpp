#include "instructionexecuter.h"
#include <assert.h>
InstructionExecuter::InstructionExecuter()
{
}
void InstructionExecuter::addressing(InstructionHighLevelFormat& highFormat,RegisterFile& registerFile,
					   Memory& memory,ExecOperands& operands)
{
//	switch(highFormat)
}
void InstructionExecuter::addressingOneOperand(InstructionHighLevelFormat& highFormat,RegisterFile& registerFile,
								 Memory& memory,IFOperand& ifOperand,
								 ExecReadWriteOperand*& execOperand)
{
	if(!ifOperand.isExists)
	{
		execOperand=NULL;
		return;
	}
	switch(ifOperand.type)
	{
	case IFOperand::IMMEDIATE:
		{
			switch(ifOperand.finalSize)
			{
			case DATA_SIZE_BYTE:
				execOperand = new ExecImmediateOperand(ifOperand.content.immediate.valueU8,ifOperand.finalSize);
				break;
			case DATA_SIZE_WORD:
				execOperand = new ExecImmediateOperand(ifOperand.content.immediate.valueU16,ifOperand.finalSize);
				break;
			case DATA_SIZE_DWORD:
				execOperand = new ExecImmediateOperand(ifOperand.content.immediate.valueU32,ifOperand.finalSize);
				break;
			case DATA_SIZE_6BYTES:
				execOperand = new ExecImmediateOperand(ifOperand.content.immediate.valueU48,ifOperand.finalSize);
				break;
			case DATA_SIZE_QWORD:
				execOperand = new ExecImmediateOperand(ifOperand.content.immediate.valueU64,ifOperand.finalSize);
				break;
			default:
				assert(0);
			}
			break;
		}
	case IFOperand::GP_REGISTER:
		{
			execOperand = new ExecGPRegisterOperand(registerFile,ifOperand.content.gpregister,
													ifOperand.finalSize,highFormat.hasRexPrefix);
			break;
		}
	case IFOperand::SEGMENT_REGISTER:
		{
			execOperand = new ExecSegmentRegisterOperand(registerFile,ifOperand.content.segmentRegister);
			break;
		}
	case IFOperand::MEMORY_MODRM:
		{
//			execOperand = new ExecMemoryOperand();
			break;
		}
	case IFOperand::MEMORY_OFFSETS:
		{
//			execOperand = new ExecMemoryOperand(memory,registerFile.getSSR(ifOperand.content.memory.))
			break;
		}
	default:
		assert(0);
		break;
	}
}
void InstructionExecuter::execute(InstructionHighLevelFormat& highFormat,RegisterFile& registerFile,
					Memory& memory,ExecOperands& operands)
{
}
