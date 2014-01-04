#ifndef IOPORTLIST_H
#define IOPORTLIST_H
#include "ioport.h"
#include <string.h>
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <QDebug>

class IOPortList
{
public:
    IOPortList(Memory& memory,RegisterFile& registerFile)
        :_memory(memory),_registerFile(registerFile)
    {
        _ioPortList = new IOPort*[1<<16];
        ::memset(_ioPortList,0,sizeof(IOPort*)*(1<<16));

//        int70Written=0;
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
        qDebug("IOPortList:portNumber:%xh",portNumber);//<<"IOPortList:"<<"portNumber:"<<QDebug::hex<<portNumber<<"h";
        qDebug()<<_registerFile.toString().c_str();
        if(portNumber==0x2f2 || portNumber==0x2f3 || portNumber==0x2f4 || portNumber==0x2f5|| portNumber==0x2f6|| portNumber==0x2f7)
        {
            return;
        }
        if(portNumber==0x61)
        {
            return ;
        }
        if(portNumber==0x40)
        {
            return ;
        }
        if(portNumber==0x3d4)//Video CRTC index register
        {
            return;
        }
        if(portNumber==0x3d5)//Other video CRTC registers
        {
            return ;
        }
        if(portNumber==0x3d8)//CGA mode control register
        {
            return ;
        }
        if(portNumber==0x3d9)//CGA palette register
        {
            return;
        }
        if(_ioPortList[portNumber])
            _ioPortList[portNumber]->write2Port(value,_memory,
                                           _registerFile);
        else
        {
            std::cerr<<"Error:"<<"Didn't implement port:"<<std::hex<<portNumber
                    <<"h try to write value:"<<std::hex<<value<<"h"<<std::endl;
            std::cerr<<_registerFile.toString();
            ::exit(-1);
        }
    }
    u32 readFromPort(u16 portNumber)
    {
        if(portNumber==0x21)
        {
            return 0xcccccccc;
        }
        if(portNumber==0x61)
        {
            return 0xcccccccc;
        }
        if(portNumber==0x3d5)//Other video CRTC registers
        {
            return 0xcccccccc;
        }
        if(portNumber==0x3da)
        {
            return 0xcccccccc;
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
//private:
//    u8 int70Written;
};

#endif // IOPORTLIST_H
