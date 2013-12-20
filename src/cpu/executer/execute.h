#ifndef EXECUTE_H
#define EXECUTE_H
#include "cpu/instructionformat.h"
#include "cpu/executer/operand/execreadwriteoperand.h"
#include "cpu/register/registerfile.h"
#include "memory/memory.h"
#include "io/ioportlist.h"
#define EXECUTE_FUNC(funcName) void funcName(OperatingEnvironment operatingEnvironment,\
    EffectiveSize effectiveAddressSize,ExecReadWriteOperand* dest,ExecReadOperand* src, \
    ExecReadOperand* src2,RegisterFile& registerFile,Memory& memory,IOPortList& ioPortList)

//typedef void (*ExecuteFunc)(EffectiveSize dataSize,ExecReadWriteOperand* dest,ExecReadOperand* src,
//                            ExecReadOperand* src2,RegisterFile& registerFile,Memory& memory);
typedef EXECUTE_FUNC(*ExecuteFunc);
//void move(EffectiveSize dataSize,ExecReadWriteOperand* dest,ExecReadOperand* src,ExecReadOperand* src2,
//          RegisterFile& registerFile,Memory& memory);
//0x0
EXECUTE_FUNC(executeADD);
EXECUTE_FUNC(executePUSH);
EXECUTE_FUNC(executePOP);
EXECUTE_FUNC(executeOR);
//0x1
EXECUTE_FUNC(executeADC);
EXECUTE_FUNC(executeSBB);
//0x2
EXECUTE_FUNC(executeAND);
EXECUTE_FUNC(executeDAA);
EXECUTE_FUNC(executeSUB);
EXECUTE_FUNC(executeDAS);
//0x3
EXECUTE_FUNC(executeXOR);
EXECUTE_FUNC(executeAAA);
EXECUTE_FUNC(executeCMP);
EXECUTE_FUNC(executeAAS);
//0x4
EXECUTE_FUNC(executeINC);
EXECUTE_FUNC(executeDEC);
//0x5
//0x6
EXECUTE_FUNC(executePUSHAD);
EXECUTE_FUNC(executePOPAD);
EXECUTE_FUNC(executeBOUND);
EXECUTE_FUNC(executeARPL);
EXECUTE_FUNC(executeIMUL3); //IMUL with 3 operands.
EXECUTE_FUNC(executeINSB);
EXECUTE_FUNC(executeINSWD);
EXECUTE_FUNC(executeOUTB);
EXECUTE_FUNC(executeOUTSWD);
//0x7
EXECUTE_FUNC(executeJO);
EXECUTE_FUNC(executeJNO);
EXECUTE_FUNC(executeJB);
EXECUTE_FUNC(executeJNB);
EXECUTE_FUNC(executeJZ);
EXECUTE_FUNC(executeJNZ);
EXECUTE_FUNC(executeJBE);
EXECUTE_FUNC(executeJNBE);
EXECUTE_FUNC(executeJS);
EXECUTE_FUNC(executeJNS);
EXECUTE_FUNC(executeJP);
EXECUTE_FUNC(executeJNP);
EXECUTE_FUNC(executeJL);
EXECUTE_FUNC(executeJNL);
EXECUTE_FUNC(executeJLE);
EXECUTE_FUNC(executeJNLE);
//0x8
EXECUTE_FUNC(executeTEST);
EXECUTE_FUNC(executeXCHG);
EXECUTE_FUNC(executeMOVE);
EXECUTE_FUNC(executeLEA);
//0x9
EXECUTE_FUNC(executeCBW_CWDE_CDQE);
EXECUTE_FUNC(executeCWD_CDQ_CQO);
EXECUTE_FUNC(executeCALL_Ap);
EXECUTE_FUNC(executeWAIT_FWAIT);
EXECUTE_FUNC(executePUSHFDQ);
EXECUTE_FUNC(executePOPFDQ);
EXECUTE_FUNC(executeSAHF);
EXECUTE_FUNC(executeLAHF);
//0xa
EXECUTE_FUNC(executeMOVSB);
EXECUTE_FUNC(executeMOVSWDQ);
EXECUTE_FUNC(executeCMPSB);
EXECUTE_FUNC(executeCMPSWDQ);
EXECUTE_FUNC(executeSTOSB);
EXECUTE_FUNC(executeSTOSWDQ);
EXECUTE_FUNC(executeLODSB);
EXECUTE_FUNC(executeLODSWDQ);
EXECUTE_FUNC(executeSCASB);
EXECUTE_FUNC(executeSCASWDQ);
//0xb
//0xc
//group2
EXECUTE_FUNC(executeROL);
EXECUTE_FUNC(executeROR);
EXECUTE_FUNC(executeRCL);
EXECUTE_FUNC(executeRCR);
//EXECUTE_FUNC(executeSHL_SAL);
EXECUTE_FUNC(executeSHR);
EXECUTE_FUNC(executeSHL_SAL);
EXECUTE_FUNC(executeSAR);
EXECUTE_FUNC(executeRETNEAR);//only this one.
EXECUTE_FUNC(executeLES);
EXECUTE_FUNC(executeLDS);

EXECUTE_FUNC(executeENTER);
EXECUTE_FUNC(executeLEAVE);
EXECUTE_FUNC(executeRETFAR);
EXECUTE_FUNC(executeINT3);
EXECUTE_FUNC(executeINT);
EXECUTE_FUNC(executeINTO);
EXECUTE_FUNC(executeIRET_IRETD_IRETQ);

//0xd
EXECUTE_FUNC(executeAAM);
EXECUTE_FUNC(executeAAD);
EXECUTE_FUNC(executeSALC);
EXECUTE_FUNC(executeXLAT);

//0xe
EXECUTE_FUNC(executeLOOPNZ);
EXECUTE_FUNC(executeLOOPZ);
EXECUTE_FUNC(executeLOOP);
EXECUTE_FUNC(executeJRCXZ);
EXECUTE_FUNC(executeIN);
EXECUTE_FUNC(executeOUT);
EXECUTE_FUNC(executeCALL_Jz);
EXECUTE_FUNC(executeJMP_J);//includes Jz & Jb
EXECUTE_FUNC(executeJMP_p);//includes Mp or Ap
//0xf
EXECUTE_FUNC(executeINT1);
EXECUTE_FUNC(executeHLT);
EXECUTE_FUNC(executeCMC);
//group 3
EXECUTE_FUNC(executeNOT);
EXECUTE_FUNC(executeNEG);
EXECUTE_FUNC(executeMUL1);
EXECUTE_FUNC(executeIMUL1);
EXECUTE_FUNC(executeDIV1);
EXECUTE_FUNC(executeIDIV1);

EXECUTE_FUNC(executeCLC);
EXECUTE_FUNC(executeSTC);
EXECUTE_FUNC(executeCLI);
EXECUTE_FUNC(executeSTI);
EXECUTE_FUNC(executeCLD);
EXECUTE_FUNC(executeSTD);

//group 4

//group 5
EXECUTE_FUNC(executeCALL_Ev);
EXECUTE_FUNC(executeJMP_Ev);


#endif // EXECUTE_H
