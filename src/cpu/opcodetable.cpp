#include "opcodetable.h"

OpcodeTableEntry opcodeTableGroup1_80[8]=
{
    OpcodeTableEntry("ADD",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=000
    OpcodeTableEntry("OR",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=001
    OpcodeTableEntry("ADC",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=010
    OpcodeTableEntry("SBB",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=011
    OpcodeTableEntry("AND",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=100
    OpcodeTableEntry("SUB",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=101
    OpcodeTableEntry("XOR",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=110
    OpcodeTableEntry("CMP",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup1_81[8]=
{
    OpcodeTableEntry("ADD",NULL,OT_E,OS_b,OT_I,OS_z),//ModRM.reg=000
    OpcodeTableEntry("OR",NULL,OT_E,OS_b,OT_I,OS_z),//ModRM.reg=001
    OpcodeTableEntry("ADC",NULL,OT_E,OS_b,OT_I,OS_z),//ModRM.reg=010
    OpcodeTableEntry("SBB",NULL,OT_E,OS_b,OT_I,OS_z),//ModRM.reg=011
    OpcodeTableEntry("AND",NULL,OT_E,OS_b,OT_I,OS_z),//ModRM.reg=100
    OpcodeTableEntry("SUB",NULL,OT_E,OS_b,OT_I,OS_z),//ModRM.reg=101
    OpcodeTableEntry("XOR",NULL,OT_E,OS_b,OT_I,OS_z),//ModRM.reg=110
    OpcodeTableEntry("CMP",NULL,OT_E,OS_b,OT_I,OS_z),//ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup1_82[8]=
{
    //invalid in 64-bit mode.
    OpcodeTableEntry("ADD",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=000
    OpcodeTableEntry("OR",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=001
    OpcodeTableEntry("ADC",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=010
    OpcodeTableEntry("SBB",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=011
    OpcodeTableEntry("AND",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=100
    OpcodeTableEntry("SUB",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=101
    OpcodeTableEntry("XOR",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=110
    OpcodeTableEntry("CMP",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup1_83[8]=
{
    OpcodeTableEntry("ADD",NULL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=000
    OpcodeTableEntry("OR",NULL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=001
    OpcodeTableEntry("ADC",NULL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=010
    OpcodeTableEntry("SBB",NULL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=011
    OpcodeTableEntry("AND",NULL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=100
    OpcodeTableEntry("SUB",NULL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=101
    OpcodeTableEntry("XOR",NULL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=110
    OpcodeTableEntry("CMP",NULL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup1a[8]=
{
    OpcodeTableEntry("POP",NULL,OT_E,OS_v),
    OpcodeTableEntry("invalid"),
    OpcodeTableEntry("invalid"),
    OpcodeTableEntry("invalid"),
    OpcodeTableEntry("invalid"),
    OpcodeTableEntry("invalid"),
    OpcodeTableEntry("invalid"),
    OpcodeTableEntry("invalid")
};
OpcodeTableEntry opcodeTableGroup2_c0[8]=
{
	OpcodeTableEntry("ROL",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=000
	OpcodeTableEntry("ROR",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=001
	OpcodeTableEntry("RCL",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=010
	OpcodeTableEntry("RCR",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=011
	OpcodeTableEntry("SHL/SAL",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=100
	OpcodeTableEntry("SHR",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=101
	OpcodeTableEntry("SHL/SAL",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=110
	OpcodeTableEntry("SAR",NULL,OT_E,OS_b,OT_I,OS_b) //ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup2_c1[8]=
{
	OpcodeTableEntry("ROL",NULL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=000
	OpcodeTableEntry("ROR",NULL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=001
	OpcodeTableEntry("RCL",NULL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=010
	OpcodeTableEntry("RCR",NULL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=011
	OpcodeTableEntry("SHL/SAL",NULL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=100
	OpcodeTableEntry("SHR",NULL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=101
	OpcodeTableEntry("SHL/SAL",NULL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=110
	OpcodeTableEntry("SAR",NULL,OT_E,OS_v,OT_I,OS_b) //ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup2_d0[8]=
{
	OpcodeTableEntry("ROL",NULL,OT_E,OS_b,OT_ONE,OS_b),//ModRM.reg=000
	OpcodeTableEntry("ROR",NULL,OT_E,OS_b,OT_ONE,OS_b),//ModRM.reg=001
	OpcodeTableEntry("RCL",NULL,OT_E,OS_b,OT_ONE,OS_b),//ModRM.reg=010
	OpcodeTableEntry("RCR",NULL,OT_E,OS_b,OT_ONE,OS_b),//ModRM.reg=011
	OpcodeTableEntry("SHL/SAL",NULL,OT_E,OS_b,OT_ONE,OS_b),//ModRM.reg=100
	OpcodeTableEntry("SHR",NULL,OT_E,OS_b,OT_ONE,OS_b),//ModRM.reg=101
	OpcodeTableEntry("SHL/SAL",NULL,OT_E,OS_b,OT_ONE,OS_b),//ModRM.reg=110
	OpcodeTableEntry("SAR",NULL,OT_E,OS_b,OT_ONE,OS_b) //ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup2_d1[8]=
{
	OpcodeTableEntry("ROL",NULL,OT_E,OS_v,OT_ONE,OS_b),//ModRM.reg=000
	OpcodeTableEntry("ROR",NULL,OT_E,OS_v,OT_ONE,OS_b),//ModRM.reg=001
	OpcodeTableEntry("RCL",NULL,OT_E,OS_v,OT_ONE,OS_b),//ModRM.reg=010
	OpcodeTableEntry("RCR",NULL,OT_E,OS_v,OT_ONE,OS_b),//ModRM.reg=011
	OpcodeTableEntry("SHL/SAL",NULL,OT_E,OS_v,OT_ONE,OS_b),//ModRM.reg=100
	OpcodeTableEntry("SHR",NULL,OT_E,OS_v,OT_ONE,OS_b),//ModRM.reg=101
	OpcodeTableEntry("SHL/SAL",NULL,OT_E,OS_v,OT_ONE,OS_b),//ModRM.reg=110
	OpcodeTableEntry("SAR",NULL,OT_E,OS_v,OT_ONE,OS_b) //ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup2_d2[8]=
{
	OpcodeTableEntry("ROL",NULL,OT_E,OS_b,OT_RCX,OS_b),//ModRM.reg=000
	OpcodeTableEntry("ROR",NULL,OT_E,OS_b,OT_RCX,OS_b),//ModRM.reg=001
	OpcodeTableEntry("RCL",NULL,OT_E,OS_b,OT_RCX,OS_b),//ModRM.reg=010
	OpcodeTableEntry("RCR",NULL,OT_E,OS_b,OT_RCX,OS_b),//ModRM.reg=011
	OpcodeTableEntry("SHL/SAL",NULL,OT_E,OS_b,OT_RCX,OS_b),//ModRM.reg=100
	OpcodeTableEntry("SHR",NULL,OT_E,OS_b,OT_RCX,OS_b),//ModRM.reg=101
	OpcodeTableEntry("SHL/SAL",NULL,OT_E,OS_b,OT_RCX,OS_b),//ModRM.reg=110
	OpcodeTableEntry("SAR",NULL,OT_E,OS_b,OT_RCX,OS_b) //ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup2_d3[8]=
{
	OpcodeTableEntry("ROL",NULL,OT_E,OS_v,OT_RCX,OS_b),//ModRM.reg=000
	OpcodeTableEntry("ROR",NULL,OT_E,OS_v,OT_RCX,OS_b),//ModRM.reg=001
	OpcodeTableEntry("RCL",NULL,OT_E,OS_v,OT_RCX,OS_b),//ModRM.reg=010
	OpcodeTableEntry("RCR",NULL,OT_E,OS_v,OT_RCX,OS_b),//ModRM.reg=011
	OpcodeTableEntry("SHL/SAL",NULL,OT_E,OS_v,OT_RCX,OS_b),//ModRM.reg=100
	OpcodeTableEntry("SHR",NULL,OT_E,OS_v,OT_RCX,OS_b),//ModRM.reg=101
	OpcodeTableEntry("SHL/SAL",NULL,OT_E,OS_v,OT_RCX,OS_b),//ModRM.reg=110
	OpcodeTableEntry("SAR",NULL,OT_E,OS_v,OT_RCX,OS_b) //ModRM.reg=111
};

OpcodeTableEntry opcodeTableGroup3_f6[8]=
{
	OpcodeTableEntry("TEST",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=000
	OpcodeTableEntry("TEST",NULL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=001
	OpcodeTableEntry("NOT",NULL,OT_E,OS_b),//ModRM.reg=010
	OpcodeTableEntry("NEG",NULL,OT_E,OS_b),//ModRM.reg=011
	OpcodeTableEntry("MUL",NULL,OT_E,OS_b),//ModRM.reg=100
	OpcodeTableEntry("IMUL",NULL,OT_E,OS_b),//ModRM.reg=101
	OpcodeTableEntry("DIV",NULL,OT_E,OS_b),//ModRM.reg=110
	OpcodeTableEntry("IDIV",NULL,OT_E,OS_b),//ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup3_f7[8]=
{
	OpcodeTableEntry("TEST",NULL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=000
	OpcodeTableEntry("TEST",NULL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=001
	OpcodeTableEntry("NOT",NULL,OT_E,OS_v),//ModRM.reg=010
	OpcodeTableEntry("NEG",NULL,OT_E,OS_v),//ModRM.reg=011
	OpcodeTableEntry("MUL",NULL,OT_E,OS_v),//ModRM.reg=100
	OpcodeTableEntry("IMUL",NULL,OT_E,OS_v),//ModRM.reg=101
	OpcodeTableEntry("DIV",NULL,OT_E,OS_v),//ModRM.reg=110
	OpcodeTableEntry("IDIV",NULL,OT_E,OS_v),//ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup4_fe[8]=
{
	OpcodeTableEntry("INC",NULL,OT_E,OS_b),
	OpcodeTableEntry("DEC",NULL,OT_E,OS_b),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid")
};
OpcodeTableEntry opcodeTableGroup5_ff[8]=
{
	OpcodeTableEntry("INC",NULL,OT_E,OS_v),
	OpcodeTableEntry("DEC",NULL,OT_E,OS_v),
	OpcodeTableEntry("CALL",NULL,OT_E,OS_v),
	OpcodeTableEntry("CALL",NULL,OT_M,OS_p),
	OpcodeTableEntry("JMP",NULL,OT_E,OS_v),
	OpcodeTableEntry("JMP",NULL,OT_M,OS_p),
	OpcodeTableEntry("PUSH",NULL,OT_E,OS_v),
	OpcodeTableEntry("invalid")
};
OpcodeTableEntry opcodeTableGroup6_00[8]=
{
	OpcodeTableEntry("SLDT",NULL,OT_E,OS_Mw_Rv),
	OpcodeTableEntry("STR",NULL,OT_E,OS_Mw_Rv),
	OpcodeTableEntry("LLDT",NULL,OT_E,OS_w),
	OpcodeTableEntry("LTR",NULL,OT_E,OS_w),
	OpcodeTableEntry("VERR",NULL,OT_E,OS_w),
	OpcodeTableEntry("VERW",NULL,OT_E,OS_w),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid")
};
OpcodeTableEntry opcodeTableGroup7_01[8]=
{
	OpcodeTableEntry("SGDT",NULL,OT_M,OS_s),
	OpcodeTableEntry("SIDT",NULL,OT_M,OS_s),
	OpcodeTableEntry("LGDT",NULL,OT_M,OS_s),
	OpcodeTableEntry("LIDT",NULL,OT_M,OS_s),
	OpcodeTableEntry("SMSW",NULL,OT_E,OS_Mw_Rv),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("LMSW",NULL,OT_E,OS_w),
	OpcodeTableEntry("INVLPG Mb SWAPGS",NULL)
};
OpcodeTableEntry opcodeTableGroup8_ba[8]=
{
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("BT",NULL,OT_E,OS_v,OT_I,OS_b),
	OpcodeTableEntry("BTS",NULL,OT_E,OS_v,OT_I,OS_b),
	OpcodeTableEntry("BTR",NULL,OT_E,OS_v,OT_I,OS_b),
	OpcodeTableEntry("BTC",NULL,OT_E,OS_v,OT_I,OS_b)
};
OpcodeTableEntry opcodeTableGroup9_c7[8]=
{
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("CMPXCHG8B Mq CMPXCHG16 Mdq"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid")
};
OpcodeTableEntry opcodeTableGroup11_c6[8]=
{
	OpcodeTableEntry("MOV",NULL,OT_E,OS_b,OT_I,OS_b),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid")
};
OpcodeTableEntry opcodeTableGroup11_c7[8]=
{
	OpcodeTableEntry("MOV",NULL,OT_E,OS_v,OT_I,OS_z),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid")
};
OpcodeTableEntry opcodeTableGroup12_71[8]=
{
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("PSRLW",NULL,OT_PR,OS_q,OT_I,OS_b),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("PSRAW",NULL,OT_PR,OS_q,OT_I,OS_b),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("PSLLW",NULL,OT_PR,OS_q,OT_I,OS_b),
	OpcodeTableEntry("invalid")
};
OpcodeTableEntry opcodeTableGroup13_72[8]=
{
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("PSRLD",NULL,OT_PR,OS_q,OT_I,OS_b),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("PSRAD",NULL,OT_PR,OS_q,OT_I,OS_b),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("PSLLD",NULL,OT_PR,OS_q,OT_I,OS_b),
	OpcodeTableEntry("invalid")
};
OpcodeTableEntry opcodeTableGroup14_73[8]=
{
	OpcodeTableEntry("invalid",NULL),
	OpcodeTableEntry("invalid",NULL),
	OpcodeTableEntry("PSRLQ",NULL,OT_PR,OS_q,OT_I,OS_b),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("PSLLQ",NULL,OT_PR,OS_q,OT_I,OS_b),
	OpcodeTableEntry("invalid")
};
OpcodeTableEntry opcodeTableGroup15_ae[8]=
{
	OpcodeTableEntry("FXSAVE",NULL,OT_M,OS_NOT_EXISTS),
	OpcodeTableEntry("FXSTOR",NULL,OT_M,OS_NOT_EXISTS),
	OpcodeTableEntry("LDMXCSR",NULL,OT_M,OS_d),
	OpcodeTableEntry("STMXCSR",NULL,OT_M,OS_d),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("LFENCE"),
	OpcodeTableEntry("MFENCE"),
	OpcodeTableEntry("SFENCE/CLFLUSH",NULL,OT_M,OS_b)
};
OpcodeTableEntry opcodeTableOneByte[256]=
{
    OpcodeTableEntry("ADD",NULL,OT_E,OS_b,OT_G,OS_b),//0x00
    OpcodeTableEntry("ADD",NULL,OT_E,OS_v,OT_G,OS_v),//0x01
    OpcodeTableEntry("ADD",NULL,OT_G,OS_b,OT_E,OS_b),//0x02
    OpcodeTableEntry("ADD",NULL,OT_G,OS_v,OT_E,OS_v),//0x03
    OpcodeTableEntry("ADD",NULL,OT_RAX,OS_b,OT_I,OS_b),//0x04
    OpcodeTableEntry("ADD",NULL,OT_RAX,OS_v,OT_I,OS_z),//0x05
    OpcodeTableEntry("PUSH",NULL,OT_ES,OS_w),//0x06
    OpcodeTableEntry("POP",NULL,OT_ES,OS_w),//0x07
    OpcodeTableEntry("OR",NULL,OT_E,OS_b,OT_G,OS_b),//0x08
    OpcodeTableEntry("OR",NULL,OT_E,OS_v,OT_G,OS_v),//0x09
    OpcodeTableEntry("OR",NULL,OT_G,OS_b,OT_E,OS_b),//0x0a
    OpcodeTableEntry("OR",NULL,OT_G,OS_v,OT_E,OS_v),//0x0b
    OpcodeTableEntry("OR",NULL,OT_RAX,OS_b,OT_I,OS_b),//0x0c
    OpcodeTableEntry("OR",NULL,OT_RAX,OS_v,OT_I,OS_z),//0x0d
    OpcodeTableEntry("PUSH",NULL,OT_CS,OS_w),//0x0e
    OpcodeTableEntry("escape prefix",NULL),//0x0f
    OpcodeTableEntry("ADC",NULL,OT_E,OS_b,OT_G,OS_b),//0x10
    OpcodeTableEntry("ADC",NULL,OT_E,OS_v,OT_G,OS_v),//0x11
    OpcodeTableEntry("ADC",NULL,OT_G,OS_b,OT_E,OS_b),//0x12
    OpcodeTableEntry("ADC",NULL,OT_G,OS_v,OT_E,OS_v),//0x13
    OpcodeTableEntry("ADC",NULL,OT_RAX,OS_b,OT_I,OS_b),//0x14
    OpcodeTableEntry("ADC",NULL,OT_RAX,OS_v,OT_I,OS_z),//0x15
    OpcodeTableEntry("PUSH",NULL,OT_SS,OS_w),//0x16
    OpcodeTableEntry("POP",NULL,OT_SS,OS_w),//0x17
    OpcodeTableEntry("SBB",NULL,OT_E,OS_b,OT_G,OS_b),//0x18
    OpcodeTableEntry("SBB",NULL,OT_E,OS_v,OT_G,OS_v),//0x19
    OpcodeTableEntry("SBB",NULL,OT_G,OS_b,OT_E,OS_b),//0x1a
    OpcodeTableEntry("SBB",NULL,OT_G,OS_v,OT_E,OS_v),//0x1b
    OpcodeTableEntry("SBB",NULL,OT_RAX,OS_b,OT_I,OS_b),//0x1c
    OpcodeTableEntry("SBB",NULL,OT_RAX,OS_v,OT_I,OS_z),//0x1d
    OpcodeTableEntry("PUSH",NULL,OT_DS,OS_w),//0x1e
    OpcodeTableEntry("POP",NULL,OT_DS,OS_w),//0x1f
    OpcodeTableEntry("AND",NULL,OT_E,OS_b,OT_G,OS_b),//0x20
    OpcodeTableEntry("AND",NULL,OT_E,OS_v,OT_G,OS_v),//0x21
    OpcodeTableEntry("AND",NULL,OT_G,OS_b,OT_E,OS_b),//0x22
    OpcodeTableEntry("AND",NULL,OT_G,OS_v,OT_E,OS_v),//0x23
    OpcodeTableEntry("AND",NULL,OT_RAX,OS_b,OT_I,OS_b),//0x24
    OpcodeTableEntry("AND",NULL,OT_RAX,OS_v,OT_I,OS_z),//0x25
    OpcodeTableEntry("seg ES",NULL),//0x26
    OpcodeTableEntry("DAA",NULL),//0x27
    OpcodeTableEntry("SUB",NULL,OT_E,OS_b,OT_G,OS_b),//0x28
    OpcodeTableEntry("SUB",NULL,OT_E,OS_v,OT_G,OS_v),//0x29
    OpcodeTableEntry("SUB",NULL,OT_G,OS_b,OT_E,OS_b),//0x2a
    OpcodeTableEntry("SUB",NULL,OT_G,OS_v,OT_E,OS_v),//0x2b
    OpcodeTableEntry("SUB",NULL,OT_RAX,OS_b,OT_I,OS_b),//0x2c
    OpcodeTableEntry("SUB",NULL,OT_RAX,OS_v,OT_I,OS_z),//0x2d
    OpcodeTableEntry("seg CS",NULL),//0x2e
    OpcodeTableEntry("DAS",NULL),//0x2f
    OpcodeTableEntry("XOR",NULL,OT_E,OS_b,OT_G,OS_b),//0x30
    OpcodeTableEntry("XOR",NULL,OT_E,OS_v,OT_G,OS_v),//0x31
    OpcodeTableEntry("XOR",NULL,OT_G,OS_b,OT_E,OS_b),//0x32
    OpcodeTableEntry("XOR",NULL,OT_G,OS_v,OT_E,OS_v),//0x33
    OpcodeTableEntry("XOR",NULL,OT_RAX,OS_b,OT_I,OS_b),//0x34
    OpcodeTableEntry("XOR",NULL,OT_RAX,OS_v,OT_I,OS_z),//0x35
    OpcodeTableEntry("seg SS",NULL),//0x36
    OpcodeTableEntry("AAA",NULL),//0x37
    OpcodeTableEntry("CMP",NULL,OT_E,OS_b,OT_G,OS_b),//0x38
    OpcodeTableEntry("CMP",NULL,OT_E,OS_v,OT_G,OS_v),//0x39
    OpcodeTableEntry("CMP",NULL,OT_G,OS_b,OT_E,OS_b),//0x3a
    OpcodeTableEntry("CMP",NULL,OT_G,OS_v,OT_E,OS_v),//0x3b
    OpcodeTableEntry("CMP",NULL,OT_RAX,OS_b,OT_I,OS_b),//0x3c
    OpcodeTableEntry("CMP",NULL,OT_RAX,OS_v,OT_I,OS_z),//0x3d
    OpcodeTableEntry("seg DS",NULL),//0x3e
    OpcodeTableEntry("AAS",NULL),//0x3f
    OpcodeTableEntry("INC",NULL,OT_RAX,OS_z),//0x40
    OpcodeTableEntry("INC",NULL,OT_RCX,OS_z),//0x41
    OpcodeTableEntry("INC",NULL,OT_RDX,OS_z),//0x42
    OpcodeTableEntry("INC",NULL,OT_RBX,OS_z),//0x43
    OpcodeTableEntry("INC",NULL,OT_RSP,OS_z),//0x44
    OpcodeTableEntry("INC",NULL,OT_RBP,OS_z),//0x45
    OpcodeTableEntry("INC",NULL,OT_RSI,OS_z),//0x46
    OpcodeTableEntry("INC",NULL,OT_RDI,OS_z),//0x47
    OpcodeTableEntry("DEC",NULL,OT_RAX,OS_z),//0x48
    OpcodeTableEntry("DEC",NULL,OT_RCX,OS_z),//0x49
    OpcodeTableEntry("DEC",NULL,OT_RDX,OS_z),//0x4a
    OpcodeTableEntry("DEC",NULL,OT_RBX,OS_z),//0x4b
    OpcodeTableEntry("DEC",NULL,OT_RSP,OS_z),//0x4c
    OpcodeTableEntry("DEC",NULL,OT_RBP,OS_z),//0x4d
    OpcodeTableEntry("DEC",NULL,OT_RSI,OS_z),//0x4e
    OpcodeTableEntry("DEC",NULL,OT_RDI,OS_z),//0x4f
    OpcodeTableEntry("PUSH",NULL,OT_RAX,OS_v),//0x50
    OpcodeTableEntry("PUSH",NULL,OT_RCX,OS_v),//0x51
    OpcodeTableEntry("PUSH",NULL,OT_RDX,OS_v),//0x52
    OpcodeTableEntry("PUSH",NULL,OT_RBX,OS_v),//0x53
    OpcodeTableEntry("PUSH",NULL,OT_RSP,OS_v),//0x54
    OpcodeTableEntry("PUSH",NULL,OT_RBP,OS_v),//0x55
    OpcodeTableEntry("PUSH",NULL,OT_RSI,OS_v),//0x56
    OpcodeTableEntry("PUSH",NULL,OT_RDI,OS_v),//0x57
    OpcodeTableEntry("POP",NULL,OT_RAX,OS_v),//0x58
    OpcodeTableEntry("POP",NULL,OT_RCX,OS_v),//0x59
    OpcodeTableEntry("POP",NULL,OT_RDX,OS_v),//0x5a
    OpcodeTableEntry("POP",NULL,OT_RBX,OS_v),//0x5b
    OpcodeTableEntry("POP",NULL,OT_RSP,OS_v),//0x5c
    OpcodeTableEntry("POP",NULL,OT_RBP,OS_v),//0x5d
    OpcodeTableEntry("POP",NULL,OT_RSI,OS_v),//0x5e
    OpcodeTableEntry("POP",NULL,OT_RDI,OS_v),//0x5f
    OpcodeTableEntry("PUSHAx",NULL),//0x60
    OpcodeTableEntry("POPA/D",NULL),//0x61
    OpcodeTableEntry("BOUND",NULL,OT_G,OS_v,OT_M,OS_a),//0x62
    OpcodeTableEntry("ARPL",NULL,OT_E,OS_w,OT_G,OS_w),//0x63
    OpcodeTableEntry("seg FS",NULL),//0x64
    OpcodeTableEntry("seg DS",NULL),//0x65
    OpcodeTableEntry("operand size",NULL),//0x66
    OpcodeTableEntry("address size",NULL),//0x67
    OpcodeTableEntry("PUSH",NULL,OT_I,OS_z),//0x68
    OpcodeTableEntry("IMUL",NULL,OT_G,OS_v,OT_E,OS_v,OT_I,OS_z),//0x69
    OpcodeTableEntry("PUSH",NULL,OT_I,OS_b),//0x6a
    OpcodeTableEntry("IMUL",NULL,OT_G,OS_v,OT_E,OS_v,OT_I,OS_b),//0x6b
    OpcodeTableEntry("INSB",NULL,OT_Y,OS_b,OT_RDX,OS_w),//0x6c
    OpcodeTableEntry("INSW/D",NULL,OT_Y,OS_z,OT_RDX,OS_w),//0x6d
    OpcodeTableEntry("OUTSB",NULL,OT_RDX,OS_w,OT_X,OS_b),//0x6e
    OpcodeTableEntry("OUTSW/D",NULL,OT_RDX,OS_w,OT_X,OS_z),//0x6f
    OpcodeTableEntry("JO",NULL,OT_J,OS_b),//0x70
    OpcodeTableEntry("JNO",NULL,OT_J,OS_b),//0x71
    OpcodeTableEntry("JB",NULL,OT_J,OS_b),//0x72
    OpcodeTableEntry("JNB",NULL,OT_J,OS_b),//0x73
    OpcodeTableEntry("JZ",NULL,OT_J,OS_b),//0x74
    OpcodeTableEntry("JNZ",NULL,OT_J,OS_b),//0x75
    OpcodeTableEntry("JBE",NULL,OT_J,OS_b),//0x76
    OpcodeTableEntry("JNBE",NULL,OT_J,OS_b),//0x77
    OpcodeTableEntry("JS",NULL,OT_J,OS_b),//0x78
    OpcodeTableEntry("JNS",NULL,OT_J,OS_b),//0x79
    OpcodeTableEntry("JP",NULL,OT_J,OS_b),//0x7a
    OpcodeTableEntry("JNP",NULL,OT_J,OS_b),//0x7b
    OpcodeTableEntry("JL",NULL,OT_J,OS_b),//0x7c
    OpcodeTableEntry("JNL",NULL,OT_J,OS_b),//0x7d
    OpcodeTableEntry("JLE",NULL,OT_J,OS_b),//0x7e
    OpcodeTableEntry("JNLE",NULL,OT_J,OS_b),//0x7f
    OpcodeTableEntry("Group 1",opcodeTableGroup1_80),//0x80
    OpcodeTableEntry("Group 1",opcodeTableGroup1_81),//0x81
    OpcodeTableEntry("Group 1",opcodeTableGroup1_82),//0x82
    OpcodeTableEntry("Group 1",opcodeTableGroup1_83),//0x83
    OpcodeTableEntry("TEST",NULL,OT_E,OS_b,OT_G,OS_b),//0x84
    OpcodeTableEntry("TEST",NULL,OT_E,OS_v,OT_G,OS_v),//0x85
    OpcodeTableEntry("XCHG",NULL,OT_E,OS_b,OT_G,OS_b),//0x86
    OpcodeTableEntry("XCHG",NULL,OT_E,OS_v,OT_G,OS_b),//0x87
    OpcodeTableEntry("MOV",NULL,OT_E,OS_b,OT_G,OS_b),//0x88
    OpcodeTableEntry("MOV",NULL,OT_E,OS_v,OT_G,OS_v),//0x89
    OpcodeTableEntry("MOV",NULL,OT_G,OS_b,OT_E,OS_b),//0x8a
    OpcodeTableEntry("MOV",NULL,OT_G,OS_v,OT_E,OS_v),//0x8b
    OpcodeTableEntry("MOV",NULL,OT_E,OS_Mw_Rv,OT_S,OS_w),//0x8c
    OpcodeTableEntry("LEA",NULL,OT_G,OS_v,OT_M,OS_NOT_EXISTS),//0x8d
    OpcodeTableEntry("MOV",NULL,OT_S,OS_w,OT_E,OS_w),//0x8e
    OpcodeTableEntry("Group 1a",opcodeTableGroup1a),//0x8f
	OpcodeTableEntry("NOP/PAUSE",NULL),//0x90 //XCHG r8,rAX in 64-bit mode.
	OpcodeTableEntry("XCHG",NULL,OT_RCX,OS_v,OT_RAX,OS_v),//0x91
	OpcodeTableEntry("XCHG",NULL,OT_RDX,OS_v,OT_RAX,OS_v),//0x92
	OpcodeTableEntry("XCHG",NULL,OT_RBX,OS_v,OT_RAX,OS_v),//0x93
	OpcodeTableEntry("XCHG",NULL,OT_RSP,OS_v,OT_RAX,OS_v),//0x94
	OpcodeTableEntry("XCHG",NULL,OT_RBP,OS_v,OT_RAX,OS_v),//0x95
	OpcodeTableEntry("XCHG",NULL,OT_RSI,OS_v,OT_RAX,OS_v),//0x96
	OpcodeTableEntry("XCHG",NULL,OT_RDI,OS_v,OT_RAX,OS_v),//0x97
	OpcodeTableEntry("CBW/CWDE/CDQE",NULL),//0x98
	OpcodeTableEntry("CWD/CDQ/CQO",NULL),//0x99
	OpcodeTableEntry("CALL",NULL,OT_A,OS_p),//0x9a
	OpcodeTableEntry("WAIT/FWAIT",NULL),//0x9b
	OpcodeTableEntry("PUSHF/D/Q",NULL,OT_F,OS_v),//0x9c
	OpcodeTableEntry("POPF/D/Q",NULL,OT_F,OS_v),//0x9d
	OpcodeTableEntry("SAHF",NULL),//0x9e
	OpcodeTableEntry("LAHF",NULL),//0x9f
	OpcodeTableEntry("MOV",NULL,OT_RAX,OS_b,OT_O,OS_b),//0xa0
	OpcodeTableEntry("MOV",NULL,OT_RAX,OS_v,OT_O,OS_v),//0xa1
	OpcodeTableEntry("MOV",NULL,OT_O,OS_b,OT_RAX,OS_b),//0xa2
	OpcodeTableEntry("MOV",NULL,OT_O,OS_v,OT_RAX,OS_v),//0xa3
	OpcodeTableEntry("MOVSB",NULL,OT_Y,OS_b,OT_X,OS_b),//0xa4
	OpcodeTableEntry("MOVSW/D/Q",NULL,OT_Y,OS_v,OT_X,OS_v),//0xa5
	OpcodeTableEntry("CMPSB",NULL,OT_X,OS_b,OT_Y,OS_b),//0xa6
	OpcodeTableEntry("CMPSW/D/Q",NULL,OT_X,OS_v,OT_Y,OS_v),//0xa7
	OpcodeTableEntry("TEST",NULL,OT_RAX,OS_b,OT_I,OS_b),//0xa8
	OpcodeTableEntry("TEST",NULL,OT_RAX,OS_z,OT_I,OS_z),//0xa9
	OpcodeTableEntry("STOSB",NULL,OT_Y,OS_v,OT_RAX,OS_b),//0xaa
	OpcodeTableEntry("STOSW/D/Q",NULL,OT_Y,OS_v,OT_RAX,OS_v),//0xab
	OpcodeTableEntry("LODSB",NULL,OT_RAX,OS_b,OT_X,OS_b),//0xac
	OpcodeTableEntry("LODSW/D/Q",NULL,OT_RAX,OS_v,OT_X,OS_v),//0xad
	OpcodeTableEntry("SCASB",NULL,OT_RAX,OS_b,OT_Y,OS_b),//0xae
	OpcodeTableEntry("SCASW/D/Q",NULL,OT_RAX,OS_v,OT_Y,OS_v),//0xaf
	OpcodeTableEntry("MOV",NULL,OT_RAX,OS_b,OT_I,OS_b),//0xb0
	OpcodeTableEntry("MOV",NULL,OT_RCX,OS_b,OT_I,OS_b),//0xb1
	OpcodeTableEntry("MOV",NULL,OT_RDX,OS_b,OT_I,OS_b),//0xb2
	OpcodeTableEntry("MOV",NULL,OT_RBX,OS_b,OT_I,OS_b),//0xb3
	OpcodeTableEntry("MOV",NULL,OT_RSP,OS_b,OT_I,OS_b),//0xb4 //OT_RSP=AH in 16bit
	OpcodeTableEntry("MOV",NULL,OT_RBP,OS_b,OT_I,OS_b),//0xb5 //OT_RBP=CH in 16bit
	OpcodeTableEntry("MOV",NULL,OT_RSI,OS_b,OT_I,OS_b),//0xb6 //OT_RSI=DH in 16bit
	OpcodeTableEntry("MOV",NULL,OT_RDI,OS_b,OT_I,OS_b),//0xb7 //OT_RDI=BH in 16bit
	OpcodeTableEntry("MOV",NULL,OT_RAX,OS_v,OT_I,OS_v),//0xb8
	OpcodeTableEntry("MOV",NULL,OT_RCX,OS_v,OT_I,OS_v),//0xb9
	OpcodeTableEntry("MOV",NULL,OT_RDX,OS_v,OT_I,OS_v),//0xba
	OpcodeTableEntry("MOV",NULL,OT_RBX,OS_v,OT_I,OS_v),//0xbb
	OpcodeTableEntry("MOV",NULL,OT_RSP,OS_v,OT_I,OS_v),//0xbc
	OpcodeTableEntry("MOV",NULL,OT_RBP,OS_v,OT_I,OS_v),//0xbd
	OpcodeTableEntry("MOV",NULL,OT_RSI,OS_v,OT_I,OS_v),//0xbe
	OpcodeTableEntry("MOV",NULL,OT_RDI,OS_v,OT_I,OS_v),//0xbf
	OpcodeTableEntry("Group 2",opcodeTableGroup2_c0),//0xc0
	OpcodeTableEntry("Group 2",opcodeTableGroup2_c1),//0xc1
	OpcodeTableEntry("RET near",NULL,OT_I,OS_w),//0xc2
	OpcodeTableEntry("RET near",NULL,OT_ZERO,OS_w),//0xc3
	OpcodeTableEntry("LES",NULL,OT_G,OS_z,OT_M,OS_p),//0xc4
	OpcodeTableEntry("LDS",NULL,OT_G,OS_z,OT_M,OS_p),//0xc5
	OpcodeTableEntry("Group 11",opcodeTableGroup11_c6),//0xc6
	OpcodeTableEntry("Group 11",opcodeTableGroup11_c7),//0xc7
	OpcodeTableEntry("ENTER",NULL,OT_I,OS_w,OT_I,OS_b),//0xc8
	OpcodeTableEntry("LEAVE",NULL),//0xc9
	OpcodeTableEntry("RET far",NULL,OT_I,OS_w),//0xca
	OpcodeTableEntry("RET far",NULL,OT_ZERO,OS_w),//0xcb
	OpcodeTableEntry("INT3",NULL),//0xcc
	OpcodeTableEntry("INT",NULL,OT_I,OS_b),//0xcd
	OpcodeTableEntry("INTO",NULL),//0xce
	OpcodeTableEntry("IRET/IRETD/IRETQ",NULL),//0xcf
	OpcodeTableEntry("Group 2",opcodeTableGroup2_d0),//0xd0
	OpcodeTableEntry("Group 2",opcodeTableGroup2_d1),//0xd1
	OpcodeTableEntry("Group 2",opcodeTableGroup2_d2),//0xd2
	OpcodeTableEntry("Group 2",opcodeTableGroup2_d3),//0xd3
	OpcodeTableEntry("AAM",NULL),//0xd4
	OpcodeTableEntry("AAD",NULL),//0xd5
	OpcodeTableEntry("SALC",NULL),//0xd6
	OpcodeTableEntry("XLAT",NULL),//0xd7
	OpcodeTableEntry("x87",NULL),//0xd8
	OpcodeTableEntry("x87",NULL),//0xd9
	OpcodeTableEntry("x87",NULL),//0xda
	OpcodeTableEntry("x87",NULL),//0xdb
	OpcodeTableEntry("x87",NULL),//0xdc
	OpcodeTableEntry("x87",NULL),//0xdd
	OpcodeTableEntry("x87",NULL),//0xde
	OpcodeTableEntry("x87",NULL),//0xdf
	OpcodeTableEntry("LOOPNE/NZ",NULL,OT_J,OS_b),//0xe0
	OpcodeTableEntry("LOOPE/Z",NULL,OT_J,OS_b),//0xe1
	OpcodeTableEntry("LOOP",NULL,OT_J,OS_b),//0xe2
	OpcodeTableEntry("JrCXZ",NULL,OT_J,OS_b),//0xe3
	OpcodeTableEntry("IN",NULL,OT_RAX,OS_b,OT_I,OS_b),//0xe4
	OpcodeTableEntry("IN",NULL,OT_RAX,OS_z,OT_I,OS_b),//0xe5
	OpcodeTableEntry("OUT",NULL,OT_I,OS_b,OT_RAX,OS_b),//0xe6
	OpcodeTableEntry("OUT",NULL,OT_I,OS_b,OT_RAX,OS_z),//0xe7
	OpcodeTableEntry("CALL",NULL,OT_J,OS_z),//0xe8
	OpcodeTableEntry("JMP",NULL,OT_J,OS_z),//0xe9
	OpcodeTableEntry("JMP",NULL,OT_A,OS_p),//0xea
	OpcodeTableEntry("JMP",NULL,OT_J,OS_b),//0xeb
	OpcodeTableEntry("IN",NULL,OT_RAX,OS_b,OT_RDX,OS_w),//0xec
	OpcodeTableEntry("IN",NULL,OT_RAX,OS_z,OT_RDX,OS_w),//0xed
	OpcodeTableEntry("OUT",NULL,OT_RDX,OS_w,OT_RAX,OS_b),//0xee
	OpcodeTableEntry("OUT",NULL,OT_RDX,OS_w,OT_RAX,OS_z),//0xef
	OpcodeTableEntry("lock",NULL),//0xf0
	OpcodeTableEntry("INT1/ICE Bkpt",NULL),//0xf1
	OpcodeTableEntry("repne",NULL),//0xf2
	OpcodeTableEntry("rep/repe",NULL),//0xf3
	OpcodeTableEntry("HLT",NULL),//0xf4
	OpcodeTableEntry("CMC",NULL),//0xf5
	OpcodeTableEntry("Group 3",opcodeTableGroup3_f6),//0xf6
	OpcodeTableEntry("Group 3",opcodeTableGroup3_f7),//0xf7
	OpcodeTableEntry("CLC",NULL),//0xf8
	OpcodeTableEntry("STC",NULL),//0xf9
	OpcodeTableEntry("CLI",NULL),//0xfa
	OpcodeTableEntry("STI",NULL),//0xfb
	OpcodeTableEntry("CLD",NULL),//0xfc
	OpcodeTableEntry("STD",NULL),//0xfd
	OpcodeTableEntry("Group 4",opcodeTableGroup4_fe),//0xfe
	OpcodeTableEntry("Group 5",opcodeTableGroup5_ff)//0xff
};
OpcodeTableEntry opcodeTableTwoByte_0x0F[256]=
{
	OpcodeTableEntry("Group 6",opcodeTableGroup6_00),//0x00
	OpcodeTableEntry("Group 7",opcodeTableGroup7_01),//0x01
	OpcodeTableEntry("LAR",NULL,OT_G,OS_v,OT_E,OS_w),//0x02
	OpcodeTableEntry("LSL",NULL,OT_G,OS_v,OT_E,OS_w),//0x03
	OpcodeTableEntry("invalid",NULL),//0x04
	OpcodeTableEntry("SYSCALL",NULL),//0x05
	OpcodeTableEntry("CLTS",NULL),//0x06
	OpcodeTableEntry("SYSRET",NULL),//0x07
	OpcodeTableEntry("INVD",NULL),//0x08
	OpcodeTableEntry("WBINVD",NULL),//0x09
	OpcodeTableEntry("invalid",NULL),//0x0a
	OpcodeTableEntry("UD2",NULL),//0x0b
	OpcodeTableEntry("invalid",NULL),//0x0c
	OpcodeTableEntry("Group P",NULL),//0x0d
	OpcodeTableEntry("FEMMS",NULL),//0x0e
	OpcodeTableEntry("3DNow",NULL),//0x0f
	OpcodeTableEntry("MOVUPS",NULL,OT_V,OS_ps,OT_W,OS_ps),//0x10
	OpcodeTableEntry("MOVUPS",NULL,OT_W,OS_ps,OT_V,OS_ps),//0x11
	OpcodeTableEntry("MOVLPS/MOVHLPS",NULL),//0x12 //not full
	OpcodeTableEntry("MOVLPS",NULL,OT_M,OS_q,OT_V,OS_ps),//0x13
	OpcodeTableEntry("UNPCKLPS",NULL,OT_V,OS_ps,OT_W,OS_q),//0x14
	OpcodeTableEntry("UNPCKLPS",NULL,OT_V,OS_ps,OT_W,OS_q),//0x15
	OpcodeTableEntry("MOVHPS/MOVLHPS",NULL),//0x16 //not full
	OpcodeTableEntry("MOVHPS",NULL,OT_M,OS_q,OT_V,OS_ps),//0x17
	OpcodeTableEntry("Group 16",NULL),//0x18
	OpcodeTableEntry("NOP",NULL),//0x19
	OpcodeTableEntry("NOP",NULL),//0x1a
	OpcodeTableEntry("NOP",NULL),//0x1b
	OpcodeTableEntry("NOP",NULL),//0x1c
	OpcodeTableEntry("NOP",NULL),//0x1d
	OpcodeTableEntry("NOP",NULL),//0x1e
	OpcodeTableEntry("NOP",NULL),//0x1f
	OpcodeTableEntry("MOV",NULL,OT_R,OS_d_q,OT_C,OS_d_q),//0x20
	OpcodeTableEntry("MOV",NULL,OT_R,OS_d_q,OT_D,OS_d_q),//0x21
	OpcodeTableEntry("MOV",NULL,OT_C,OS_d_q,OT_R,OS_d_q),//0x22
	OpcodeTableEntry("MOV",NULL,OT_D,OS_d_q,OT_R,OS_d_q),//0x23
	OpcodeTableEntry("invalid",NULL),//0x24
	OpcodeTableEntry("invalid",NULL),//0x25
	OpcodeTableEntry("invalid",NULL),//0x26
	OpcodeTableEntry("invalid",NULL),//0x27
	OpcodeTableEntry("MOVAPS",NULL,OT_V,OS_ps,OT_W,OS_ps),//0x28
	OpcodeTableEntry("MOVAPS",NULL,OT_W,OS_ps,OT_V,OS_ps),//0x29
	OpcodeTableEntry("CVTPI2PS",NULL,OT_V,OS_ps,OT_Q,OS_q),//0x2a
	OpcodeTableEntry("MOVNTPS",NULL,OT_M,OS_dq,OT_V,OS_ps),//0x2b
	OpcodeTableEntry("CVTTPS2PI",NULL,OT_P,OS_q,OT_W,OS_ps),//0x2c
	OpcodeTableEntry("CVTPS2PI",NULL,OT_P,OS_q,OT_W,OS_ps),//0x2d
	OpcodeTableEntry("UCOMISS",NULL,OT_V,OS_ss,OT_W,OS_ss),//0x2e
	OpcodeTableEntry("COMISS",NULL,OT_V,OS_ps,OT_W,OS_ps),//0x2f
	OpcodeTableEntry("WRMSR",NULL),//0x30
	OpcodeTableEntry("RDTSC",NULL),//0x31
	OpcodeTableEntry("RDMSR",NULL),//0x32
	OpcodeTableEntry("RDPMC",NULL),//0x33
	OpcodeTableEntry("SYSENTER",NULL),//0x34
	OpcodeTableEntry("SYSEXIT",NULL),//0x35
	OpcodeTableEntry("invalid",NULL),//0x36
	OpcodeTableEntry("invalid",NULL),//0x37
	OpcodeTableEntry("invalid",NULL),//0x38
	OpcodeTableEntry("invalid",NULL),//0x39
	OpcodeTableEntry("invalid",NULL),//0x3a
	OpcodeTableEntry("invalid",NULL),//0x3b
	OpcodeTableEntry("invalid",NULL),//0x3c
	OpcodeTableEntry("invalid",NULL),//0x3d
	OpcodeTableEntry("invalid",NULL),//0x3e
	OpcodeTableEntry("invalid",NULL),//0x3f
	OpcodeTableEntry("CMOVO",NULL,OT_G,OS_v,OT_E,OS_v),//0x40
	OpcodeTableEntry("CMOVNO",NULL,OT_G,OS_v,OT_E,OS_v),//0x41
	OpcodeTableEntry("CMOVB",NULL,OT_G,OS_v,OT_E,OS_v),//0x42
	OpcodeTableEntry("CMOVNB",NULL,OT_G,OS_v,OT_E,OS_v),//0x43
	OpcodeTableEntry("CMOVZ",NULL,OT_G,OS_v,OT_E,OS_v),//0x44
	OpcodeTableEntry("CMOVNZ",NULL,OT_G,OS_v,OT_E,OS_v),//0x45
	OpcodeTableEntry("CMOVBE",NULL,OT_G,OS_v,OT_E,OS_v),//0x46
	OpcodeTableEntry("CMOVNBE",NULL,OT_G,OS_v,OT_E,OS_v),//0x47
	OpcodeTableEntry("CMOVS",NULL,OT_G,OS_v,OT_E,OS_v),//0x48
	OpcodeTableEntry("CMOVNS",NULL,OT_G,OS_v,OT_E,OS_v),//0x49
	OpcodeTableEntry("CMOVP",NULL,OT_G,OS_v,OT_E,OS_v),//0x4a
	OpcodeTableEntry("CMOVNP",NULL,OT_G,OS_v,OT_E,OS_v),//0x4b
	OpcodeTableEntry("CMOVL",NULL,OT_G,OS_v,OT_E,OS_v),//0x4c
	OpcodeTableEntry("CMOVNL",NULL,OT_G,OS_v,OT_E,OS_v),//0x4d
	OpcodeTableEntry("CMOVLE",NULL,OT_G,OS_v,OT_E,OS_v),//0x4e
	OpcodeTableEntry("CMOVNLE",NULL,OT_G,OS_v,OT_E,OS_v),//0x4f
	OpcodeTableEntry("MOVMSKPS",NULL,OT_G,OS_d,OT_VR,OS_ps),//0x50
	OpcodeTableEntry("SQRTPS",NULL,OT_V,OS_ps,OT_W,OS_ps),//0x51
	OpcodeTableEntry("RSQRTPS",NULL,OT_V,OS_ps,OT_W,OS_ps),//0x52
	OpcodeTableEntry("RCPPS",NULL,OT_V,OS_ps,OT_W,OS_ps),//0x53
	OpcodeTableEntry("ANDPS",NULL,OT_V,OS_ps,OT_W,OS_ps),//0x54
	OpcodeTableEntry("ANDNPS",NULL,OT_V,OS_ps,OT_W,OS_ps),//0x55
	OpcodeTableEntry("ORPS",NULL,OT_V,OS_ps,OT_W,OS_ps),//0x56
	OpcodeTableEntry("XORPS",NULL,OT_V,OS_ps,OT_W,OS_ps),//0x57
	OpcodeTableEntry("ADDPS",NULL,OT_V,OS_ps,OT_W,OS_ps),//0x58
	OpcodeTableEntry("MULPS",NULL,OT_V,OS_ps,OT_W,OS_ps),//0x59
	OpcodeTableEntry("CVTPS2PD",NULL,OT_V,OS_pd,OT_W,OS_ps),//0x5a
	OpcodeTableEntry("CVTDQ2PS",NULL,OT_V,OS_ps,OT_W,OS_dq),//0x5b
	OpcodeTableEntry("SUBPS",NULL,OT_V,OS_ps,OT_W,OS_ps),//0x5c
	OpcodeTableEntry("MINPS",NULL,OT_V,OS_ps,OT_W,OS_ps),//0x5d
	OpcodeTableEntry("DIVPS",NULL,OT_V,OS_ps,OT_W,OS_ps),//0x5e
	OpcodeTableEntry("MAXPS",NULL,OT_V,OS_ps,OT_W,OS_ps),//0x5f
	OpcodeTableEntry("PUNPCKLBW",NULL,OT_P,OS_q,OT_Q,OS_d),//0x60
	OpcodeTableEntry("PUNPCKLWD",NULL,OT_P,OS_q,OT_Q,OS_d),//0x61
	OpcodeTableEntry("PUNPCKLDQ",NULL,OT_P,OS_q,OT_Q,OS_d),//0x62
	OpcodeTableEntry("PACKSSWB",NULL,OT_P,OS_q,OT_Q,OS_d),//0x63
	OpcodeTableEntry("PCMPGTB",NULL,OT_P,OS_q,OT_Q,OS_d),//0x64
	OpcodeTableEntry("PCMPGTW",NULL,OT_P,OS_q,OT_Q,OS_d),//0x65
	OpcodeTableEntry("PCMPGTD",NULL,OT_P,OS_q,OT_Q,OS_d),//0x66
	OpcodeTableEntry("PACKUSWB",NULL,OT_P,OS_q,OT_Q,OS_d),//0x67
	OpcodeTableEntry("PUNPCKHBW",NULL,OT_P,OS_q,OT_Q,OS_d),//0x68
	OpcodeTableEntry("PUNPCKHWD",NULL,OT_P,OS_q,OT_Q,OS_d),//0x69
	OpcodeTableEntry("PUNPCKHDQ",NULL,OT_P,OS_q,OT_Q,OS_d),//0x6a
	OpcodeTableEntry("PACKSSDW",NULL,OT_P,OS_q,OT_Q,OS_q),//0x6b
	OpcodeTableEntry("invalid",NULL),//0x6c
	OpcodeTableEntry("invalid",NULL),//0x6d
	OpcodeTableEntry("MOVD",NULL,OT_P,OS_q,OT_E,OS_d_q),//0x6e
	OpcodeTableEntry("MOVQ",NULL,OT_P,OS_q,OT_Q,OS_q),//0x6f
	OpcodeTableEntry("PSHUFW",NULL,OT_P,OS_q,OT_Q,OS_q,OT_I,OS_b),//0x70
	OpcodeTableEntry("Group 12",opcodeTableGroup12_71),//0x71
	OpcodeTableEntry("Group 13",opcodeTableGroup13_72),//0x72
	OpcodeTableEntry("Group 14",opcodeTableGroup14_73),//0x73
	OpcodeTableEntry("PCMPEQB",NULL,OT_V,OS_dq,OT_W,OS_dq),//0x74
	OpcodeTableEntry("PCMPEQW",NULL,OT_V,OS_dq,OT_W,OS_dq),//0x75
	OpcodeTableEntry("PCMPEQD",NULL,OT_V,OS_dq,OT_W,OS_dq),//0x76
	OpcodeTableEntry("invalid",NULL),//0x77
	OpcodeTableEntry("invalid",NULL),//0x78
	OpcodeTableEntry("invalid",NULL),//0x79
	OpcodeTableEntry("invalid",NULL),//0x7a
	OpcodeTableEntry("invalid",NULL),//0x7b
	OpcodeTableEntry("invalid",NULL),//0x7c
	OpcodeTableEntry("invalid",NULL),//0x7d
	OpcodeTableEntry("MOVD",NULL,OT_E,OS_d_q,OT_P,OS_d_q),//0x7e
	OpcodeTableEntry("MOVQ",NULL,OT_Q,OS_q,OT_P,OS_q),//0x7f
	OpcodeTableEntry("JO",NULL,OT_J,OS_z),//0x80
	OpcodeTableEntry("JNO",NULL,OT_J,OS_z),//0x81
	OpcodeTableEntry("JB",NULL,OT_J,OS_z),//0x82
	OpcodeTableEntry("JNB",NULL,OT_J,OS_z),//0x83
	OpcodeTableEntry("JZ",NULL,OT_J,OS_z),//0x84
	OpcodeTableEntry("JNZ",NULL,OT_J,OS_z),//0x85
	OpcodeTableEntry("JBE",NULL,OT_J,OS_z),//0x86
	OpcodeTableEntry("JNBE",NULL,OT_J,OS_z),//0x87
	OpcodeTableEntry("JS",NULL,OT_J,OS_z),//0x88
	OpcodeTableEntry("JNS",NULL,OT_J,OS_z),//0x89
	OpcodeTableEntry("JP",NULL,OT_J,OS_z),//0x8a
	OpcodeTableEntry("JNP",NULL,OT_J,OS_z),//0x8b
	OpcodeTableEntry("JL",NULL,OT_J,OS_z),//0x8c
	OpcodeTableEntry("JNL",NULL,OT_J,OS_z),//0x8d
	OpcodeTableEntry("JLE",NULL,OT_J,OS_z),//0x8e
	OpcodeTableEntry("JNLE",NULL,OT_J,OS_z),//0x8f
	OpcodeTableEntry("SETO",NULL,OT_E,OS_b),//0x90
	OpcodeTableEntry("SETNO",NULL,OT_E,OS_b),//0x91
	OpcodeTableEntry("SETB",NULL,OT_E,OS_b),//0x92
	OpcodeTableEntry("SETNB",NULL,OT_E,OS_b),//0x93
	OpcodeTableEntry("SETZ",NULL,OT_E,OS_b),//0x94
	OpcodeTableEntry("SETNZ",NULL,OT_E,OS_b),//0x95
	OpcodeTableEntry("SETBE",NULL,OT_E,OS_b),//0x96
	OpcodeTableEntry("SETNBE",NULL,OT_E,OS_b),//0x97
	OpcodeTableEntry("SETS",NULL,OT_E,OS_b),//0x98
	OpcodeTableEntry("SETNS",NULL,OT_E,OS_b),//0x99
	OpcodeTableEntry("SETP",NULL,OT_E,OS_b),//0x9a
	OpcodeTableEntry("SETNP",NULL,OT_E,OS_b),//0x9b
	OpcodeTableEntry("SETL",NULL,OT_E,OS_b),//0x9c
	OpcodeTableEntry("SETNL",NULL,OT_E,OS_b),//0x9d
	OpcodeTableEntry("SETLE",NULL,OT_E,OS_b),//0x9e
	OpcodeTableEntry("SETNLE",NULL,OT_E,OS_b),//0x9f
	OpcodeTableEntry("PUSH",NULL,OT_FS,OS_w),//0xa0
	OpcodeTableEntry("POP",NULL,OT_FS,OS_w),//0xa1
	OpcodeTableEntry("CPUID",NULL),//0xa2
	OpcodeTableEntry("BT",NULL,OT_E,OS_v,OT_G,OS_v),//0xa3
	OpcodeTableEntry("SHLD",NULL,OT_E,OS_v,OT_G,OS_v,OT_I,OS_b),//0xa4
	OpcodeTableEntry("SHLD",NULL,OT_E,OS_v,OT_G,OS_v,OT_RCX,OS_b),//0xa5
	OpcodeTableEntry("invalid",NULL),//0xa6
	OpcodeTableEntry("invalid",NULL),//0xa7
	OpcodeTableEntry("PUSH",NULL,OT_GS),//0xa8
	OpcodeTableEntry("POP",NULL,OT_GS),//0xa9
	OpcodeTableEntry("RSM",NULL),//0xaa
	OpcodeTableEntry("BTS",NULL,OT_E,OS_v,OT_G,OS_v),//0xab
	OpcodeTableEntry("SHRD",NULL,OT_E,OS_v,OT_G,OS_v,OT_I,OS_b),//0xac
	OpcodeTableEntry("SHRD",NULL,OT_E,OS_v,OT_G,OS_v,OT_RCX,OS_b),//0xad
	OpcodeTableEntry("Group 15",NULL),//0xae
	OpcodeTableEntry("IMUL",NULL,OT_G,OS_v,OT_E,OS_v),//0xaf
	OpcodeTableEntry("CMPXCHG",NULL,OT_E,OS_b,OT_G,OS_b),//0xb0
	OpcodeTableEntry("CMPXCHG",NULL,OT_E,OS_v,OT_G,OS_v),//0xb1
	OpcodeTableEntry("LSS",NULL,OT_G,OS_z,OT_M,OS_p),//0xb2
	OpcodeTableEntry("BTR",NULL,OT_E,OS_v,OT_G,OS_v),//0xb3
	OpcodeTableEntry("LFS",NULL,OT_G,OS_z,OT_M,OS_p),//0xb4
	OpcodeTableEntry("LGS",NULL,OT_G,OS_z,OT_M,OS_p),//0xb5
	OpcodeTableEntry("MOVZX",NULL,OT_G,OS_v,OT_E,OS_b),//0xb6
	OpcodeTableEntry("MOVZX",NULL,OT_G,OS_v,OT_E,OS_w),//0xb7
	OpcodeTableEntry("invalid",NULL),//0xb8
	OpcodeTableEntry("Group 10",NULL),//0xb9
	OpcodeTableEntry("Group 8",opcodeTableGroup8_ba),//0xba
	OpcodeTableEntry("BTC",NULL,OT_E,OS_v,OT_G,OS_v),//0xbb
	OpcodeTableEntry("BSF",NULL,OT_G,OS_v,OT_E,OS_v),//0xbc
	OpcodeTableEntry("BSR",NULL,OT_G,OS_v,OT_E,OS_v),//0xbd
	OpcodeTableEntry("MOVSX",NULL,OT_G,OS_v,OT_E,OS_b),//0xbe
	OpcodeTableEntry("MOVSX",NULL,OT_G,OS_v,OT_E,OS_w),//0xbf
	OpcodeTableEntry("XADD",NULL,OT_E,OS_b,OT_G,OS_b),//0xc0
	OpcodeTableEntry("XADD",NULL,OT_E,OS_v,OT_G,OS_v),//0xc1
	OpcodeTableEntry("CMPPS",NULL,OT_V,OS_ps,OT_W,OS_ps,OT_I,OS_b),//0xc2
	OpcodeTableEntry("MOVNTI",NULL,OT_M,OS_d_q,OT_G,OS_d_q),//0xc3
	OpcodeTableEntry("PINSRW",NULL,OT_P,OS_q,OT_E,OS_w,OT_I,OS_b),//0xc4
	OpcodeTableEntry("PEXTRW",NULL,OT_G,OS_d,OT_PR,OS_q,OT_I,OS_b),//0xc5
	OpcodeTableEntry("SHUFPS",NULL,OT_V,OS_ps,OT_W,OS_ps,OT_I,OS_b),//0xc6
	OpcodeTableEntry("Group 9",opcodeTableGroup9_c7),//0xc7
	OpcodeTableEntry("BSWAP",NULL,OT_RAX,OS_v),//0xc8
	OpcodeTableEntry("BSWAP",NULL,OT_RCX,OS_v),//0xc9
	OpcodeTableEntry("BSWAP",NULL,OT_RDX,OS_v),//0xca
	OpcodeTableEntry("BSWAP",NULL,OT_RBX,OS_v),//0xcb
	OpcodeTableEntry("BSWAP",NULL,OT_RSP,OS_v),//0xcc
	OpcodeTableEntry("BSWAP",NULL,OT_RBP,OS_v),//0xcd
	OpcodeTableEntry("BSWAP",NULL,OT_RSI,OS_v),//0xce
	OpcodeTableEntry("BSWAP",NULL,OT_RDI,OS_v),//0xcf
	OpcodeTableEntry("invalid",NULL),//0xd0
	OpcodeTableEntry("PSRLW",NULL,OT_P,OS_q,OT_Q,OS_q),//0xd1
	OpcodeTableEntry("PSRLD",NULL,OT_P,OS_q,OT_Q,OS_q),//0xd2
	OpcodeTableEntry("PSRLQ",NULL,OT_P,OS_q,OT_Q,OS_q),//0xd3
	OpcodeTableEntry("PADDQ",NULL,OT_P,OS_q,OT_Q,OS_q),//0xd4
	OpcodeTableEntry("PMULLW",NULL,OT_P,OS_q,OT_Q,OS_q),//0xd5
	OpcodeTableEntry("invalid",NULL),//0xd6
	OpcodeTableEntry("PMOVMSKB",NULL,OT_G,OS_d,OT_PR,OS_q),//0xd7
	OpcodeTableEntry("PSBUUSB",NULL,OT_P,OS_q,OT_Q,OS_q),//0xd8
	OpcodeTableEntry("PSUBUSW",NULL,OT_P,OS_q,OT_Q,OS_q),//0xd9
	OpcodeTableEntry("PMINUB",NULL,OT_P,OS_q,OT_Q,OS_q),//0xda
	OpcodeTableEntry("PAND",NULL,OT_P,OS_q,OT_Q,OS_q),//0xdb
	OpcodeTableEntry("PADDUSB",NULL,OT_P,OS_q,OT_Q,OS_q),//0xdc
	OpcodeTableEntry("PADDUSW",NULL,OT_P,OS_q,OT_Q,OS_q),//0xdd
	OpcodeTableEntry("PMAXUB",NULL,OT_P,OS_q,OT_Q,OS_q),//0xde
	OpcodeTableEntry("PANDN",NULL,OT_P,OS_q,OT_Q,OS_q),//0xdf
	OpcodeTableEntry("PAVGB",NULL,OT_P,OS_q,OT_Q,OS_q),//0xe0
	OpcodeTableEntry("PSRAW",NULL,OT_P,OS_q,OT_Q,OS_q),//0xe1
	OpcodeTableEntry("PSRAD",NULL,OT_P,OS_q,OT_Q,OS_q),//0xe2
	OpcodeTableEntry("PAVGW",NULL,OT_P,OS_q,OT_Q,OS_q),//0xe3
	OpcodeTableEntry("PMULHUW",NULL,OT_P,OS_q,OT_Q,OS_q),//0xe4
	OpcodeTableEntry("PMULHW",NULL,OT_P,OS_q,OT_Q,OS_q),//0xe5
	OpcodeTableEntry("invalid",NULL),//0xe6
	OpcodeTableEntry("MOVNTQ",NULL,OT_M,OS_q,OT_P,OS_q),//0xe7
	OpcodeTableEntry("PSUBSB",NULL,OT_P,OS_q,OT_Q,OS_q),//0xe8
	OpcodeTableEntry("PSUBSW",NULL,OT_P,OS_q,OT_Q,OS_q),//0xe9
	OpcodeTableEntry("PMINSW",NULL,OT_P,OS_q,OT_Q,OS_q),//0xea
	OpcodeTableEntry("POR",NULL,OT_P,OS_q,OT_Q,OS_q),//0xeb
	OpcodeTableEntry("PADDSB",NULL,OT_P,OS_q,OT_Q,OS_q),//0xec
	OpcodeTableEntry("PADDSW",NULL,OT_P,OS_q,OT_Q,OS_q),//0xed
	OpcodeTableEntry("PMAXSW",NULL,OT_P,OS_q,OT_Q,OS_q),//0xee
	OpcodeTableEntry("PXOR",NULL,OT_P,OS_q,OT_Q,OS_q),//0xef
	OpcodeTableEntry("invalid",NULL),//0xf0
	OpcodeTableEntry("PSLLW",NULL,OT_P,OS_q,OT_Q,OS_q),//0xf1
	OpcodeTableEntry("PSLLD",NULL,OT_P,OS_q,OT_Q,OS_q),//0xf2
	OpcodeTableEntry("PSLLQ",NULL,OT_P,OS_q,OT_Q,OS_q),//0xf3
	OpcodeTableEntry("PMULUDQ",NULL,OT_P,OS_q,OT_Q,OS_q),//0xf4
	OpcodeTableEntry("PMADDWD",NULL,OT_P,OS_q,OT_Q,OS_q),//0xf5
	OpcodeTableEntry("PSADBW",NULL,OT_P,OS_q,OT_Q,OS_q),//0xf6
	OpcodeTableEntry("MASKMOVQ",NULL,OT_P,OS_q,OT_PR,OS_q),//0xf7
	OpcodeTableEntry("PSUBB",NULL,OT_P,OS_q,OT_Q,OS_q),//0xf8
	OpcodeTableEntry("PSUBW",NULL,OT_P,OS_q,OT_Q,OS_q),//0xf9
	OpcodeTableEntry("PSUBD",NULL,OT_P,OS_q,OT_Q,OS_q),//0xfa
	OpcodeTableEntry("PSUBQ",NULL,OT_P,OS_q,OT_Q,OS_q),//0xfb
	OpcodeTableEntry("PADDB",NULL,OT_P,OS_q,OT_Q,OS_q),//0xfc
	OpcodeTableEntry("PADDW",NULL,OT_P,OS_q,OT_Q,OS_q),//0xfd
	OpcodeTableEntry("PADDD",NULL,OT_P,OS_q,OT_Q,OS_q),//0xfe
	OpcodeTableEntry("invalid",NULL) //0xff
};

