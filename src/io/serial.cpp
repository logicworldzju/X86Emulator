#include "serial.h"
#include <assert.h>
#include <QDebug>


Serial::Serial()
    :_ioPort(*this)
{
}

u32 Serial::readFromPort(Memory &memory, RegisterFile &registerFile)
{
    assert(0);
    return 0xcccccccc;
}

void Serial::write2Port(u32 value, Memory &memory, RegisterFile &registerFile)
{
    (void)value;(void)memory;(void)registerFile;
    qDebug()<<"Serial:write2Port"<<endl;
//    qDebug()<<registerFile.toString().c_str();
    switch(registerFile.getGPR8BitsHigh(RAX))
    {
    case 0x00:
        qDebug("Serial:Initial serial adapter.parameter:%xh,port:%xh",registerFile.getGPR8BitsLow(RAX),registerFile.getGPR16Bits(RDX));
        registerFile.setGPR16Bits(RAX,0);
        break;
    case 0x1:
        qDebug("Serial:Send %c",registerFile.getGPR8BitsLow(RAX));
        registerFile.setGPR8BitsHigh(RAX,0);
        break;
    default:
        assert(0);
    }
}
