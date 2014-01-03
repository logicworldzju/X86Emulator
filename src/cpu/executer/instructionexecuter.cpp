#include "instructionexecuter.h"
#include <assert.h>
#include "execute.h"
InstructionExecuter::InstructionExecuter()
{
}
void InstructionExecuter::addressing(InstructionHighLevelFormat& highFormat,RegisterFile& registerFile,
					   Memory& memory,ExecOperands& operands)
{
    if(highFormat.dest.isExists)
    {
        operands.setDest(addressingOneOperand(highFormat,registerFile,memory,highFormat.dest));
    }
    if(highFormat.src.isExists)
    {
        operands.setSrc(addressingOneOperand(highFormat,registerFile,memory,highFormat.src));
    }
    if(highFormat.src2.isExists)
    {
        operands.setSrc2(addressingOneOperand(highFormat,registerFile,memory,highFormat.src2));
    }
}
ExecReadWriteOperand* InstructionExecuter::addressingOneOperand(InstructionHighLevelFormat& highFormat,RegisterFile& registerFile,
                                 Memory& memory,IFOperand& ifOperand)
{
    ExecReadWriteOperand* execOperand=NULL;
	if(!ifOperand.isExists)
	{
		execOperand=NULL;
        return NULL;
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
            assert(ifOperand.content.gpregister<16);
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
            if(highFormat.effectiveAddressSize==EFFECTIVE_16_BITS)
            {
                execOperand = new ExecMemoryOperand(memory,registerFile.getSSR(ifOperand.content.memory.finalMemorySegmentRegister),
                                                    calculateAddress16BitMode(registerFile,ifOperand),ifOperand.finalSize);
            }
            else
            {
                execOperand = new ExecMemoryOperand(memory,registerFile.getSSR(ifOperand.content.memory.finalMemorySegmentRegister),
                                                    calculateAddress3264BitMode(registerFile,ifOperand),ifOperand.finalSize);
            }
//			execOperand = new ExecMemoryOperand();
//        execOperand = new ExecMemoryOperand(memory,ifOperand.content.memory)
			break;
		}
    case IFOperand::MEMORY_OFFSETS:
    {
        switch(highFormat.effectiveAddressSize)
        {
        case EFFECTIVE_16_BITS:
            execOperand = new ExecMemoryOperand(memory,registerFile.getSSR(ifOperand.content.memory.finalMemorySegmentRegister),
                                                ifOperand.content.memory.memoryMode.moffsets.valueU16,ifOperand.finalSize);
            break;
        case EFFECTIVE_32_BITS:
            execOperand = new ExecMemoryOperand(memory,registerFile.getSSR(ifOperand.content.memory.finalMemorySegmentRegister),
                                                ifOperand.content.memory.memoryMode.moffsets.valueU32,ifOperand.finalSize);
            break;
        case EFFECTIVE_64_BITS:
            execOperand = new ExecMemoryOperand(memory,registerFile.getSSR(ifOperand.content.memory.finalMemorySegmentRegister),
                                                ifOperand.content.memory.memoryMode.moffsets.valueU64,ifOperand.finalSize);
            break;
        default:
            assert(0);
        }
        break;
    }
	default:
		assert(0);
		break;
    }
    return execOperand;
}

u32 InstructionExecuter::calculateAddress16BitMode(RegisterFile &registerFile, IFOperand &ifOperand)
{
    IFOperand::Content::Memory::MemoryMode::Bit16Mode& bit16Mode = ifOperand.content.memory.memoryMode.bit16Mode;

    u32 result=0;
    switch (bit16Mode.modRM.rm)
    {
    case 0x0:
        result+=registerFile.getGPR16Bits(RBX)+registerFile.getGPR16Bits(RSI);
        if(bit16Mode.modRM.mod==0x1)
            result+=bit16Mode.disp.valueS8;
        else if(bit16Mode.modRM.mod==0x2)
            result+=bit16Mode.disp.valueS16;
        break;
    case 0x1:
        result+=registerFile.getGPR16Bits(RBX)+registerFile.getGPR16Bits(RDI);
        if(bit16Mode.modRM.mod==0x1)
            result+=bit16Mode.disp.valueS8;
        else if(bit16Mode.modRM.mod==0x2)
            result+=bit16Mode.disp.valueS16;
        break;
    case 0x2:
        result+=registerFile.getGPR16Bits(RBP)+registerFile.getGPR16Bits(RSI);
        if(bit16Mode.modRM.mod==0x1)
            result+=bit16Mode.disp.valueS8;
        else if(bit16Mode.modRM.mod==0x2)
            result+=bit16Mode.disp.valueS16;
        break;
    case 0x3:
        result+=registerFile.getGPR16Bits(RBP)+registerFile.getGPR16Bits(RDI);
        if(bit16Mode.modRM.mod==0x1)
            result+=bit16Mode.disp.valueS8;
        else if(bit16Mode.modRM.mod==0x2)
            result+=bit16Mode.disp.valueS16;
        break;
    case 0x4:
        result+=registerFile.getGPR16Bits(RSI);
        if(bit16Mode.modRM.mod==0x1)
            result+=bit16Mode.disp.valueS8;
        else if(bit16Mode.modRM.mod==0x2)
            result+=bit16Mode.disp.valueS16;
        break;
    case 0x5:
        result+=registerFile.getGPR16Bits(RDI);
        if(bit16Mode.modRM.mod==0x1)
            result+=bit16Mode.disp.valueS8;
        else if(bit16Mode.modRM.mod==0x2)
            result+=bit16Mode.disp.valueS16;
        break;
    case 0x6:
        if(bit16Mode.modRM.mod==0x0)
        {
            result+=bit16Mode.disp.valueU16;
        }
        else
        {
            result+=registerFile.getGPR16Bits(RBP);
            if(bit16Mode.modRM.mod==0x1)
                result+=bit16Mode.disp.valueS8;
            else if(bit16Mode.modRM.mod==0x2)
                result+=bit16Mode.disp.valueS16;
        }
        break;
    case 0x7:
        result+=registerFile.getGPR16Bits(RBX);
        if(bit16Mode.modRM.mod==0x1)
            result+=bit16Mode.disp.valueS8;
        else if(bit16Mode.modRM.mod==0x2)
            result+=bit16Mode.disp.valueS16;
        break;
    default:
        assert(0);
        break;
    }
//    assert(result<0x10000); address at 0x162ee,break the rule.
    return result&0xffff;
}

u32 InstructionExecuter::calculateAddress3264BitMode(RegisterFile &registerFile, IFOperand &ifOperand)
{
    IFOperand::Content::Memory::MemoryMode::Bit3264Mode& bit3264Mode=ifOperand.content.memory.memoryMode.bit3264Mode;
    u32 result=0;
    switch(bit3264Mode.modRM.rm)
    {
    case 0x0:
    case 0x1:
    case 0x2:
    case 0x3:
//    case 0x4:
//    case 0x5:
    case 0x6:
    case 0x7:
    case 0x8:
    case 0x9:
    case 0xa:
    case 0xb:
//    case 0xc:
//    case 0xd:
    case 0xe:
    case 0xf:
        result+=registerFile.getGPR64Bits(bit3264Mode.modRM.rm);
        if(bit3264Mode.modRM.mod==0x1)
            result+=bit3264Mode.disp.valueS8;
        else if(bit3264Mode.modRM.mod==0x2)
            result+=bit3264Mode.disp.valueS32;
        break;
    case 0x4:
        result+=calculateAddressSIB(registerFile,ifOperand);
        if(bit3264Mode.modRM.mod==0x1)
            result+=bit3264Mode.disp.valueS8;
        else if(bit3264Mode.modRM.mod==0x2)
            result+=bit3264Mode.disp.valueS32;
        break;
    case 0x5:
        if(bit3264Mode.modRM.mod==0x0)
        {
            result+=bit3264Mode.disp.valueU32;
        }
        else
        {
            result+=registerFile.getGPR64Bits(RBP);
            if(bit3264Mode.modRM.mod==0x1)
                result+=bit3264Mode.disp.valueS8;
            else if(bit3264Mode.modRM.mod==0x2)
                result+=bit3264Mode.disp.valueS32;
        }
        break;
    case 0xc:
        result+=calculateAddressSIB(registerFile,ifOperand);
        if(bit3264Mode.modRM.mod==0x1)
            result+=bit3264Mode.disp.valueS8;
        else if(bit3264Mode.modRM.mod==0x2)
            result+=bit3264Mode.disp.valueS32;
        break;
    case 0xd:
        if(bit3264Mode.modRM.mod==0x0)
        {
            result+=bit3264Mode.disp.valueU32;
        }
        else
        {
            result+=registerFile.getGPR64Bits(R13);
            if(bit3264Mode.modRM.mod==0x1)
                result+=bit3264Mode.disp.valueS8;
            else if(bit3264Mode.modRM.mod==0x2)
                result+=bit3264Mode.disp.valueS32;
        }
        break;
    default:
        assert(0);
    }
    return result;
}

u32 InstructionExecuter::calculateAddressSIB(RegisterFile &registerFile, IFOperand &ifOperand)
{
    IFOperand::Content::Memory::MemoryMode::Bit3264Mode::SIB& sib=ifOperand.content.memory.memoryMode.bit3264Mode.sib;
    return registerFile.getGPR64Bits(sib.base)+u64(1<<sib.scale)*registerFile.getGPR64Bits(sib.index);
}
void InstructionExecuter::execute(InstructionHighLevelFormat& highFormat, RegisterFile& registerFile,
                    Memory& memory, IOPortList &ioPortList, ExecOperands& operands)
{
    assert(highFormat.opcode->execFunc);

    ExecuteFunc* func =(ExecuteFunc*)highFormat.opcode->execFunc;
    (*func)(highFormat.operatingEnvironment,highFormat.effectiveAddressSize,
            highFormat.effectiveOperandSize,highFormat.effectiveSegmentRegister,
            operands.getDest(),operands.getSrc(),operands.getSrc2(),registerFile,memory,ioPortList);
}
