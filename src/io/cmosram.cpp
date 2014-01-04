#include "cmosram.h"
#include<QDebug>
#include <string.h>
CMOSRAM::CMOSRAM()
    :_indexIOPort(*this),_dataIOPort(*this)
{
    ::memset(_ram,0,sizeof(_ram));
}

u32 CMOSRAM::indexReadFromPort(Memory &memory, RegisterFile &registerFile)
{
    assert(0);
    return 0xcccccccc;
}

void CMOSRAM::indexWrite2Port(u32 value, Memory &memory, RegisterFile &registerFile)
{
    _index=u8(value&0x7f);
}

void CMOSRAM::dataWrite2Port(u32 value, Memory &memory, RegisterFile &registerFile)
{
    switch(_index)
    {
    case 0xa:
        assert(value==0x26);
        _ram[_index]=(u8)value;
        break;
    case 0xb:
        assert(value==2);
        _ram[_index]=(u8)value;
        break;
    default:
        qDebug()<<"out 0x71 called.";
        qDebug()<<"index:"<<(int)_index<<",value"<<value;
        assert(0);
    }
}

u32 CMOSRAM::dataReadFromPort(Memory &memory, RegisterFile &registerFile)
{
    switch(_index)
	{
	case 0xb:
		return 0x2;
		break;
	case 0xf:
		return 0;
		break;
	default:
        qDebug()<<"in 0x71 called.";
        qDebug()<<"index:"<<(int)_index;
        assert(0);
		break;
	}
}
