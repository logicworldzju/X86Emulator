#include "systemservice.h"
#include <assert.h>
#include <QDebug>

SystemService::SystemService()
    :_ioPort(*this)
{
}

u32 SystemService::readFromPort(Memory &memory, RegisterFile &registerFile)
{
    assert(0);
    return 0xcccccccc;
}

void SystemService::write2Port(u32 value, Memory &memory, RegisterFile &registerFile)
{
    switch(registerFile.getGPR8BitsHigh(RAX))
    {
    case 0x24:
//        switch(eCPU.al)
        switch(registerFile.getGPR8BitsLow(RAX))
        {
        case 0x03:
//            (*(unsigned short*)((t=eCPU.ss,t<<=4)+eCPU.sp+4+MemoryStart))&=~CF;
            registerFile.getFlagsBits().CF=0;
//            eCPU.ah=0;
            registerFile.setGPR8BitsHigh(RAX,0);
//            eCPU.bx=3;
            registerFile.setGPR16Bits(RBX,3);
            break;
        default:
            assert(0);
        }
        assert(0);
        break;
    case 0x88://read extented memory size.
//        (*(unsigned short*)((t=eCPU.ss,t<<=4)+eCPU.sp+4+MemoryStart))&=~CF;
        registerFile.getFlagsBits().CF=0;
//        if (MemorySize>16)
//            eCPU.ax=0x3c00;
//        else
//            eCPU.ax=MemorySize*1024-256;
        registerFile.setGPR16Bits(RAX,0);
        break;
    case 0xd8:
//        (*(unsigned short*)((t=eCPU.ss,t<<=4)+eCPU.sp+4+MemoryStart))|=CF;
        registerFile.getFlagsBits().CF=0;
//        eCPU.ah=0x86;
        assert(0);
        break;
    case 0x41://unknow funciton.
        //acording to bochs.
        registerFile.setGPR8BitsHigh(RAX,0x86);
        registerFile.getFlagsBits().CF=1;
        break;
    default:
        qDebug()<<"int 15h function "<<hex<<(int)registerFile.getGPR8BitsHigh(RAX)<<"h called.";
        assert(0);
    }
}
