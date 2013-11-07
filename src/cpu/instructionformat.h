#ifndef INSTRUCTIONFORMAT_H
#define INSTRUCTIONFORMAT_H

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
#define ESCAPE_OPCODE1 0x3a0f
#define ESCAPE_OPCODE2 0x380f

#define MAX_OPCODE_LENGTH 5

enum SegmentRegister
{
    CS=0,
    DS,
    ES,
    SS,
    FS,
    GS,
    NOT_EXISTS
};
enum GPRegister
{
    RAX=0,
    RCX,
    RDX,
    RBX,
    RSP,
    RBP,
    RSI,
    RDI,
    R8,
    R9,
    R10,
    R11,
    R12,
    R13,
    R14,
    R15
};
enum ControlRegister
{
    CR0=0,
    CR1,
    CR2,
    CR3,
    CR4,
    CR5,
    CR6,
    CR7,
    CR8,
    CR9,
    CR10,
    CR11,
    CR12,
    CR13,
    CR14,
    CR15
};

union Displacement
{
    char disp8;
    unsigned char dispu8;
    short disp16;
    unsigned short dispu16;
    int disp32;
    unsigned int dispu32;
    long long disp64;
    unsigned long long dispu64;
};
union Immediate
{
    char imm8;
    unsigned char immu8;
    short imm16;
    unsigned short immu16;
    int imm32;
    unsigned int immu32;
    long long imm64;
    unsigned long long immu64;
};
struct FarPointer
{
    unsigned short selector;
    Immediate immediate;
};

struct InstructionLowLevelFormat
{
    //---------------------Legacy Prefix----------------
    bool hasLegacyPrefix;
    struct LegacyPrefix
    {
        unsigned char operandSizeOverride:1;
        unsigned char addressSizeOverride:1;
        unsigned char rep_repz:1;
        unsigned char repnz:1;
        unsigned char lock:1;
        SegmentRegister segmentOverride;
    }legacyPrefix;
    //-----------------------Rex Prefix----------------
    //It is not used now as it is used in x64 machine.
    bool hasRexPrefix;
    struct REX
    {
        unsigned char b:1;
        unsigned char x:1;
        unsigned char r:1;
        unsigned char w:1;
    }rex;
    //----------------------Opcode---------------------
    unsigned char opcodeLength;
    unsigned char opcode[MAX_OPCODE_LENGTH];
    //----------------------ModRM----------------------
    bool hasModRM;
    struct ModRM
    {
        unsigned char rm:3;
        unsigned char reg:3;
        unsigned char mod:2;
    }modRM;
    //-----------------------SIB-----------------------
    bool hasSIB;
    struct SIB
    {
        unsigned char base:3;
        unsigned char index:3;
        unsigned char scale:2;
    }sib;
    //-------------------Displacement------------------
    bool hasDisplacement;
    Displacement displacement;
    //-------------------Immediate--------------------
    bool hasImmediate;
    Immediate immediate;
};
struct Operand
{
    enum OperandType
    {
        FAR_POINTER,
        IMMEDIATE,
        SEGMENT_REGISTER,
        GP_REGISTER,
        MEMORY
    }type;
    enum OperandSize
    {
        BYTE,
        WORD,
        DWORD,
        QWORD,
        NOT_ASSIGNED
    }size;
    union
    {
        FarPointer farPointer;
        Immediate immediate;
        SegmentRegister segmentRegister;
        GPRegister gpregister;
        union Memory
        {
            struct Bit16Mode
            {
                struct ModRM
                {
                    unsigned char rm:3;
//                    unsigned char reg:3;
                    unsigned char mod:2;
                }modRM;
                Displacement disp;
            }bit16Mode;
            struct Bit3264Mode
            {
                struct ModRM
                {
                    unsigned char rm:4; //add the REX.B in the most significant bit.
//                    unsigned char reg:3;
                    unsigned char mod:2;
                }modRM;
                struct SIB
                {
                    unsigned char base:4;//add the REX.B in the most significant bit.
                    unsigned char index:4;//add the REX.X in the most significant bit.
                    unsigned char scale:2;
                }sib;
                Displacement displacement;
            }bit3264Mode;
        }memory;
    };
};
struct InstructionHighLevelFormat
{
    enum OperatingEnvironment
    {
        BIT_16=0,
        BIT_32,
        BIT_64
    }operatingEnvironment;
    //----------------Prefix related-----------------
    enum EffectiveOperandSize
    {
        BIT_16=0,
        BIT_32,
        BIT_64
    }effectiveOperandSize;
    enum EffectiveAddressSize
    {
        BIT_16=0,
        BIT_32,
        BIT_64
    }effectiveAddressSize;
    SegmentRegister effectiveSegmentRegister;
    struct LegacyPrefix
    {
//        unsigned char operandSizeOverride:1;
//        unsigned char addressSizeOverride:1;
        unsigned char rep_repz:1;
        unsigned char repnz:1;
        unsigned char lock:1;
//        SegmentRegister segmentOverride;
    }legacyPrefix;
    //------------Opcode related--------------------


    //------------Operand related-------------------
    Operand dest;
    Operand src;

};

#endif // INSTRUCTIONFORMAT_H
