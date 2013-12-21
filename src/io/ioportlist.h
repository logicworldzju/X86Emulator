#ifndef IOPORTLIST_H
#define IOPORTLIST_H
#include "ioport.h"
#include <string.h>
#include <assert.h>
#include <iostream>
#include <stdlib.h>

class IOPortList
{
public:
    IOPortList(Memory& memory,RegisterFile& registerFile)
        :_memory(memory),_registerFile(registerFile)
    {
        _ioPortList = new IOPort*[1<<16];
        ::memset(_ioPortList,0,sizeof(IOPort*)*(1<<16));
    }
    ~IOPortList()
    {
        delete _ioPortList;
    }
    void add2PortList(u16 portNumber,IOPort* ioPort)
    {
        assert(!_ioPortList[portNumber]);
        _ioPortList[portNumber]=ioPort;
    }
public:
    void write2Port(u16 portNumber,u32 value)
    {
        if(_ioPortList[portNumber])
            _ioPortList[portNumber]->write2Port(value,_memory,
                                           _registerFile);
        else
        {
            std::cerr<<"Error:"<<"Didn't implement port:"<<portNumber
                    <<" try to write value:"<<value<<std::endl;
            std::cerr<<_registerFile.toString();
            ::exit(-1);
        }
    }
    u32 readFromPort(u16 portNumber)
    {
        if(_ioPortList[portNumber])
            return _ioPortList[portNumber]->readFromPort(_memory,
                                                    _registerFile);
        else
        {
            std::cerr<<"Error:"<<"Didn't implement port:"<<portNumber
                    <<" try to read"<<std::endl;
            std::cerr<<_registerFile.toString();
            ::exit(-1);
        }
    }
protected:
    IOPort** _ioPortList;
    Memory& _memory;
    RegisterFile& _registerFile;
};

#endif // IOPORTLIST_H
