#include "pic.h"
#include <assert.h>

PIC::PIC()
    :_ioPort(*this)
{
}

u32 PIC::readFromPort20h(Memory &memory, RegisterFile &registerFile)
{
    assert(0);
    return 0xcccccccc;
}

void PIC::write2Port20h(u32 value, Memory &memory, RegisterFile &registerFile)
{
    /*int tempC;
    int i;
    if (eCPU.al & 0x10)		// ICW1 ?
    {
    }
    else					// OCW2
    {
        tempC=eCPU.al & 0xe0;	// R、SL、EOI三位
        switch(tempC)
        {
        case 0x00:
        case 0x20:
            i=0;					// 把ISR中优先级最高的1恢复为0
            while (!(ISR & (1<<i)) && i<32)
                i++;
            if (i<32)
                ISR^=(1<<i);
            break;
        case 0x60:
            i=eCPU.al&0x07;			// 复位ISR中由L2L1L0指定的位
            ISR&=(1<<i);
            break;
        }
    }*/
    assert(value==0x20);
}
