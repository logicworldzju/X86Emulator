#ifndef DEBUGCPU_H
#define DEBUGCPU_H

#include "cpu.h"
#include <vector>
#include <set>
#include <string>

class DebugCPU : public CPU
{
    Q_OBJECT
public:
    explicit DebugCPU(QObject *parent = 0);
    virtual void run();
private:
    void head();
    void tail();
    void help();
    void tip();
    u32 readInt(bool &isInt);
    static std::string outputInstruction(u32 ip, const std::vector<u8> &bin,InstructionHighLevelFormat &highFormat);
    void showDisasm(u32 address,u32 length);
    void showData(u32 address,u32 length);
protected:
    virtual void doStartInstruction(u32 addressIP);
    virtual void doDecodeInstruction(u32 ip,const std::vector<u8>& bin,InstructionLowLevelFormat& lowFormat,
        InstructionHighLevelFormat& highFormat);
    virtual void doAddressing(ExecOperands& operands)
    {
        (void)operands;
    }
    virtual void doExecuteInstruction(){}
private:
    std::set<u32> _breakPointList;
    bool _stopAtNextInstruction;
    u32 _instCount;
};

#endif // DEBUGCPU_H
