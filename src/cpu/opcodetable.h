#ifndef OPCODETABLE_H
#define OPCODETABLE_H

#include <string>
#include "type.h"

enum OTOperandType
{
    OT_NOT_EXISTS=0,
    OT_RAX=1,
    OT_RCX=2,
    OT_RDX=3,
    OT_RBX=4,
    OT_RSP=5,
    OT_RBP=6,
    OT_RSI=7,
    OT_RDI=8,
/*    OperandType_R8,
    OperandType_R9,
    OperandType_R10,
    OperandType_R11,
    OperandType_R12,
    OperandType_R13,
    OperandType_R14,
    OperandType_R15,*/
    OT_ES=9,
    OT_CS=10,
    OT_SS=11,
    OT_DS=12,
    OT_FS=13,
    OT_GS=14,
    OT_A=15,
    OT_C=16,
    OT_D=17,
    OT_E=18,
    OT_F=19,
    OT_G=20,
    OT_I=21,
    OT_J=22,
    OT_M=23,
    OT_O=24,
    OT_P=25,
    OT_PR=26,
    OT_Q=27,
    OT_R=28,
    OT_S=29,
    OT_V=30,
    OT_VR=31,
    OT_W=32,
    OT_X=33,
    OT_Y=34,
    OT_ZERO=35, //special operand which is actually embedded in the opcode.
    OT_ONE=36  //special operand which is actually embedded in the opcode.
};
enum OTOperandSize
{
    OS_NOT_EXISTS=0,
    OS_a=1,
    OS_b=2,
    OS_d=3,
    OS_dq=4,
    OS_p=5,
    OS_pd=6,
    OS_pi=7,
    OS_ps=8,
    OS_q=9,
    OS_s=10,
    OS_sd=11,
    OS_si=12,
    OS_ss=13,
    OS_v=14,
    OS_w=15,
    OS_z=16,
    OS_slash_n=17,
    OS_Mw_Rv=18,//especially for MOV Mw/Rv,Sw
    OS_d_q=19//for d/q
};

struct OpcodeTableEntry
{
    std::string name;
    struct OTOperand
    {
        OTOperandType type;
        OTOperandSize size;
    };
    OTOperand dest;
    OTOperand src;
    OTOperand src2;
    void* execFunc;
    u32 execCount;//used for statistics.
    OpcodeTableEntry(std::string name,void* execFunc=NULL,
                     OTOperandType destType=OT_NOT_EXISTS,
                     OTOperandSize destSize=OS_NOT_EXISTS,
                     OTOperandType srcType=OT_NOT_EXISTS,
                     OTOperandSize srcSize=OS_NOT_EXISTS,
                     OTOperandType src2Type=OT_NOT_EXISTS,
                     OTOperandSize src2Size=OS_NOT_EXISTS)
    {
        this->name = name;
        this->execFunc = execFunc;
        this->dest.type=destType;
        this->dest.size=destSize;
        this->src.type=srcType;
        this->src.size=srcSize;
        this->src2.type=src2Type;
        this->src2.size=src2Size;

        this->execCount=0;
    }
};


extern OpcodeTableEntry opcodeTableOneByte[256];
extern OpcodeTableEntry opcodeTableTwoByte_0x0F[256];

#endif // OPCODETABLE_H
