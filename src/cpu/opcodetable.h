#ifndef OPCODETABLE_H
#define OPCODETABLE_H

#include <string>
enum OperandType
{
    OT_NOT_EXISTS=0,
    OT_RAX,
    OT_RCX,
    OT_RDX,
    OT_RBX,
    OT_RSP,
    OT_RBP,
    OT_RSI,
    OT_RDI,
/*    OperandType_R8,
    OperandType_R9,
    OperandType_R10,
    OperandType_R11,
    OperandType_R12,
    OperandType_R13,
    OperandType_R14,
    OperandType_R15,*/
    OT_ES,
    OT_CS,
    OT_SS,
    OT_DS,
    OT_FS,
    OT_GS,


    OT_A,
    OT_C,
    OT_D,
    OT_E,
    OT_F,
    OT_G,
    OT_I,
    OT_J,
    OT_M,
    OT_O,
    OT_P,
    OT_PR,
    OT_Q,
    OT_R,
    OT_S,
    OT_V,
    OT_VR,
    OT_W,
    OT_X,
	OT_Y,
	OT_ZERO, //special operand which is actually embedded in the opcode.
	OT_ONE  //special operand which is actually embedded in the opcode.

};
enum OperandSize
{
    OS_NOT_EXISTS=0,
    OS_a,
    OS_b,
    OS_d,
    OS_dq,
    OS_p,
    OS_pd,
    OS_pi,
    OS_ps,
    OS_q,
    OS_s,
    OS_sd,
    OS_si,
    OS_ss,
    OS_v,
    OS_w,
    OS_z,
    OS_slash_n,
	OS_Mw_Rv,//especially for MOV Mw/Rv,Sw
	OS_d_q//for d/q
};

struct OpcodeTableEntry
{
    std::string name;
    struct
    {
        OperandType type;
        OperandSize size;
    }dest;
    struct
    {
        OperandType type;
        OperandSize size;
    }src;
    struct
    {
        OperandType type;
        OperandSize size;
    }src2;
    void* execFunc;
    OpcodeTableEntry(std::string name,void* execFunc=NULL,
                     OperandType destType=OT_NOT_EXISTS,
                     OperandSize destSize=OS_NOT_EXISTS,
                     OperandType srcType=OT_NOT_EXISTS,
                     OperandSize srcSize=OS_NOT_EXISTS,
                     OperandType src2Type=OT_NOT_EXISTS,
                     OperandSize src2Size=OS_NOT_EXISTS)
    {
        this->name = name;
        this->execFunc = execFunc;
        this->dest.type=destType;
        this->dest.size=destSize;
        this->src.type=srcType;
        this->src.size=srcSize;
        this->src2.type=src2Type;
        this->src2.size=src2Size;
    }
};


extern OpcodeTableEntry opcodeTableOneByte[256];
extern OpcodeTableEntry opcodeTableTwoByte_0x0F[256];

#endif // OPCODETABLE_H
