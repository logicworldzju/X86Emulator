#ifndef INTERRUPT_H
#define INTERRUPT_H
#include "type.h"

class Interrupt
{
public:
    Interrupt()
    {
        _isInterrupt=false;
    }
    void set(u8 intVectorNumber)
    {
        _isInterrupt=true;
        _intVectorNumber = intVectorNumber;
    }
    void clear()
    {
        _isInterrupt = false;
    }
    s32 get()
    {
        if(_isInterrupt)
            return _intVectorNumber;
        else
            return -1;
    }
private:
    u8 _intVectorNumber;
    bool _isInterrupt;
};

#endif // INTERRUPT_H
