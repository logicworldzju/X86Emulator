#include "instructiondecoder.h"
#include "cpu/cputype.h"
#include "cpu/opcodetable.h"
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include "cpu/instructioncode.h"

InstructionDecoder::InstructionDecoder()
{
}

bool InstructionDecoder::decode(InstructionStream &stream,
                                OperatingEnvironment env,
                                InstructionLowLevelFormat& lowFormat,
                                InstructionHighLevelFormat& highFormat)
{
    //-----------------Operating Environment---------------
    highFormat.operatingEnvironment=env;
    //--------------------Legacy Prefix--------------------
    u8 lastCode;
    bool next=true;
    while(next)
    {
        u8 legacyPrefix = stream.get8Bits();
        lastCode=legacyPrefix;
        switch(legacyPrefix)
        {
        case LEGACY_PREFIX_OPERAND_SIZE_OVERRIDE:
        {
            lowFormat.hasLegacyPrefix=true;
            lowFormat.legacyPrefix.operandSizeOverride=1;
            break;
        }
        case LEGACY_PREFIX_ADDRESS_SIZE_OVERRIDE:
        {
            lowFormat.hasLegacyPrefix=true;
            lowFormat.legacyPrefix.addressSizeOverride=1;
            break;
        }
        case LEGACY_PREFIX_SEGMENT_OVERRIDE_CS:
        {
            lowFormat.hasLegacyPrefix=true;
            lowFormat.legacyPrefix.hasSegmentOverride=true;
            lowFormat.legacyPrefix.segmentOverride=CS;
            break;
        }
        case LEGACY_PREFIX_SEGMENT_OVERRIDE_DS:
        {
            lowFormat.hasLegacyPrefix=true;
            lowFormat.legacyPrefix.hasSegmentOverride=true;
            lowFormat.legacyPrefix.segmentOverride=DS;
            break;
        }
        case LEGACY_PREFIX_SEGMENT_OVERRIDE_ES:
        {
            lowFormat.hasLegacyPrefix=true;
            lowFormat.legacyPrefix.hasSegmentOverride=true;
            lowFormat.legacyPrefix.segmentOverride=ES;
            break;
        }
        case LEGACY_PREFIX_SEGMENT_OVERRIDE_SS:
        {
            lowFormat.hasLegacyPrefix=true;
            lowFormat.legacyPrefix.hasSegmentOverride=true;
            lowFormat.legacyPrefix.segmentOverride=SS;
            break;
        }
        case LEGACY_PREFIX_SEGMENT_OVERRIDE_FS:
        {
            lowFormat.hasLegacyPrefix=true;
            lowFormat.legacyPrefix.hasSegmentOverride=true;
            lowFormat.legacyPrefix.segmentOverride=FS;
            break;
        }
        case LEGACY_PREFIX_SEGMENT_OVERRIDE_GS:
        {
            lowFormat.hasLegacyPrefix=true;
            lowFormat.legacyPrefix.hasSegmentOverride=true;
            lowFormat.legacyPrefix.segmentOverride=GS;
            break;
        }
        case LEGACY_PREFIX_REP_REPZ:
        {
            lowFormat.hasLegacyPrefix=true;
            lowFormat.legacyPrefix.rep_repz=1;
            break;
        }
        case LEGACY_PREFIX_REPNZ:
        {
            lowFormat.hasLegacyPrefix=true;
            lowFormat.legacyPrefix.repnz=1;
            break;
        }
        case LEGACY_PREFIX_LOCK:
        {
            lowFormat.hasLegacyPrefix=true;
            lowFormat.legacyPrefix.lock=1;
            break;
        }
        default:
            next=false;
            break;
        }
    }
    //-----------------REX------------------------------
    if(env==ENV_64_BITS)
    {
        u8 rexPrefix = lastCode;
        if(rexPrefix>=REX_PREFIX_BASE && rexPrefix<REX_PREFIX_BASE+0x10)
        {
            lowFormat.hasRexPrefix=true;
            lowFormat.rex.b=rexPrefix&0x01;
            lowFormat.rex.x=(rexPrefix>>1)&0x01;
            lowFormat.rex.r=(rexPrefix>>2)&0x01;
            lowFormat.rex.w=(rexPrefix>>3)&0x01;
            lastCode=stream.get8Bits();
            highFormat.hasRexPrefix=true;
        }
    }
    //--------------Set HighLevel Prefix----------------
    //Set OperandSize
    if(lowFormat.legacyPrefix.operandSizeOverride==1)
    {
        switch(env)
        {
        case ENV_16_BITS:
            highFormat.effectiveOperandSize=EFFECTIVE_32_BITS;
            break;
        case ENV_32_BITS:
            highFormat.effectiveOperandSize=EFFECTIVE_16_BITS;
            break;
        case ENV_64_BITS:
            if(lowFormat.rex.w)
                highFormat.effectiveOperandSize=EFFECTIVE_64_BITS;
            else
                highFormat.effectiveOperandSize=EFFECTIVE_16_BITS;
            break;
        }
    }
    else
    {
        switch(env)
        {
        case ENV_16_BITS:
            highFormat.effectiveOperandSize=EFFECTIVE_16_BITS;
            break;
        case ENV_32_BITS:
            highFormat.effectiveOperandSize=EFFECTIVE_32_BITS;
            break;
        case ENV_64_BITS:
            if(lowFormat.rex.w)
                highFormat.effectiveOperandSize=EFFECTIVE_64_BITS;
            else
                highFormat.effectiveOperandSize=EFFECTIVE_32_BITS;
            break;
        }
    }
    //Set AddressSize
    if(lowFormat.legacyPrefix.addressSizeOverride==1)
    {
        switch(env)
        {
        case ENV_16_BITS:
            highFormat.effectiveAddressSize=EFFECTIVE_32_BITS;
            break;
        case ENV_32_BITS:
            highFormat.effectiveAddressSize=EFFECTIVE_16_BITS;
            break;
        case ENV_64_BITS:
            highFormat.effectiveAddressSize=EFFECTIVE_32_BITS;
            break;
        default:
            break;
        }
    }
    else
    {
        switch(env)
        {
        case ENV_16_BITS:
            highFormat.effectiveAddressSize=EFFECTIVE_16_BITS;
            break;
        case ENV_32_BITS:
            highFormat.effectiveAddressSize=EFFECTIVE_32_BITS;
            break;
        case ENV_64_BITS:
            highFormat.effectiveAddressSize=EFFECTIVE_64_BITS;
            break;
        default:
            break;
        }
    }

    //set effectiveSegmentRegister
    if(lowFormat.legacyPrefix.hasSegmentOverride)
    {
        highFormat.effectiveSegmentRegister=lowFormat.legacyPrefix.segmentOverride;
    }
    else
    {
        highFormat.effectiveSegmentRegister=DS;
    }

    //Set rep_repz,repnz,lock prefix.
    highFormat.legacyPrefix.rep_repz=lowFormat.legacyPrefix.rep_repz;
    highFormat.legacyPrefix.repnz=lowFormat.legacyPrefix.repnz;
    highFormat.legacyPrefix.lock=lowFormat.legacyPrefix.lock;
    //---------------------Opcode------------------------
    //Get opcode table entry.
    u8 opcode=lastCode;
    lowFormat.opcodeLength=0;
    lowFormat.opcode[lowFormat.opcodeLength++]=opcode;
    OpcodeTableEntry* opcodeTable=opcodeTableOneByte;
    if(opcode==ESCAPE_OPCODE0)
    {
        opcode=stream.get8Bits();
        lowFormat.opcode[lowFormat.opcodeLength++]=opcode;
        opcodeTable = opcodeTableTwoByte_0x0F;
    }
    if(opcodeTable[opcode].name.substr(0,5)=="Group")
    {
        OpcodeTableEntry* groupOpcodeTable=(OpcodeTableEntry*)opcodeTable[opcode].execFunc;
        if(!groupOpcodeTable)
        {
            std::cerr<<"Error:"<<"Try to look into the group opcode but find NULL,opcode:"
                       <<opcode<<std::endl;
            exit(-1);
        }
        lastCode = stream.get8Bits();
        lowFormat.hasModRM=true;
        lowFormat.modRM.rm=(lastCode>>0)&0x7;
        lowFormat.modRM.reg=(lastCode>>3)&0x7;
        lowFormat.modRM.mod=(lastCode>>6)&0x3;
        highFormat.opcode=&groupOpcodeTable[lowFormat.modRM.reg];
    }
    else
    {
        highFormat.opcode=&opcodeTable[opcode];
    }
    //--------------Read ModRM SIB DISP IMM---------
    //process dest
    {
        (*OS_jumpTable[highFormat.opcode->dest.size])(stream,lowFormat,highFormat,
                                                      highFormat.dest);
        (*OT_jumpTable[highFormat.opcode->dest.type])(stream,lowFormat,highFormat,
                                                      highFormat.dest);
    }
    //process src
    {
        (*OS_jumpTable[highFormat.opcode->src.size])(stream,lowFormat,highFormat,
                                                     highFormat.src);
        (*OT_jumpTable[highFormat.opcode->src.type])(stream,lowFormat,highFormat,
                                                      highFormat.src);
    }
    //process src2
    {
        (*OS_jumpTable[highFormat.opcode->src2.size])(stream,lowFormat,highFormat,
                                                      highFormat.src2);
        (*OT_jumpTable[highFormat.opcode->src2.type])(stream,lowFormat,highFormat,
                                                      highFormat.src2);
    }
    return true;
}
void InstructionDecoder::getModRM(InstructionStream& stream,
                         InstructionLowLevelFormat& lowFormat)
{
    if(!lowFormat.hasModRM)
    {
        u8 modRM = stream.get8Bits();
        lowFormat.hasModRM=true;
        lowFormat.modRM.rm = (modRM>>0)&0x7;
        lowFormat.modRM.reg = (modRM>>3)&0x7;
        lowFormat.modRM.mod = (modRM>>6)&0x3;
    }
}
void InstructionDecoder::getSIB(InstructionStream& stream,
                         InstructionLowLevelFormat& lowFormat)
{
    if(!lowFormat.hasSIB)
    {
        u8 sib = stream.get8Bits();
        lowFormat.hasSIB=true;
        lowFormat.sib.base=(sib>>0)&0x7;
        lowFormat.sib.index=(sib>>3)&0x7;
        lowFormat.sib.scale=(sib>>6)&0x3;
    }
}
void InstructionDecoder::OT_NOT_EXISTS_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    //do nothing.
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;
    operand.isExists=false;
}
void InstructionDecoder::OT_RAX_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;
    operand.isExists=true;
    operand.type = IFOperand::GP_REGISTER;
    operand.content.gpregister=RAX;
}
void InstructionDecoder::OT_RCX_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;
    operand.type = IFOperand::GP_REGISTER;
    operand.content.gpregister=RCX;
}
void InstructionDecoder::OT_RDX_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;
    operand.type = IFOperand::GP_REGISTER;
    operand.content.gpregister=RDX;
}
void InstructionDecoder::OT_RBX_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;
    operand.type = IFOperand::GP_REGISTER;
    operand.content.gpregister=RBX;
}
void InstructionDecoder::OT_RSP_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;
    operand.type = IFOperand::GP_REGISTER;
    operand.content.gpregister=RSP;
}
void InstructionDecoder::OT_RBP_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;
    operand.type = IFOperand::GP_REGISTER;
    operand.content.gpregister=RBP;
}
void InstructionDecoder::OT_RSI_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;
    operand.type = IFOperand::GP_REGISTER;
    operand.content.gpregister=RSI;
}
void InstructionDecoder::OT_RDI_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;
    operand.type = IFOperand::GP_REGISTER;
    operand.content.gpregister=RDI;
}
void InstructionDecoder::OT_ES_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;
    operand.type = IFOperand::SEGMENT_REGISTER;
    operand.content.segmentRegister=ES;
}
void InstructionDecoder::OT_CS_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;
    operand.type = IFOperand::SEGMENT_REGISTER;
    operand.content.segmentRegister=CS;
}
void InstructionDecoder::OT_SS_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;
    operand.type = IFOperand::SEGMENT_REGISTER;
    operand.content.segmentRegister=SS;
}
void InstructionDecoder::OT_DS_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;
    operand.type = IFOperand::SEGMENT_REGISTER;
    operand.content.segmentRegister=DS;
}
void InstructionDecoder::OT_FS_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;
    operand.type = IFOperand::SEGMENT_REGISTER;
    operand.content.segmentRegister=FS;
}
void InstructionDecoder::OT_GS_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;
    operand.type = IFOperand::SEGMENT_REGISTER;
    operand.content.segmentRegister=GS;
}
void InstructionDecoder::OT_A_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;

    operand.type = IFOperand::IMMEDIATE;
    if(operand.finalSize==DATA_SIZE_DWORD)
    {
        u16 disp = stream.get16Bits();
        u16 selector = stream.get16Bits();
        operand.content.immediate.valueU32=PACK_16_16_TO_32BITS(disp,selector);

        lowFormat.hasImmediate=true;
        lowFormat.immediateSize=operand.finalSize;
        lowFormat.immediate.valueU32=operand.content.immediate.valueU32;
    }
    else if(operand.finalSize==DATA_SIZE_6BYTES)
    {
        u32 disp = stream.get32Bits();
        u16 selector = stream.get16Bits();
        operand.content.immediate.valueU48 = PACK_32_16_TO_48BITS(disp,selector);

        lowFormat.hasImmediate=true;
        lowFormat.immediateSize=operand.finalSize;
        lowFormat.immediate.valueU48=operand.content.immediate.valueU48;
    }
    else
    {
        assert(0);
    }
}
void InstructionDecoder::OT_C_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;

    getModRM(stream,lowFormat);
    operand.type=IFOperand::CONTROL_REGISTER;
    operand.content.controlRegister=static_cast<ControlRegister>(lowFormat.modRM.reg);

}
void InstructionDecoder::OT_D_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;

    getModRM(stream,lowFormat);
    operand.type=IFOperand::DEBUG_REGISTER;
    operand.content.debugRegister=static_cast<DebugRegister>(lowFormat.modRM.reg);
}
void InstructionDecoder::OT_E_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;

    getModRM(stream,lowFormat);
    if(lowFormat.modRM.mod==0x3)//register.
    {
        operand.type=IFOperand::GP_REGISTER;
        operand.content.gpregister=static_cast<GPRegister>((lowFormat.rex.b<<3)|lowFormat.modRM.rm);
    }
    else
    {
        operand.type=IFOperand::MEMORY_MODRM;
//        highFormat.effectiveSegmentRegister=lowFormat.legacyPrefix.segmentOverride;
//        operand.content.finalMemorySegmentRegister=lowFormat.legacyPrefix.segmentOverride;
        operand.content.memory.finalMemorySegmentRegister=highFormat.effectiveSegmentRegister;
        operand.content.memory.defaultMemorySegmentRegister=DS;
        if(highFormat.effectiveAddressSize==EFFECTIVE_16_BITS)
        {
            operand.content.memory.memoryMode.bit16Mode.modRM.rm=lowFormat.modRM.rm;
            operand.content.memory.memoryMode.bit16Mode.modRM.mod=lowFormat.modRM.mod;
            if(lowFormat.modRM.mod==0x2 || (lowFormat.modRM.mod==0x0 &&
                                            lowFormat.modRM.rm==0x6))
            {
                operand.content.memory.memoryMode.bit16Mode.disp.valueU16=stream.get16Bits();
                lowFormat.hasDisplacement=true;
                lowFormat.displacementSize=DATA_SIZE_WORD;
                lowFormat.displacement.valueU16=operand.content.memory.memoryMode.bit16Mode.disp.valueU16;
            }
            else if(lowFormat.modRM.mod==0x1)
            {
                operand.content.memory.memoryMode.bit16Mode.disp.valueU8=stream.get8Bits();
                lowFormat.hasDisplacement=true;
                lowFormat.displacementSize=DATA_SIZE_BYTE;
                lowFormat.displacement.valueU8=operand.content.memory.memoryMode.bit16Mode.disp.valueU8;
            }
            if((lowFormat.modRM.mod==0&&(lowFormat.modRM.rm==2||lowFormat.modRM.rm==3))||
                    (lowFormat.modRM.mod==1&&(lowFormat.modRM.rm==2 || lowFormat.modRM.rm==3 ||
                                              lowFormat.modRM.rm==6))||
                    (lowFormat.modRM.mod==2 &&(lowFormat.modRM.rm==2 || lowFormat.modRM.rm==3 ||
                                               lowFormat.modRM.rm==6)))
            {
//                highFormat.effectiveSegmentRegister=SS;
                operand.content.memory.finalMemorySegmentRegister=SS;
                operand.content.memory.defaultMemorySegmentRegister=SS;
            }
        }
        else
        {
            operand.content.memory.memoryMode.bit3264Mode.modRM.rm=(lowFormat.rex.b<<3)|lowFormat.modRM.rm;
            operand.content.memory.memoryMode.bit3264Mode.modRM.mod=lowFormat.modRM.mod;
            //read sib if exists
            if(lowFormat.modRM.rm==0x4)
            {
                getSIB(stream,lowFormat);
                operand.content.memory.memoryMode.bit3264Mode.sib.base=(lowFormat.rex.b<<3)|lowFormat.sib.base;
                operand.content.memory.memoryMode.bit3264Mode.sib.index=(lowFormat.rex.x<<3)|lowFormat.sib.index;
                operand.content.memory.memoryMode.bit3264Mode.sib.scale=lowFormat.sib.scale;
                if(operand.content.memory.memoryMode.bit3264Mode.sib.base==RSP ||
                        operand.content.memory.memoryMode.bit3264Mode.sib.base==RBP)
                {
//                    highFormat.effectiveSegmentRegister=SS;
                    operand.content.memory.finalMemorySegmentRegister=SS;
                    operand.content.memory.defaultMemorySegmentRegister=SS;
                }
            }

            //read disp if exists
            if(lowFormat.modRM.mod==0x2 || (lowFormat.modRM.mod==0x0 &&
                                            lowFormat.modRM.rm==0x5))
            {
                operand.content.memory.memoryMode.bit3264Mode.disp.valueU32=stream.get32Bits();
                lowFormat.hasDisplacement=true;
                lowFormat.displacementSize=DATA_SIZE_DWORD;
                lowFormat.displacement.valueU32=operand.content.memory.memoryMode.bit3264Mode.disp.valueU32;
            }
            else if(lowFormat.modRM.mod==0x1)
            {
                operand.content.memory.memoryMode.bit3264Mode.disp.valueU8=stream.get8Bits();
                lowFormat.hasDisplacement=true;
                lowFormat.displacementSize=DATA_SIZE_BYTE;
                lowFormat.displacement.valueU8=operand.content.memory.memoryMode.bit3264Mode.disp.valueU8;
            }
            if(operand.content.memory.memoryMode.bit3264Mode.modRM.rm==RBP
                    &&(lowFormat.modRM.mod==1||lowFormat.modRM.mod==2))
            {
//                highFormat.effectiveSegmentRegister=SS;
                operand.content.memory.finalMemorySegmentRegister=SS;
                operand.content.memory.defaultMemorySegmentRegister=SS;
            }
        }
    }

}
void InstructionDecoder::OT_F_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

//    std::cerr<<"Error:"<<"Operand Type OT_F is not implemented."<<std::endl;
//    ::exit(-1);
    //do nothing. as it is embedded in the opcode.
    operand.isExists=false;
}
void InstructionDecoder::OT_G_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;

    getModRM(stream,lowFormat);
    operand.type=IFOperand::GP_REGISTER;
    operand.content.gpregister = static_cast<GPRegister>((lowFormat.rex.r<<3)|lowFormat.modRM.reg);
}
void InstructionDecoder::OT_I_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;

    operand.type=IFOperand::IMMEDIATE;
    if(!lowFormat.hasImmediate)
    {
        switch(operand.finalSize)
        {
        case DATA_SIZE_BYTE:
            operand.content.immediate.valueU8=stream.get8Bits();
            lowFormat.hasImmediate=true;
            lowFormat.immediateSize=operand.finalSize;
            lowFormat.immediate.valueU8=operand.content.immediate.valueU8;
            break;
        case DATA_SIZE_WORD:
            operand.content.immediate.valueU16=stream.get16Bits();
            lowFormat.hasImmediate=true;
            lowFormat.immediateSize=operand.finalSize;
            lowFormat.immediate.valueU16=operand.content.immediate.valueU16;
            break;
        case DATA_SIZE_DWORD:
            operand.content.immediate.valueU32=stream.get32Bits();
            lowFormat.hasImmediate=true;
            lowFormat.immediateSize=operand.finalSize;
            lowFormat.immediate.valueU32=operand.content.immediate.valueU32;
            break;
        case DATA_SIZE_6BYTES:
        {
            u32 lower32Bits=stream.get32Bits();
            u16 higher16Bits=stream.get16Bits();
            operand.content.immediate.valueU48=PACK_32_16_TO_48BITS(lower32Bits,higher16Bits);
            lowFormat.hasImmediate=true;
            lowFormat.immediateSize=operand.finalSize;
            lowFormat.immediate.valueU48=operand.content.immediate.valueU48;
            break;
        }
        case DATA_SIZE_QWORD:
            operand.content.immediate.valueU64=stream.get64Bits();
            lowFormat.hasImmediate=true;
            lowFormat.immediateSize=operand.finalSize;
            lowFormat.immediate.valueU64=operand.content.immediate.valueU64;
            break;
        default:
            assert(0);
            break;
        }
    }
    else
    {
        switch(operand.finalSize)
        {
        case DATA_SIZE_BYTE:
            operand.content.immediate.valueU8=stream.get8Bits();
            lowFormat.hasImmediate2=true;
            lowFormat.immediate2Size=operand.finalSize;
            lowFormat.immediate2.valueU8=operand.content.immediate.valueU8;
            break;
        case DATA_SIZE_WORD:
            operand.content.immediate.valueU16=stream.get16Bits();
            lowFormat.hasImmediate2=true;
            lowFormat.immediate2Size=operand.finalSize;
            lowFormat.immediate2.valueU16=operand.content.immediate.valueU16;
            break;
        case DATA_SIZE_DWORD:
            operand.content.immediate.valueU32=stream.get32Bits();
            lowFormat.hasImmediate2=true;
            lowFormat.immediate2Size=operand.finalSize;
            lowFormat.immediate2.valueU32=operand.content.immediate.valueU32;
            break;
        case DATA_SIZE_6BYTES:
        {
            u32 lower32Bits=stream.get32Bits();
            u16 higher16Bits=stream.get16Bits();
            operand.content.immediate.valueU48=PACK_32_16_TO_48BITS(lower32Bits,higher16Bits);
            lowFormat.hasImmediate2=true;
            lowFormat.immediate2Size=operand.finalSize;
            lowFormat.immediate2.valueU48=operand.content.immediate.valueU48;
            break;
        }
        case DATA_SIZE_QWORD:
            operand.content.immediate.valueU64=stream.get64Bits();
            lowFormat.hasImmediate2=true;
            lowFormat.immediate2Size=operand.finalSize;
            lowFormat.immediate2.valueU64=operand.content.immediate.valueU64;
            break;
        default:
            assert(0);
            break;
        }
    }
}
void InstructionDecoder::OT_J_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;

    operand.type = IFOperand::IMMEDIATE;

    switch(operand.finalSize)
    {
    case DATA_SIZE_BYTE:
        operand.content.immediate.valueU8=stream.get8Bits();
        lowFormat.hasDisplacement=true;
        lowFormat.displacementSize=operand.finalSize;
        lowFormat.displacement.valueU8=operand.content.immediate.valueU8;
        break;
    case DATA_SIZE_WORD:
        operand.content.immediate.valueU16=stream.get16Bits();
        lowFormat.hasDisplacement=true;
        lowFormat.displacementSize=operand.finalSize;
        lowFormat.displacement.valueU16=operand.content.immediate.valueU16;
        break;
    case DATA_SIZE_DWORD:
        operand.content.immediate.valueU32=stream.get32Bits();
        lowFormat.hasDisplacement=true;
        lowFormat.displacementSize=operand.finalSize;
        lowFormat.displacement.valueU32=operand.content.immediate.valueU32;
        break;
    case DATA_SIZE_QWORD:
        operand.content.immediate.valueU64=stream.get64Bits();
        lowFormat.hasDisplacement=true;
        lowFormat.displacementSize=operand.finalSize;
        lowFormat.displacement.valueU64=operand.content.immediate.valueU64;
        break;
    default:
        assert(0);
        break;
    }


}
void InstructionDecoder::OT_M_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    OT_E_jump(stream,lowFormat,highFormat,operand);
    assert(lowFormat.modRM.mod!=0x3);
}
/*
  @note A problem maybe here.Whether I should put the absolute displacement address into the
  displacement part.
*/
void InstructionDecoder::OT_O_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;

//    highFormat.effectiveSegmentRegister=lowFormat.legacyPrefix.segmentOverride;
    operand.content.memory.finalMemorySegmentRegister=lowFormat.legacyPrefix.segmentOverride;
    operand.content.memory.defaultMemorySegmentRegister=DS;

    operand.type=IFOperand::MEMORY_OFFSETS;
    switch(highFormat.effectiveAddressSize)
    {
    case EFFECTIVE_16_BITS:
        lowFormat.hasDisplacement=true;
        lowFormat.displacementSize=DATA_SIZE_WORD;
        lowFormat.displacement.valueU16=stream.get16Bits();
        operand.content.memory.memoryMode.moffsets.valueU16=lowFormat.displacement.valueU16;
        break;
    case EFFECTIVE_32_BITS:
        lowFormat.hasDisplacement=true;
        lowFormat.displacementSize=DATA_SIZE_DWORD;
        lowFormat.displacement.valueU32=stream.get32Bits();
        operand.content.memory.memoryMode.moffsets.valueU32=lowFormat.displacement.valueU32;
        break;
    case EFFECTIVE_64_BITS:
        lowFormat.hasDisplacement=true;
        lowFormat.displacementSize=DATA_SIZE_QWORD;
        lowFormat.displacement.valueU64=stream.get64Bits();
        operand.content.memory.memoryMode.moffsets.valueU64=lowFormat.displacement.valueU64;
        break;
    default:
        assert(0);
    }
}
void InstructionDecoder::OT_P_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    std::cerr<<"Error:"<<"Operand Type OT_P is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OT_PR_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    std::cerr<<"Error:"<<"Operand Type OT_PR is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OT_Q_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    std::cerr<<"Error:"<<"Operand Type OT_Q is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OT_R_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    OT_E_jump(stream,lowFormat,highFormat,operand);
    assert(lowFormat.modRM.mod==0x3);
}
void InstructionDecoder::OT_S_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists = true;

    operand.type = IFOperand::SEGMENT_REGISTER;
    getModRM(stream,lowFormat);
    operand.content.segmentRegister=static_cast<SegmentRegister>(lowFormat.modRM.reg);
}
void InstructionDecoder::OT_V_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    std::cerr<<"Error:"<<"Operand Type OT_V is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OT_VR_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    std::cerr<<"Error:"<<"Operand Type OT_VR is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OT_W_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    std::cerr<<"Error:"<<"Operand Type OT_W is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OT_X_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;
//    OT_RSI_jump(stream,lowFormat,highFormat,operand);
//    highFormat.effectiveSegmentRegister=lowFormat.legacyPrefix.segmentOverride;
    operand.type=IFOperand::MEMORY_MODRM;
    if(highFormat.effectiveAddressSize==EFFECTIVE_16_BITS)
    {
        operand.content.memory.memoryMode.bit16Mode.modRM.mod=0;
        operand.content.memory.memoryMode.bit16Mode.modRM.rm=4;
    }
    else
    {
        operand.content.memory.memoryMode.bit3264Mode.modRM.mod=0;
        operand.content.memory.memoryMode.bit3264Mode.modRM.rm=6;
    }
    operand.content.memory.finalMemorySegmentRegister=lowFormat.legacyPrefix.segmentOverride;
    operand.content.memory.defaultMemorySegmentRegister=DS;
}
void InstructionDecoder::OT_Y_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists=true;

    operand.type=IFOperand::MEMORY_MODRM;
    if(highFormat.effectiveAddressSize==EFFECTIVE_16_BITS)
    {
        operand.content.memory.memoryMode.bit16Mode.modRM.mod=0;
        operand.content.memory.memoryMode.bit16Mode.modRM.rm=5;
    }
    else
    {
        operand.content.memory.memoryMode.bit3264Mode.modRM.mod=0;
        operand.content.memory.memoryMode.bit3264Mode.modRM.rm=7;
    }
    operand.content.memory.finalMemorySegmentRegister=ES;
    operand.content.memory.defaultMemorySegmentRegister=ES;
//    OT_RDI_jump(stream,lowFormat,highFormat,operand);
}
void InstructionDecoder::OT_ZERO_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists = true;

    operand.type=IFOperand::IMMEDIATE;
    switch(operand.finalSize)
    {
    case DATA_SIZE_BYTE:
        operand.content.immediate.valueU8=0;
        break;
    case DATA_SIZE_WORD:
        operand.content.immediate.valueU16=0;
        break;
    case DATA_SIZE_DWORD:
        operand.content.immediate.valueU32=0;
        break;
    case DATA_SIZE_QWORD:
        operand.content.immediate.valueU64=0;
        break;
    case DATA_SIZE_6BYTES:
    case DATA_SIZE_DQWORD:
    case DATA_SIZE_10BYTES:
        assert(0);
        break;
    }
}
void InstructionDecoder::OT_ONE_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.isExists = true;

    operand.type=IFOperand::IMMEDIATE;
    switch(operand.finalSize)
    {
    case DATA_SIZE_BYTE:
        operand.content.immediate.valueU8=1;
        break;
    case DATA_SIZE_WORD:
        operand.content.immediate.valueU16=1;
        break;
    case DATA_SIZE_DWORD:
        operand.content.immediate.valueU32=1;
        break;
    case DATA_SIZE_QWORD:
        operand.content.immediate.valueU64=1;
        break;
    case DATA_SIZE_6BYTES:
    case DATA_SIZE_DQWORD:
    case DATA_SIZE_10BYTES:
        assert(0);
        break;
    }
}
void InstructionDecoder::OS_NOT_EXISTS_jump(InstructionStream& stream,
                                            InstructionLowLevelFormat& lowFormat,
                                            InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    //do nothing.
}
void InstructionDecoder::OS_a_jump(InstructionStream& stream,
                                   InstructionLowLevelFormat& lowFormat,
                                   InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    switch(highFormat.effectiveOperandSize)
    {
    case EFFECTIVE_16_BITS:
        operand.finalSize=DATA_SIZE_DWORD;
        break;
    case EFFECTIVE_32_BITS:
    case EFFECTIVE_64_BITS:
        operand.finalSize=DATA_SIZE_QWORD;
        break;
    }
}
void InstructionDecoder::OS_b_jump(InstructionStream& stream,
                                   InstructionLowLevelFormat& lowFormat,
                                   InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.finalSize=DATA_SIZE_BYTE;
}
void InstructionDecoder::OS_d_jump(InstructionStream& stream,
                                   InstructionLowLevelFormat& lowFormat,
                                   InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.finalSize=DATA_SIZE_DWORD;
}
void InstructionDecoder::OS_dq_jump(InstructionStream& stream,
                                    InstructionLowLevelFormat& lowFormat,
                                    InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;
//    operand.size=IFOperand::
//    std::cerr<<"Error:"<<"Operand Type OS_dq is not implemented."<<std::endl;
//    ::exit(-1);
    operand.finalSize=DATA_SIZE_DQWORD;
}
void InstructionDecoder::OS_p_jump(InstructionStream& stream,
                                   InstructionLowLevelFormat& lowFormat,
                                   InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    switch(highFormat.effectiveOperandSize)
    {
    case EFFECTIVE_16_BITS:
        operand.finalSize=DATA_SIZE_DWORD;
        break;
    case EFFECTIVE_32_BITS:
    case EFFECTIVE_64_BITS:
        operand.finalSize=DATA_SIZE_6BYTES;
        break;
    }
}
void InstructionDecoder::OS_pd_jump(InstructionStream& stream,
                                    InstructionLowLevelFormat& lowFormat,
                                    InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    std::cerr<<"Error:"<<"Operand Type OS_pd is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OS_pi_jump(InstructionStream& stream,
                                    InstructionLowLevelFormat& lowFormat,
                                    InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    std::cerr<<"Error:"<<"Operand Type OS_pi is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OS_ps_jump(InstructionStream& stream,
                                    InstructionLowLevelFormat& lowFormat,
                                    InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    std::cerr<<"Error:"<<"Operand Type OS_ps is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OS_q_jump(InstructionStream& stream,
                                   InstructionLowLevelFormat& lowFormat,
                                   InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.finalSize=DATA_SIZE_QWORD;
}
void InstructionDecoder::OS_s_jump(InstructionStream& stream,
                                   InstructionLowLevelFormat& lowFormat,
                                   InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    std::cerr<<"Error:"<<"Operand Type OS_s is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OS_sd_jump(InstructionStream& stream,
                                    InstructionLowLevelFormat& lowFormat,
                                    InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    std::cerr<<"Error:"<<"Operand Type OS_sd is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OS_si_jump(InstructionStream& stream,
                                    InstructionLowLevelFormat& lowFormat,
                                    InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    std::cerr<<"Error:"<<"Operand Type OS_si is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OS_ss_jump(InstructionStream& stream,
                                    InstructionLowLevelFormat& lowFormat,
                                    InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    std::cerr<<"Error:"<<"Operand Type OS_ss is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OS_v_jump(InstructionStream& stream,
                                   InstructionLowLevelFormat& lowFormat,
                                   InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    switch(highFormat.effectiveOperandSize)
    {
    case EFFECTIVE_16_BITS:
        operand.finalSize=DATA_SIZE_WORD;
        break;
    case EFFECTIVE_32_BITS:
        operand.finalSize=DATA_SIZE_DWORD;
        break;
    case EFFECTIVE_64_BITS:
        operand.finalSize=DATA_SIZE_QWORD;
        break;
    }
}
void InstructionDecoder::OS_w_jump(InstructionStream& stream,
                                   InstructionLowLevelFormat& lowFormat,
                                   InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    operand.finalSize=DATA_SIZE_WORD;
}
void InstructionDecoder::OS_z_jump(InstructionStream& stream,
                                   InstructionLowLevelFormat& lowFormat,
                                   InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    switch(highFormat.effectiveOperandSize)
    {
    case EFFECTIVE_16_BITS:
        operand.finalSize=DATA_SIZE_WORD;
        break;
    case EFFECTIVE_32_BITS:
    case EFFECTIVE_64_BITS:
        operand.finalSize=DATA_SIZE_DWORD;
        break;
    }
}
void InstructionDecoder::OS_slash_n_jump(InstructionStream& stream,
                                         InstructionLowLevelFormat& lowFormat,
                                         InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    std::cerr<<"Error:"<<"Operand Type OS_slash_n is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OS_Mw_Rv_jump(InstructionStream& stream,
                                       InstructionLowLevelFormat& lowFormat,
                                       InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    getModRM(stream,lowFormat);
    if(lowFormat.modRM.mod!=3)
    {
        operand.finalSize=DATA_SIZE_WORD;
    }
    else
    {
        OS_v_jump(stream,lowFormat,highFormat,operand);
    }
}
void InstructionDecoder::OS_d_q_jump(InstructionStream& stream,
                                     InstructionLowLevelFormat& lowFormat,
                                     InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
	(void)stream;(void)lowFormat;(void)highFormat;(void)operand;

    std::cerr<<"Error:"<<"Operand Type OS_d_q is not implemented."<<std::endl;
    ::exit(-1);
}
InstructionDecoder::OT_jump InstructionDecoder::OT_jumpTable[]=
{
    OT_NOT_EXISTS_jump,
    OT_RAX_jump,
    OT_RCX_jump,
    OT_RDX_jump,
    OT_RBX_jump,
    OT_RSP_jump,
    OT_RBP_jump,
    OT_RSI_jump,
    OT_RDI_jump,

    OT_ES_jump,
    OT_CS_jump,
    OT_SS_jump,
    OT_DS_jump,
    OT_FS_jump,
    OT_GS_jump,

    OT_A_jump,
    OT_C_jump,
    OT_D_jump,
    OT_E_jump,
    OT_F_jump,
    OT_G_jump,
    OT_I_jump,
    OT_J_jump,
    OT_M_jump,
    OT_O_jump,
    OT_P_jump,
    OT_PR_jump,
    OT_Q_jump,
    OT_R_jump,
    OT_S_jump,
    OT_V_jump,
    OT_VR_jump,
    OT_W_jump,
    OT_X_jump,
    OT_Y_jump,
    OT_ZERO_jump,
    OT_ONE_jump
};
InstructionDecoder::OS_jump InstructionDecoder::OS_jumpTable[]=
{
    OS_NOT_EXISTS_jump,
    OS_a_jump,
    OS_b_jump,
    OS_d_jump,
    OS_dq_jump,
    OS_p_jump,
    OS_pd_jump,
    OS_pi_jump,
    OS_ps_jump,
    OS_q_jump,
    OS_s_jump,
    OS_sd_jump,
    OS_si_jump,
    OS_ss_jump,
    OS_v_jump,
    OS_w_jump,
    OS_z_jump,
    OS_slash_n_jump,
    OS_Mw_Rv_jump,//especially for MOV Mw/Rv,Sw
    OS_d_q_jump//for d/q
};
