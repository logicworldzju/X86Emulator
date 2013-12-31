#include "testdebugcpu.h"
#include "memory/debugmemory.h"
#include "cpu/debugcpu.h"
#include "bios/bios.h"
#include "io/ioportlist.h"
#include "interrupt/interrupt.h"

TestDebugCPU::TestDebugCPU(QObject *parent) :
    QObject(parent)
{
}

void TestDebugCPU::test()
{
    DebugCPU cpu;

    DebugMemory memory;
    IOPortList ioPortList(memory,cpu.getRegisterFile());
    Interrupt interrupt;

    cpu.initHardwareConnection(memory,ioPortList,interrupt);

    BIOS bios(memory,"bios.bin");
    cpu.start();
    cpu.wait();
}
