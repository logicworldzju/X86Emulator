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
        std::cout<<"IOPortList:"<<"portNumber:"<<std::hex<<portNumber<<"h"<<std::endl;
        if(portNumber==0x20)
        {
            return;
        }
        if(portNumber==0x14)//serial
        {
            return;
        }
        if(portNumber==0x17)//parallel
        {
            return;
        }
        if(portNumber==0x70)//RAM DATA
        {
            int70Written=(u8)(value&0x7f);
            return;
        }
        if(portNumber==0x71)//RAM DATA
        {
            return;
        }
        if(portNumber==0x15)//system
        {
            return;
        }
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
        if(portNumber==0x71)//RAM DATA
        {
            switch(int70Written)
            {
            case 0xb:
                return 0x2;
                break;
            case 0xf:
                return 0;
                break;
            default:
                return 0;
                break;
            }
        }
        if(_ioPortList[portNumber])
            return _ioPortList[portNumber]->readFromPort(_memory,
                                                    _registerFile);
        else
        {
            std::cerr<<"Error:"<<"Didn't implement port:"<<std::hex<<portNumber<<"h"
                    <<" try to read"<<std::endl;
            std::cerr<<_registerFile.toString();
            ::exit(-1);
        }
    }
protected:
    IOPort** _ioPortList;
    Memory& _memory;
    RegisterFile& _registerFile;
private:
    u8 int70Written;
};

#endif // IOPORTLIST_H
