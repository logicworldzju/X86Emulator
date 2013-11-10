#ifndef GPREGISTER_H
#define GPREGISTER_H
#include "type.h"
#include <string.h>
class GPRegisterClass
{
public:
    GPRegisterClass()
    {
        ::memset(_reg,0,sizeof(_reg));
    }
    virtual u8 get8Bits()
    {
        return _reg[0];
    }
    virtual void set8Bits(u8 value)
    {
        _reg[0]=value;
    }
    //for example AL,CL,DL,BL
    virtual u8 get8BitsLow()
    {
        return get8Bits();
    }
    virtual void set8BitsLow(u8 value)
    {
        set8Bits(value);
    }
    //for example AH,CH,DH,BH
    virtual u8 get8BitsHigh()
    {
        return _reg[1];
    }
    virtual void set8BitsHigh(u8 value)
    {
        _reg[1]=value;
    }
    virtual u16 get16Bits()
    {
        return (_reg[1]<<8)+(_reg[0]<<1);
    }
    virtual void set16Bits(u16 value)
    {
        for(int i=0; i<2; i++)
        {
            _reg[i]=u8(value);
            value>>=8;
        }
    }
    virtual u32 get32Bits()
    {
        return (_reg[3]<<24)+(_reg[2]<<16)+(_reg[1]<<8)+(_reg[0]<<1);
    }
    virtual void set32Bits(u32 value)
    {
        for(int i=0; i<4; i++)
        {
            _reg[i]=u8(value);
            value>>=8;
        }
    }
    virtual u64 get64Bits()
    {
        u64 result=0;
        for(int i=7; i>=0; i--)
        {
            result=(result+_reg[i])<<8;
        }
        return result;
    }
    virtual void set64Bits(u64 value)
    {
        for(int i=0; i<8; i++)
        {
            _reg[i]=u8(value);
            value>>=8;
        }
    }
private:
    u8 _reg[8];
};

#endif // GPREGISTER_H
