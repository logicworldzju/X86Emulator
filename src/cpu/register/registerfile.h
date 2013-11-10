#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#include "type.h"
#include "gpregister.h"
#include "flags.h"
#include <assert.h>
#include <string.h>
#include "cpu/cputype.h"
class RegisterFile
{
public:
    RegisterFile()
    {
        ::memset(_sementRegisters,0,sizeof(_sementRegisters));
        _ip=0;
    }
    //--------------------General Purpose Instruction---------
    //------General Purpose registers.---------
    //This is different from getGPR8BitsLow
    u8 getGPR8Bits(u8 index)
    {
        assert(index<8);
        if(index<4)
            return _gpRegisters[index].get8Bits();
        else
            return _gpRegisters[index-4].get8BitsHigh();
    }
    //This is different from setGPR8BitsLow
    void setGPR8Bits(u8 index,u8 value)
    {
        assert(index<8);
        if(index<4)
            _gpRegisters[index].set8Bits(value);
        else
            _gpRegisters[index-4].set8BitsHigh(value);
    }
    //for example AL,CL,DL,BL
    u8 getGPR8BitsLow(u8 index)
    {
        assert(index<16);
        return _gpRegisters[index].get8BitsLow();
    }
    void setGPR8BitsLow(u8 index,u8 value)
    {
        assert(index<16);
        _gpRegisters[index].set8BitsLow(value);
    }
    //for example AH,CH,DH,BH
    u8 getGPR8BitsHigh(u8 index)
    {
        assert(index<16);
        return _gpRegisters[index].get8BitsHigh();
    }
    void setGPR8BitsHigh(u8 index,u8 value)
    {
        assert(index<16);
        _gpRegisters[index].set8BitsHigh(value);
    }
    u16 getGPR16Bits(u8 index)
    {
        assert(index<16);
        return _gpRegisters[index].get16Bits();
    }
    void setGPR16Bits(u8 index,u16 value)
    {
        assert(index<16);
        _gpRegisters[index].set16Bits(value);
    }
    u32 getGPR32Bits(u8 index)
    {
        assert(index<16);
        return _gpRegisters[index].get32Bits();
    }
    void setGPR32Bits(u8 index,u32 value)
    {
        assert(index<16);
        _gpRegisters[index].set32Bits(value);
    }
    u64 getGPR64Bits(u8 index)
    {
        assert(index<16);
        return _gpRegisters[index].get64Bits();
    }
    void setGPR64Bits(u8 index,u64 value)
    {
        assert(index<16);
        _gpRegisters[index].set64Bits(value);
    }
    //-------------Segment Registers----------
    enum SegmentRegisterIndex
    {
        ES=0,CS,SS,DS,FS,GS
    };
    u16 getSR(u8 index)
    {
        assert(index<6);
        return _sementRegisters[index];
    }
    void setSR(u8 index,u16 value)
    {
        assert(index<6);
        _sementRegisters[index]=value;
    }
    //-------------------------System Instructions-------------
    //-------------------PC-------------------
    u32 getIP()
    {
        return _ip;
    }
    void setIP(u32 ip)
    {
        _ip = ip;
    }
    //------------------Flags-----------------
    FlagsBits& getFlagsBits()
    {
        return _flags.flagBits;
    }
    u32 getFlags32Bits()
    {
        return _flags.flags32Bits;
    }
    u16 getFlags16Bits()
    {
        return (u16)_flags.flags32Bits;
    }
    void setFlags32Bits(u32 flags)
    {
        _flags.flags32Bits=flags;
    }
    void setFlags16Bits(u16 flags)
    {
        _flags.flags32Bits=(_flags.flags32Bits&0xffff0000)|flags;
    }
    //---------------Control Registers--------
    //---------------Debug Registers----------
    //---------Descriptor-Table Registers-----
    //------------------Task Registers--------
    //------------------128-Bit Media Instructions-------------
    //-------------------64-Bit Media Instructions-------------
    //----------------X87 Floating-point Instructions----------
protected:
    GPRegisterClass _gpRegisters[16];
    u16 _sementRegisters[6];
    u32 _ip;
    Flags _flags;
};

#endif // REGISTERFILE_H
