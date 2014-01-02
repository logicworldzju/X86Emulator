#include <QApplication>
#include "gui/mainwindow.h"
#include "memory/debugmemory.h"
#include "cpu/debugcpu.h"
#include "interrupt/interrupt.h"

#include "bios/bios.h"
#include "io/ioportlist.h"
#include "io/keyboard.h"
#include "io/diskette.h"
#include "io/timeofday.h"
#include "gui/video.h"

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
    //MainWindow w(memory);
    //w.show();

    //ConsoleWidget
    ConsoleWidget w(NULL,memory.getVideoMemoryAddress());
    w.show();

    //Keyboard
    Keyboard keyboard;
    ioPortList.add2PortList(0x16,&keyboard.keyio);
    QObject::connect(&w,SIGNAL(keyStatusChange(u16,bool)),&keyboard,SLOT(keyStatusGet(u16,bool)));
    QObject::connect(&w,SIGNAL(toggleKeyChange(bool,bool,bool,bool,bool,bool)),&keyboard,SLOT(toggleKeyGet(bool,bool,bool,bool,bool,bool)));

    //Video
    Video video(memory,cpu.getRegisterFile(),w);
    ioPortList.add2PortList(0x10,&video);

    //Diskette
    Diskette diskette("images/DOS.IMG","images/NP.IMA");
    ioPortList.add2PortList(0x13,&diskette.getIOPort());

    //TimeOfDay
    TimeOfDay timeOfDay;
    ioPortList.add2PortList(0x1a,&timeOfDay.getIOPort());

    //-------------------------------------
    //start cpu execution in another thread.
    cpu.start();
    //------------------------------------------------------------------------

    return a.exec();
}

