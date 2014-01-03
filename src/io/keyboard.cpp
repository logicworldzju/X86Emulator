#include "keyboard.h"
using namespace std;
#include <iostream>
#include <assert.h>
#include <QDebug>

Keyboard::Keyboard(QObject *parent) :
    QObject(parent)
{
}
KeyboardIO::KeyboardIO()
    :_semaphore(0)
{
    shiftflagstatus=0x0000;
    isinsert=false;
}
void KeyboardIO::getToggleKey(bool shiftdown,bool controldown,bool altdown,bool capslock,bool numlock,bool scrolllock){
    shiftflagstatus=(capslock<<14)+(numlock<<13)+(scrolllock<<12)+(altdown<<9)+(controldown<<8)+((this->isinsert)<<7)+(capslock<<6)+(numlock<<5)+(scrolllock<<4)+(altdown<<3)+(controldown<<2)+(shiftdown<<1);
    return;
}


void KeyboardIO::write2Port(u32 value, Memory& _memory, RegisterFile& _registerFile)
{
    (void)_memory;(void)value;
    u8 func;
    func = _registerFile.getGPR8BitsHigh(RAX);
    function(func, _registerFile);
}
u32 KeyboardIO::readFromPort(Memory& _memory, RegisterFile& _registerFile)
{
    (void)_memory;(void)_registerFile;
    assert(0);
    return 0xcccccccc;
//    return keyboardbuffer.first();
}


void KeyboardIO::function(u8 func, RegisterFile& _registerFile)
{
    u16 temp;
    switch(func)
    {
    case 0x00:
    {
        //temp=keyboardbuffer.dequeue();
        temp=deqBlock();
        _registerFile.setGPR16Bits(RAX,temp);
        break;
    }
    case 0x01:
    {
        //        if(!_keyboardBuffer.isEmpty()){
        //            temp=_keyboardBuffer[0];
        //            _registerFile.setGPR16Bits(RAX,temp);
        //            _registerFile.getFlagsBits().ZF=0;
        //        }
        //        else{
        //            _registerFile.setGPR16Bits(RAX,0x0000);
        //            _registerFile.getFlagsBits().ZF=1;
        //        }
        bool isGetIt;
        temp = getFirstNonblock(isGetIt);
        if(isGetIt)
        {
            _registerFile.setGPR16Bits(RAX,temp);
            _registerFile.getFlagsBits().ZF=0;
        }
        else
        {
            _registerFile.setGPR16Bits(RAX,0x0000);
            _registerFile.getFlagsBits().ZF=1;
        }
        break;
    }
    case 0x02:
    {
        _registerFile.setGPR8BitsLow(RAX,shiftflagstatus);
        break;
    }
    case 0x03:
    {
        cout<<"This is INT 16h Function 03h!"<<endl;
        break;
    }
    case 0x05:
    {
        temp=_registerFile.getGPR16Bits(RCX);
        //        _keyboardBuffer.enqueue(temp);
        enq(temp);
        _registerFile.setGPR8BitsLow(RAX,0x000);
        _registerFile.getFlagsBits().CF=0;
        break;
    }
    case 0x10:
    {
        //        temp=_keyboardBuffer.dequeue();
        //        _registerFile.setGPR16Bits(RAX,temp);
        temp=deqBlock();
        _registerFile.setGPR16Bits(RAX,temp);
        cout<<"This is INT16h Function 10h, not Function 00h!"<<endl;
        break;
    }
    case 0x11:
        //        if(!_keyboardBuffer.isEmpty()){
        //            temp=_keyboardBuffer[0];
        //            _registerFile.setGPR16Bits(RAX,temp);
        //            _registerFile.getFlagsBits().ZF=0;
        //        }
        //        else{
        //            _registerFile.setGPR16Bits(RAX,0x0000);
        //            _registerFile.getFlagsBits().ZF=1;
        //        }
    {
        bool isGetIt;
        temp = getFirstNonblock(isGetIt);
        if(isGetIt)
        {
            _registerFile.setGPR16Bits(RAX,temp);
            _registerFile.getFlagsBits().ZF=0;
//            qDebug("Keyboard:get one key by funciton11h %xh",temp);
//            cout<<"This is INT16h Function 11h, not Function 01h!"<<endl;
        }
        else
        {
            //            _registerFile.setGPR16Bits(RAX,0x0000);
            _registerFile.getFlagsBits().ZF=1;
        }
        cout<<"This is INT16h Function 11h, not Function 01h!"<<endl;
        break;
    }
    case 0x12:
    {
        _registerFile.setGPR16Bits(RAX,shiftflagstatus);
        break;\
    }
    default:
    {
        cout<<"Can't use INT16h Function "<<hex<<func<<"h!"<<endl;
        assert(0);
    }
    }
}

void KeyboardIO::enq(u16 data)
{
    {
        QMutexLocker locker(&_keyboardBufferLock);
        _keyboardBuffer.enqueue(data);
    }
    _semaphore.release();
//    qDebug()<<_semaphore.available();
    qDebug("Keyboard:insert one key %xh",data);
//    assert(0);
}

u16 KeyboardIO::deqBlock()
{
    _semaphore.acquire();
    {
        QMutexLocker locker(&_keyboardBufferLock);
        return _keyboardBuffer.dequeue();
    }
//    qDebug()<<_semaphore.available();
}

u16 KeyboardIO::deqNonblock(bool &isGetIt)
{
    if(_semaphore.tryAcquire())
    {
        isGetIt=true;
        {
            QMutexLocker locker(&_keyboardBufferLock);
            return _keyboardBuffer.dequeue();
        }
    }
    else
    {
        isGetIt=false;
        return 0;
    }
//    qDebug()<<_semaphore.available();
}
u16 KeyboardIO::getFirstBlock()
{
    _semaphore.acquire();
    {
        _semaphore.release();
        QMutexLocker locker(&_keyboardBufferLock);
//        return keyboardbuffer.dequeue();
        return _keyboardBuffer.first();
    }
}

u16 KeyboardIO::getFirstNonblock(bool &isGetIt)
{
    if(_semaphore.available()>=1)
    {
        isGetIt=true;
        {
            QMutexLocker locker(&_keyboardBufferLock);
            return _keyboardBuffer.first();
        }
    }
    else
    {
        isGetIt=false;
        return 0;
    }
//    qDebug()<<_semaphore.available();
//    assert(0);
}


void Keyboard::toggleKeyGet(bool isShiftDown,bool isControlDown,bool isAltDown,bool isCapsLock,bool isNumLock,bool isScrollLock)
{
    keyio.getToggleKey(isShiftDown,isControlDown,isAltDown,isCapsLock,isNumLock,isScrollLock);
}

void Keyboard::keyStatusGet(u16 characterCode, bool isPressed)
{
    if(!isPressed) return;
    if(characterCode == 0x5200 && isPressed==true)
    {
        if(keyio.isinsert)
        {
            keyio.isinsert=false;
            keyio.shiftflagstatus-=128;
        }
        else
        {
            keyio.isinsert=true;
            keyio.shiftflagstatus+=128;
        }
    }
    else
    {
        keyio.enq(characterCode);
    }
}
