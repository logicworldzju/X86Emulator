#ifndef SERIAL_H
#define SERIAL_H

#include "io/ioport.h"

class Serial
{
public:
    Serial();
    IOPort& getIOPort(){return _ioPort;}
    u32 readFromPort(Memory &memory, RegisterFile &registerFile);
    void write2Port(u32 value, Memory &memory, RegisterFile &registerFile);
private:
    class SerialIOPort:public IOPort
    {
    public:
        SerialIOPort(Serial& serial):_serial(serial){}
        u32 readFromPort(Memory &memory, RegisterFile &registerFile){return _serial.readFromPort(memory,registerFile);}
        void write2Port(u32 value, Memory &memory, RegisterFile &registerFile){_serial.write2Port(value,memory,registerFile);}
    private:
        Serial& _serial;
    };
    SerialIOPort _ioPort;
};
#endif // SERIAL_H
