#ifndef DISKETTE_H
#define DISKETTE_H

#include "io/ioport.h"
#include "floppy.h"
#include <QObject>

class Diskette
{
public:
    Diskette(const std::string& floppyFileName0,
             const std::string& floppyFileName1);
    IOPort& getIOPort(){return _ioPort;}
    u32 readFromPort(Memory &memory, RegisterFile &registerFile);
    void write2Port(u32 value, Memory &memory, RegisterFile &registerFile);
private:
    class DisketteIOPort:public IOPort
    {
    public:
        DisketteIOPort(Diskette& diskette):_diskette(diskette){}
        u32 readFromPort(Memory &memory, RegisterFile &registerFile){return _diskette.readFromPort(memory,registerFile);}
        void write2Port(u32 value, Memory &memory, RegisterFile &registerFile){_diskette.write2Port(value,memory,registerFile);}
    private:
        Diskette& _diskette;
    };
    DisketteIOPort _ioPort;
    Floppy _floppy0;
    Floppy _floppy1;
};

#endif // DISKETTE_H
