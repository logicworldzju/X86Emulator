#ifndef INSTRUCTIONTYPE_H
#define INSTRUCTIONTYPE_H

//------------------------------------Register--------------------------------------------
enum SegmentRegister
{
    ES=0,CS,SS,DS,FS,GS
};
enum GPRegister
{
    RAX=0,RCX,RDX,RBX,RSP,RBP,RSI,RDI,R8,R9,R10,R11,R12,R13,R14,R15
};
enum ControlRegister
{
    CR0=0,CR1,CR2,CR3,CR4,CR5,CR6,CR7,CR8,CR9,CR10,CR11,CR12,CR13,CR14,CR15
};
enum DebugRegister
{
    DR0=0,DR1,DR2,DR3,DR4,DR5,DR6,DR7,DR8,DR9,DR10,DR11,DR12,DR13,DR14,DR15
};
enum MMXRegister
{
    MMX0=0,MMX1,MMX2,MMX3,MMX4,MMX5,MMX6,MMX7
};
enum XMMRegister
{
    XMM0=0,XMM1,XMM2,XMM3,XMM4,XMM5,XMM6,XMM7,XMM8,XMM9,XMM10,XMM11,XMM12,XMM13,XMM14,XMM15
};
//---------------------------------------------------------------------------------------
enum OperatingEnvironment
{
    ENV_16_BITS=0,ENV_32_BITS,ENV_64_BITS
};
enum EffectiveSize
{
    EFFECTIVE_16_BITS=0,EFFECTIVE_32_BITS,EFFECTIVE_64_BITS
};
enum DataSize
{
    DATA_SIZE_BYTE=0,
    DATA_SIZE_WORD,
    DATA_SIZE_DWORD,
    DATA_SIZE_6BYTES,
    DATA_SIZE_QWORD,
    DATA_SIZE_DQWORD,
    DATA_SIZE_10BYTES
};
#define PACK_16_16_TO_32BITS(low16Bits,high16Bits) ((static_cast<u32>(high16Bits)<<16)|low16Bits)
#define PACK_32_16_TO_48BITS(low32Bits,high16Bits) ((static_cast<u48>(high16Bits)<<32)|low32Bits)

#endif // INSTRUCTIONTYPE_H
