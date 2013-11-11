#ifndef INSTRUCTIONTOSTRING_H
#define INSTRUCTIONTOSTRING_H

#include "cpu/instructionformat.h"
#include <string>

class InstructionToString
{
public:
    InstructionToString();
    void toString(InstructionHighLevelFormat& highFormat,
                         std::string& inst);
protected:
    void operandToString(InstructionHighLevelFormat& highFormat,
                         std::string& inst,
                         IFOperand& operand);
    void immediateToString(InstructionHighLevelFormat& highFormat,
                           std::string& inst,
                           IFOperand& operand);
    void segementRegisterToString(InstructionHighLevelFormat& highFormat,
                                  std::string& inst,
                                  IFOperand& operand);
    void gpRegisterToString(InstructionHighLevelFormat& highFormat,
                            std::string& inst,
                            IFOperand& operand);
    void memoryModRMToString(InstructionHighLevelFormat& highFormat,
                             std::string& inst,
                             IFOperand& operand);
    void memoryModRM16BitsToString(InstructionHighLevelFormat& highFormat,
                             std::string& inst,
                             IFOperand& operand);
    void memoryModRM3264BitsToString(InstructionHighLevelFormat& highFormat,
                             std::string& inst,
                             IFOperand& operand);
    void moffsetsToString(InstructionHighLevelFormat& highFormat,
                          std::string& inst,
                          IFOperand& operand);
    virtual void relativeAddressToString(s32 relativeAddress,std::string& str);
    void dispImmUnsignedToString(DispImm dispImm,DataSize size,std::string& dispImmString);
    void dispImmSignedToString(DispImm dispImm,DataSize size,std::string& dispImmString,bool withPlus=false);
    void s64ToString(s64 value,std::string& str,bool withPlus=false);
    void u64ToString(u64 value,std::string& str);

protected:
    static const char* _segmentRegisterString[6];
    static const char* _gpRegister8BitsLowString[16];
    static const char* _gpRegister8BitsString[8];
    static const char* _gpRegister16BitsString[16];
    static const char* _gpRegister32BitsString[16];
    static const char* _gpRegister64BitsString[16];
    static const char* _controlRegisterString[16];
    static const char* _debugRegisterString[16];
    static const char* _mmxRegisterString[8];
    static const char* _xmmRegisterString[16];

    static const char* _dataSizeString[7];

    static const char* _modrm16BitsString[3][8];
    static const char* _moderm3264BitsString[3][16];
};

#endif // INSTRUCTIONTOSTRING_H
