#include "gui/mainwindow.h"
#include <QApplication>
#include "memory/debugmemory.h"
#include "cpu/debugcpu.h"
#include "bios/bios.h"
#include "io/ioportlist.h"
#include "interrupt/interrupt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //------------------------------------------------------------------------
    //CPU&DebugCPU
    DebugCPU cpu;

    //-------------------------------------
    //Memory&IOPortList&Interrupt
    DebugMemory memory;
    IOPortList ioPortList(memory,cpu.getRegisterFile());
    Interrupt interrupt;

    cpu.initHardwareConnection(memory,ioPortList,interrupt);

    //-------------------------------------
    //BIOS&IO
    BIOS bios(memory,"../src/bios/bios.bin");
    //! @todo put your written io class here.


    //-------------------------------------
    //start cpu execution in another thread.
    cpu.start();
    //------------------------------------------------------------------------

    MainWindow w;
    w.show();

    return a.exec();
}

