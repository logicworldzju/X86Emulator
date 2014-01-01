#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QWidget>
#include "consoleimage.h"
#include <QTimer>

class ConsoleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConsoleWidget(QWidget *parent = 0, const u8* videoMemory=0);
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
    bool getShowCursor(){return _isShowCursor;}
signals:
    void toggleKeyChange(bool isShiftDown,bool isControlDown,bool isAltDown,bool isCapsLock,
                         bool isNumLock,bool isScrollLock);
    void keyStatusChange(u16 characterCode,bool isPressed);
protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
private:
    ConsoleImage _consoleImage;
    const u8* _videoMemory;

    QPoint _cursorPosition;
    bool _isShowCursor;//this is the general control of cursor show or not.
    bool _showCursorThisMoment;//this control the cursor blink.
    u32 _showCursorCount;

    QTimer _timer;

    //toggle key status.
    bool _isShiftDown;
    bool _isControlDown;
    bool _isAltDown;
    bool _isCapsLock;
    bool _isNumLock;
    bool _isScrollLock;

};

#endif // CONSOLEWIDGET_H
