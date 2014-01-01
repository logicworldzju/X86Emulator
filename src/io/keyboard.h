#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QObject>
#include "ioport.h"
#include <QQueue>
#include <QSemaphore>
#include <QMutex>
#include <QMutexLocker>


class KeyboardIO:public IOPort
{
public:
    KeyboardIO();
    void write2Port(u32 value, Memory& _memory, RegisterFile& _registerFile);
    u32 readFromPort(Memory& _memory, RegisterFile& _registerFile);
    void function(u8 func,RegisterFile& _registerFile);
    void getToggleKey(bool shiftdown,bool controldown,bool altdown,bool capslock,bool numlock,bool scrolllock);
    void enq(u16 data);
    u16 deqBlock();
    u16 deqNonblock(bool& isGetIt);
    friend class KeyBoard;
    u16 getFirstBlock();
    u16 getFirstNonblock(bool& isGetIt);
private:
    QQueue<u16> _keyboardBuffer;
    QMutex _keyboardBufferLock;
    u16 shiftflagstatus;
    bool isinsert;

    QSemaphore _semaphore;
};


class KeyBoard : public QObject
{
    Q_OBJECT
public:
    explicit KeyBoard(QObject *parent = 0);
    KeyboardIO keyio;
    
public slots:
    void toggleKeyGet(bool isShiftDown,bool isControlDown,bool isAltDown,bool isCapsLock,
                         bool isNumLock,bool isScrollLock);
    void keyStatusGet(u16 characterCode,bool isPressed);
};




#endif // KEYBOARD_H
