#ifndef PIC_H
#define PIC_H

#include "io/ioport.h"

class PIC
{
public:
    PIC();
    IOPort& getIOPort(){return _ioPort;}
    u32 readFromPort20h(Memory &memory, RegisterFile &registerFile);
    void write2Port20h(u32 value, Memory &memory, RegisterFile &registerFile);
private:
    class PICIOPort:public IOPort
    {
    public:
        PICIOPort(PIC& pic):_pic(pic){}
        u32 readFromPort(Memory &memory, RegisterFile &registerFile){return _pic.readFromPort20h(memory,registerFile);}
        void write2Port(u32 value, Memory &memory, RegisterFile &registerFile){_pic.write2Port20h(value,memory,registerFile);}
    private:
        PIC& _pic;
    };
    PICIOPort _ioPort;
};

#endif // PIC_H
