#include "testconsolewidget.h"
#include "gui/consolewidget.h"
#include <string>

TestConsoleWidget::TestConsoleWidget(QObject *parent) :
    QObject(parent)
{
}

void TestConsoleWidget::test()
{
    ConsoleWidget widget;
    u8 videoBuffer[80*25*2]={0};//={'a',0x00,'b',0x01,'c',0x02,'d',0x03,'e',0x04,'f',0x05,'g',0x06,'h',0x07,
//                            'i',0x08,'j',0x09,'k',0x0a,'l',0x0b,'m',0x0c,'n','o','p','q','r'};
//    ::memset(videoBuffer,0,sizeof(videoBuffer));
    for(int i=0; i<256; i++)
    {
        videoBuffer[i*2+0]=u8(i);
        videoBuffer[i*2+1]=u8(i);
    }

    widget.setVideoMemoryAddress(videoBuffer);
    widget.show();
    {
        widget.showCursor();
        widget.setCursorPosition(QPoint(11,2));
        QCOMPARE(widget.getCursorPosition().x(),11);
        QCOMPARE(widget.getCursorPosition().y(),2);
    }
//    {
//        widget.hideCursor();
//    }
//    {
//        widget.showCursor();
//        widget.setCursorPosition(QPoint(100,2));
//    }
    QTest::qWait(150000);
}
