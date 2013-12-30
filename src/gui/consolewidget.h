#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QWidget>
#include "consoleimage.h"
#include <QTimer>

class ConsoleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConsoleWidget(/*const u8* videoMemory,*/QWidget *parent = 0);
    void setVideoMemoryAddress(const u8* videoMemory);
    void setCursorPosition(const QPoint& cursorPosition){_cursorPosition=cursorPosition;}
    const QPoint& getCursorPosition(){ return _cursorPosition;}
    void showCursor()
    {
        _isShowCursor=true;
    }
    void hideCursor()
    {
        _isShowCursor=false;
    }
    void setShowCursor(bool isShowCursor)
    {
        _isShowCursor=isShowCursor;
    }
protected:
    void paintEvent(QPaintEvent *);
private:
    ConsoleImage _consoleImage;
    const u8* _videoMemory;

    QPoint _cursorPosition;
    bool _isShowCursor;//this is the general control of cursor show or not.
    bool _showCursorThisMoment;//this control the cursor blink.
    u32 _showCursorCount;

    QTimer _timer;
};

#endif // CONSOLEWIDGET_H
