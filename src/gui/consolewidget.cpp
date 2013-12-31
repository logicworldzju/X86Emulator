#include "consolewidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <assert.h>
#include "charactercode.h"
#include <QDebug>

ConsoleWidget::ConsoleWidget(QWidget *parent,const u8 *videoMemory) :
    QWidget(parent),_consoleImage("resource/Asci0816.zf")
{
    _videoMemory = NULL;
    _isShowCursor=true;
    _showCursorThisMoment=true;
    _showCursorCount=0;

    _isShiftDown=false;
    _isControlDown=false;
    _isAltDown=false;
    _isCapsLock=false;
    _isNumLock=false;
    _isScrollLock=false;
    if(videoMemory!=NULL)
        setVideoMemoryAddress(videoMemory);

    this->setMinimumWidth(_consoleImage.getImage().width());
    this->setMinimumHeight(_consoleImage.getImage().height());
    this->setMaximumWidth(_consoleImage.getImage().width());
    this->setMaximumHeight(_consoleImage.getImage().height());

    this->setWindowTitle("X86Emulator");
    this->setFocus();

    _timer.setInterval(50);
    connect(&_timer,SIGNAL(timeout()),this,SLOT(update()));
    _timer.start();

    CharacterCode::initTranslateTable();
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

void ConsoleWidget::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key==Qt::Key_Shift)
    {
        _isShiftDown=true;
//        qDebug("shift pressed.");
        emit toggleKeyChange(_isShiftDown,_isControlDown,_isAltDown,_isCapsLock,_isNumLock,_isScrollLock);
    }
    else if(key==Qt::Key_Control)
    {
        _isControlDown=true;
//        qDebug("control pressed.");
        emit toggleKeyChange(_isShiftDown,_isControlDown,_isAltDown,_isCapsLock,_isNumLock,_isScrollLock);
    }
    else if(key==Qt::Key_Alt)
    {
        _isAltDown=true;
//        qDebug("ALT pressed.");
        emit toggleKeyChange(_isShiftDown,_isControlDown,_isAltDown,_isCapsLock,_isNumLock,_isScrollLock);
    }
    else if(key==Qt::Key_CapsLock)
    {
//        qDebug("capslock pressed.");
        _isCapsLock=!_isCapsLock;
        emit toggleKeyChange(_isShiftDown,_isControlDown,_isAltDown,_isCapsLock,_isNumLock,_isScrollLock);
    }
    else if(key==Qt::Key_NumLock)
    {
        _isNumLock=!_isNumLock;
//        qDebug("numlock pressed.");
        emit toggleKeyChange(_isShiftDown,_isControlDown,_isAltDown,_isCapsLock,_isNumLock,_isScrollLock);
    }
    else if(key==Qt::Key_ScrollLock)
    {
        _isScrollLock=!_isScrollLock;
//        qDebug("scrolllock pressed.");
        emit toggleKeyChange(_isShiftDown,_isControlDown,_isAltDown,_isCapsLock,_isNumLock,_isScrollLock);
    }
    else
    {
        u16 characterCode = CharacterCode::fromQtKey(key,event->modifiers(),true);
//        qDebug()<<characterCode;
        emit keyStatusChange(characterCode,true);
    }

}

void ConsoleWidget::keyReleaseEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key==Qt::Key_Shift)
    {
        _isShiftDown=false;
//        qDebug("shift unpressed.");
        emit toggleKeyChange(_isShiftDown,_isControlDown,_isAltDown,_isCapsLock,_isNumLock,_isScrollLock);
    }
    else if(key==Qt::Key_Control)
    {
        _isControlDown=false;
//        qDebug("control unpressed.");
        emit toggleKeyChange(_isShiftDown,_isControlDown,_isAltDown,_isCapsLock,_isNumLock,_isScrollLock);
    }
    else if(key==Qt::Key_Alt)
    {
        _isAltDown=false;
//        qDebug("alt unpressed.");
        emit toggleKeyChange(_isShiftDown,_isControlDown,_isAltDown,_isCapsLock,_isNumLock,_isScrollLock);
    }
    else if(key==Qt::Key_CapsLock)
    {
//        qDebug("capslock unpressed.");
    }
    else if(key==Qt::Key_NumLock)
    {
//        qDebug("numlock unpressed.");
    }
    else if(key==Qt::Key_ScrollLock)
    {
//        qDebug("scrolllock unpressed.");
    }
    else
    {
        u16 characterCode = CharacterCode::fromQtKey(key,event->modifiers(),false);
//        qDebug()<<characterCode;
        emit keyStatusChange(characterCode,false);
    }
}


