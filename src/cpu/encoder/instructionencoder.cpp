#include "instructionencoder.h"
#include "cpu/instructioncode.h"
#include <assert.h>
InstructionEncoder::InstructionEncoder()
{
}

void InstructionEncoder::encode(const InstructionLowLevelFormat &lowFormat,
                                std::vector<u8>& inst)
{
    //---------------------Legacy Prefix-----------------------
    if(lowFormat.hasLegacyPrefix)
    {
        if(lowFormat.legacyPrefix.rep_repz)
        {
            inst.push_back(LEGACY_PREFIX_REP_REPZ);
        }
        if(lowFormat.legacyPrefix.repnz)
        {
            inst.push_back(LEGACY_PREFIX_REPNZ);
        }
        if(lowFormat.legacyPrefix.lock)
        {
            inst.push_back(LEGACY_PREFIX_LOCK);
        }
        if(lowFormat.legacyPrefix.addressSizeOverride)
        {
            inst.push_back(LEGACY_PREFIX_ADDRESS_SIZE_OVERRIDE);
        }
        if(lowFormat.legacyPrefix.operandSizeOverride)
        {
            inst.push_back(LEGACY_PREFIX_OPERAND_SIZE_OVERRIDE);
        }

        if(lowFormat.legacyPrefix.hasSegmentOverride)
        {
            switch(lowFormat.legacyPrefix.segmentOverride)
            {
            case ES:
                inst.push_back(LEGACY_PREFIX_SEGMENT_OVERRIDE_ES);
                break;
            case CS:
                inst.push_back(LEGACY_PREFIX_SEGMENT_OVERRIDE_CS);
                break;
            case SS:
                inst.push_back(LEGACY_PREFIX_SEGMENT_OVERRIDE_SS);
                break;
            case FS:
                inst.push_back(LEGACY_PREFIX_SEGMENT_OVERRIDE_FS);
                break;
            case GS:
                inst.push_back(LEGACY_PREFIX_SEGMENT_OVERRIDE_GS);
                break;
            case DS:
                inst.push_back(LEGACY_PREFIX_SEGMENT_OVERRIDE_DS);
                break;
            }
        }

    }
    //---------------------Rex Prefix-----------------------
    if(lowFormat.hasRexPrefix)
    {
        /*
        u8 b:1;
        u8 x:1;
        u8 r:1;
        u8 w:1;*/
        inst.push_back(REX_PREFIX_BASE|(lowFormat.rex.w<<3)|
                (lowFormat.rex.r<<2)|(lowFormat.rex.x<<1)|(lowFormat.rex.b<<0));
    }
    //-----------------------Opcode------------------------
    for(u8 i=0; i<lowFormat.opcodeLength; i++)
    {
        inst.push_back(lowFormat.opcode[i]);
    }
    //----------------------ModRM--------------------------
    if(lowFormat.hasModRM)
    {
        /*
        struct ModRM
        {
            u8 rm:3;
            u8 reg:3;
            u8 mod:2;
        }modRM;
        */
        inst.push_back((lowFormat.modRM.mod<<6)|(lowFormat.modRM.reg<<3)|
                (lowFormat.modRM.rm<<0));
    }
    //-----------------------SIB---------------------------
    if(lowFormat.hasSIB)
    {
        /*
        struct SIB
        {
            u8 base:3;
            u8 index:3;
            u8 scale:2;
        }sib;
        */
        inst.push_back((lowFormat.sib.scale<<6)|(lowFormat.sib.index<<3)
                |(lowFormat.sib.base<<0));
    }
    //-------------------Displacement---------------------
    if(lowFormat.hasDisplacement)
    {
        writeDispToInst(lowFormat.displacementSize,lowFormat.displacement,
                        inst);
    }
    //------------------Immediate------------------------
    if(lowFormat.hasImmediate)
    {
        writeImmToInst(lowFormat.immediateSize,lowFormat.immediate,
                       inst);
    }
    if(lowFormat.hasImmediate2)
    {
        writeImmToInst(lowFormat.immediate2Size,lowFormat.immediate2,
                       inst);
    }

}

void InstructionEncoder::writeImmToInst(DataSize size, DispImm imm,std::vector<u8>& inst)
{
    u64 value;
    u8 writeLength=0;
    switch(size)
    {
    case DATA_SIZE_BYTE:
        value=imm.valueU8;
        writeLength=1;
        break;
    case DATA_SIZE_WORD:
        value=imm.valueU16;
        writeLength=2;
        break;
    case DATA_SIZE_DWORD:
        value=imm.valueU32;
        writeLength=4;
        break;
    case DATA_SIZE_6BYTES:
        value=imm.valueU48;
        writeLength=6;
        break;
    case DATA_SIZE_QWORD:
        value=imm.valueU64;
        writeLength=8;
        break;
    case DATA_SIZE_DQWORD:
    case DATA_SIZE_10BYTES:
        assert(0);
        break;
    }
    for(u8 i=0; i<writeLength; i++)
    {
        inst.push_back(u8(value&0xff));
        value>>=8;
    }
}

void InstructionEncoder::writeDispToInst(DataSize size, DispImm disp,
                                         std::vector<u8>& inst)
{
    u64 value;
    u8 writeLength=0;
    switch(size)
    {
    case DATA_SIZE_BYTE:
        value=disp.valueU8;
        writeLength=1;
        break;
    case DATA_SIZE_WORD:
        value=disp.valueU16;
        writeLength=2;
        break;
    case DATA_SIZE_DWORD:
        value=disp.valueU32;
        writeLength=4;
        break;
    case DATA_SIZE_6BYTES:
        value=disp.valueU48;
        writeLength=6;
        break;
    case DATA_SIZE_QWORD:
        value=disp.valueU64;
        writeLength=8;
        break;
    case DATA_SIZE_DQWORD:
    case DATA_SIZE_10BYTES:
        assert(0);
        break;
    }
    for(u8 i=0; i<writeLength; i++)
    {
        inst.push_back(u8(value&0xff));
        value>>=8;
    }
}
