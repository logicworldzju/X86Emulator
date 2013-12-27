#ifndef CPU_H
#define CPU_H

#include <QThread>
#include <vector>
#include "memory/memory.h"
#include "register/registerfile.h"
#include "io/ioportlist.h"
#include "interrupt/interrupt.h"
#include "cpu/instructionformat.h"
#include "cpu/executer/operand/execoperands.h"

class CPU : public QThread
{
    Q_OBJECT
public:
    explicit CPU(QObject *parent = 0);
    virtual void initHardwareConnection(Memory& memory,IOPortList& ioPortList,Interrupt& interrupt)
    {
        _memory=&memory;
        _ioPortList=&ioPortList;
        _interrupt=&interrupt;
    }
    RegisterFile& getRegisterFile()
    {
        return _registerFile;
    }
    void run();
    void exit()
    {
        shouldExit=true;
    }
protected:
    virtual void doStartInstruction(u32 addressIP)
    {
        (void)addressIP;
    }
    virtual void doDecodeInstruction(u32 ip,const std::vector<u8>& bin,InstructionLowLevelFormat& lowFormat,
        InstructionHighLevelFormat& highFormat)
    {
        (void)ip;(void)bin;(void)lowFormat;(void)highFormat;
    }
    virtual void doAddressing(ExecOperands& operands)
    {
        (void)operands;
    }
    virtual void doExecuteInstruction(){}
protected:
    RegisterFile _registerFile;
    Memory* _memory;
    IOPortList* _ioPortList;
    Interrupt* _interrupt;

    bool shouldExit;
};

#endif // CPU_H
