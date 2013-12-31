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
    BIOS bios(memory,"bios.bin");
    //! @todo put your written io class here.


    //----------------------
    //MainWindow is nolonger necessary.
    //(init mainwindow first as the ConsoleWidget is in the mainwindow).
//    MainWindow w(memory);
//    w.show();
    ConsoleWidget w(NULL,memory.getVideoMemoryAddress());
    w.show();
    //w.getConsoleWidget() this may be used by the Video BIOS function.

    //-------------------------------------
    //start cpu execution in another thread.
    cpu.start();
    //------------------------------------------------------------------------

    return a.exec();
}

