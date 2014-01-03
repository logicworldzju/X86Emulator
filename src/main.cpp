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
#include "io/printer.h"
#include "io/serial.h"
#include "io/cmosram.h"
#include "io/systemservice.h"
#include "io/pic.h"

#include <stdio.h>
#include <fstream>
std::ofstream fdebug("debug.txt");

void myMessageOutput(QtMsgType type, const char *msg)
{
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s\n", msg);
        fdebug<<msg<<std::endl;
        fdebug.flush();
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s\n", msg);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s\n", msg);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s\n", msg);
        abort();
    }
}
int main(int argc, char *argv[])
{
//    qInstallMsgHandler(myMessageOutput);

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
    BIOS bios(memory,"bios.bin","biosdata.bin");
    //! @todo put your written io class here.

    //----------------------
    //MainWindow is nolonger necessary.
    //(init mainwindow first as the ConsoleWidget is in the mainwindow).
    //MainWindow w(memory);
    //w.show();

    //ConsoleWidget
    ConsoleWidget w(NULL,memory.getVideoTextMemoryAddress());
    w.show();

    //Keyboard
    Keyboard keyboard;
    ioPortList.add2PortList(0x16+0x80,&keyboard.keyio);
    QObject::connect(&w,SIGNAL(keyStatusChange(u16,bool)),&keyboard,SLOT(keyStatusGet(u16,bool)));
    QObject::connect(&w,SIGNAL(toggleKeyChange(bool,bool,bool,bool,bool,bool)),&keyboard,SLOT(toggleKeyGet(bool,bool,bool,bool,bool,bool)));

    //Video
    Video video(memory,cpu.getRegisterFile(),w);
    ioPortList.add2PortList(0x10+0x80,&video);

    //Diskette
    Diskette diskette("images/DOS.IMG","images/NP.IMA");
    ioPortList.add2PortList(0x13+0x80,&diskette.getIOPort());

    //TimeOfDay
    TimeOfDay timeOfDay;
    ioPortList.add2PortList(0x1a+0x80,&timeOfDay.getIOPort());

    //CMOSRAM
    CMOSRAM cmosRAM;
    ioPortList.add2PortList(0x70,&cmosRAM.getIndexIOPort());
    ioPortList.add2PortList(0x71,&cmosRAM.getDataIOPort());

    //Printer
    Printer printer;
    ioPortList.add2PortList(0x17+0x80,&printer.getIOPort());

    //Serial
    Serial serial;
    ioPortList.add2PortList(0x14+0x80,&serial.getIOPort());

    //SystemService
    SystemService systemService;
    ioPortList.add2PortList(0x15+0x80,&systemService.getIOPort());

    //PIC
    PIC pic;
    ioPortList.add2PortList(0x20,&pic.getIOPort());
    //-------------------------------------
    //start cpu execution in another thread.
    cpu.start();
    //------------------------------------------------------------------------

    return a.exec();
}

