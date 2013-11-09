#include "instructiondecoder.h"
#include "cpu/cputype.h"
#include "cpu/opcodetable.h"
#include <iostream>
#include <stdlib.h>
#include <assert.h>
//------------------------------Legacy Prefix------------------------
#define LEGACY_PREFIX_OPERAND_SIZE_OVERRIDE 0x66
#define LEGACY_PREFIX_ADDRESS_SIZE_OVERRIDE 0x67

#define LEGACY_PREFIX_SEGMENT_OVERRIDE_CS 0x2e
#define LEGACY_PREFIX_SEGMENT_OVERRIDE_DS 0x3e
#define LEGACY_PREFIX_SEGMENT_OVERRIDE_ES 0x26
#define LEGACY_PREFIX_SEGMENT_OVERRIDE_SS 0x36
#define LEGACY_PREFIX_SEGMENT_OVERRIDE_FS 0x64
#define LEGACY_PREFIX_SEGMENT_OVERRIDE_GS 0x65

#define LEGACY_PREFIX_REP_REPZ 0xf3
#define LEGACY_PREFIX_REPNZ 0xf2
#define LEGACY_PREFIX_LOCK 0xf0

//-----------------------------Rex Prefix----------------------------
#define REX_PREFIX_BASE 0x40
//-----------------------------Opcode--------------------------------
//--------------------Escape Opcode---------------------
#define ESCAPE_OPCODE0 0x0f
#define ESCAPE_OPCODE0_0 0x3a //used in SIMD
#define ESCAPE_OPCODE0_1 0x38 //used in SIMD

InstructionDecoder::InstructionDecoder()
{
}

bool InstructionDecoder::decode(InstructionStream &stream,
                                InstructionHighLevelFormat::OperatingEnvironment env,
                                InstructionLowLevelFormat& lowFormat,
                                InstructionHighLevelFormat& highFormat)
{
    //-----------------Operating Environment---------------
    highFormat.operatingEnvironment=env;
    //--------------------Legacy Prefix--------------------
    u8 lastCode;
//    u8 instLen=0;
//    lowFormat.opcodeLength=0;
    bool next=true;
    while(next)
    {
        u8 legacyPrefix = stream.get8Bits();
//        lowFormat.opcode[lowFormat.opcodeLength]=legacyPrefix;
//        lowFormat.opcodeLength++;
//        instruction[instLen++]=legacyPrefix;
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
            lowFormat.legacyPrefix.segmentOverride=CS;
            break;
        }
        case LEGACY_PREFIX_SEGMENT_OVERRIDE_DS:
        {
            lowFormat.hasLegacyPrefix=true;
            lowFormat.legacyPrefix.segmentOverride=DS;
            break;
        }
        case LEGACY_PREFIX_SEGMENT_OVERRIDE_ES:
        {
            lowFormat.hasLegacyPrefix=true;
            lowFormat.legacyPrefix.segmentOverride=ES;
            break;
        }
        case LEGACY_PREFIX_SEGMENT_OVERRIDE_SS:
        {
            lowFormat.hasLegacyPrefix=true;
            lowFormat.legacyPrefix.segmentOverride=SS;
            break;
        }
        case LEGACY_PREFIX_SEGMENT_OVERRIDE_FS:
        {
            lowFormat.hasLegacyPrefix=true;
            lowFormat.legacyPrefix.segmentOverride=FS;
            break;
        }
        case LEGACY_PREFIX_SEGMENT_OVERRIDE_GS:
        {
            lowFormat.hasLegacyPrefix=true;
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
    if(env==InstructionHighLevelFormat::BIT_64)
    {
        u8 rexPrefix = lastCode;
        if(rexPrefix>=REX_PREFIX_BASE && rexPrefix<REX_PREFIX_BASE+0x10)
        {
            lowFormat.hasRexPrefix=true;
            lowFormat.rex.b=rexPrefix&0x01;
            lowFormat.rex.x=(rexPrefix>>1)&0x01;
            lowFormat.rex.r=(rexPrefix>>2)&0x01;
            lowFormat.rex.w=(rexPrefix>>3)&0x01;
//            lowFormat.opcode[lowFormat.opcodeLength++]=stream.get8Bits();
            lastCode=stream.get8Bits();
        }
    }
    //--------------Set HighLevel Prefix----------------
    if(lowFormat.legacyPrefix.operandSizeOverride==1)
    {
        switch(env)
        {
        case InstructionHighLevelFormat::BIT_16:
            highFormat.effectiveOperandSize=InstructionHighLevelFormat::BIT_32;
            break;
        case InstructionHighLevelFormat::BIT_32:
            highFormat.effectiveOperandSize=InstructionHighLevelFormat::BIT_16;
            break;
        case InstructionHighLevelFormat::BIT_64:
            if(lowFormat.rex.w)
                highFormat.effectiveOperandSize=InstructionHighLevelFormat::BIT_64;
            else
                highFormat.effectiveOperandSize=InstructionHighLevelFormat::BIT_16;
            break;
        }
    }
    else
    {
        switch(env)
        {
        case InstructionHighLevelFormat::BIT_16:
            highFormat.effectiveOperandSize=InstructionHighLevelFormat::BIT_16;
            break;
        case InstructionHighLevelFormat::BIT_32:
            highFormat.effectiveOperandSize=InstructionHighLevelFormat::BIT_32;
            break;
        case InstructionHighLevelFormat::BIT_64:
            if(lowFormat.rex.w)
                highFormat.effectiveOperandSize=InstructionHighLevelFormat::BIT_64;
            else
                highFormat.effectiveOperandSize=InstructionHighLevelFormat::BIT_32;
            break;
        }
    }
    if(lowFormat.legacyPrefix.addressSizeOverride==1)
    {
        switch(env)
        {
        case InstructionHighLevelFormat::BIT_16:
            highFormat.effectiveAddressSize=InstructionHighLevelFormat::BIT_32;
            break;
        case InstructionHighLevelFormat::BIT_32:
            highFormat.effectiveAddressSize=InstructionHighLevelFormat::BIT_16;
            break;
        case InstructionHighLevelFormat::BIT_64:
            highFormat.effectiveAddressSize=InstructionHighLevelFormat::BIT_32;
            break;
        default:
            break;
        }
    }
    else
    {
        switch(env)
        {
        case InstructionHighLevelFormat::BIT_16:
            highFormat.effectiveAddressSize=InstructionHighLevelFormat::BIT_16;
            break;
        case InstructionHighLevelFormat::BIT_32:
            highFormat.effectiveAddressSize=InstructionHighLevelFormat::BIT_32;
            break;
        case InstructionHighLevelFormat::BIT_64:
            highFormat.effectiveAddressSize=InstructionHighLevelFormat::BIT_64;
            break;
        default:
            break;
        }
    }

    //Unable to set effectiveSegmentRegister;
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
//    bool isGetNextByte=false;
    if(opcodeTable[opcode].name.substr(0,5)=="Group")
    {
        OpcodeTableEntry* groupOpcodeTable=(OpcodeTableEntry*)opcodeTable[opcode].execFunc;
        lastCode = stream.get8Bits();
//        isGetNextByte=true;
        lowFormat.hasModRM=true;
        lowFormat.modRM.rm=(lastCode>>0)&0x7;
        lowFormat.modRM.reg=(lastCode>>3)&0x7;
        lowFormat.modRM.mod=(lastCode>>6)&0x3;
        highFormat.opcode=&groupOpcodeTable[lowFormat.modRM.reg];
    }
    else
    {
        highFormat.opcode=&opcodeTable[opcode];
//        lastCode = stream.get8Bits();
    }
    //--------------Read ModRM SIB DISP IMM---------
    //process dest
    if(highFormat.opcode->dest.size==OS_Mw_Rv)
    {

        (*OT_jumpTable[highFormat.opcode->dest.type])(stream,lowFormat,highFormat,
                                                      highFormat.dest);
        (*OS_jumpTable[highFormat.opcode->dest.size])(highFormat,highFormat.dest);
    }
    else
    {
        (*OS_jumpTable[highFormat.opcode->dest.size])(highFormat,highFormat.dest);
        (*OT_jumpTable[highFormat.opcode->dest.type])(stream,lowFormat,highFormat,
                                                      highFormat.dest);
    }
    //process src
    if(highFormat.opcode->src.size==OS_Mw_Rv)
    {

        (*OT_jumpTable[highFormat.opcode->src.type])(stream,lowFormat,highFormat,
                                                      highFormat.src);
        (*OS_jumpTable[highFormat.opcode->src.size])(highFormat,highFormat.src);
    }
    else
    {
        (*OS_jumpTable[highFormat.opcode->src.size])(highFormat,highFormat.src);
        (*OT_jumpTable[highFormat.opcode->src.type])(stream,lowFormat,highFormat,
                                                      highFormat.src);
    }
    return true;
    //process src2
    if(highFormat.opcode->src2.size==OS_Mw_Rv)
    {

        (*OT_jumpTable[highFormat.opcode->src2.type])(stream,lowFormat,highFormat,
                                                      highFormat.src2);
        (*OS_jumpTable[highFormat.opcode->src2.size])(highFormat,highFormat.src2);
    }
    else
    {
        (*OS_jumpTable[highFormat.opcode->src2.size])(highFormat,highFormat.src2);
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
}
void InstructionDecoder::OT_RAX_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type = IFOperand::GP_REGISTER;
    operand.content.gpregister=RAX;
}
void InstructionDecoder::OT_RCX_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type = IFOperand::GP_REGISTER;
    operand.content.gpregister=RCX;
}
void InstructionDecoder::OT_RDX_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type = IFOperand::GP_REGISTER;
    operand.content.gpregister=RDX;
}
void InstructionDecoder::OT_RBX_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type = IFOperand::GP_REGISTER;
    operand.content.gpregister=RBX;
}
void InstructionDecoder::OT_RSP_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type = IFOperand::GP_REGISTER;
    operand.content.gpregister=RSP;
}
void InstructionDecoder::OT_RBP_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type = IFOperand::GP_REGISTER;
    operand.content.gpregister=RBP;
}
void InstructionDecoder::OT_RSI_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type = IFOperand::GP_REGISTER;
    operand.content.gpregister=RSI;
}
void InstructionDecoder::OT_RDI_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type = IFOperand::GP_REGISTER;
    operand.content.gpregister=RDI;
}
void InstructionDecoder::OT_ES_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type = IFOperand::SEGMENT_REGISTER;
    operand.content.segmentRegister=ES;
}
void InstructionDecoder::OT_CS_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type = IFOperand::SEGMENT_REGISTER;
    operand.content.segmentRegister=CS;
}
void InstructionDecoder::OT_SS_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type = IFOperand::SEGMENT_REGISTER;
    operand.content.segmentRegister=SS;
}
void InstructionDecoder::OT_DS_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type = IFOperand::SEGMENT_REGISTER;
    operand.content.segmentRegister=DS;
}
void InstructionDecoder::OT_FS_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type = IFOperand::SEGMENT_REGISTER;
    operand.content.segmentRegister=FS;
}
void InstructionDecoder::OT_GS_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type = IFOperand::SEGMENT_REGISTER;
    operand.content.segmentRegister=GS;
}
void InstructionDecoder::OT_A_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type = IFOperand::FAR_POINTER;
    if(operand.size==IFOperand::WORD)
    {
        operand.content.farPointer.immediate.immu16 = stream.get16Bits();
        operand.content.farPointer.selector = stream.get16Bits();
    }
    else if(operand.size==IFOperand::DWORD)
    {
        operand.content.farPointer.immediate.immu32 = stream.get32Bits();
        operand.content.farPointer.selector = stream.get16Bits();
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
    //not implemented.
//    assert(0);
    std::cerr<<"Error:"<<"Operand Type OT_C is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OT_D_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    //not implemented.
//    assert(0);
    std::cerr<<"Error:"<<"Operand Type OT_D is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OT_E_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    getModRM(stream,lowFormat);
    if(lowFormat.modRM.mod==0x3)//register.
    {
        operand.type=IFOperand::GP_REGISTER;
        operand.content.gpregister=(lowFormat.rex.b<<3)|lowFormat.modRM.rm;
    }
    else
    {
        operand.type=IFOperand::MEMORY;
        highFormat.effectiveSegmentRegister=lowFormat.legacyPrefix.segmentOverride;
        if(highFormat.effectiveAddressSize==InstructionHighLevelFormat::BIT_16)
        {
            operand.content.memory.bit16Mode.modRM.rm=lowFormat.modRM.rm;
            operand.content.memory.bit16Mode.modRM.mod=lowFormat.modRM.mod;
            if(lowFormat.modRM.mod==0x2 || (lowFormat.modRM.mod==0x0 &&
                                            lowFormat.modRM.rm==0x6))
            {
                operand.content.memory.bit16Mode.disp.dispu16=stream.get16Bits();
                lowFormat.hasDisplacement=true;
                lowFormat.displacement.dispu16=operand.content.memory.bit16Mode.disp.dispu16;
            }
            else if(lowFormat.modRM.mod==0x1)
            {
                operand.content.memory.bit16Mode.disp.dispu8=stream.get8Bits();
                lowFormat.hasDisplacement=true;
                lowFormat.displacement.dispu8=operand.content.memory.bit16Mode.disp.dispu8;
            }
            if((lowFormat.modRM.mod==0&&(lowFormat.modRM.rm==2||lowFormat.modRM.rm==3))||
                    (lowFormat.modRM.mod==1&&(lowFormat.modRM.rm==2 || lowFormat.modRM.rm==3 ||
                                              lowFormat.modRM.rm==6))||
                    (lowFormat.modRM.mod==2 &&(lowFormat.modRM.rm==2 || lowFormat.modRM.rm==3 ||
                                               lowFormat.modRM.rm==6)))
            {
                highFormat.effectiveSegmentRegister=SS;
            }
        }
        else
        {
            operand.content.memory.bit3264Mode.modRM.rm=(lowFormat.rex.b<<3)|lowFormat.modRM.rm;
            operand.content.memory.bit3264Mode.modRM.mod=lowFormat.modRM.mod;
            //read sib if exists
            if(lowFormat.modRM.rm==0x4)
            {
                getSIB(stream,lowFormat);
                operand.content.memory.bit3264Mode.sib.base=(lowFormat.rex.b<<3)|lowFormat.sib.base;
                operand.content.memory.bit3264Mode.sib.index=(lowFormat.rex.x<<3)|lowFormat.sib.index;
                operand.content.memory.bit3264Mode.sib.scale=lowFormat.sib.scale;
                if(operand.content.memory.bit3264Mode.sib.base==RSP ||
                        operand.content.memory.bit3264Mode.sib.base==RBP)
                {
                    highFormat.effectiveSegmentRegister=SS;
                }
            }

            //read disp if exists
            if(lowFormat.modRM.mod==0x2 || (lowFormat.modRM.mod==0x0 &&
                                            lowFormat.modRM.rm==0x5))
            {
                operand.content.memory.bit3264Mode.disp.dispu32=stream.get32Bits();
                lowFormat.hasDisplacement=true;
                lowFormat.displacement.dispu32=operand.content.memory.bit3264Mode.disp.dispu32;
            }
            else if(lowFormat.modRM.mod==0x1)
            {
                operand.content.memory.bit3264Mode.disp.dispu8=stream.get8Bits();
                lowFormat.hasDisplacement=true;
                lowFormat.displacement.dispu8=operand.content.memory.bit3264Mode.disp.dispu8;
            }
            if(operand.content.memory.bit3264Mode.modRM.rm==RBP
                    &&(lowFormat.modRM.mod==1||lowFormat.modRM.mod==2))
            {
                highFormat.effectiveSegmentRegister=SS;
            }
        }
    }

}
void InstructionDecoder::OT_F_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    std::cerr<<"Error:"<<"Operand Type OT_F is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OT_G_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    getModRM(stream,lowFormat);
    operand.type=IFOperand::GP_REGISTER;
    operand.content.gpregister = (lowFormat.rex.r<<3)|lowFormat.modRM.reg;
}
void InstructionDecoder::OT_I_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type=IFOperand::IMMEDIATE;
    switch(operand.size)
    {
    case IFOperand::BYTE:
        operand.content.immediate.immu8=stream.get8Bits();
        lowFormat.hasImmediate=true;
        lowFormat.immediate.immu8=operand.content.immediate.immu8;
        break;
    case IFOperand::WORD:
        operand.content.immediate.immu16=stream.get16Bits();
        lowFormat.hasImmediate=true;
        lowFormat.immediate.immu16=operand.content.immediate.immu16;
        break;
    case IFOperand::DWORD:
        operand.content.immediate.immu32=stream.get32Bits();
        lowFormat.hasImmediate=true;
        lowFormat.immediate.immu32=operand.content.immediate.immu32;
        break;
    case IFOperand::QWORD:
        operand.content.immediate.immu64=stream.get64Bits();
        lowFormat.hasImmediate=true;
        lowFormat.immediate.immu64=operand.content.immediate.immu64;
        break;
    case IFOperand::NOT_ASSIGNED:
        assert(0);
        break;
    }
}
void InstructionDecoder::OT_J_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    OT_I_jump(stream,lowFormat,highFormat,operand);
}
void InstructionDecoder::OT_M_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    OT_E_jump(stream,lowFormat,highFormat,operand);
    assert(lowFormat.modRM.mod!=0x3);
}
void InstructionDecoder::OT_O_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    std::cerr<<"Error:"<<"Operand Type OT_O is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OT_P_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    std::cerr<<"Error:"<<"Operand Type OT_P is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OT_PR_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    std::cerr<<"Error:"<<"Operand Type OT_PR is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OT_Q_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    std::cerr<<"Error:"<<"Operand Type OT_Q is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OT_R_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    OT_E_jump(stream,lowFormat,highFormat,operand);
    assert(lowFormat.modRM.mod==0x3);
}
void InstructionDecoder::OT_S_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type = IFOperand::SEGMENT_REGISTER;
    getModRM(stream,lowFormat);
    operand.content.segmentRegister=lowFormat.modRM.reg;
}
void InstructionDecoder::OT_V_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    std::cerr<<"Error:"<<"Operand Type OT_V is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OT_VR_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    std::cerr<<"Error:"<<"Operand Type OT_VR is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OT_W_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    std::cerr<<"Error:"<<"Operand Type OT_W is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OT_X_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    OT_RSI_jump(stream,lowFormat,highFormat,operand);
    highFormat.effectiveSegmentRegister=lowFormat.legacyPrefix.segmentOverride;
}
void InstructionDecoder::OT_Y_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    OT_RDI_jump(stream,lowFormat,highFormat,operand);
}
void InstructionDecoder::OT_ZERO_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type=IFOperand::IMMEDIATE;
    switch(operand.size)
    {
    case IFOperand::BYTE:
        operand.content.immediate.immu8=0;
        break;
    case IFOperand::WORD:
        operand.content.immediate.immu16=0;
        break;
    case IFOperand::DWORD:
        operand.content.immediate.immu32=0;
        break;
    case IFOperand::QWORD:
        operand.content.immediate.immu64=0;
        break;
    case IFOperand::NOT_ASSIGNED:
        assert(0);
    }
}
void InstructionDecoder::OT_ONE_jump(InstructionStream& stream,
                 InstructionLowLevelFormat& lowFormat,
                 InstructionHighLevelFormat& highFormat,
                 IFOperand& operand)
{
    operand.type=IFOperand::IMMEDIATE;
    switch(operand.size)
    {
    case IFOperand::BYTE:
        operand.content.immediate.immu8=1;
        break;
    case IFOperand::WORD:
        operand.content.immediate.immu16=1;
        break;
    case IFOperand::DWORD:
        operand.content.immediate.immu32=1;
        break;
    case IFOperand::QWORD:
        operand.content.immediate.immu64=1;
        break;
    case IFOperand::NOT_ASSIGNED:
        assert(0);
    }
}
void InstructionDecoder::OS_NOT_EXISTS_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    //do nothing.
}
void InstructionDecoder::OS_a_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    switch(highFormat.effectiveOperandSize)
    {
    case InstructionHighLevelFormat::BIT_16:
        operand.size=IFOperand::DWORD;
        break;
    case InstructionHighLevelFormat::BIT_32:
    case InstructionHighLevelFormat::BIT_64:
        operand.size=IFOperand::QWORD;
        break;
    }
}
void InstructionDecoder::OS_b_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    operand.size=IFOperand::BYTE;
}
void InstructionDecoder::OS_d_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    operand.size=IFOperand::DWORD;
}
void InstructionDecoder::OS_dq_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
//    operand.size=IFOperand::
    std::cerr<<"Error:"<<"Operand Type OS_dq is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OS_p_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    switch(highFormat.effectiveOperandSize)
    {
    case InstructionHighLevelFormat::BIT_16:
        operand.size=IFOperand::WORD;
        break;
    case InstructionHighLevelFormat::BIT_32:
    case InstructionHighLevelFormat::BIT_64:
        operand.size=IFOperand::DWORD;
        break;
    }
}
void InstructionDecoder::OS_pd_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    std::cerr<<"Error:"<<"Operand Type OS_pd is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OS_pi_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    std::cerr<<"Error:"<<"Operand Type OS_pi is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OS_ps_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    std::cerr<<"Error:"<<"Operand Type OS_ps is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OS_q_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    operand.size=IFOperand::QWORD;
}
void InstructionDecoder::OS_s_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    std::cerr<<"Error:"<<"Operand Type OS_s is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OS_sd_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    std::cerr<<"Error:"<<"Operand Type OS_sd is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OS_si_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    std::cerr<<"Error:"<<"Operand Type OS_si is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OS_ss_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    std::cerr<<"Error:"<<"Operand Type OS_ss is not implemented."<<std::endl;
    ::exit(-1);
}
void InstructionDecoder::OS_v_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    switch(highFormat.effectiveOperandSize)
    {
    case InstructionHighLevelFormat::BIT_16:
        operand.size=IFOperand::WORD;
        break;
    case InstructionHighLevelFormat::BIT_32:
        operand.size=IFOperand::DWORD;
        break;
    case InstructionHighLevelFormat::BIT_64:
        operand.size=IFOperand::QWORD;
        break;
    }
}
void InstructionDecoder::OS_w_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    operand.size=IFOperand::WORD;
}
void InstructionDecoder::OS_z_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    switch(highFormat.effectiveOperandSize)
    {
    case InstructionHighLevelFormat::BIT_16:
        operand.size=IFOperand::WORD;
        break;
    case InstructionHighLevelFormat::BIT_32:
    case InstructionHighLevelFormat::BIT_64:
        operand.size=IFOperand::DWORD;
        break;
    }
}
void InstructionDecoder::OS_slash_n_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    std::cerr<<"Error:"<<"Operand Type OS_slash_n is not implemented."<<std::endl;
    ::exit(-1);
}
//Note:It should be called after the corresping OT_E_jump function.
void InstructionDecoder::OS_Mw_Rv_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
    if(operand.type==IFOperand::MEMORY)
    {
        operand.size=IFOperand::WORD;
    }
    else
    {
        OS_v_jump(highFormat,operand);
    }
}
void InstructionDecoder::OS_d_q_jump(InstructionHighLevelFormat& highFormat,
                        IFOperand& operand)
{
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
