#ifndef FLAGS_H
#define FLAGS_H
#include "type.h"
#include <string>
#include <sstream>

struct FlagsBits
{
    u32 CF:1;//0
    u32 :1;//1
    u32 PF:1;//2
    u32 :1;//3
    u32 AF:1;//4
    u32 :1;//5
    u32 ZF:1;//6
    u32 SF:1;//7
    u32 TF:1;//8
    u32 IF:1;//9
    u32 DF:1;//10
    u32 OF:1;//11
    u32 IOPL:2;//12,13
    u32 NT:1;//14
    u32 :1;//15
    u32 RF:1;//16
    u32 VM:1;//17
    u32 AC:1;//18
    u32 VIF:1;//19
    u32 VIP:1;//20
    u32 ID:1;//21
    std::string toString()
    {
        std::ostringstream stream;
        stream<<"CF:"<<CF<<" ";
        stream<<"PF:"<<PF<<" ";
        stream<<"AF:"<<AF<<" ";
        stream<<"ZF:"<<ZF<<" ";
        stream<<"SF:"<<SF<<" ";
        stream<<"TF:"<<TF<<" ";
        stream<<"IF:"<<IF<<" ";
        stream<<"DF:"<<DF<<std::endl;
        stream<<"OF:"<<OF<<" ";
        stream<<"IOPL:"<<IOPL<<" ";
        stream<<"NT:"<<NT<<" ";
        stream<<"RF:"<<RF<<" ";
        stream<<"VM:"<<VM<<" ";
        stream<<"AC:"<<AC<<" ";
        stream<<"VIF:"<<VIF<<" ";
        stream<<"VIP:"<<VIP<<" ";
        stream<<"ID:"<<ID<<std::endl;

        return stream.str();
    }
};
union Flags
{
    FlagsBits flagBits;
//        u64 flags64Bits; a problem here the lower 32 bits is
    //flags32Bits in the big endian system?It doesn't seem so.
    u32 flags32Bits;
    //u16 flags16Bits;
    Flags()
    {
        flags32Bits=0;
    }
};

#endif // FLAGS_H
