#include "testtimeofday.h"
#include "io/TimeOfDay.h"
#include "memory/debugmemory.h"
#include "cpu/debugcpu.h"
TestTimeOfDay::TestTimeOfDay(QObject *parent) :
    QObject(parent)
{
}

void TestTimeOfDay::test()
{
    TimeOfDay timeOfDay;
    DebugMemory memory;
    DebugCPU cpu;

    {
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,0);
        timeOfDay.getIOPort().write2Port(0,memory,cpu.getRegisterFile());
    }
    {
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,1);
        timeOfDay.getIOPort().write2Port(0,memory,cpu.getRegisterFile());
    }
    {
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,2);
        timeOfDay.getIOPort().write2Port(0,memory,cpu.getRegisterFile());
    }
    {
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,3);
        timeOfDay.getIOPort().write2Port(0,memory,cpu.getRegisterFile());
    }
    {
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,4);
        timeOfDay.getIOPort().write2Port(0,memory,cpu.getRegisterFile());
    }
    {
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,5);
        timeOfDay.getIOPort().write2Port(0,memory,cpu.getRegisterFile());
    }
}
