#include "opcodetable.h"
//#include "instructionformat.h"
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
    OpcodeTableEntry("",NULL),//0x90
    OpcodeTableEntry("",NULL),//0x91
    OpcodeTableEntry("",NULL),//0x92
    OpcodeTableEntry("",NULL),//0x93
    OpcodeTableEntry("",NULL),//0x94
    OpcodeTableEntry("",NULL),//0x95
    OpcodeTableEntry("",NULL),//0x96
    OpcodeTableEntry("",NULL),//0x97
    OpcodeTableEntry("",NULL),//0x98
    OpcodeTableEntry("",NULL),//0x99
    OpcodeTableEntry("",NULL),//0x9a
    OpcodeTableEntry("",NULL),//0x9b
    OpcodeTableEntry("",NULL),//0x9c
    OpcodeTableEntry("",NULL),//0x9d
    OpcodeTableEntry("",NULL),//0x9e
    OpcodeTableEntry("",NULL),//0x9f
    OpcodeTableEntry("",NULL),//0xa0
    OpcodeTableEntry("",NULL),//0xa1
    OpcodeTableEntry("",NULL),//0xa2
    OpcodeTableEntry("",NULL),//0xa3
    OpcodeTableEntry("",NULL),//0xa4
    OpcodeTableEntry("",NULL),//0xa5
    OpcodeTableEntry("",NULL),//0xa6
    OpcodeTableEntry("",NULL),//0xa7
    OpcodeTableEntry("",NULL),//0xa8
    OpcodeTableEntry("",NULL),//0xa9
    OpcodeTableEntry("",NULL),//0xaa
    OpcodeTableEntry("",NULL),//0xab
    OpcodeTableEntry("",NULL),//0xac
    OpcodeTableEntry("",NULL),//0xad
    OpcodeTableEntry("",NULL),//0xae
    OpcodeTableEntry("",NULL),//0xaf
    OpcodeTableEntry("",NULL),//0xb0
    OpcodeTableEntry("",NULL),//0xb1
    OpcodeTableEntry("",NULL),//0xb2
    OpcodeTableEntry("",NULL),//0xb3
    OpcodeTableEntry("",NULL),//0xb4
    OpcodeTableEntry("",NULL),//0xb5
    OpcodeTableEntry("",NULL),//0xb6
    OpcodeTableEntry("",NULL),//0xb7
    OpcodeTableEntry("",NULL),//0xb8
    OpcodeTableEntry("",NULL),//0xb9
    OpcodeTableEntry("",NULL),//0xba
    OpcodeTableEntry("",NULL),//0xbb
    OpcodeTableEntry("",NULL),//0xbc
    OpcodeTableEntry("",NULL),//0xbd
    OpcodeTableEntry("",NULL),//0xbe
    OpcodeTableEntry("",NULL),//0xbf
    OpcodeTableEntry("",NULL),//0xc0
    OpcodeTableEntry("",NULL),//0xc1
    OpcodeTableEntry("",NULL),//0xc2
    OpcodeTableEntry("",NULL),//0xc3
    OpcodeTableEntry("",NULL),//0xc4
    OpcodeTableEntry("",NULL),//0xc5
    OpcodeTableEntry("",NULL),//0xc6
    OpcodeTableEntry("",NULL),//0xc7
    OpcodeTableEntry("",NULL),//0xc8
    OpcodeTableEntry("",NULL),//0xc9
    OpcodeTableEntry("",NULL),//0xca
    OpcodeTableEntry("",NULL),//0xcb
    OpcodeTableEntry("",NULL),//0xcc
    OpcodeTableEntry("",NULL),//0xcd
    OpcodeTableEntry("",NULL),//0xce
    OpcodeTableEntry("",NULL),//0xcf
    OpcodeTableEntry("",NULL),//0xd0
    OpcodeTableEntry("",NULL),//0xd1
    OpcodeTableEntry("",NULL),//0xd2
    OpcodeTableEntry("",NULL),//0xd3
    OpcodeTableEntry("",NULL),//0xd4
    OpcodeTableEntry("",NULL),//0xd5
    OpcodeTableEntry("",NULL),//0xd6
    OpcodeTableEntry("",NULL),//0xd7
    OpcodeTableEntry("",NULL),//0xd8
    OpcodeTableEntry("",NULL),//0xd9
    OpcodeTableEntry("",NULL),//0xda
    OpcodeTableEntry("",NULL),//0xdb
    OpcodeTableEntry("",NULL),//0xdc
    OpcodeTableEntry("",NULL),//0xdd
    OpcodeTableEntry("",NULL),//0xde
    OpcodeTableEntry("",NULL),//0xdf
    OpcodeTableEntry("",NULL),//0xe0
    OpcodeTableEntry("",NULL),//0xe1
    OpcodeTableEntry("",NULL),//0xe2
    OpcodeTableEntry("",NULL),//0xe3
    OpcodeTableEntry("",NULL),//0xe4
    OpcodeTableEntry("",NULL),//0xe5
    OpcodeTableEntry("",NULL),//0xe6
    OpcodeTableEntry("",NULL),//0xe7
    OpcodeTableEntry("",NULL),//0xe8
    OpcodeTableEntry("",NULL),//0xe9
    OpcodeTableEntry("",NULL),//0xea
    OpcodeTableEntry("",NULL),//0xeb
    OpcodeTableEntry("",NULL),//0xec
    OpcodeTableEntry("",NULL),//0xed
    OpcodeTableEntry("",NULL),//0xee
    OpcodeTableEntry("",NULL),//0xef
    OpcodeTableEntry("",NULL),//0xf0
    OpcodeTableEntry("",NULL),//0xf1
    OpcodeTableEntry("",NULL),//0xf2
    OpcodeTableEntry("",NULL),//0xf3
    OpcodeTableEntry("",NULL),//0xf4
    OpcodeTableEntry("",NULL),//0xf5
    OpcodeTableEntry("",NULL),//0xf6
    OpcodeTableEntry("",NULL),//0xf7
    OpcodeTableEntry("",NULL),//0xf8
    OpcodeTableEntry("",NULL),//0xf9
    OpcodeTableEntry("",NULL),//0xfa
    OpcodeTableEntry("",NULL),//0xfb
    OpcodeTableEntry("",NULL),//0xfc
    OpcodeTableEntry("",NULL),//0xfd
    OpcodeTableEntry("",NULL),//0xfe
    OpcodeTableEntry("",NULL)//0xff
//    {,NULL},//0x0                    ""
//    {,NULL},//0x1
//    {,NULL},//0x2
//    {,NULL},//0x3
//    {,NULL},//0x4
//    {,NULL},//0x5
//    {,NULL},//0x6
//    {,NULL},//0x7
//    {,NULL},//0x8
//    {,NULL},//0x9
//    {,NULL},//0xa
//    {,NULL},//0xb
//    {,NULL},//0xc
//    {,NULL},//0xd
//    {,NULL},//0xe
//    {,NULL},//0xf
};
extern OpcodeTableEntry opcodeTableTwoByte_0x0F[256];
