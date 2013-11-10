#ifndef INSTRUCTIONFORMAT_H
#define INSTRUCTIONFORMAT_H

#include "opcodetable.h"
#include <string.h>
#include "cputype.h"

#define MAX_OPCODE_LENGTH 5


union Displacement
{
    s8 disp8;
    u8 dispu8;
    s16 disp16;
    u16 dispu16;
    s32 disp32;
    u32 dispu32;
    s48 disp48;
    u48 dispu48;
    s64 disp64;
    u64 dispu64;
};
union Immediate
{
    s8 imm8;
    u8 immu8;
    s16 imm16;
    u16 immu16;
    s32 imm32;
    u32 immu32;
    s48 imm48;
    u48 immu48;
    s64 imm64;
    u64 immu64;
};
struct InstructionLowLevelFormat
{
    //---------------------Legacy Prefix----------------
    bool hasLegacyPrefix;
    struct LegacyPrefix
    {
        u8 operandSizeOverride:1;
        u8 addressSizeOverride:1;
        u8 rep_repz:1;
        u8 repnz:1;
        u8 lock:1;
        SegmentRegister segmentOverride;
    }legacyPrefix;
    //-----------------------Rex Prefix----------------
    //It is not used now as it is used in x64 machine.
    bool hasRexPrefix;
    struct REX
    {
        u8 b:1;
        u8 x:1;
        u8 r:1;
        u8 w:1;
    }rex;
    //----------------------Opcode---------------------
    u8 opcodeLength;
    u8 opcode[MAX_OPCODE_LENGTH];
    //----------------------ModRM----------------------
    bool hasModRM;
    struct ModRM
    {
        u8 rm:3;
        u8 reg:3;
        u8 mod:2;
    }modRM;
    //-----------------------SIB-----------------------
    bool hasSIB;
    struct SIB
    {
        u8 base:3;
        u8 index:3;
        u8 scale:2;
    }sib;
    //-------------------Displacement------------------
    bool hasDisplacement;
    DataSize displacementSize;
    Displacement displacement;
    //-------------------Immediate--------------------
    bool hasImmediate;
    DataSize immediateSize;
    Immediate immediate;
    //immediate2 used for some ill form like
    //enter Iw,Ib;
    bool hasImmediate2;
    DataSize immediate2Size;
    Immediate immediate2;
    InstructionLowLevelFormat()
    {
        ::memset(this,0,sizeof(InstructionLowLevelFormat));
        legacyPrefix.segmentOverride=DS;
    }
};
struct IFOperand //Instruction Format Operand
{
    bool isExists;

    DataSize finalSize;//the final size of the operand,take effective operand size
            //and operand size requirement into consideration.

    enum IFOperandType
    {
        IMMEDIATE,

        SEGMENT_REGISTER,
        GP_REGISTER,
        CONTROL_REGISTER,
        DEBUG_REGISTER,
        MMX_REGISTER,
        XMM_REGISTER,

        MEMORY_MODRM,
        MEMORY_OFFSETS
    }type;
    union Content
    {
        //--------------Immediate-----------
        Immediate immediate;
        //--------------Register------------
        SegmentRegister segmentRegister;
        GPRegister gpregister;
        ControlRegister controlRegister;
        DebugRegister debugRegister;
        MMXRegister mmxRegister;
        XMMRegister xmmRegister;
        //--------------Memory-------------
        union Memory
        {
            struct Bit16Mode
            {
                struct ModRM
                {
                    u8 rm:3;
                    u8 mod:2;
                }modRM;
                Displacement disp;
            }bit16Mode;
            struct Bit3264Mode
            {
                struct ModRM
                {
                    u8 rm:4; //add the REX.B in the most significant bit.
                    u8 mod:2;
                }modRM;
                struct SIB
                {
                    u8 base:4;//add the REX.B in the most significant bit.
                    u8 index:4;//add the REX.X in the most significant bit.
                    u8 scale:2;
                }sib;
                Displacement disp;
            }bit3264Mode;
            Displacement moffsets;
        }memory;
    }content;
    IFOperand()
    {
        ::memset(this,0,sizeof(IFOperand));
        isExists=false;
    }
};
struct InstructionHighLevelFormat
{
    OperatingEnvironment operatingEnvironment;
    //----------------Prefix related-----------------
    EffectiveSize effectiveOperandSize;
    EffectiveSize effectiveAddressSize;
    SegmentRegister effectiveSegmentRegister;
    struct LegacyPrefix
    {
        unsigned char rep_repz:1;
        unsigned char repnz:1;
        unsigned char lock:1;
    }legacyPrefix;
    //------------Opcode related--------------------
    OpcodeTableEntry* opcode;
    //------------Operand related-------------------
    IFOperand dest;
    IFOperand src;
    IFOperand src2;
    InstructionHighLevelFormat()
    {
        ::memset(this,0,sizeof(InstructionHighLevelFormat));
        effectiveSegmentRegister=DS;
    }
};

#endif // INSTRUCTIONFORMAT_H
