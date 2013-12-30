#include "consolewidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <assert.h>

ConsoleWidget::ConsoleWidget(QWidget *parent) :
    QWidget(parent),_consoleImage("resource/Asci0816.zf")
{
    _videoMemory = NULL;
    _isShowCursor=true;
    _showCursorThisMoment=true;
    _showCursorCount=0;
//    setVideoMemoryAddress(videoMemory);

    this->setMinimumWidth(_consoleImage.getImage().width());
    this->setMinimumHeight(_consoleImage.getImage().height());

    _timer.setInterval(50);
    connect(&_timer,SIGNAL(timeout()),this,SLOT(update()));
    _timer.start();
}

void ConsoleWidget::setVideoMemoryAddress(const u8 *videoMemory)
{
    assert(videoMemory);
    _videoMemory=videoMemory;
}

void ConsoleWidget::paintEvent(QPaintEvent *event)
{
    (void)event;
    QPainter painter(this);

    if(++_showCursorCount>=10)
    {
        _showCursorCount=0;
        _showCursorThisMoment=!_showCursorThisMoment;
    }

    _consoleImage.draw(_videoMemory,_cursorPosition,_isShowCursor&&_showCursorThisMoment);
    painter.drawImage(QPoint(0,0),_consoleImage.getImage());
}


