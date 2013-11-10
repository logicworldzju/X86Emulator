#ifndef IOPORT_H
#define IOPORT_H

#include "type.h"
#include "cpu/register/registerfile.h"
#include "memory/memory.h"


class IOPort
{
public:
    virtual void write2Port(u32 value,Memory& memory,
                            RegisterFile& registerFile);
    virtual u32 readFromPort(Memory& memory,
                             RegisterFile& registerFile);
};

#endif // IOPORT_H
