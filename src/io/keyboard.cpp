#include "keyboard.h"

KeyBoard::KeyBoard(QObject *parent) :
    QObject(parent)
{
}
keyboardio::keyboardio()
{
    shiftflagstatus=0x0000;
    isinsert=false;
}
void keyboardio::getToggleKey(bool shiftdown,bool controldown,bool altdown,bool capslock,bool numlock,bool scrolllock){
    shiftflagstatus=(capslock<<14)+(numlock<<13)+(scrolllock<<12)+(altdown<<9)+(controldown<<8)+((this->isinsert)<<7)+(capslock<<6)+(numlock<<5)+(scrolllock<<4)+(altdown<<3)+(controldown<<2)+(shiftdown<<1);
    return;
}


void keyboardio::write2Port(u32 value, Memory& _memory, RegisterFile& _registerFile)
{
    u8 func;
    func = _registerFile.getGPR8BitsHigh(RAX);
    function(func, _registerFile);
}
u32 keyboardio::readFromPort(Memory& _memory, RegisterFile& _registerFile)
{
    return keyboardbuffer.first();
}


void keyboardio::function(u8 func, RegisterFile& _registerFile)
{
    u16 temp;
    switch(func){
        case 0x00:
            temp=keyboardbuffer.dequeue();
            _registerFile.setGPR16Bits(RAX,temp);
            break;
        case 0x01:
            if(!keyboardbuffer.isEmpty()){
                temp=keyboardbuffer[0];
                _registerFile.setGPR16Bits(RAX,temp);
                _registerFile.getFlagsBits().ZF=0;
            }
            else{
                _registerFile.setGPR16Bits(RAX,0x0000);
                _registerFile.getFlagsBits().ZF=1;
            }
            break;
        case 0x02:
            _registerFile.setGPR8BitsLow(RAX,shiftflagstatus);
            break;
        case 0x03:
            cout<<"This is INT 16h Function 03h!"<<endl;
            break;
        case 0x05:
            temp=_registerFile.getGPR16Bits(RCX);
            keyboardbuffer.enqueue(temp);
            _registerFile.setGPR8BitsLow(RAX,0x000);
            _registerFile.getFlagsBits().CF=0;
            break;
        case 0x10:
            temp=keyboardbuffer.dequeue();
            _registerFile.setGPR16Bits(RAX,temp);
            cout<<"This is INT16h Function 10h, not Function 00h!"<<endl;
            break;
        case 0x11:
            if(!keyboardbuffer.isEmpty()){
                temp=keyboardbuffer[0];
                _registerFile.setGPR16Bits(RAX,temp);
                _registerFile.getFlagsBits().ZF=0;
            }
            else{
                _registerFile.setGPR16Bits(RAX,0x0000);
                _registerFile.getFlagsBits().ZF=1;
            }
            cout<<"This is INT16h Function 11h, not Function 01h!"<<endl;
            break;
        case 0x12:
            _registerFile.setGPR16Bits(RAX,shiftflagstatus);
            break;\
        default:
            cout<<"Can't use INT16h Function "<<hex<<func<<"h!"<<endl;
    }
}

void keyboardio::enq(u16 data)
{
    keyboardbuffer.enqueue(data);
}

u16 keyboardio::deq()
{
    return keyboardbuffer.dequeue();
}

void KeyBoard::toggleKeyGet(bool isShiftDown,bool isControlDown,bool isAltDown,bool isCapsLock,bool isNumLock,bool isScrollLock)
{
    keyio.getToggleKey(isShiftDown,isControlDown,isAltDown,isCapsLock,isNumLock,isScrollLock);
}

void KeyBoard::keyStatusGet(u16 characterCode, bool isPressed){
    if(isPressed == 0){
        if(characterCode == 0x5200){
            if(keyio.isinsert){
                keyio.isinsert=false;
                keyio.shiftflagstatus-=128;
            }
            else{
                keyio.isinsert=true;
                keyio.shiftflagstatus+=128;
            }
        }
        else{
            keyio.enq(characterCode);
        }
    }
}

u16 keyboardio::getbuffer()
{
    return keyboardbuffer.first();
}

