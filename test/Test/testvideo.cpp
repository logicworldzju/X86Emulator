#include "testvideo.h"
#include "gui/video.h"
#include "cpu/debugcpu.h"
#include "memory/debugmemory.h"
#include "io/ioportlist.h"
#include <string>
#include <string.h>
#include "gui/consolewidget.h"

TestVideo::TestVideo(QObject *parent):QObject(parent)
{
}

void TestVideo::test()
{
    DebugCPU cpu;
    DebugMemory memory;
    IOPortList ioPortList(memory,cpu.getRegisterFile());
    ConsoleWidget consoleWidget(0,memory.getVideoTextMemoryAddress());
    Video video(memory,cpu.getRegisterFile(),consoleWidget);
    ioPortList.add2PortList(0x10,&video);
    //-------------------------------------------------------------------------------------------------
    //void DispModeChanged();                                 //00h
    cpu.getRegisterFile().setGPR8BitsHigh(RAX,0);
    ioPortList.write2Port(0x10,0);
    //void SetCursorType();                                   //01h
    cpu.getRegisterFile().setGPR8BitsHigh(RAX,1);
    cpu.getRegisterFile().setGPR8BitsHigh(RCX,1<<5);
    ioPortList.write2Port(0x10,0);
    QCOMPARE(consoleWidget.getShowCursor(),false);
    QCOMPARE(video.CurVisible,false);
    //void SetCursorPositon();                                //02h
    cpu.getRegisterFile().setGPR8BitsHigh(RBX,0);
    cpu.getRegisterFile().setGPR16Bits(RDX,0x1122);
    cpu.getRegisterFile().setGPR8BitsHigh(RAX,2);
    ioPortList.write2Port(0x10,0);
    QCOMPARE(consoleWidget.getCursorPosition(),QPoint(0x22,0x11));
    QCOMPARE(int(video.CurColumn),int(0x22));
    QCOMPARE(int(video.CurRow),int(0x11));

    cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
    cpu.getRegisterFile().setGPR16Bits(RDX,0x3344);
    cpu.getRegisterFile().setGPR8BitsHigh(RAX,2);
    ioPortList.write2Port(0x10,0);
    QCOMPARE(consoleWidget.getCursorPosition(),QPoint(0x22,0x11));
    QCOMPARE(int(video.CurColumn),int(0x22));
    QCOMPARE(int(video.CurRow),int(0x11));
    QCOMPARE(int(video.CurPage[1*2+0]),int(0x33));
    QCOMPARE(int(video.CurPage[1*2+1]),int(0x44));
    //void ReadCurrentCursorPosition();                       //03h
    cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
    cpu.getRegisterFile().setGPR8BitsHigh(RAX,3);
    ioPortList.write2Port(0x10,0);
    QCOMPARE(int(cpu.getRegisterFile().getGPR16Bits(RAX)),int(0));
    QCOMPARE(int(cpu.getRegisterFile().getGPR16Bits(RDX)),int(0x3344));
    //void ReadLightPenPosition();                            //04h
    //void SelectNewVideoPage();                              //05h
    cpu.getRegisterFile().setGPR8BitsLow(RAX,1);
    cpu.getRegisterFile().setGPR8BitsHigh(RAX,5);
    ioPortList.write2Port(0x10,0);
    QCOMPARE((consoleWidget.getCursorPosition()),QPoint(0x44,0x33));
    QCOMPARE(int(video.CurrentPage),int(1));
    QCOMPARE(int(video.CurColumn),int(0x44));
    QCOMPARE(int(video.CurRow),int(0x33));
    //void ScrollCurrentPageUp();                             //06h
    {
        u8* videoBase = memory.getVideoTextMemoryAddress()+video.CurrentPage*80*25*2;
        (videoBase+80*2*10+5*2)[0]=0xc1;
        (videoBase+80*2*10+5*2)[1]=0x1c;
        cpu.getRegisterFile().setGPR8BitsLow(RAX,2);
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,0xcc);
        cpu.getRegisterFile().setGPR8BitsHigh(RCX,2);
        cpu.getRegisterFile().setGPR8BitsLow(RCX,2);
        cpu.getRegisterFile().setGPR8BitsHigh(RDX,12);
        cpu.getRegisterFile().setGPR8BitsLow(RDX,12);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,6);
        ioPortList.write2Port(0x10,0);
        QCOMPARE(int((videoBase+80*2*(10-2)+5*2)[0]),int(0xc1));
        QCOMPARE(int((videoBase+80*2*(10-2)+5*2)[1]),int(0x1c));
        QCOMPARE(int((videoBase+80*2*(12)+2*2)[0]),int(' '));
        QCOMPARE(int((videoBase+80*2*(12)+2*2)[1]),int(0xcc));
        QCOMPARE(int((videoBase+80*2*(12)+12*2)[0]),int(' '));
        QCOMPARE(int((videoBase+80*2*(12)+12*2)[1]),int(0xcc));

        QCOMPARE(int((videoBase+80*2*(12)+1*2)[0]),int(0));
        QCOMPARE(int((videoBase+80*2*(12)+1*2)[1]),int(0));
        QCOMPARE(int((videoBase+80*2*(12)+13*2)[0]),int(0));
        QCOMPARE(int((videoBase+80*2*(12)+13*2)[1]),int(0));
    }
    {
        u8* videoBase = memory.getVideoTextMemoryAddress()+video.CurrentPage*80*25*2;
        (videoBase+80*2*10+5*2)[0]=0xc1;
        (videoBase+80*2*10+5*2)[1]=0x1c;
        cpu.getRegisterFile().setGPR8BitsLow(RAX,0);
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,0xcd);
        cpu.getRegisterFile().setGPR8BitsHigh(RCX,2);
        cpu.getRegisterFile().setGPR8BitsLow(RCX,2);
        cpu.getRegisterFile().setGPR8BitsHigh(RDX,12);
        cpu.getRegisterFile().setGPR8BitsLow(RDX,12);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,6);
        ioPortList.write2Port(0x10,0);
        QCOMPARE(int((videoBase+80*2*(10-2)+5*2)[0]),int(' '));
        QCOMPARE(int((videoBase+80*2*(10-2)+5*2)[1]),int(0xcd));
        QCOMPARE(int((videoBase+80*2*(12)+2*2)[0]),int(' '));
        QCOMPARE(int((videoBase+80*2*(12)+2*2)[1]),int(0xcd));
        QCOMPARE(int((videoBase+80*2*(12)+12*2)[0]),int(' '));
        QCOMPARE(int((videoBase+80*2*(12)+12*2)[1]),int(0xcd));

        QCOMPARE(int((videoBase+80*2*(2)+12*2)[0]),int(' '));
        QCOMPARE(int((videoBase+80*2*(2)+12*2)[1]),int(0xcd));
        QCOMPARE(int((videoBase+80*2*(2)+2*2)[0]),int(' '));
        QCOMPARE(int((videoBase+80*2*(2)+2*2)[1]),int(0xcd));

        QCOMPARE(int((videoBase+80*2*(12)+1*2)[0]),int(0));
        QCOMPARE(int((videoBase+80*2*(12)+1*2)[1]),int(0));
        QCOMPARE(int((videoBase+80*2*(12)+13*2)[0]),int(0));
        QCOMPARE(int((videoBase+80*2*(12)+13*2)[1]),int(0));
    }
    //void ScrollCurrentPageDown();                           //07h
    {
        u8* videoBase = memory.getVideoTextMemoryAddress()+video.CurrentPage*80*25*2;
        (videoBase+80*2*10+5*2)[0]=0xc2;
        (videoBase+80*2*10+5*2)[1]=0x2c;
        cpu.getRegisterFile().setGPR8BitsLow(RAX,2);
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,0xcc);
        cpu.getRegisterFile().setGPR8BitsHigh(RCX,2);
        cpu.getRegisterFile().setGPR8BitsLow(RCX,2);
        cpu.getRegisterFile().setGPR8BitsHigh(RDX,12);
        cpu.getRegisterFile().setGPR8BitsLow(RDX,12);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,7);
        ioPortList.write2Port(0x10,0);
        QCOMPARE(int((videoBase+80*2*(10+2)+5*2)[0]),int(0xc2));
        QCOMPARE(int((videoBase+80*2*(10+2)+5*2)[1]),int(0x2c));
        QCOMPARE(int((videoBase+80*2*(2)+2*2)[0]),int(' '));
        QCOMPARE(int((videoBase+80*2*(2)+2*2)[1]),int(0xcc));
        QCOMPARE(int((videoBase+80*2*(2)+12*2)[0]),int(' '));
        QCOMPARE(int((videoBase+80*2*(2)+12*2)[1]),int(0xcc));

        QCOMPARE(int((videoBase+80*2*(12)+1*2)[0]),int(0));
        QCOMPARE(int((videoBase+80*2*(12)+1*2)[1]),int(0));
        QCOMPARE(int((videoBase+80*2*(12)+13*2)[0]),int(0));
        QCOMPARE(int((videoBase+80*2*(12)+13*2)[1]),int(0));
    }
    {
        u8* videoBase = memory.getVideoTextMemoryAddress()+video.CurrentPage*80*25*2;
        (videoBase+80*2*10+5*2)[0]=0xc1;
        (videoBase+80*2*10+5*2)[1]=0x1c;
        cpu.getRegisterFile().setGPR8BitsLow(RAX,0);
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,0xce);
        cpu.getRegisterFile().setGPR8BitsHigh(RCX,2);
        cpu.getRegisterFile().setGPR8BitsLow(RCX,2);
        cpu.getRegisterFile().setGPR8BitsHigh(RDX,12);
        cpu.getRegisterFile().setGPR8BitsLow(RDX,12);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,7);
        ioPortList.write2Port(0x10,0);
        QCOMPARE(int((videoBase+80*2*(10-2)+5*2)[0]),int(' '));
        QCOMPARE(int((videoBase+80*2*(10-2)+5*2)[1]),int(0xce));
        QCOMPARE(int((videoBase+80*2*(12)+2*2)[0]),int(' '));
        QCOMPARE(int((videoBase+80*2*(12)+2*2)[1]),int(0xce));
        QCOMPARE(int((videoBase+80*2*(12)+12*2)[0]),int(' '));
        QCOMPARE(int((videoBase+80*2*(12)+12*2)[1]),int(0xce));

        QCOMPARE(int((videoBase+80*2*(2)+12*2)[0]),int(' '));
        QCOMPARE(int((videoBase+80*2*(2)+12*2)[1]),int(0xce));
        QCOMPARE(int((videoBase+80*2*(2)+2*2)[0]),int(' '));
        QCOMPARE(int((videoBase+80*2*(2)+2*2)[1]),int(0xce));

        QCOMPARE(int((videoBase+80*2*(12)+1*2)[0]),int(0));
        QCOMPARE(int((videoBase+80*2*(12)+1*2)[1]),int(0));
        QCOMPARE(int((videoBase+80*2*(12)+13*2)[0]),int(0));
        QCOMPARE(int((videoBase+80*2*(12)+13*2)[1]),int(0));
    }
    //void ReadCharacter_AttributefromScreen();               //08h
    {
        u8* videoBase = memory.getVideoTextMemoryAddress()+video.CurrentPage*80*25*2;
        (videoBase+80*2*10+5*2)[0]=0xc1;
        (videoBase+80*2*10+5*2)[1]=0x1c;
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
        cpu.getRegisterFile().setGPR16Bits(RDX,0x0a05);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,2);
        ioPortList.write2Port(0x10,0);
        QCOMPARE(int(video.CurPage[1*2+0]),0xa);
        QCOMPARE(int(video.CurPage[1*2+1]),0x5);

        cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,8);
        ioPortList.write2Port(0x10,0);
        QCOMPARE(int(cpu.getRegisterFile().getGPR16Bits(RAX)),int(0x1cc1));
    }
    //void WriteCharacter_AttributetoScreen();                //09h
    {
//        u8* videoBase = memory.getVideoMemoryAddress()+video.CurrentPage*80*25*2;
//        (videoBase+80*2*10+5*2)[0]=0xc1;
//        (videoBase+80*2*10+5*2)[1]=0x1c;
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,2);
        cpu.getRegisterFile().setGPR16Bits(RDX,0x0a05);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,2);
        ioPortList.write2Port(0x10,0);
        QCOMPARE(int(video.CurPage[2*2+0]),0xa);
        QCOMPARE(int(video.CurPage[2*2+1]),0x5);

        cpu.getRegisterFile().setGPR8BitsLow(RAX,0x23);
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,2);
        cpu.getRegisterFile().setGPR8BitsLow(RBX,2);
        cpu.getRegisterFile().setGPR16Bits(RCX,3);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,9);
        ioPortList.write2Port(0x10,0);
        QCOMPARE(int(video.CurPage[2*2+0]),0xa);
        QCOMPARE(int(video.CurPage[2*2+1]),0x5);

        cpu.getRegisterFile().setGPR8BitsHigh(RBX,2);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,8);
        ioPortList.write2Port(0x10,0);
        QCOMPARE(int(cpu.getRegisterFile().getGPR16Bits(RAX)),int(0x223));
    }
    //void WriteCharacterOnlytoScreen();                      //0Ah
    {
//        u8* videoBase = memory.getVideoMemoryAddress()+video.CurrentPage*80*25*2;
//        (videoBase+80*2*10+5*2)[0]=0xc1;
//        (videoBase+80*2*10+5*2)[1]=0x1c;
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,2);
        cpu.getRegisterFile().setGPR16Bits(RDX,0x0a05);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,2);
        ioPortList.write2Port(0x10,0);
        QCOMPARE(int(video.CurPage[2*2+0]),0xa);
        QCOMPARE(int(video.CurPage[2*2+1]),0x5);

        cpu.getRegisterFile().setGPR8BitsLow(RAX,0x22);
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,2);
//        cpu.getRegisterFile().setGPR8BitsLow(RBX,2);
        cpu.getRegisterFile().setGPR16Bits(RCX,3);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,10);
        ioPortList.write2Port(0x10,0);
        QCOMPARE(int(video.CurPage[2*2+0]),0xa);
        QCOMPARE(int(video.CurPage[2*2+1]),0x5);

        cpu.getRegisterFile().setGPR8BitsHigh(RBX,2);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,8);
        ioPortList.write2Port(0x10,0);
        QCOMPARE(int(cpu.getRegisterFile().getGPR16Bits(RAX)),int(0x222));
    }
    //void SetColorPalette();                                 //0Bh
    //void WritePixel();                                      //0Ch
    //void ReadPixel();                                       //0Dh
    //void WriteTeletypetoActivePage();                       //0Eh
    {
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
        cpu.getRegisterFile().setGPR16Bits(RDX,0x0a4e);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,2);
        ioPortList.write2Port(0x10,0);

        cpu.getRegisterFile().setGPR8BitsLow(RAX,'a');
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,0xe);
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
        ioPortList.write2Port(0x10,0);

        QCOMPARE(int(video.CurPage[1*2+0]),0xa);
        QCOMPARE(int(video.CurPage[1*2+1]),0x4f);
        u8* videoBase = memory.getVideoTextMemoryAddress()+1*80*25*2;
        QCOMPARE(int((videoBase+0xa*80*2+0x4e*2)[0]),int('a'));
    }
    {
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
        cpu.getRegisterFile().setGPR16Bits(RDX,0x0a4f);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,2);
        ioPortList.write2Port(0x10,0);

        cpu.getRegisterFile().setGPR8BitsLow(RAX,'a');
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,0xe);
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
        ioPortList.write2Port(0x10,0);

        QCOMPARE(int(video.CurPage[1*2+0]),0xb);
        QCOMPARE(int(video.CurPage[1*2+1]),0x0);
        u8* videoBase = memory.getVideoTextMemoryAddress()+1*80*25*2;
        QCOMPARE(int((videoBase+0xa*80*2+0x4f*2)[0]),int('a'));
    }
    {
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
        cpu.getRegisterFile().setGPR16Bits(RDX,0x184f);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,2);
        ioPortList.write2Port(0x10,0);

        cpu.getRegisterFile().setGPR8BitsLow(RAX,'a');
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,0xe);
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
        ioPortList.write2Port(0x10,0);

        QCOMPARE(int(video.CurPage[1*2+0]),0x18);
        QCOMPARE(int(video.CurPage[1*2+1]),0x0);
        u8* videoBase = memory.getVideoTextMemoryAddress()+1*80*25*2;
        QCOMPARE(int((videoBase+0x17*80*2+0x4f*2)[0]),int('a'));
    }
    {
        //test backspace
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
        cpu.getRegisterFile().setGPR16Bits(RDX,0x184f);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,2);
        ioPortList.write2Port(0x10,0);

        cpu.getRegisterFile().setGPR8BitsLow(RAX,0x8);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,0xe);
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
        ioPortList.write2Port(0x10,0);

        QCOMPARE(int(video.CurPage[1*2+0]),0x18);
        QCOMPARE(int(video.CurPage[1*2+1]),0x4e);
    }
    {
        //test bell
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
        cpu.getRegisterFile().setGPR16Bits(RDX,0x184f);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,2);
        ioPortList.write2Port(0x10,0);

        cpu.getRegisterFile().setGPR8BitsLow(RAX,0x7);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,0xe);
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
        ioPortList.write2Port(0x10,0);

        QCOMPARE(int(video.CurPage[1*2+0]),0x18);
        QCOMPARE(int(video.CurPage[1*2+1]),0x4f);
    }
    {
        //test LF
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
        cpu.getRegisterFile().setGPR16Bits(RDX,0x1840);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,2);
        ioPortList.write2Port(0x10,0);

        cpu.getRegisterFile().setGPR8BitsLow(RAX,0xa);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,0xe);
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
        ioPortList.write2Port(0x10,0);

        QCOMPARE(int(video.CurPage[1*2+0]),0x18);
        QCOMPARE(int(video.CurPage[1*2+1]),0x40);
    }
    {
        //test CR
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
        cpu.getRegisterFile().setGPR16Bits(RDX,0x184f);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,2);
        ioPortList.write2Port(0x10,0);

        cpu.getRegisterFile().setGPR8BitsLow(RAX,0xd);
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,0xe);
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
        ioPortList.write2Port(0x10,0);

        QCOMPARE(int(video.CurPage[1*2+0]),0x18);
        QCOMPARE(int(video.CurPage[1*2+1]),0x0);
    }
    //void ReturnVideoStatus();                               //0Fh
    {
        cpu.getRegisterFile().setGPR8BitsHigh(RAX,0xf);
        ioPortList.write2Port(0x10,0);

        QCOMPARE(int(cpu.getRegisterFile().getGPR8BitsHigh(RAX)),int(80));
        QCOMPARE(int(cpu.getRegisterFile().getGPR8BitsHigh(RBX)),int(1));
    }
    //void WriteString();                                     //13h
    {
        u8 videoBuffer[]={'a',0x00,'b',0x01,'c',0x02,'d',0x03,'e',0x04,'f',
                                 0x05,'g',0x06,'h',0x07,'i',0x08,'j',0x09,'k',0x0a,
                                 'l',0x0b,'m',0x0c,'n',0xd,'o',0xe,'p',0xf,'q',0x10,'r',0x11};
        memcpy(memory.getMemoryAddress()+0x400,videoBuffer,sizeof(videoBuffer));
        cpu.getRegisterFile().setSR(ES,0x10);
        cpu.getRegisterFile().setGPR16Bits(RBP,0x300);
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
        cpu.getRegisterFile().setGPR8BitsLow(RBX,0x1);
        cpu.getRegisterFile().setGPR16Bits(RCX,sizeof(videoBuffer)/2);
        cpu.getRegisterFile().setGPR16Bits(RDX,0x114f);
        cpu.getRegisterFile().setGPR8BitsLow(RAX,0x3);

        cpu.getRegisterFile().setGPR8BitsHigh(RAX,0x13);
        ioPortList.write2Port(0x10,0);

        QCOMPARE(int(video.CurPage[1*2+0]),0x12);
        QCOMPARE(int(video.CurPage[1*2+1]),17);

    }
    {
        u8 videoBuffer[]={'a','b','c','d','e','f',
                                 'g','h','i','j','k',
                                 'l','m','n','o','p','q','r',0xd,0xa};
        memcpy(memory.getMemoryAddress()+0x400,videoBuffer,sizeof(videoBuffer));
        cpu.getRegisterFile().setSR(ES,0x10);
        cpu.getRegisterFile().setGPR16Bits(RBP,0x300);
        cpu.getRegisterFile().setGPR8BitsHigh(RBX,1);
        cpu.getRegisterFile().setGPR8BitsLow(RBX,0x1);
        cpu.getRegisterFile().setGPR16Bits(RCX,sizeof(videoBuffer));
        cpu.getRegisterFile().setGPR16Bits(RDX,0x184f);
        cpu.getRegisterFile().setGPR8BitsLow(RAX,0x1);

        cpu.getRegisterFile().setGPR8BitsHigh(RAX,0x13);
        ioPortList.write2Port(0x10,0);

        QCOMPARE(int(video.CurPage[1*2+0]),0x18);
        QCOMPARE(int(video.CurPage[1*2+1]),0);
    }
//    cpu.getRegisterFile().setGPR8BitsHigh(RAX,0);
//    ioPortList.write2Port(0x10,0);
//    QCOMPARE((int)cpu.getRegisterFile().getGPR8BitsHigh(RAX),0);
//    ::memset(videoBuffer,0,sizeof(videoBuffer));
//        widget.hideCursor();
//    }
//    {
//        widget.showCursor();
//        widget.setCursorPosition(QPoint(100,2));
//    }
    //QTest::qWait(150000);
}

