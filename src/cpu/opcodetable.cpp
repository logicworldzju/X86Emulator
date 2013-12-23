#include "opcodetable.h"
#include "executer/execute.h"

OpcodeTableEntry opcodeTableGroup1_80[8]=
{
    OpcodeTableEntry("ADD",(void*)executeADD,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=000
    OpcodeTableEntry("OR",(void*)executeOR,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=001
    OpcodeTableEntry("ADC",(void*)executeADC,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=010
    OpcodeTableEntry("SBB",(void*)executeSBB,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=011
    OpcodeTableEntry("AND",(void*)executeAND,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=100
    OpcodeTableEntry("SUB",(void*)executeSUB,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=101
    OpcodeTableEntry("XOR",(void*)executeXOR,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=110
    OpcodeTableEntry("CMP",(void*)executeCMP,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup1_81[8]=
{
    OpcodeTableEntry("ADD",(void*)executeADD,OT_E,OS_b,OT_I,OS_z),//ModRM.reg=000
    OpcodeTableEntry("OR",(void*)executeOR,OT_E,OS_b,OT_I,OS_z),//ModRM.reg=001
    OpcodeTableEntry("ADC",(void*)executeADC,OT_E,OS_b,OT_I,OS_z),//ModRM.reg=010
    OpcodeTableEntry("SBB",(void*)executeSBB,OT_E,OS_b,OT_I,OS_z),//ModRM.reg=011
    OpcodeTableEntry("AND",(void*)executeAND,OT_E,OS_b,OT_I,OS_z),//ModRM.reg=100
    OpcodeTableEntry("SUB",(void*)executeSUB,OT_E,OS_b,OT_I,OS_z),//ModRM.reg=101
    OpcodeTableEntry("XOR",(void*)executeXOR,OT_E,OS_b,OT_I,OS_z),//ModRM.reg=110
    OpcodeTableEntry("CMP",(void*)executeCMP,OT_E,OS_b,OT_I,OS_z),//ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup1_82[8]=
{
    //invalid in 64-bit mode.
    OpcodeTableEntry("ADD",(void*)executeADD,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=000
    OpcodeTableEntry("OR",(void*)executeOR,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=001
    OpcodeTableEntry("ADC",(void*)executeADC,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=010
    OpcodeTableEntry("SBB",(void*)executeSBB,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=011
    OpcodeTableEntry("AND",(void*)executeAND,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=100
    OpcodeTableEntry("SUB",(void*)executeSUB,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=101
    OpcodeTableEntry("XOR",(void*)executeXOR,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=110
    OpcodeTableEntry("CMP",(void*)executeCMP,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup1_83[8]=
{
    OpcodeTableEntry("ADD",(void*)executeADD,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=000
    OpcodeTableEntry("OR",(void*)executeOR,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=001
    OpcodeTableEntry("ADC",(void*)executeADC,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=010
    OpcodeTableEntry("SBB",(void*)executeSBB,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=011
    OpcodeTableEntry("AND",(void*)executeAND,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=100
    OpcodeTableEntry("SUB",(void*)executeSUB,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=101
    OpcodeTableEntry("XOR",(void*)executeXOR,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=110
    OpcodeTableEntry("CMP",(void*)executeCMP,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup1a[8]=
{
    OpcodeTableEntry("POP",(void*)executePOP,OT_E,OS_v),
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
    OpcodeTableEntry("ROL",(void*)executeROL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=000
    OpcodeTableEntry("ROR",(void*)executeROR,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=001
    OpcodeTableEntry("RCL",(void*)executeRCL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=010
    OpcodeTableEntry("RCR",(void*)executeRCR,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=011
    OpcodeTableEntry("SHL/SAL",(void*)executeSHL_SAL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=100
    OpcodeTableEntry("SHR",(void*)executeSHR,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=101
    OpcodeTableEntry("SHL/SAL",(void*)executeSHL_SAL,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=110
    OpcodeTableEntry("SAR",(void*)executeSAR,OT_E,OS_b,OT_I,OS_b) //ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup2_c1[8]=
{
    OpcodeTableEntry("ROL",(void*)executeROL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=000
    OpcodeTableEntry("ROR",(void*)executeROR,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=001
    OpcodeTableEntry("RCL",(void*)executeRCL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=010
    OpcodeTableEntry("RCR",(void*)executeRCR,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=011
    OpcodeTableEntry("SHL/SAL",(void*)executeSHL_SAL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=100
    OpcodeTableEntry("SHR",(void*)executeSHR,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=101
    OpcodeTableEntry("SHL/SAL",(void*)executeSHL_SAL,OT_E,OS_v,OT_I,OS_b),//ModRM.reg=110
    OpcodeTableEntry("SAR",(void*)executeSAR,OT_E,OS_v,OT_I,OS_b) //ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup2_d0[8]=
{
    OpcodeTableEntry("ROL",(void*)executeROL,OT_E,OS_b,OT_ONE,OS_b),//ModRM.reg=000
    OpcodeTableEntry("ROR",(void*)executeROR,OT_E,OS_b,OT_ONE,OS_b),//ModRM.reg=001
    OpcodeTableEntry("RCL",(void*)executeRCL,OT_E,OS_b,OT_ONE,OS_b),//ModRM.reg=010
    OpcodeTableEntry("RCR",(void*)executeRCR,OT_E,OS_b,OT_ONE,OS_b),//ModRM.reg=011
    OpcodeTableEntry("SHL/SAL",(void*)executeSHL_SAL,OT_E,OS_b,OT_ONE,OS_b),//ModRM.reg=100
    OpcodeTableEntry("SHR",(void*)executeSHR,OT_E,OS_b,OT_ONE,OS_b),//ModRM.reg=101
    OpcodeTableEntry("SHL/SAL",(void*)executeSHL_SAL,OT_E,OS_b,OT_ONE,OS_b),//ModRM.reg=110
    OpcodeTableEntry("SAR",(void*)executeSAR,OT_E,OS_b,OT_ONE,OS_b) //ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup2_d1[8]=
{
    OpcodeTableEntry("ROL",(void*)executeROL,OT_E,OS_v,OT_ONE,OS_b),//ModRM.reg=000
    OpcodeTableEntry("ROR",(void*)executeROR,OT_E,OS_v,OT_ONE,OS_b),//ModRM.reg=001
    OpcodeTableEntry("RCL",(void*)executeRCL,OT_E,OS_v,OT_ONE,OS_b),//ModRM.reg=010
    OpcodeTableEntry("RCR",(void*)executeRCR,OT_E,OS_v,OT_ONE,OS_b),//ModRM.reg=011
    OpcodeTableEntry("SHL/SAL",(void*)executeSHL_SAL,OT_E,OS_v,OT_ONE,OS_b),//ModRM.reg=100
    OpcodeTableEntry("SHR",(void*)executeSHR,OT_E,OS_v,OT_ONE,OS_b),//ModRM.reg=101
    OpcodeTableEntry("SHL/SAL",(void*)executeSHL_SAL,OT_E,OS_v,OT_ONE,OS_b),//ModRM.reg=110
    OpcodeTableEntry("SAR",(void*)executeSAR,OT_E,OS_v,OT_ONE,OS_b) //ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup2_d2[8]=
{
    OpcodeTableEntry("ROL",(void*)executeROL,OT_E,OS_b,OT_RCX,OS_b),//ModRM.reg=000
    OpcodeTableEntry("ROR",(void*)executeROR,OT_E,OS_b,OT_RCX,OS_b),//ModRM.reg=001
    OpcodeTableEntry("RCL",(void*)executeRCL,OT_E,OS_b,OT_RCX,OS_b),//ModRM.reg=010
    OpcodeTableEntry("RCR",(void*)executeRCR,OT_E,OS_b,OT_RCX,OS_b),//ModRM.reg=011
    OpcodeTableEntry("SHL/SAL",(void*)executeSHL_SAL,OT_E,OS_b,OT_RCX,OS_b),//ModRM.reg=100
    OpcodeTableEntry("SHR",(void*)executeSHR,OT_E,OS_b,OT_RCX,OS_b),//ModRM.reg=101
    OpcodeTableEntry("SHL/SAL",(void*)executeSHL_SAL,OT_E,OS_b,OT_RCX,OS_b),//ModRM.reg=110
    OpcodeTableEntry("SAR",(void*)executeSAR,OT_E,OS_b,OT_RCX,OS_b) //ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup2_d3[8]=
{
    OpcodeTableEntry("ROL",(void*)executeROL,OT_E,OS_v,OT_RCX,OS_b),//ModRM.reg=000
    OpcodeTableEntry("ROR",(void*)executeROR,OT_E,OS_v,OT_RCX,OS_b),//ModRM.reg=001
    OpcodeTableEntry("RCL",(void*)executeRCL,OT_E,OS_v,OT_RCX,OS_b),//ModRM.reg=010
    OpcodeTableEntry("RCR",(void*)executeRCR,OT_E,OS_v,OT_RCX,OS_b),//ModRM.reg=011
    OpcodeTableEntry("SHL/SAL",(void*)executeSHL_SAL,OT_E,OS_v,OT_RCX,OS_b),//ModRM.reg=100
    OpcodeTableEntry("SHR",(void*)executeSHR,OT_E,OS_v,OT_RCX,OS_b),//ModRM.reg=101
    OpcodeTableEntry("SHL/SAL",(void*)executeSHL_SAL,OT_E,OS_v,OT_RCX,OS_b),//ModRM.reg=110
    OpcodeTableEntry("SAR",(void*)executeSAR,OT_E,OS_v,OT_RCX,OS_b) //ModRM.reg=111
};

OpcodeTableEntry opcodeTableGroup3_f6[8]=
{
    OpcodeTableEntry("TEST",(void*)executeTEST,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=000
    OpcodeTableEntry("TEST",(void*)executeTEST,OT_E,OS_b,OT_I,OS_b),//ModRM.reg=001
    OpcodeTableEntry("NOT",(void*)executeNOT,OT_E,OS_b),//ModRM.reg=010
    OpcodeTableEntry("NEG",(void*)executeNEG,OT_E,OS_b),//ModRM.reg=011
    OpcodeTableEntry("MUL",(void*)executeMUL1,OT_E,OS_b),//ModRM.reg=100
    OpcodeTableEntry("IMUL",(void*)executeIMUL1,OT_E,OS_b),//ModRM.reg=101
    OpcodeTableEntry("DIV",(void*)executeDIV1,OT_E,OS_b),//ModRM.reg=110
    OpcodeTableEntry("IDIV",(void*)executeIDIV1,OT_E,OS_b),//ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup3_f7[8]=
{
        OpcodeTableEntry("TEST",(void*)executeTEST,OT_E,OS_v,OT_I,OS_z),//ModRM.reg=000
        OpcodeTableEntry("TEST",(void*)executeTEST,OT_E,OS_v,OT_I,OS_z),//ModRM.reg=001
    OpcodeTableEntry("NOT",(void*)executeNOT,OT_E,OS_v),//ModRM.reg=010
    OpcodeTableEntry("NEG",(void*)executeNEG,OT_E,OS_v),//ModRM.reg=011
    OpcodeTableEntry("MUL",(void*)executeMUL1,OT_E,OS_v),//ModRM.reg=100
    OpcodeTableEntry("IMUL",(void*)executeIMUL1,OT_E,OS_v),//ModRM.reg=101
    OpcodeTableEntry("DIV",(void*)executeDIV1,OT_E,OS_v),//ModRM.reg=110
    OpcodeTableEntry("IDIV",(void*)executeIDIV1,OT_E,OS_v),//ModRM.reg=111
};
OpcodeTableEntry opcodeTableGroup4_fe[8]=
{
    OpcodeTableEntry("INC",(void*)executeINC,OT_E,OS_b),
    OpcodeTableEntry("DEC",(void*)executeDEC,OT_E,OS_b),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid")
};
OpcodeTableEntry opcodeTableGroup5_ff[8]=
{
    OpcodeTableEntry("INC",(void*)executeINC,OT_E,OS_v),
    OpcodeTableEntry("DEC",(void*)executeDEC,OT_E,OS_v),
    OpcodeTableEntry("CALL near",(void*)executeCALLNEAR_Ev,OT_E,OS_v),
        OpcodeTableEntry("CALL far",(void*)executeCALLFAR_p,OT_M,OS_p),
    OpcodeTableEntry("JMP near",(void*)executeJMPNEAR_Ev,OT_E,OS_v),
        OpcodeTableEntry("JMP far",(void*)executeJMPFAR_p,OT_M,OS_p),
    OpcodeTableEntry("PUSH",(void*)executePUSH,OT_E,OS_v),
	OpcodeTableEntry("invalid")
};
OpcodeTableEntry opcodeTableGroup6_00[8]=
{
    OpcodeTableEntry("SLDT",(void*)NULL,OT_E,OS_Mw_Rv),
    OpcodeTableEntry("STR",(void*)NULL,OT_E,OS_Mw_Rv),
    OpcodeTableEntry("LLDT",(void*)NULL,OT_E,OS_w),
    OpcodeTableEntry("LTR",(void*)NULL,OT_E,OS_w),
    OpcodeTableEntry("VERR",(void*)NULL,OT_E,OS_w),
    OpcodeTableEntry("VERW",(void*)NULL,OT_E,OS_w),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid")
};
OpcodeTableEntry opcodeTableGroup7_01[8]=
{
    OpcodeTableEntry("SGDT",(void*)NULL,OT_M,OS_s),
    OpcodeTableEntry("SIDT",(void*)NULL,OT_M,OS_s),
    OpcodeTableEntry("LGDT",(void*)NULL,OT_M,OS_s),
    OpcodeTableEntry("LIDT",(void*)NULL,OT_M,OS_s),
    OpcodeTableEntry("SMSW",(void*)NULL,OT_E,OS_Mw_Rv),
	OpcodeTableEntry("invalid"),
    OpcodeTableEntry("LMSW",(void*)NULL,OT_E,OS_w),
    OpcodeTableEntry("INVLPG Mb SWAPGS",(void*)NULL)
};
OpcodeTableEntry opcodeTableGroup8_ba[8]=
{
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
    OpcodeTableEntry("BT",(void*)NULL,OT_E,OS_v,OT_I,OS_b),
    OpcodeTableEntry("BTS",(void*)NULL,OT_E,OS_v,OT_I,OS_b),
    OpcodeTableEntry("BTR",(void*)NULL,OT_E,OS_v,OT_I,OS_b),
    OpcodeTableEntry("BTC",(void*)NULL,OT_E,OS_v,OT_I,OS_b)
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
    OpcodeTableEntry("MOV",(void*)NULL,OT_E,OS_b,OT_I,OS_b),
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
    OpcodeTableEntry("MOV",(void*)NULL,OT_E,OS_v,OT_I,OS_z),
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
    OpcodeTableEntry("PSRLW",(void*)NULL,OT_PR,OS_q,OT_I,OS_b),
	OpcodeTableEntry("invalid"),
    OpcodeTableEntry("PSRAW",(void*)NULL,OT_PR,OS_q,OT_I,OS_b),
	OpcodeTableEntry("invalid"),
    OpcodeTableEntry("PSLLW",(void*)NULL,OT_PR,OS_q,OT_I,OS_b),
	OpcodeTableEntry("invalid")
};
OpcodeTableEntry opcodeTableGroup13_72[8]=
{
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
    OpcodeTableEntry("PSRLD",(void*)NULL,OT_PR,OS_q,OT_I,OS_b),
	OpcodeTableEntry("invalid"),
    OpcodeTableEntry("PSRAD",(void*)NULL,OT_PR,OS_q,OT_I,OS_b),
	OpcodeTableEntry("invalid"),
    OpcodeTableEntry("PSLLD",(void*)NULL,OT_PR,OS_q,OT_I,OS_b),
	OpcodeTableEntry("invalid")
};
OpcodeTableEntry opcodeTableGroup14_73[8]=
{
    OpcodeTableEntry("invalid",(void*)NULL),
    OpcodeTableEntry("invalid",(void*)NULL),
    OpcodeTableEntry("PSRLQ",(void*)NULL,OT_PR,OS_q,OT_I,OS_b),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("invalid"),
    OpcodeTableEntry("PSLLQ",(void*)NULL,OT_PR,OS_q,OT_I,OS_b),
	OpcodeTableEntry("invalid")
};
OpcodeTableEntry opcodeTableGroup15_ae[8]=
{
    OpcodeTableEntry("FXSAVE",(void*)NULL,OT_M,OS_NOT_EXISTS),
    OpcodeTableEntry("FXSTOR",(void*)NULL,OT_M,OS_NOT_EXISTS),
    OpcodeTableEntry("LDMXCSR",(void*)NULL,OT_M,OS_d),
    OpcodeTableEntry("STMXCSR",(void*)NULL,OT_M,OS_d),
	OpcodeTableEntry("invalid"),
	OpcodeTableEntry("LFENCE"),
	OpcodeTableEntry("MFENCE"),
    OpcodeTableEntry("SFENCE/CLFLUSH",(void*)NULL,OT_M,OS_b)
};
OpcodeTableEntry opcodeTableOneByte[256]=
{
    OpcodeTableEntry("ADD",(void*)executeADD,OT_E,OS_b,OT_G,OS_b),//0x00
    OpcodeTableEntry("ADD",(void*)executeADD,OT_E,OS_v,OT_G,OS_v),//0x01
    OpcodeTableEntry("ADD",(void*)executeADD,OT_G,OS_b,OT_E,OS_b),//0x02
    OpcodeTableEntry("ADD",(void*)executeADD,OT_G,OS_v,OT_E,OS_v),//0x03
    OpcodeTableEntry("ADD",(void*)executeADD,OT_RAX,OS_b,OT_I,OS_b),//0x04
    OpcodeTableEntry("ADD",(void*)executeADD,OT_RAX,OS_v,OT_I,OS_z),//0x05
    OpcodeTableEntry("PUSH",(void*)executePUSH,OT_ES,OS_w),//0x06
    OpcodeTableEntry("POP",(void*)executePOP,OT_ES,OS_w),//0x07
    OpcodeTableEntry("OR",(void*)executeOR,OT_E,OS_b,OT_G,OS_b),//0x08
    OpcodeTableEntry("OR",(void*)executeOR,OT_E,OS_v,OT_G,OS_v),//0x09
    OpcodeTableEntry("OR",(void*)executeOR,OT_G,OS_b,OT_E,OS_b),//0x0a
    OpcodeTableEntry("OR",(void*)executeOR,OT_G,OS_v,OT_E,OS_v),//0x0b
    OpcodeTableEntry("OR",(void*)executeOR,OT_RAX,OS_b,OT_I,OS_b),//0x0c
    OpcodeTableEntry("OR",(void*)executeOR,OT_RAX,OS_v,OT_I,OS_z),//0x0d
    OpcodeTableEntry("PUSH",(void*)executePUSH,OT_CS,OS_w),//0x0e
    OpcodeTableEntry("escape prefix",(void*)NULL),//0x0f
    OpcodeTableEntry("ADC",(void*)executeADC,OT_E,OS_b,OT_G,OS_b),//0x10
    OpcodeTableEntry("ADC",(void*)executeADC,OT_E,OS_v,OT_G,OS_v),//0x11
    OpcodeTableEntry("ADC",(void*)executeADC,OT_G,OS_b,OT_E,OS_b),//0x12
    OpcodeTableEntry("ADC",(void*)executeADC,OT_G,OS_v,OT_E,OS_v),//0x13
    OpcodeTableEntry("ADC",(void*)executeADC,OT_RAX,OS_b,OT_I,OS_b),//0x14
    OpcodeTableEntry("ADC",(void*)executeADC,OT_RAX,OS_v,OT_I,OS_z),//0x15
    OpcodeTableEntry("PUSH",(void*)executePUSH,OT_SS,OS_w),//0x16
    OpcodeTableEntry("POP",(void*)executePOP,OT_SS,OS_w),//0x17
    OpcodeTableEntry("SBB",(void*)executeSBB,OT_E,OS_b,OT_G,OS_b),//0x18
    OpcodeTableEntry("SBB",(void*)executeSBB,OT_E,OS_v,OT_G,OS_v),//0x19
    OpcodeTableEntry("SBB",(void*)executeSBB,OT_G,OS_b,OT_E,OS_b),//0x1a
    OpcodeTableEntry("SBB",(void*)executeSBB,OT_G,OS_v,OT_E,OS_v),//0x1b
    OpcodeTableEntry("SBB",(void*)executeSBB,OT_RAX,OS_b,OT_I,OS_b),//0x1c
    OpcodeTableEntry("SBB",(void*)executeSBB,OT_RAX,OS_v,OT_I,OS_z),//0x1d
    OpcodeTableEntry("PUSH",(void*)executePUSH,OT_DS,OS_w),//0x1e
    OpcodeTableEntry("POP",(void*)executePOP,OT_DS,OS_w),//0x1f
    OpcodeTableEntry("AND",(void*)executeAND,OT_E,OS_b,OT_G,OS_b),//0x20
    OpcodeTableEntry("AND",(void*)executeAND,OT_E,OS_v,OT_G,OS_v),//0x21
    OpcodeTableEntry("AND",(void*)executeAND,OT_G,OS_b,OT_E,OS_b),//0x22
    OpcodeTableEntry("AND",(void*)executeAND,OT_G,OS_v,OT_E,OS_v),//0x23
    OpcodeTableEntry("AND",(void*)executeAND,OT_RAX,OS_b,OT_I,OS_b),//0x24
    OpcodeTableEntry("AND",(void*)executeAND,OT_RAX,OS_v,OT_I,OS_z),//0x25
    OpcodeTableEntry("seg ES",(void*)NULL),//0x26
    OpcodeTableEntry("DAA",(void*)executeDAA),//0x27
    OpcodeTableEntry("SUB",(void*)executeSUB,OT_E,OS_b,OT_G,OS_b),//0x28
    OpcodeTableEntry("SUB",(void*)executeSUB,OT_E,OS_v,OT_G,OS_v),//0x29
    OpcodeTableEntry("SUB",(void*)executeSUB,OT_G,OS_b,OT_E,OS_b),//0x2a
    OpcodeTableEntry("SUB",(void*)executeSUB,OT_G,OS_v,OT_E,OS_v),//0x2b
    OpcodeTableEntry("SUB",(void*)executeSUB,OT_RAX,OS_b,OT_I,OS_b),//0x2c
    OpcodeTableEntry("SUB",(void*)executeSUB,OT_RAX,OS_v,OT_I,OS_z),//0x2d
    OpcodeTableEntry("seg CS",(void*)NULL),//0x2e
    OpcodeTableEntry("DAS",(void*)executeDAS),//0x2f
    OpcodeTableEntry("XOR",(void*)executeXOR,OT_E,OS_b,OT_G,OS_b),//0x30
    OpcodeTableEntry("XOR",(void*)executeXOR,OT_E,OS_v,OT_G,OS_v),//0x31
    OpcodeTableEntry("XOR",(void*)executeXOR,OT_G,OS_b,OT_E,OS_b),//0x32
    OpcodeTableEntry("XOR",(void*)executeXOR,OT_G,OS_v,OT_E,OS_v),//0x33
    OpcodeTableEntry("XOR",(void*)executeXOR,OT_RAX,OS_b,OT_I,OS_b),//0x34
    OpcodeTableEntry("XOR",(void*)executeXOR,OT_RAX,OS_v,OT_I,OS_z),//0x35
    OpcodeTableEntry("seg SS",(void*)NULL),//0x36
    OpcodeTableEntry("AAA",(void*)executeAAA),//0x37
    OpcodeTableEntry("CMP",(void*)executeCMP,OT_E,OS_b,OT_G,OS_b),//0x38
    OpcodeTableEntry("CMP",(void*)executeCMP,OT_E,OS_v,OT_G,OS_v),//0x39
    OpcodeTableEntry("CMP",(void*)executeCMP,OT_G,OS_b,OT_E,OS_b),//0x3a
    OpcodeTableEntry("CMP",(void*)executeCMP,OT_G,OS_v,OT_E,OS_v),//0x3b
    OpcodeTableEntry("CMP",(void*)executeCMP,OT_RAX,OS_b,OT_I,OS_b),//0x3c
    OpcodeTableEntry("CMP",(void*)executeCMP,OT_RAX,OS_v,OT_I,OS_z),//0x3d
    OpcodeTableEntry("seg DS",(void*)NULL),//0x3e
    OpcodeTableEntry("AAS",(void*)executeAAS),//0x3f
    OpcodeTableEntry("INC",(void*)executeINC,OT_RAX,OS_z),//0x40
    OpcodeTableEntry("INC",(void*)executeINC,OT_RCX,OS_z),//0x41
    OpcodeTableEntry("INC",(void*)executeINC,OT_RDX,OS_z),//0x42
    OpcodeTableEntry("INC",(void*)executeINC,OT_RBX,OS_z),//0x43
    OpcodeTableEntry("INC",(void*)executeINC,OT_RSP,OS_z),//0x44
    OpcodeTableEntry("INC",(void*)executeINC,OT_RBP,OS_z),//0x45
    OpcodeTableEntry("INC",(void*)executeINC,OT_RSI,OS_z),//0x46
    OpcodeTableEntry("INC",(void*)executeINC,OT_RDI,OS_z),//0x47
    OpcodeTableEntry("DEC",(void*)executeDEC,OT_RAX,OS_z),//0x48
    OpcodeTableEntry("DEC",(void*)executeDEC,OT_RCX,OS_z),//0x49
    OpcodeTableEntry("DEC",(void*)executeDEC,OT_RDX,OS_z),//0x4a
    OpcodeTableEntry("DEC",(void*)executeDEC,OT_RBX,OS_z),//0x4b
    OpcodeTableEntry("DEC",(void*)executeDEC,OT_RSP,OS_z),//0x4c
    OpcodeTableEntry("DEC",(void*)executeDEC,OT_RBP,OS_z),//0x4d
    OpcodeTableEntry("DEC",(void*)executeDEC,OT_RSI,OS_z),//0x4e
    OpcodeTableEntry("DEC",(void*)executeDEC,OT_RDI,OS_z),//0x4f
    OpcodeTableEntry("PUSH",(void*)executePUSH,OT_RAX,OS_v),//0x50
    OpcodeTableEntry("PUSH",(void*)executePUSH,OT_RCX,OS_v),//0x51
    OpcodeTableEntry("PUSH",(void*)executePUSH,OT_RDX,OS_v),//0x52
    OpcodeTableEntry("PUSH",(void*)executePUSH,OT_RBX,OS_v),//0x53
    OpcodeTableEntry("PUSH",(void*)executePUSH,OT_RSP,OS_v),//0x54
    OpcodeTableEntry("PUSH",(void*)executePUSH,OT_RBP,OS_v),//0x55
    OpcodeTableEntry("PUSH",(void*)executePUSH,OT_RSI,OS_v),//0x56
    OpcodeTableEntry("PUSH",(void*)executePUSH,OT_RDI,OS_v),//0x57
    OpcodeTableEntry("POP",(void*)executePOP,OT_RAX,OS_v),//0x58
    OpcodeTableEntry("POP",(void*)executePOP,OT_RCX,OS_v),//0x59
    OpcodeTableEntry("POP",(void*)executePOP,OT_RDX,OS_v),//0x5a
    OpcodeTableEntry("POP",(void*)executePOP,OT_RBX,OS_v),//0x5b
    OpcodeTableEntry("POP",(void*)executePOP,OT_RSP,OS_v),//0x5c
    OpcodeTableEntry("POP",(void*)executePOP,OT_RBP,OS_v),//0x5d
    OpcodeTableEntry("POP",(void*)executePOP,OT_RSI,OS_v),//0x5e
    OpcodeTableEntry("POP",(void*)executePOP,OT_RDI,OS_v),//0x5f
    OpcodeTableEntry("PUSHA/D",(void*)executePUSHAD),//0x60
    OpcodeTableEntry("POPA/D",(void*)executePOPAD),//0x61
    OpcodeTableEntry("BOUND",(void*)executeBOUND,OT_G,OS_v,OT_M,OS_a),//0x62
    OpcodeTableEntry("ARPL",(void*)executeARPL,OT_E,OS_w,OT_G,OS_w),//0x63
    OpcodeTableEntry("seg FS",(void*)NULL),//0x64
    OpcodeTableEntry("seg DS",(void*)NULL),//0x65
    OpcodeTableEntry("operand size",(void*)NULL),//0x66
    OpcodeTableEntry("address size",(void*)NULL),//0x67
    OpcodeTableEntry("PUSH",(void*)executePUSH,OT_I,OS_z),//0x68
    OpcodeTableEntry("IMUL",(void*)executeIMUL3,OT_G,OS_v,OT_E,OS_v,OT_I,OS_z),//0x69
    OpcodeTableEntry("PUSH",(void*)executePUSH,OT_I,OS_b),//0x6a
    OpcodeTableEntry("IMUL",(void*)executeIMUL3,OT_G,OS_v,OT_E,OS_v,OT_I,OS_b),//0x6b
    OpcodeTableEntry("INSB",(void*)executeINSB,OT_Y,OS_b,OT_RDX,OS_w),//0x6c
    OpcodeTableEntry("INSW/D",(void*)executeINSWD,OT_Y,OS_z,OT_RDX,OS_w),//0x6d
    OpcodeTableEntry("OUTSB",(void*)executeOUTSB,OT_RDX,OS_w,OT_X,OS_b),//0x6e
    OpcodeTableEntry("OUTSW/D",(void*)executeOUTSWD,OT_RDX,OS_w,OT_X,OS_z),//0x6f
    OpcodeTableEntry("JO",(void*)executeJO,OT_J,OS_b),//0x70
    OpcodeTableEntry("JNO",(void*)executeJNO,OT_J,OS_b),//0x71
    OpcodeTableEntry("JB",(void*)executeJB,OT_J,OS_b),//0x72
    OpcodeTableEntry("JNB",(void*)executeJNB,OT_J,OS_b),//0x73
    OpcodeTableEntry("JZ",(void*)executeJZ,OT_J,OS_b),//0x74
    OpcodeTableEntry("JNZ",(void*)executeJNZ,OT_J,OS_b),//0x75
    OpcodeTableEntry("JBE",(void*)executeJBE,OT_J,OS_b),//0x76
    OpcodeTableEntry("JNBE",(void*)executeJNBE,OT_J,OS_b),//0x77
    OpcodeTableEntry("JS",(void*)executeJS,OT_J,OS_b),//0x78
    OpcodeTableEntry("JNS",(void*)executeJNS,OT_J,OS_b),//0x79
    OpcodeTableEntry("JP",(void*)executeJP,OT_J,OS_b),//0x7a
    OpcodeTableEntry("JNP",(void*)executeJNP,OT_J,OS_b),//0x7b
    OpcodeTableEntry("JL",(void*)executeJL,OT_J,OS_b),//0x7c
    OpcodeTableEntry("JNL",(void*)executeJNL,OT_J,OS_b),//0x7d
    OpcodeTableEntry("JLE",(void*)executeJLE,OT_J,OS_b),//0x7e
    OpcodeTableEntry("JNLE",(void*)executeJNLE,OT_J,OS_b),//0x7f
    OpcodeTableEntry("Group 1",opcodeTableGroup1_80),//0x80
    OpcodeTableEntry("Group 1",opcodeTableGroup1_81),//0x81
    OpcodeTableEntry("Group 1",opcodeTableGroup1_82),//0x82
    OpcodeTableEntry("Group 1",opcodeTableGroup1_83),//0x83
    OpcodeTableEntry("TEST",(void*)executeTEST,OT_E,OS_b,OT_G,OS_b),//0x84
    OpcodeTableEntry("TEST",(void*)executeTEST,OT_E,OS_v,OT_G,OS_v),//0x85
    OpcodeTableEntry("XCHG",(void*)executeXCHG,OT_E,OS_b,OT_G,OS_b),//0x86
    OpcodeTableEntry("XCHG",(void*)executeXCHG,OT_E,OS_v,OT_G,OS_v),//0x87
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_E,OS_b,OT_G,OS_b),//0x88
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_E,OS_v,OT_G,OS_v),//0x89
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_G,OS_b,OT_E,OS_b),//0x8a
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_G,OS_v,OT_E,OS_v),//0x8b
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_E,OS_Mw_Rv,OT_S,OS_w),//0x8c
    OpcodeTableEntry("LEA",(void*)executeLEA,OT_G,OS_v,OT_M,OS_NOT_EXISTS),//0x8d
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_S,OS_w,OT_E,OS_w),//0x8e
    OpcodeTableEntry("Group 1a",opcodeTableGroup1a),//0x8f
    OpcodeTableEntry("NOP/PAUSE",(void*)executeXCHG,OT_RAX,OS_v,OT_RAX,OS_v),//0x90 //XCHG r8,rAX in 64-bit mode.
    OpcodeTableEntry("XCHG",(void*)executeXCHG,OT_RCX,OS_v,OT_RAX,OS_v),//0x91
    OpcodeTableEntry("XCHG",(void*)executeXCHG,OT_RDX,OS_v,OT_RAX,OS_v),//0x92
    OpcodeTableEntry("XCHG",(void*)executeXCHG,OT_RBX,OS_v,OT_RAX,OS_v),//0x93
    OpcodeTableEntry("XCHG",(void*)executeXCHG,OT_RSP,OS_v,OT_RAX,OS_v),//0x94
    OpcodeTableEntry("XCHG",(void*)executeXCHG,OT_RBP,OS_v,OT_RAX,OS_v),//0x95
    OpcodeTableEntry("XCHG",(void*)executeXCHG,OT_RSI,OS_v,OT_RAX,OS_v),//0x96
    OpcodeTableEntry("XCHG",(void*)executeXCHG,OT_RDI,OS_v,OT_RAX,OS_v),//0x97
    OpcodeTableEntry("CBW/CWDE/CDQE",(void*)executeCBW_CWDE_CDQE),//0x98
    OpcodeTableEntry("CWD/CDQ/CQO",(void*)executeCWD_CDQ_CQO),//0x99
    OpcodeTableEntry("CALL far",(void*)executeCALLFAR_p,OT_A,OS_p),//0x9a
    OpcodeTableEntry("WAIT/FWAIT",(void*)executeWAIT_FWAIT),//0x9b
    OpcodeTableEntry("PUSHF/D/Q",(void*)executePUSHFDQ,OT_F,OS_v),//0x9c
    OpcodeTableEntry("POPF/D/Q",(void*)executePOPFDQ,OT_F,OS_v),//0x9d
    OpcodeTableEntry("SAHF",(void*)executeSAHF),//0x9e
    OpcodeTableEntry("LAHF",(void*)executeLAHF),//0x9f
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_RAX,OS_b,OT_O,OS_b),//0xa0
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_RAX,OS_v,OT_O,OS_v),//0xa1
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_O,OS_b,OT_RAX,OS_b),//0xa2
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_O,OS_v,OT_RAX,OS_v),//0xa3
    OpcodeTableEntry("MOVSB",(void*)executeMOVS,OT_Y,OS_b,OT_X,OS_b),//0xa4
    OpcodeTableEntry("MOVSW/D/Q",(void*)executeMOVS,OT_Y,OS_v,OT_X,OS_v),//0xa5
    OpcodeTableEntry("CMPSB",(void*)executeCMPS,OT_X,OS_b,OT_Y,OS_b),//0xa6
    OpcodeTableEntry("CMPSW/D/Q",(void*)executeCMPS,OT_X,OS_v,OT_Y,OS_v),//0xa7
    OpcodeTableEntry("TEST",(void*)executeTEST,OT_RAX,OS_b,OT_I,OS_b),//0xa8
    OpcodeTableEntry("TEST",(void*)executeTEST,OT_RAX,OS_z,OT_I,OS_z),//0xa9
    OpcodeTableEntry("STOSB",(void*)executeSTOS,OT_Y,OS_v,OT_RAX,OS_b),//0xaa
    OpcodeTableEntry("STOSW/D/Q",(void*)executeSTOS,OT_Y,OS_v,OT_RAX,OS_v),//0xab
    OpcodeTableEntry("LODSB",(void*)executeLODS,OT_RAX,OS_b,OT_X,OS_b),//0xac
    OpcodeTableEntry("LODSW/D/Q",(void*)executeLODS,OT_RAX,OS_v,OT_X,OS_v),//0xad
    OpcodeTableEntry("SCASB",(void*)executeSCAS,OT_RAX,OS_b,OT_Y,OS_b),//0xae
    OpcodeTableEntry("SCASW/D/Q",(void*)executeSCAS,OT_RAX,OS_v,OT_Y,OS_v),//0xaf
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_RAX,OS_b,OT_I,OS_b),//0xb0
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_RCX,OS_b,OT_I,OS_b),//0xb1
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_RDX,OS_b,OT_I,OS_b),//0xb2
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_RBX,OS_b,OT_I,OS_b),//0xb3
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_RSP,OS_b,OT_I,OS_b),//0xb4 //OT_RSP=AH in 16bit
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_RBP,OS_b,OT_I,OS_b),//0xb5 //OT_RBP=CH in 16bit
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_RSI,OS_b,OT_I,OS_b),//0xb6 //OT_RSI=DH in 16bit
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_RDI,OS_b,OT_I,OS_b),//0xb7 //OT_RDI=BH in 16bit
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_RAX,OS_v,OT_I,OS_v),//0xb8
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_RCX,OS_v,OT_I,OS_v),//0xb9
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_RDX,OS_v,OT_I,OS_v),//0xba
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_RBX,OS_v,OT_I,OS_v),//0xbb
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_RSP,OS_v,OT_I,OS_v),//0xbc
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_RBP,OS_v,OT_I,OS_v),//0xbd
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_RSI,OS_v,OT_I,OS_v),//0xbe
    OpcodeTableEntry("MOV",(void*)executeMOVE,OT_RDI,OS_v,OT_I,OS_v),//0xbf
	OpcodeTableEntry("Group 2",opcodeTableGroup2_c0),//0xc0
	OpcodeTableEntry("Group 2",opcodeTableGroup2_c1),//0xc1
    OpcodeTableEntry("RET near",(void*)executeRETNEAR,OT_I,OS_w),//0xc2
    OpcodeTableEntry("RET near",(void*)executeRETNEAR,OT_ZERO,OS_w),//0xc3
    OpcodeTableEntry("LES",(void*)executeLES,OT_G,OS_z,OT_M,OS_p),//0xc4
    OpcodeTableEntry("LDS",(void*)executeLDS,OT_G,OS_z,OT_M,OS_p),//0xc5
	OpcodeTableEntry("Group 11",opcodeTableGroup11_c6),//0xc6
	OpcodeTableEntry("Group 11",opcodeTableGroup11_c7),//0xc7
    OpcodeTableEntry("ENTER",(void*)executeENTER,OT_I,OS_w,OT_I,OS_b),//0xc8
    OpcodeTableEntry("LEAVE",(void*)executeLEAVE),//0xc9
    OpcodeTableEntry("RET far",(void*)executeRETFAR,OT_I,OS_w),//0xca
    OpcodeTableEntry("RET far",(void*)executeRETFAR,OT_ZERO,OS_w),//0xcb
    OpcodeTableEntry("INT3",(void*)executeINT3),//0xcc
    OpcodeTableEntry("INT",(void*)executeINT,OT_I,OS_b),//0xcd
    OpcodeTableEntry("INTO",(void*)executeINTO),//0xce
    OpcodeTableEntry("IRET/IRETD/IRETQ",(void*)executeIRET_IRETD_IRETQ),//0xcf
	OpcodeTableEntry("Group 2",opcodeTableGroup2_d0),//0xd0
	OpcodeTableEntry("Group 2",opcodeTableGroup2_d1),//0xd1
	OpcodeTableEntry("Group 2",opcodeTableGroup2_d2),//0xd2
	OpcodeTableEntry("Group 2",opcodeTableGroup2_d3),//0xd3
        OpcodeTableEntry("AAM",(void*)executeAAM,OT_I,OS_b),//0xd4
        OpcodeTableEntry("AAD",(void*)executeAAD,OT_I,OS_b),//0xd5
    OpcodeTableEntry("SALC",(void*)executeSALC),//0xd6
    OpcodeTableEntry("XLAT",(void*)executeXLAT),//0xd7
    OpcodeTableEntry("x87",(void*)NULL),//0xd8
    OpcodeTableEntry("x87",(void*)NULL),//0xd9
    OpcodeTableEntry("x87",(void*)NULL),//0xda
    OpcodeTableEntry("x87",(void*)NULL),//0xdb
    OpcodeTableEntry("x87",(void*)NULL),//0xdc
    OpcodeTableEntry("x87",(void*)NULL),//0xdd
    OpcodeTableEntry("x87",(void*)NULL),//0xde
    OpcodeTableEntry("x87",(void*)NULL),//0xdf
    OpcodeTableEntry("LOOPNE/NZ",(void*)executeLOOPNZ,OT_J,OS_b),//0xe0
    OpcodeTableEntry("LOOPE/Z",(void*)executeLOOPZ,OT_J,OS_b),//0xe1
    OpcodeTableEntry("LOOP",(void*)executeLOOP,OT_J,OS_b),//0xe2
    OpcodeTableEntry("JrCXZ",(void*)executeJRCXZ,OT_J,OS_b),//0xe3
    OpcodeTableEntry("IN",(void*)executeIN,OT_RAX,OS_b,OT_I,OS_b),//0xe4
    OpcodeTableEntry("IN",(void*)executeIN,OT_RAX,OS_z,OT_I,OS_b),//0xe5
    OpcodeTableEntry("OUT",(void*)executeOUT,OT_I,OS_b,OT_RAX,OS_b),//0xe6
    OpcodeTableEntry("OUT",(void*)executeOUT,OT_I,OS_b,OT_RAX,OS_z),//0xe7
    OpcodeTableEntry("CALL near",(void*)executeCALLNEAR_Jz,OT_J,OS_z),//0xe8
    OpcodeTableEntry("JMP near",(void*)executeJMPNEAR_J,OT_J,OS_z),//0xe9
    OpcodeTableEntry("JMP far",(void*)executeJMPFAR_p,OT_A,OS_p),//0xea
    OpcodeTableEntry("JMP near",(void*)executeJMPNEAR_J,OT_J,OS_b),//0xeb
    OpcodeTableEntry("IN",(void*)executeIN,OT_RAX,OS_b,OT_RDX,OS_w),//0xec
    OpcodeTableEntry("IN",(void*)executeIN,OT_RAX,OS_z,OT_RDX,OS_w),//0xed
    OpcodeTableEntry("OUT",(void*)executeOUT,OT_RDX,OS_w,OT_RAX,OS_b),//0xee
    OpcodeTableEntry("OUT",(void*)executeOUT,OT_RDX,OS_w,OT_RAX,OS_z),//0xef
    OpcodeTableEntry("lock",(void*)NULL),//0xf0
    OpcodeTableEntry("INT1/ICE Bkpt",(void*)executeINT1),//0xf1
    OpcodeTableEntry("repne",(void*)NULL),//0xf2
    OpcodeTableEntry("rep/repe",(void*)NULL),//0xf3
    OpcodeTableEntry("HLT",(void*)executeHLT),//0xf4
    OpcodeTableEntry("CMC",(void*)executeCMC),//0xf5
	OpcodeTableEntry("Group 3",opcodeTableGroup3_f6),//0xf6
	OpcodeTableEntry("Group 3",opcodeTableGroup3_f7),//0xf7
    OpcodeTableEntry("CLC",(void*)executeCLC),//0xf8
    OpcodeTableEntry("STC",(void*)executeSTC),//0xf9
    OpcodeTableEntry("CLI",(void*)executeCLI),//0xfa
    OpcodeTableEntry("STI",(void*)executeSTI),//0xfb
    OpcodeTableEntry("CLD",(void*)executeCLD),//0xfc
    OpcodeTableEntry("STD",(void*)executeSTD),//0xfd
	OpcodeTableEntry("Group 4",opcodeTableGroup4_fe),//0xfe
	OpcodeTableEntry("Group 5",opcodeTableGroup5_ff)//0xff
};
OpcodeTableEntry opcodeTableTwoByte_0x0F[256]=
{
	OpcodeTableEntry("Group 6",opcodeTableGroup6_00),//0x00
	OpcodeTableEntry("Group 7",opcodeTableGroup7_01),//0x01
    OpcodeTableEntry("LAR",(void*)NULL,OT_G,OS_v,OT_E,OS_w),//0x02
    OpcodeTableEntry("LSL",(void*)NULL,OT_G,OS_v,OT_E,OS_w),//0x03
    OpcodeTableEntry("invalid",(void*)NULL),//0x04
    OpcodeTableEntry("SYSCALL",(void*)NULL),//0x05
    OpcodeTableEntry("CLTS",(void*)NULL),//0x06
    OpcodeTableEntry("SYSRET",(void*)NULL),//0x07
    OpcodeTableEntry("INVD",(void*)NULL),//0x08
    OpcodeTableEntry("WBINVD",(void*)NULL),//0x09
    OpcodeTableEntry("invalid",(void*)NULL),//0x0a
    OpcodeTableEntry("UD2",(void*)NULL),//0x0b
    OpcodeTableEntry("invalid",(void*)NULL),//0x0c
    OpcodeTableEntry("Group P",(void*)NULL),//0x0d
    OpcodeTableEntry("FEMMS",(void*)NULL),//0x0e
    OpcodeTableEntry("3DNow",(void*)NULL),//0x0f
    OpcodeTableEntry("MOVUPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_ps),//0x10
    OpcodeTableEntry("MOVUPS",(void*)NULL,OT_W,OS_ps,OT_V,OS_ps),//0x11
    OpcodeTableEntry("MOVLPS/MOVHLPS",(void*)NULL),//0x12 //not full
    OpcodeTableEntry("MOVLPS",(void*)NULL,OT_M,OS_q,OT_V,OS_ps),//0x13
    OpcodeTableEntry("UNPCKLPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_q),//0x14
    OpcodeTableEntry("UNPCKLPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_q),//0x15
    OpcodeTableEntry("MOVHPS/MOVLHPS",(void*)NULL),//0x16 //not full
    OpcodeTableEntry("MOVHPS",(void*)NULL,OT_M,OS_q,OT_V,OS_ps),//0x17
    OpcodeTableEntry("Group 16",(void*)NULL),//0x18
    OpcodeTableEntry("NOP",(void*)NULL),//0x19
    OpcodeTableEntry("NOP",(void*)NULL),//0x1a
    OpcodeTableEntry("NOP",(void*)NULL),//0x1b
    OpcodeTableEntry("NOP",(void*)NULL),//0x1c
    OpcodeTableEntry("NOP",(void*)NULL),//0x1d
    OpcodeTableEntry("NOP",(void*)NULL),//0x1e
    OpcodeTableEntry("NOP",(void*)NULL),//0x1f
    OpcodeTableEntry("MOV",(void*)NULL,OT_R,OS_d_q,OT_C,OS_d_q),//0x20
    OpcodeTableEntry("MOV",(void*)NULL,OT_R,OS_d_q,OT_D,OS_d_q),//0x21
    OpcodeTableEntry("MOV",(void*)NULL,OT_C,OS_d_q,OT_R,OS_d_q),//0x22
    OpcodeTableEntry("MOV",(void*)NULL,OT_D,OS_d_q,OT_R,OS_d_q),//0x23
    OpcodeTableEntry("invalid",(void*)NULL),//0x24
    OpcodeTableEntry("invalid",(void*)NULL),//0x25
    OpcodeTableEntry("invalid",(void*)NULL),//0x26
    OpcodeTableEntry("invalid",(void*)NULL),//0x27
    OpcodeTableEntry("MOVAPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_ps),//0x28
    OpcodeTableEntry("MOVAPS",(void*)NULL,OT_W,OS_ps,OT_V,OS_ps),//0x29
    OpcodeTableEntry("CVTPI2PS",(void*)NULL,OT_V,OS_ps,OT_Q,OS_q),//0x2a
    OpcodeTableEntry("MOVNTPS",(void*)NULL,OT_M,OS_dq,OT_V,OS_ps),//0x2b
    OpcodeTableEntry("CVTTPS2PI",(void*)NULL,OT_P,OS_q,OT_W,OS_ps),//0x2c
    OpcodeTableEntry("CVTPS2PI",(void*)NULL,OT_P,OS_q,OT_W,OS_ps),//0x2d
    OpcodeTableEntry("UCOMISS",(void*)NULL,OT_V,OS_ss,OT_W,OS_ss),//0x2e
    OpcodeTableEntry("COMISS",(void*)NULL,OT_V,OS_ps,OT_W,OS_ps),//0x2f
    OpcodeTableEntry("WRMSR",(void*)NULL),//0x30
    OpcodeTableEntry("RDTSC",(void*)NULL),//0x31
    OpcodeTableEntry("RDMSR",(void*)NULL),//0x32
    OpcodeTableEntry("RDPMC",(void*)NULL),//0x33
    OpcodeTableEntry("SYSENTER",(void*)NULL),//0x34
    OpcodeTableEntry("SYSEXIT",(void*)NULL),//0x35
    OpcodeTableEntry("invalid",(void*)NULL),//0x36
    OpcodeTableEntry("invalid",(void*)NULL),//0x37
    OpcodeTableEntry("invalid",(void*)NULL),//0x38
    OpcodeTableEntry("invalid",(void*)NULL),//0x39
    OpcodeTableEntry("invalid",(void*)NULL),//0x3a
    OpcodeTableEntry("invalid",(void*)NULL),//0x3b
    OpcodeTableEntry("invalid",(void*)NULL),//0x3c
    OpcodeTableEntry("invalid",(void*)NULL),//0x3d
    OpcodeTableEntry("invalid",(void*)NULL),//0x3e
    OpcodeTableEntry("invalid",(void*)NULL),//0x3f
    OpcodeTableEntry("CMOVO",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0x40
    OpcodeTableEntry("CMOVNO",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0x41
    OpcodeTableEntry("CMOVB",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0x42
    OpcodeTableEntry("CMOVNB",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0x43
    OpcodeTableEntry("CMOVZ",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0x44
    OpcodeTableEntry("CMOVNZ",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0x45
    OpcodeTableEntry("CMOVBE",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0x46
    OpcodeTableEntry("CMOVNBE",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0x47
    OpcodeTableEntry("CMOVS",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0x48
    OpcodeTableEntry("CMOVNS",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0x49
    OpcodeTableEntry("CMOVP",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0x4a
    OpcodeTableEntry("CMOVNP",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0x4b
    OpcodeTableEntry("CMOVL",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0x4c
    OpcodeTableEntry("CMOVNL",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0x4d
    OpcodeTableEntry("CMOVLE",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0x4e
    OpcodeTableEntry("CMOVNLE",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0x4f
    OpcodeTableEntry("MOVMSKPS",(void*)NULL,OT_G,OS_d,OT_VR,OS_ps),//0x50
    OpcodeTableEntry("SQRTPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_ps),//0x51
    OpcodeTableEntry("RSQRTPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_ps),//0x52
    OpcodeTableEntry("RCPPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_ps),//0x53
    OpcodeTableEntry("ANDPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_ps),//0x54
    OpcodeTableEntry("ANDNPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_ps),//0x55
    OpcodeTableEntry("ORPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_ps),//0x56
    OpcodeTableEntry("XORPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_ps),//0x57
    OpcodeTableEntry("ADDPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_ps),//0x58
    OpcodeTableEntry("MULPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_ps),//0x59
    OpcodeTableEntry("CVTPS2PD",(void*)NULL,OT_V,OS_pd,OT_W,OS_ps),//0x5a
    OpcodeTableEntry("CVTDQ2PS",(void*)NULL,OT_V,OS_ps,OT_W,OS_dq),//0x5b
    OpcodeTableEntry("SUBPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_ps),//0x5c
    OpcodeTableEntry("MINPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_ps),//0x5d
    OpcodeTableEntry("DIVPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_ps),//0x5e
    OpcodeTableEntry("MAXPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_ps),//0x5f
    OpcodeTableEntry("PUNPCKLBW",(void*)NULL,OT_P,OS_q,OT_Q,OS_d),//0x60
    OpcodeTableEntry("PUNPCKLWD",(void*)NULL,OT_P,OS_q,OT_Q,OS_d),//0x61
    OpcodeTableEntry("PUNPCKLDQ",(void*)NULL,OT_P,OS_q,OT_Q,OS_d),//0x62
    OpcodeTableEntry("PACKSSWB",(void*)NULL,OT_P,OS_q,OT_Q,OS_d),//0x63
    OpcodeTableEntry("PCMPGTB",(void*)NULL,OT_P,OS_q,OT_Q,OS_d),//0x64
    OpcodeTableEntry("PCMPGTW",(void*)NULL,OT_P,OS_q,OT_Q,OS_d),//0x65
    OpcodeTableEntry("PCMPGTD",(void*)NULL,OT_P,OS_q,OT_Q,OS_d),//0x66
    OpcodeTableEntry("PACKUSWB",(void*)NULL,OT_P,OS_q,OT_Q,OS_d),//0x67
    OpcodeTableEntry("PUNPCKHBW",(void*)NULL,OT_P,OS_q,OT_Q,OS_d),//0x68
    OpcodeTableEntry("PUNPCKHWD",(void*)NULL,OT_P,OS_q,OT_Q,OS_d),//0x69
    OpcodeTableEntry("PUNPCKHDQ",(void*)NULL,OT_P,OS_q,OT_Q,OS_d),//0x6a
    OpcodeTableEntry("PACKSSDW",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0x6b
    OpcodeTableEntry("invalid",(void*)NULL),//0x6c
    OpcodeTableEntry("invalid",(void*)NULL),//0x6d
    OpcodeTableEntry("MOVD",(void*)NULL,OT_P,OS_q,OT_E,OS_d_q),//0x6e
    OpcodeTableEntry("MOVQ",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0x6f
    OpcodeTableEntry("PSHUFW",(void*)NULL,OT_P,OS_q,OT_Q,OS_q,OT_I,OS_b),//0x70
	OpcodeTableEntry("Group 12",opcodeTableGroup12_71),//0x71
	OpcodeTableEntry("Group 13",opcodeTableGroup13_72),//0x72
	OpcodeTableEntry("Group 14",opcodeTableGroup14_73),//0x73
    OpcodeTableEntry("PCMPEQB",(void*)NULL,OT_V,OS_dq,OT_W,OS_dq),//0x74
    OpcodeTableEntry("PCMPEQW",(void*)NULL,OT_V,OS_dq,OT_W,OS_dq),//0x75
    OpcodeTableEntry("PCMPEQD",(void*)NULL,OT_V,OS_dq,OT_W,OS_dq),//0x76
    OpcodeTableEntry("invalid",(void*)NULL),//0x77
    OpcodeTableEntry("invalid",(void*)NULL),//0x78
    OpcodeTableEntry("invalid",(void*)NULL),//0x79
    OpcodeTableEntry("invalid",(void*)NULL),//0x7a
    OpcodeTableEntry("invalid",(void*)NULL),//0x7b
    OpcodeTableEntry("invalid",(void*)NULL),//0x7c
    OpcodeTableEntry("invalid",(void*)NULL),//0x7d
    OpcodeTableEntry("MOVD",(void*)NULL,OT_E,OS_d_q,OT_P,OS_d_q),//0x7e
    OpcodeTableEntry("MOVQ",(void*)NULL,OT_Q,OS_q,OT_P,OS_q),//0x7f
    OpcodeTableEntry("JO",(void*)NULL,OT_J,OS_z),//0x80
    OpcodeTableEntry("JNO",(void*)NULL,OT_J,OS_z),//0x81
    OpcodeTableEntry("JB",(void*)NULL,OT_J,OS_z),//0x82
    OpcodeTableEntry("JNB",(void*)NULL,OT_J,OS_z),//0x83
    OpcodeTableEntry("JZ",(void*)NULL,OT_J,OS_z),//0x84
    OpcodeTableEntry("JNZ",(void*)NULL,OT_J,OS_z),//0x85
    OpcodeTableEntry("JBE",(void*)NULL,OT_J,OS_z),//0x86
    OpcodeTableEntry("JNBE",(void*)NULL,OT_J,OS_z),//0x87
    OpcodeTableEntry("JS",(void*)NULL,OT_J,OS_z),//0x88
    OpcodeTableEntry("JNS",(void*)NULL,OT_J,OS_z),//0x89
    OpcodeTableEntry("JP",(void*)NULL,OT_J,OS_z),//0x8a
    OpcodeTableEntry("JNP",(void*)NULL,OT_J,OS_z),//0x8b
    OpcodeTableEntry("JL",(void*)NULL,OT_J,OS_z),//0x8c
    OpcodeTableEntry("JNL",(void*)NULL,OT_J,OS_z),//0x8d
    OpcodeTableEntry("JLE",(void*)NULL,OT_J,OS_z),//0x8e
    OpcodeTableEntry("JNLE",(void*)NULL,OT_J,OS_z),//0x8f
    OpcodeTableEntry("SETO",(void*)NULL,OT_E,OS_b),//0x90
    OpcodeTableEntry("SETNO",(void*)NULL,OT_E,OS_b),//0x91
    OpcodeTableEntry("SETB",(void*)NULL,OT_E,OS_b),//0x92
    OpcodeTableEntry("SETNB",(void*)NULL,OT_E,OS_b),//0x93
    OpcodeTableEntry("SETZ",(void*)NULL,OT_E,OS_b),//0x94
    OpcodeTableEntry("SETNZ",(void*)NULL,OT_E,OS_b),//0x95
    OpcodeTableEntry("SETBE",(void*)NULL,OT_E,OS_b),//0x96
    OpcodeTableEntry("SETNBE",(void*)NULL,OT_E,OS_b),//0x97
    OpcodeTableEntry("SETS",(void*)NULL,OT_E,OS_b),//0x98
    OpcodeTableEntry("SETNS",(void*)NULL,OT_E,OS_b),//0x99
    OpcodeTableEntry("SETP",(void*)NULL,OT_E,OS_b),//0x9a
    OpcodeTableEntry("SETNP",(void*)NULL,OT_E,OS_b),//0x9b
    OpcodeTableEntry("SETL",(void*)NULL,OT_E,OS_b),//0x9c
    OpcodeTableEntry("SETNL",(void*)NULL,OT_E,OS_b),//0x9d
    OpcodeTableEntry("SETLE",(void*)NULL,OT_E,OS_b),//0x9e
    OpcodeTableEntry("SETNLE",(void*)NULL,OT_E,OS_b),//0x9f
    OpcodeTableEntry("PUSH",(void*)NULL,OT_FS,OS_w),//0xa0
    OpcodeTableEntry("POP",(void*)NULL,OT_FS,OS_w),//0xa1
    OpcodeTableEntry("CPUID",(void*)NULL),//0xa2
    OpcodeTableEntry("BT",(void*)NULL,OT_E,OS_v,OT_G,OS_v),//0xa3
    OpcodeTableEntry("SHLD",(void*)NULL,OT_E,OS_v,OT_G,OS_v,OT_I,OS_b),//0xa4
    OpcodeTableEntry("SHLD",(void*)NULL,OT_E,OS_v,OT_G,OS_v,OT_RCX,OS_b),//0xa5
    OpcodeTableEntry("invalid",(void*)NULL),//0xa6
    OpcodeTableEntry("invalid",(void*)NULL),//0xa7
    OpcodeTableEntry("PUSH",(void*)NULL,OT_GS),//0xa8
    OpcodeTableEntry("POP",(void*)NULL,OT_GS),//0xa9
    OpcodeTableEntry("RSM",(void*)NULL),//0xaa
    OpcodeTableEntry("BTS",(void*)NULL,OT_E,OS_v,OT_G,OS_v),//0xab
    OpcodeTableEntry("SHRD",(void*)NULL,OT_E,OS_v,OT_G,OS_v,OT_I,OS_b),//0xac
    OpcodeTableEntry("SHRD",(void*)NULL,OT_E,OS_v,OT_G,OS_v,OT_RCX,OS_b),//0xad
    OpcodeTableEntry("Group 15",(void*)NULL),//0xae
    OpcodeTableEntry("IMUL",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0xaf
    OpcodeTableEntry("CMPXCHG",(void*)NULL,OT_E,OS_b,OT_G,OS_b),//0xb0
    OpcodeTableEntry("CMPXCHG",(void*)NULL,OT_E,OS_v,OT_G,OS_v),//0xb1
    OpcodeTableEntry("LSS",(void*)NULL,OT_G,OS_z,OT_M,OS_p),//0xb2
    OpcodeTableEntry("BTR",(void*)NULL,OT_E,OS_v,OT_G,OS_v),//0xb3
    OpcodeTableEntry("LFS",(void*)NULL,OT_G,OS_z,OT_M,OS_p),//0xb4
    OpcodeTableEntry("LGS",(void*)NULL,OT_G,OS_z,OT_M,OS_p),//0xb5
    OpcodeTableEntry("MOVZX",(void*)NULL,OT_G,OS_v,OT_E,OS_b),//0xb6
    OpcodeTableEntry("MOVZX",(void*)NULL,OT_G,OS_v,OT_E,OS_w),//0xb7
    OpcodeTableEntry("invalid",(void*)NULL),//0xb8
    OpcodeTableEntry("Group 10",(void*)NULL),//0xb9
	OpcodeTableEntry("Group 8",opcodeTableGroup8_ba),//0xba
    OpcodeTableEntry("BTC",(void*)NULL,OT_E,OS_v,OT_G,OS_v),//0xbb
    OpcodeTableEntry("BSF",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0xbc
    OpcodeTableEntry("BSR",(void*)NULL,OT_G,OS_v,OT_E,OS_v),//0xbd
    OpcodeTableEntry("MOVSX",(void*)NULL,OT_G,OS_v,OT_E,OS_b),//0xbe
    OpcodeTableEntry("MOVSX",(void*)NULL,OT_G,OS_v,OT_E,OS_w),//0xbf
    OpcodeTableEntry("XADD",(void*)NULL,OT_E,OS_b,OT_G,OS_b),//0xc0
    OpcodeTableEntry("XADD",(void*)NULL,OT_E,OS_v,OT_G,OS_v),//0xc1
    OpcodeTableEntry("CMPPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_ps,OT_I,OS_b),//0xc2
    OpcodeTableEntry("MOVNTI",(void*)NULL,OT_M,OS_d_q,OT_G,OS_d_q),//0xc3
    OpcodeTableEntry("PINSRW",(void*)NULL,OT_P,OS_q,OT_E,OS_w,OT_I,OS_b),//0xc4
    OpcodeTableEntry("PEXTRW",(void*)NULL,OT_G,OS_d,OT_PR,OS_q,OT_I,OS_b),//0xc5
    OpcodeTableEntry("SHUFPS",(void*)NULL,OT_V,OS_ps,OT_W,OS_ps,OT_I,OS_b),//0xc6
	OpcodeTableEntry("Group 9",opcodeTableGroup9_c7),//0xc7
    OpcodeTableEntry("BSWAP",(void*)NULL,OT_RAX,OS_v),//0xc8
    OpcodeTableEntry("BSWAP",(void*)NULL,OT_RCX,OS_v),//0xc9
    OpcodeTableEntry("BSWAP",(void*)NULL,OT_RDX,OS_v),//0xca
    OpcodeTableEntry("BSWAP",(void*)NULL,OT_RBX,OS_v),//0xcb
    OpcodeTableEntry("BSWAP",(void*)NULL,OT_RSP,OS_v),//0xcc
    OpcodeTableEntry("BSWAP",(void*)NULL,OT_RBP,OS_v),//0xcd
    OpcodeTableEntry("BSWAP",(void*)NULL,OT_RSI,OS_v),//0xce
    OpcodeTableEntry("BSWAP",(void*)NULL,OT_RDI,OS_v),//0xcf
    OpcodeTableEntry("invalid",(void*)NULL),//0xd0
    OpcodeTableEntry("PSRLW",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xd1
    OpcodeTableEntry("PSRLD",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xd2
    OpcodeTableEntry("PSRLQ",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xd3
    OpcodeTableEntry("PADDQ",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xd4
    OpcodeTableEntry("PMULLW",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xd5
    OpcodeTableEntry("invalid",(void*)NULL),//0xd6
    OpcodeTableEntry("PMOVMSKB",(void*)NULL,OT_G,OS_d,OT_PR,OS_q),//0xd7
    OpcodeTableEntry("PSBUUSB",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xd8
    OpcodeTableEntry("PSUBUSW",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xd9
    OpcodeTableEntry("PMINUB",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xda
    OpcodeTableEntry("PAND",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xdb
    OpcodeTableEntry("PADDUSB",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xdc
    OpcodeTableEntry("PADDUSW",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xdd
    OpcodeTableEntry("PMAXUB",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xde
    OpcodeTableEntry("PANDN",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xdf
    OpcodeTableEntry("PAVGB",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xe0
    OpcodeTableEntry("PSRAW",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xe1
    OpcodeTableEntry("PSRAD",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xe2
    OpcodeTableEntry("PAVGW",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xe3
    OpcodeTableEntry("PMULHUW",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xe4
    OpcodeTableEntry("PMULHW",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xe5
    OpcodeTableEntry("invalid",(void*)NULL),//0xe6
    OpcodeTableEntry("MOVNTQ",(void*)NULL,OT_M,OS_q,OT_P,OS_q),//0xe7
    OpcodeTableEntry("PSUBSB",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xe8
    OpcodeTableEntry("PSUBSW",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xe9
    OpcodeTableEntry("PMINSW",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xea
    OpcodeTableEntry("POR",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xeb
    OpcodeTableEntry("PADDSB",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xec
    OpcodeTableEntry("PADDSW",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xed
    OpcodeTableEntry("PMAXSW",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xee
    OpcodeTableEntry("PXOR",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xef
    OpcodeTableEntry("invalid",(void*)NULL),//0xf0
    OpcodeTableEntry("PSLLW",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xf1
    OpcodeTableEntry("PSLLD",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xf2
    OpcodeTableEntry("PSLLQ",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xf3
    OpcodeTableEntry("PMULUDQ",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xf4
    OpcodeTableEntry("PMADDWD",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xf5
    OpcodeTableEntry("PSADBW",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xf6
    OpcodeTableEntry("MASKMOVQ",(void*)NULL,OT_P,OS_q,OT_PR,OS_q),//0xf7
    OpcodeTableEntry("PSUBB",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xf8
    OpcodeTableEntry("PSUBW",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xf9
    OpcodeTableEntry("PSUBD",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xfa
    OpcodeTableEntry("PSUBQ",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xfb
    OpcodeTableEntry("PADDB",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xfc
    OpcodeTableEntry("PADDW",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xfd
    OpcodeTableEntry("PADDD",(void*)NULL,OT_P,OS_q,OT_Q,OS_q),//0xfe
    OpcodeTableEntry("invalid",(void*)NULL) //0xff
};

