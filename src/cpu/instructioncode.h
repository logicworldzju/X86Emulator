#ifndef INSTRUCTIONCODE_H
#define INSTRUCTIONCODE_H

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

#endif // INSTRUCTIONCODE_H
