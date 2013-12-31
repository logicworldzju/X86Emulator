#include "testvideo.h"
#include "gui/video.h"
#include "cpu/debugcpu.h"
#include "memory/debugmemory.h"
#include "io/ioportlist.h"
#include <string>

TestVideo::TestVideo(QObject *parent):QObject(parent)
{
}

void TestVideo::test()
{
    DebugCPU cpu;
    DebugMemory memory;
    IOPortList ioPortList(memory,cpu.getRegisterFile());
    Video video(memory,cpu.getRegisterFile());
    ioPortList.add2PortList(0x10,&video);
    u8 videoBuffer[80*25*2]={0};//={'a',0x00,'b',0x01,'c',0x02,'d',0x03,'e',0x04,'f',0x05,'g',0x06,'h',0x07,
//                            'i',0x08,'j',0x09,'k',0x0a,'l',0x0b,'m',0x0c,'n','o','p','q','r'};
    cpu.getRegisterFile().setGPR8BitsHigh(RAX,0);
    ioPortList.write2Port(0x10,0);
    QCOMPARE( cpu.getRegisterFile().getGPR8BitsHigh(RAX),0);
//    ::memset(videoBuffer,0,sizeof(videoBuffer));
//        widget.hideCursor();
//    }
//    {
//        widget.showCursor();
//        widget.setCursorPosition(QPoint(100,2));
//    }
    //QTest::qWait(150000);
}

