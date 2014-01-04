#ifndef SYSTEMSERVICE_H
#define SYSTEMSERVICE_H

#include "io/ioport.h"

class SystemService
{
public:
    SystemService();
    IOPort& getIOPort(){return _ioPort;}
    u32 readFromPort(Memory &memory, RegisterFile &registerFile);
    void write2Port(u32 value, Memory &memory, RegisterFile &registerFile);
private:
    class SystemServiceIOPort:public IOPort
    {
    public:
        SystemServiceIOPort(SystemService& systemService):_systemService(systemService){}
        u32 readFromPort(Memory &memory, RegisterFile &registerFile){return _systemService.readFromPort(memory,registerFile);}
        void write2Port(u32 value, Memory &memory, RegisterFile &registerFile){_systemService.write2Port(value,memory,registerFile);}
    private:
        SystemService& _systemService;
    };
    SystemServiceIOPort _ioPort;
};

#endif // SYSTEMSERVICE_H
