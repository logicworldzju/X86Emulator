#include "execute.h"
#include <iostream>
#include <stdlib.h>
#include "cpu/executer/operand/execmemoryoperand.h"
//---------------------------Set Flags Function----------------------------------
inline u8 getCarryFlag(u8 msbOpt1,u8 msbOpt2,bool isPlus,u8 msbResult)
{
    u8 CF=0;
    if(isPlus)
    {
        if(msbOpt1!=0 && msbOpt2!=0)
        {
            CF=1;
        }
        else if(msbOpt1==0 && msbOpt2==0)
        {
            CF=0;
        }
        else
        {
            if(msbResult==0)
            {
                CF=1;
            }
            else
            {
                CF=0;
            }
        }
    }
    else
    {
        if(msbOpt1!=0 && msbOpt2==0)
        {
            CF=0;
        }
        else if(msbOpt1==0 && msbOpt2!=0)
        {
            CF=1;
        }
        else
        {
            if(msbOpt1==0 && msbOpt2==0)
            {
                if(msbResult==0)
                {
                    CF=0;
                }
                else
                {
                    CF=1;
                }
            }
            else
            {
                if(msbResult==0)
                {
                    CF=0;
                }
                else
                {
                    CF=1;
                }
            }
        }
    }
    return CF;
}
inline void setCarryFlag(FlagsBits& flags,u8 msbOpt1,u8 msbOpt2,bool isPlus,u8 msbResult)
{
    flags.CF=getCarryFlag(msbOpt1,msbOpt2,isPlus,msbResult);
}
inline void setParityFlag(FlagsBits& flags,u8 lsbResult)
{
    u8 result=1;
    for(int i=0; i<8; i++)
        result^=((lsbResult>>i)&0x1);
    flags.PF=result;
}
inline void setAuxiliaryCarryFlag(FlagsBits& flags,u8 bit3Opt1,u8 bit3Opt2,bool isPlus,u8 bit3Result)
{
    flags.AF=getCarryFlag(bit3Opt1,bit3Opt2,isPlus,bit3Result);
}
template<typename T>
inline void setZeroFlag(FlagsBits& flags,T result)
{
    flags.ZF=(result==0?1:0);
}
inline void setSignFlag(FlagsBits& flags,u8 msbResult)
{
    flags.SF=msbResult;
}
inline void setOverflowFlag(FlagsBits& flags,u8 msbOpt1,u8 msbOpt2,bool isPlus,u8 msbResult)
{
    if(!isPlus) msbOpt2=(msbOpt2==0?1:0);
    if(msbOpt1==msbOpt2)
    {
        if(msbResult==msbOpt1)
        {
            flags.OF=0;
        }
        else
        {
            flags.OF=1;
        }
    }
    else
    {
        flags.OF=0;
    }
}
//------------------------------------------------------------------------------
#define INSTRUCTION_NOT_IMPLEMENT(name) std::cerr<<"Error:Instruction not implement:"<<name<<std::endl;::exit(-1)

//------------------------------------------------------------------------------
//0x0
EXECUTE_FUNC(executeADD)
{
    (void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;
    (void)ioPortList;(void)memory;(void)operatingEnvironment;(void)src2;

    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        s8 opt1=dest->getS8();
        s8 opt2=src->getS8();
        s8 result=opt1+opt2;
        dest->setU8(result);

        u8 msbOpt1=u8((opt1>>7)&1);
        u8 msbOpt2=u8((opt2>>7)&1);
        u8 msbResult=u8((result>>7)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),true,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        break;
    }
    case DATA_SIZE_WORD:
    {
        s16 opt1=dest->getS16();
        s16 opt2=src->getS16();
        s16 result=opt1+opt2;
        dest->setU16(result);

        u8 msbOpt1=u8((opt1>>15)&1);
        u8 msbOpt2=u8((opt2>>15)&1);
        u8 msbResult=u8((result>>15)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),true,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        s32 opt1=dest->getS32();
        s32 opt2=src->getS32();
        s32 result=opt1+opt2;
        dest->setU32(result);

        u8 msbOpt1=u8((opt1>>31)&1);
        u8 msbOpt2=u8((opt2>>31)&1);
        u8 msbResult=u8((result>>31)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),true,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        break;
    }
    case DATA_SIZE_QWORD:
    {
        s64 opt1=dest->getS64();
        s64 opt2=src->getS64();
        s64 result=opt1+opt2;
        dest->setU64(result);

        u8 msbOpt1=u8((opt1>>63)&1);
        u8 msbOpt2=u8((opt2>>63)&1);
        u8 msbResult=u8((result>>63)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),true,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        break;
    }
    default:
        assert(0);
    }
}
template <typename T>
void PUSH(T value,EffectiveSize effectiveAddressSize,Memory& memory,RegisterFile& registerFile)
{
    assert(sizeof(T)==2 || sizeof(T)==4 || sizeof(T)==8);
    u8 dataSize=sizeof(T);

    //get memory address.
    u32 address=registerFile.getSSR(SS);
    switch(effectiveAddressSize)
    {
    case EFFECTIVE_16_BITS:
        address+=registerFile.getGPR16Bits(RSP)-dataSize;
        break;
    case EFFECTIVE_32_BITS:
    case EFFECTIVE_64_BITS:
        address+=registerFile.getGPR32Bits(RSP)-dataSize;
        break;
    }

    //write memory.
    memory.startAccess(memory.CPU_DATA_ACCESS);
    switch(sizeof(T))
    {
    case 2:
        memory.set16Bits(address,value);
        break;
    case 4:
        memory.set32Bits(address,value);
        break;
    case 8:
        memory.set64Bits(address,value);
        break;
    default:
        assert(0);
    }
    memory.endAccess();

    //write rsp.
    switch(effectiveAddressSize)
    {
    case EFFECTIVE_16_BITS:
        registerFile.setGPR16Bits(RSP,registerFile.getGPR16Bits(RSP)-dataSize);
        break;
    case EFFECTIVE_32_BITS:
    case EFFECTIVE_64_BITS:
        registerFile.setGPR32Bits(RSP,registerFile.getGPR32Bits(RSP)-dataSize);
        break;
    }

}

EXECUTE_FUNC(executePUSH)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("PUSH");
    //get data size.
    switch(dest->getSize())
    {
    case DATA_SIZE_WORD:
        PUSH<u16>(dest->getU16(),effectiveAddressSize,memory,registerFile);
        break;
    case DATA_SIZE_DWORD:
        PUSH<u32>(dest->getU32(),effectiveAddressSize,memory,registerFile);
        break;
    case DATA_SIZE_QWORD:
        PUSH<u64>(dest->getU64(),effectiveAddressSize,memory,registerFile);
        break;
    default:
        assert(0);
    }
}
template<typename T>
void POP(T& value,EffectiveSize effectiveAddressSize,Memory& memory,RegisterFile& registerFile)
{
    assert(sizeof(T)==2 || sizeof(T)==4 || sizeof(T)==8);
    u32 address=registerFile.getSSR(SS);
    u8 dataSize=sizeof(T);
    switch(effectiveAddressSize)
    {
    case EFFECTIVE_16_BITS:
        address+=registerFile.getGPR16Bits(RSP);
        registerFile.setGPR16Bits(RSP,registerFile.getGPR16Bits(RSP)+dataSize);
        break;
    case EFFECTIVE_32_BITS:
    case EFFECTIVE_64_BITS:
        address+=registerFile.getGPR32Bits(RSP);
        registerFile.setGPR32Bits(RSP,registerFile.getGPR32Bits(RSP)+dataSize);
        break;
    }

    memory.startAccess(memory.CPU_DATA_ACCESS);
    switch(sizeof(T))
    {
    case 2:
        value=(memory.get16Bits(address));
        break;
    case 4:
        value=(memory.get32Bits(address));
        break;
    case 8:
        value=(memory.get64Bits(address));
        break;
    default:
        assert(0);
    }
    memory.endAccess();


}

EXECUTE_FUNC(executePOP)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("POP");
    switch(dest->getSize())
    {
    case DATA_SIZE_WORD:
    {
        u16 value;
        POP<u16>(value,effectiveAddressSize,memory,registerFile);
        dest->setU16(value);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        u32 value;
        POP<u32>(value,effectiveAddressSize,memory,registerFile);
        dest->setU32(value);
        break;
    }
    case DATA_SIZE_QWORD:
    {
        u64 value;
        POP<u64>(value,effectiveAddressSize,memory,registerFile);
        dest->setU64(value);
        break;
    }
    default:
        assert(0);
    }
}

EXECUTE_FUNC(executeOR)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("OR");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        s8 opt1=dest->getS8();
        s8 opt2=src->getS8();
        s8 result=opt1|opt2;
        dest->setU8(result);

        u8 msbResult=u8((result>>7)&1);
        registerFile.getFlagsBits().CF=0;
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        registerFile.getFlagsBits().AF=0;
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        registerFile.getFlagsBits().OF=0;
        break;
    }
    case DATA_SIZE_WORD:
    {
        s16 opt1=dest->getS16();
        s16 opt2=src->getS16();
        s16 result=opt1|opt2;
        dest->setU16(result);

        u8 msbResult=u8((result>>15)&1);
        registerFile.getFlagsBits().CF=0;
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        registerFile.getFlagsBits().AF=0;
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        registerFile.getFlagsBits().OF=0;
        break;
    }
    case DATA_SIZE_DWORD:
    {
        s32 opt1=dest->getS32();
        s32 opt2=src->getS32();
        s32 result=opt1|opt2;
        dest->setU32(result);

        u8 msbResult=u8((result>>31)&1);
        registerFile.getFlagsBits().CF=0;
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        registerFile.getFlagsBits().AF=0;
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        registerFile.getFlagsBits().OF=0;
        break;
    }
    case DATA_SIZE_QWORD:
    {
        s64 opt1=dest->getS64();
        s64 opt2=src->getS64();
        s64 result=opt1|opt2;
        dest->setU64(result);

        u8 msbResult=u8((result>>63)&1);
        registerFile.getFlagsBits().CF=0;
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        registerFile.getFlagsBits().AF=0;
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        registerFile.getFlagsBits().OF=0;
        break;
    }
    default:
        assert(0);
    }
}

//0x1

EXECUTE_FUNC(executeADC)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("ADC");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        s8 opt1=dest->getS8();
        s8 opt2=src->getS8();
        s8 result=opt1+opt2+s8(registerFile.getFlagsBits().CF);
        dest->setU8(result);

        u8 msbOpt1=u8((opt1>>7)&1);
        u8 msbOpt2=u8((opt2>>7)&1);
        u8 msbResult=u8((result>>7)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),true,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        break;
    }
    case DATA_SIZE_WORD:
    {
        s16 opt1=dest->getS16();
        s16 opt2=src->getS16();
        s16 result=opt1+opt2+s16(registerFile.getFlagsBits().CF);
        dest->setU16(result);

        u8 msbOpt1=u8((opt1>>15)&1);
        u8 msbOpt2=u8((opt2>>15)&1);
        u8 msbResult=u8((result>>15)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),true,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        s32 opt1=dest->getS32();
        s32 opt2=src->getS32();
        s32 result=opt1+opt2+s32(registerFile.getFlagsBits().CF);
        dest->setU32(result);

        u8 msbOpt1=u8((opt1>>31)&1);
        u8 msbOpt2=u8((opt2>>31)&1);
        u8 msbResult=u8((result>>31)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),true,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        break;
    }
    case DATA_SIZE_QWORD:
    {
        s64 opt1=dest->getS64();
        s64 opt2=src->getS64();
        s64 result=opt1+opt2+s64(registerFile.getFlagsBits().CF);
        dest->setU64(result);

        u8 msbOpt1=u8((opt1>>63)&1);
        u8 msbOpt2=u8((opt2>>63)&1);
        u8 msbResult=u8((result>>63)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),true,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        break;
    }
    default:
        assert(0);
    }
}

EXECUTE_FUNC(executeSBB)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("SBB");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        s8 opt1=dest->getS8();
        s8 opt2=src->getS8();
        s8 result=opt1-opt2-s8(registerFile.getFlagsBits().CF);
        dest->setU8(result);

        u8 msbOpt1=u8((opt1>>7)&1);
        u8 msbOpt2=u8((opt2>>7)&1);
        u8 msbResult=u8((result>>7)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    case DATA_SIZE_WORD:
    {
        s16 opt1=dest->getS16();
        s16 opt2=src->getS16();
        s16 result=opt1-opt2-s16(registerFile.getFlagsBits().CF);
        dest->setU16(result);

        u8 msbOpt1=u8((opt1>>15)&1);
        u8 msbOpt2=u8((opt2>>15)&1);
        u8 msbResult=u8((result>>15)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        s32 opt1=dest->getS32();
        s32 opt2=src->getS32();
        s32 result=opt1-opt2-s32(registerFile.getFlagsBits().CF);
        dest->setU32(result);

        u8 msbOpt1=u8((opt1>>31)&1);
        u8 msbOpt2=u8((opt2>>31)&1);
        u8 msbResult=u8((result>>31)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    case DATA_SIZE_QWORD:
    {
        s64 opt1=dest->getS64();
        s64 opt2=src->getS64();
        s64 result=opt1-opt2-s64(registerFile.getFlagsBits().CF);
        dest->setU64(result);

        u8 msbOpt1=u8((opt1>>63)&1);
        u8 msbOpt2=u8((opt2>>63)&1);
        u8 msbResult=u8((result>>63)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    default:
        assert(0);
    }
}

//0x2

EXECUTE_FUNC(executeAND)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("AND");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        s8 opt1=dest->getS8();
        s8 opt2=src->getS8();
        s8 result=opt1&opt2;
        dest->setU8(result);

        u8 msbResult=u8((result>>7)&1);
        registerFile.getFlagsBits().CF=0;
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        registerFile.getFlagsBits().AF=0;
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        registerFile.getFlagsBits().OF=0;
        break;
    }
    case DATA_SIZE_WORD:
    {
        s16 opt1=dest->getS16();
        s16 opt2=src->getS16();
        s16 result=opt1&opt2;
        dest->setU16(result);

        u8 msbResult=u8((result>>15)&1);
        registerFile.getFlagsBits().CF=0;
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        registerFile.getFlagsBits().AF=0;
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        registerFile.getFlagsBits().OF=0;
        break;
    }
    case DATA_SIZE_DWORD:
    {
        s32 opt1=dest->getS32();
        s32 opt2=src->getS32();
        s32 result=opt1&opt2;
        dest->setU32(result);

        u8 msbResult=u8((result>>31)&1);
        registerFile.getFlagsBits().CF=0;
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        registerFile.getFlagsBits().AF=0;
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        registerFile.getFlagsBits().OF=0;
        break;
    }
    case DATA_SIZE_QWORD:
    {
        s64 opt1=dest->getS64();
        s64 opt2=src->getS64();
        s64 result=opt1&opt2;
        dest->setU64(result);

        u8 msbResult=u8((result>>63)&1);
        registerFile.getFlagsBits().CF=0;
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        registerFile.getFlagsBits().AF=0;
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        registerFile.getFlagsBits().OF=0;
        break;
    }
    default:
        assert(0);
    }
}

EXECUTE_FUNC(executeDAA)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("DAA");
}

EXECUTE_FUNC(executeSUB)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("SUB");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        s8 opt1=dest->getS8();
        s8 opt2=src->getS8();
        s8 result=opt1-opt2;
        dest->setU8(result);

        u8 msbOpt1=u8((opt1>>7)&1);
        u8 msbOpt2=u8((opt2>>7)&1);
        u8 msbResult=u8((result>>7)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    case DATA_SIZE_WORD:
    {
        s16 opt1=dest->getS16();
        s16 opt2=src->getS16();
        s16 result=opt1-opt2;
        dest->setU16(result);

        u8 msbOpt1=u8((opt1>>15)&1);
        u8 msbOpt2=u8((opt2>>15)&1);
        u8 msbResult=u8((result>>15)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        s32 opt1=dest->getS32();
        s32 opt2=src->getS32();
        s32 result=opt1-opt2;
        dest->setU32(result);

        u8 msbOpt1=u8((opt1>>31)&1);
        u8 msbOpt2=u8((opt2>>31)&1);
        u8 msbResult=u8((result>>31)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    case DATA_SIZE_QWORD:
    {
        s64 opt1=dest->getS64();
        s64 opt2=src->getS64();
        s64 result=opt1-opt2;
        dest->setU64(result);

        u8 msbOpt1=u8((opt1>>63)&1);
        u8 msbOpt2=u8((opt2>>63)&1);
        u8 msbResult=u8((result>>63)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    default:
        assert(0);
    }
}

EXECUTE_FUNC(executeDAS)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("DAS");
}

//0x3

EXECUTE_FUNC(executeXOR)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("XOR");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        s8 opt1=dest->getS8();
        s8 opt2=src->getS8();
        s8 result=opt1^opt2;
        dest->setU8(result);

        u8 msbResult=u8((result>>7)&1);
        registerFile.getFlagsBits().CF=0;
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        registerFile.getFlagsBits().AF=0;
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        registerFile.getFlagsBits().OF=0;
        break;
    }
    case DATA_SIZE_WORD:
    {
        s16 opt1=dest->getS16();
        s16 opt2=src->getS16();
        s16 result=opt1^opt2;
        dest->setU16(result);

        u8 msbResult=u8((result>>15)&1);
        registerFile.getFlagsBits().CF=0;
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        registerFile.getFlagsBits().AF=0;
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        registerFile.getFlagsBits().OF=0;
        break;
    }
    case DATA_SIZE_DWORD:
    {
        s32 opt1=dest->getS32();
        s32 opt2=src->getS32();
        s32 result=opt1^opt2;
        dest->setU32(result);

        u8 msbResult=u8((result>>31)&1);
        registerFile.getFlagsBits().CF=0;
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        registerFile.getFlagsBits().AF=0;
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        registerFile.getFlagsBits().OF=0;
        break;
    }
    case DATA_SIZE_QWORD:
    {
        s64 opt1=dest->getS64();
        s64 opt2=src->getS64();
        s64 result=opt1^opt2;
        dest->setU64(result);

        u8 msbResult=u8((result>>63)&1);
        registerFile.getFlagsBits().CF=0;
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        registerFile.getFlagsBits().AF=0;
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        registerFile.getFlagsBits().OF=0;
        break;
    }
    default:
        assert(0);
    }

}

EXECUTE_FUNC(executeAAA)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("AAA");
}
void CMP(ExecReadWriteOperand* dest,ExecReadWriteOperand* src,RegisterFile& registerFile)
{
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        s8 opt1=dest->getS8();
        s8 opt2=src->getS8();
        s8 result=opt1-opt2;
//        dest->setU8(result);

        u8 msbOpt1=u8((opt1>>7)&1);
        u8 msbOpt2=u8((opt2>>7)&1);
        u8 msbResult=u8((result>>7)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    case DATA_SIZE_WORD:
    {
        s16 opt1=dest->getS16();
        s16 opt2=src->getS16();
        s16 result=opt1-opt2;
//        dest->setU16(result);

        u8 msbOpt1=u8((opt1>>15)&1);
        u8 msbOpt2=u8((opt2>>15)&1);
        u8 msbResult=u8((result>>15)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        s32 opt1=dest->getS32();
        s32 opt2=src->getS32();
        s32 result=opt1-opt2;
//        dest->setU32(result);

        u8 msbOpt1=u8((opt1>>31)&1);
        u8 msbOpt2=u8((opt2>>31)&1);
        u8 msbResult=u8((result>>31)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    case DATA_SIZE_QWORD:
    {
        s64 opt1=dest->getS64();
        s64 opt2=src->getS64();
        s64 result=opt1-opt2;
//        dest->setU64(result);

        u8 msbOpt1=u8((opt1>>63)&1);
        u8 msbOpt2=u8((opt2>>63)&1);
        u8 msbResult=u8((result>>63)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    default:
        assert(0);
    }
}
EXECUTE_FUNC(executeCMP)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("CMP");
    CMP(dest,src,registerFile);
}

EXECUTE_FUNC(executeAAS)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("AAS");
}

//0x4

EXECUTE_FUNC(executeINC)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("INC");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        s8 opt1=dest->getS8();
        s8 opt2=1;
        s8 result=opt1+opt2;
        dest->setU8(result);

        u8 msbOpt1=u8((opt1>>7)&1);
        u8 msbOpt2=u8((opt2>>7)&1);
        u8 msbResult=u8((result>>7)&1);
//        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),true,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        break;
    }
    case DATA_SIZE_WORD:
    {
        s16 opt1=dest->getS16();
        s16 opt2=1;
        s16 result=opt1+opt2;
        dest->setU16(result);

        u8 msbOpt1=u8((opt1>>15)&1);
        u8 msbOpt2=u8((opt2>>15)&1);
        u8 msbResult=u8((result>>15)&1);
//        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),true,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        s32 opt1=dest->getS32();
        s32 opt2=1;
        s32 result=opt1+opt2;
        dest->setU32(result);

        u8 msbOpt1=u8((opt1>>31)&1);
        u8 msbOpt2=u8((opt2>>31)&1);
        u8 msbResult=u8((result>>31)&1);
//        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),true,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        break;
    }
    case DATA_SIZE_QWORD:
    {
        s64 opt1=dest->getS64();
        s64 opt2=1;
        s64 result=opt1+opt2;
        dest->setU64(result);

        u8 msbOpt1=u8((opt1>>63)&1);
        u8 msbOpt2=u8((opt2>>63)&1);
        u8 msbResult=u8((result>>63)&1);
//        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),true,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,true,msbResult);
        break;
    }
    default:
        assert(0);
    }

}

EXECUTE_FUNC(executeDEC)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("DEC");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        s8 opt1=dest->getS8();
        s8 opt2=1;
        s8 result=opt1-opt2;
        dest->setU8(result);

        u8 msbOpt1=u8((opt1>>7)&1);
        u8 msbOpt2=u8((opt2>>7)&1);
        u8 msbResult=u8((result>>7)&1);
//        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    case DATA_SIZE_WORD:
    {
        s16 opt1=dest->getS16();
        s16 opt2=1;
        s16 result=opt1-opt2;
        dest->setU16(result);

        u8 msbOpt1=u8((opt1>>15)&1);
        u8 msbOpt2=u8((opt2>>15)&1);
        u8 msbResult=u8((result>>15)&1);
//        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        s32 opt1=dest->getS32();
        s32 opt2=1;
        s32 result=opt1-opt2;
        dest->setU32(result);

        u8 msbOpt1=u8((opt1>>31)&1);
        u8 msbOpt2=u8((opt2>>31)&1);
        u8 msbResult=u8((result>>31)&1);
//        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    case DATA_SIZE_QWORD:
    {
        s64 opt1=dest->getS64();
        s64 opt2=1;
        s64 result=opt1-opt2;
        dest->setU64(result);

        u8 msbOpt1=u8((opt1>>63)&1);
        u8 msbOpt2=u8((opt2>>63)&1);
        u8 msbResult=u8((result>>63)&1);
//        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    default:
        assert(0);
    }
}

//0x5
//0x6

EXECUTE_FUNC(executePUSHAD)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("PUSHAD");
}

EXECUTE_FUNC(executePOPAD)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("POPAD");
}

EXECUTE_FUNC(executeBOUND)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("BOUND");
}

EXECUTE_FUNC(executeARPL)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("ARPL");
}

EXECUTE_FUNC(executeIMUL3) //IMUL with 3 operands.
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("IMUL3");
    switch(dest->getSize())
    {
    case DATA_SIZE_WORD:
    {
        s32 a=src->getS16();
        s32 b=src2->getS16();
        s32 c=a*b;
        s16 result=c&0xffff;
        dest->setU16(result);
        if(result==c)
        {
           registerFile.getFlagsBits().OF=0;
           registerFile.getFlagsBits().CF=0;
        }
        else
        {
            registerFile.getFlagsBits().OF=1;
            registerFile.getFlagsBits().CF=1;
        }
        break;
    }
    case DATA_SIZE_DWORD:
    {
        s64 a=src->getS32();
        s64 b=src2->getS32();
        s64 c=a*b;
        s32 result=c&0xffffffff;
        dest->setU32(result);
        if(result==c)
        {
           registerFile.getFlagsBits().OF=0;
           registerFile.getFlagsBits().CF=0;
        }
        else
        {
            registerFile.getFlagsBits().OF=1;
            registerFile.getFlagsBits().CF=1;
        }
        break;
    }
    case DATA_SIZE_QWORD:
        assert(0);
        break;
    default:
        assert(0);
    }
}

EXECUTE_FUNC(executeINSB)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("INSB");
}

EXECUTE_FUNC(executeINSWD)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("INSWD");
}

EXECUTE_FUNC(executeOUTSB)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("OUTB");
}

EXECUTE_FUNC(executeOUTSWD)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("OUTSWD");
}

void JUMP(EffectiveSize effectiveOperandSize,ExecReadWriteOperand* dest,RegisterFile& registerFile)
{
    switch(effectiveOperandSize)
    {
    case EFFECTIVE_16_BITS:
    {
        u32 ip=registerFile.getIP();
        u16 lowIP=u16(ip&0xffff);
        u16 finalLowIP=lowIP+dest->getS16();
//        u32 finalIP=(ip&0xffff0000)|finalLowIP;
        registerFile.setIP(finalLowIP);
        break;
    }
    case EFFECTIVE_32_BITS:
    case EFFECTIVE_64_BITS:
    {
        u32 ip=registerFile.getIP();
        u32 finalIP=ip+dest->getS32();
        registerFile.setIP(finalIP);
        break;
    }
    }
}

//0x7

EXECUTE_FUNC(executeJO)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JO");
    if(registerFile.getFlagsBits().OF==1)
    {
        JUMP(effectiveOperandSize,dest,registerFile);
    }
}

EXECUTE_FUNC(executeJNO)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JNO");
    if(registerFile.getFlagsBits().OF==0)
    {
        JUMP(effectiveOperandSize,dest,registerFile);
    }
}

EXECUTE_FUNC(executeJB)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JB");
    if(registerFile.getFlagsBits().CF==1)
    {
        JUMP(effectiveOperandSize,dest,registerFile);
    }
}

EXECUTE_FUNC(executeJNB)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JNB");
    if(registerFile.getFlagsBits().CF==0)
    {
        JUMP(effectiveOperandSize,dest,registerFile);
    }
}

EXECUTE_FUNC(executeJZ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JZ");
    if(registerFile.getFlagsBits().ZF==1)
    {
        JUMP(effectiveOperandSize,dest,registerFile);
    }
}

EXECUTE_FUNC(executeJNZ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JNZ");
    if(registerFile.getFlagsBits().ZF==0)
    {
        JUMP(effectiveOperandSize,dest,registerFile);
    }
}

EXECUTE_FUNC(executeJBE)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JBE");
    if(registerFile.getFlagsBits().CF==1 || registerFile.getFlagsBits().ZF==1)
    {
        JUMP(effectiveOperandSize,dest,registerFile);
    }
}

EXECUTE_FUNC(executeJNBE)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JNBE");
    if(registerFile.getFlagsBits().CF==0 && registerFile.getFlagsBits().ZF==0)
    {
        JUMP(effectiveOperandSize,dest,registerFile);
    }
}

EXECUTE_FUNC(executeJS)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JS");
    if(registerFile.getFlagsBits().SF==1)
    {
        JUMP(effectiveOperandSize,dest,registerFile);
    }
}

EXECUTE_FUNC(executeJNS)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JNS");
    if(registerFile.getFlagsBits().SF==0)
    {
        JUMP(effectiveOperandSize,dest,registerFile);
    }
}

EXECUTE_FUNC(executeJP)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JP");
    if(registerFile.getFlagsBits().PF==1)
    {
        JUMP(effectiveOperandSize,dest,registerFile);
    }
}

EXECUTE_FUNC(executeJNP)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JNP");
    if(registerFile.getFlagsBits().PF==0)
    {
        JUMP(effectiveOperandSize,dest,registerFile);
    }
}

EXECUTE_FUNC(executeJL)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JL");
    if(registerFile.getFlagsBits().SF!=registerFile.getFlagsBits().OF)
    {
        JUMP(effectiveOperandSize,dest,registerFile);
    }
}

EXECUTE_FUNC(executeJNL)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JNL");
    if(registerFile.getFlagsBits().SF==registerFile.getFlagsBits().OF)
    {
        JUMP(effectiveOperandSize,dest,registerFile);
    }
}

EXECUTE_FUNC(executeJLE)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JLE");
    if(registerFile.getFlagsBits().SF!=registerFile.getFlagsBits().OF || registerFile.getFlagsBits().ZF==1)
    {
        JUMP(effectiveOperandSize,dest,registerFile);
    }
}

EXECUTE_FUNC(executeJNLE)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JNLE");
    if(registerFile.getFlagsBits().SF==registerFile.getFlagsBits().OF && registerFile.getFlagsBits().ZF==0)
    {
        JUMP(effectiveOperandSize,dest,registerFile);
    }
}

//0x8

EXECUTE_FUNC(executeTEST)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("TEST");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        s8 opt1=dest->getS8();
        s8 opt2=src->getS8();
        s8 result=opt1&opt2;
//        dest->setU8(result);

        u8 msbResult=u8((result>>7)&1);
        registerFile.getFlagsBits().CF=0;
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        registerFile.getFlagsBits().AF=0;
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        registerFile.getFlagsBits().OF=0;
        break;
    }
    case DATA_SIZE_WORD:
    {
        s16 opt1=dest->getS16();
        s16 opt2=src->getS16();
        s16 result=opt1&opt2;
//        dest->setU16(result);

        u8 msbResult=u8((result>>15)&1);
        registerFile.getFlagsBits().CF=0;
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        registerFile.getFlagsBits().AF=0;
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        registerFile.getFlagsBits().OF=0;
        break;
    }
    case DATA_SIZE_DWORD:
    {
        s32 opt1=dest->getS32();
        s32 opt2=src->getS32();
        s32 result=opt1&opt2;
//        dest->setU32(result);

        u8 msbResult=u8((result>>31)&1);
        registerFile.getFlagsBits().CF=0;
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        registerFile.getFlagsBits().AF=0;
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        registerFile.getFlagsBits().OF=0;
        break;
    }
    case DATA_SIZE_QWORD:
    {
        s64 opt1=dest->getS64();
        s64 opt2=src->getS64();
        s64 result=opt1&opt2;
//        dest->setU64(result);

        u8 msbResult=u8((result>>63)&1);
        registerFile.getFlagsBits().CF=0;
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        registerFile.getFlagsBits().AF=0;
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        registerFile.getFlagsBits().OF=0;
        break;
    }
    default:
        assert(0);
    }
}

EXECUTE_FUNC(executeXCHG)
{
    //!@todo There is a problem when opcode=90 in 64bits mode.see amd64 manual xchg.
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("XCHG");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        u8 temp=dest->getU8();
        dest->setU8(src->getU8());
        src->setU8(temp);
        break;
    }
    case DATA_SIZE_WORD:
    {
        u16 temp=dest->getU16();
        dest->setU16(src->getU16());
        src->setU16(temp);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        u32 temp=dest->getU32();
        dest->setU32(src->getU32());
        src->setU32(temp);
        break;
    }
    case DATA_SIZE_QWORD:
    {
        u64 temp=dest->getU64();
        dest->setU64(src->getU64());
        src->setU64(temp);
        break;
    }
    default:
        assert(0);
    }
}

void MOVE(ExecReadWriteOperand* dest,ExecReadWriteOperand* src)
{
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
        dest->setU8(src->getU8());
        break;
    case DATA_SIZE_WORD:
        dest->setU16(src->getU16());
        break;
    case DATA_SIZE_DWORD:
        dest->setU32(src->getU32());
        break;
    case DATA_SIZE_QWORD:
        dest->setU64(src->getU64());
        break;
    default:
        assert(0);
    }
}
EXECUTE_FUNC(executeMOVE)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("MOVE");
    MOVE(dest,src);
}

EXECUTE_FUNC(executeLEA)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("LEA");
    ExecMemoryOperand* memorySrc=dynamic_cast<ExecMemoryOperand*>(src);
    assert(memorySrc);
    switch(dest->getSize())
    {
    case DATA_SIZE_WORD:
        dest->setU16(memorySrc->getOffset());
        break;
    case DATA_SIZE_DWORD:
        dest->setU32(memorySrc->getOffset());
        break;
    case DATA_SIZE_QWORD:
        dest->setU64(memorySrc->getOffset());
        break;
    default:
        assert(0);
    }
}

//0x9

EXECUTE_FUNC(executeCBW_CWDE_CDQE)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("CBW_CWDE_CDQE");
    switch(effectiveOperandSize)
    {
    case EFFECTIVE_16_BITS:
    {
        s8 al=s8(registerFile.getGPR8Bits(RAX));
        s16 ax=al;
        registerFile.setGPR16Bits(RAX,ax);
        break;
    }
    case EFFECTIVE_32_BITS:
    {
        s16 ax=s16(registerFile.getGPR16Bits(RAX));
        s32 eax=ax;
        registerFile.setGPR32Bits(RAX,eax);
        break;
    }
    case EFFECTIVE_64_BITS:
    {
        s32 eax=s32(registerFile.getGPR32Bits(RAX));
        s64 rax=eax;
        registerFile.setGPR64Bits(RAX,rax);
        break;
    }
    }
}

EXECUTE_FUNC(executeCWD_CDQ_CQO)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("CWD_CDQ_CQO");
    switch(effectiveOperandSize)
    {
    case EFFECTIVE_16_BITS:
    {
        s16 ax=registerFile.getGPR16Bits(RAX);
        if(ax<0)
        {
            registerFile.setGPR16Bits(RDX,0xffff);
        }
        else
        {
            registerFile.setGPR16Bits(RDX,0x0000);
        }
        break;
    }
    case EFFECTIVE_32_BITS:
    {
        s32 eax=registerFile.getGPR32Bits(RAX);
        if(eax<0)
        {
            registerFile.setGPR32Bits(RDX,0xffffffff);
        }
        else
        {
            registerFile.setGPR32Bits(RDX,0x00000000);
        }
        break;
    }
    case EFFECTIVE_64_BITS:
    {
        s64 rax=registerFile.getGPR64Bits(RAX);
        if(rax<0)
        {
            registerFile.setGPR64Bits(RDX,0xffffffffffffffffL);
        }
        else
        {
            registerFile.setGPR64Bits(RDX,0x0000L);
        }
        break;
    }
    }
}


EXECUTE_FUNC(executeWAIT_FWAIT)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("WAIT_FWAIT");
}

EXECUTE_FUNC(executePUSHFDQ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("PUSHFDQ");
    switch(effectiveOperandSize)
    {
    case EFFECTIVE_16_BITS:
        PUSH<u16>(registerFile.getFlags16Bits(),effectiveAddressSize,memory,registerFile);
        break;
    case EFFECTIVE_32_BITS:
        PUSH<u32>(registerFile.getFlags32Bits(),effectiveAddressSize,memory,registerFile);
        break;
    case EFFECTIVE_64_BITS:
        PUSH<u64>((u64)registerFile.getFlags32Bits(),effectiveAddressSize,memory,registerFile);
        break;
    }
}

EXECUTE_FUNC(executePOPFDQ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("POPFDQ");
    switch(effectiveOperandSize)
    {
    case EFFECTIVE_16_BITS:
    {
        u16 flags;
        POP<u16>(flags,effectiveAddressSize,memory,registerFile);
        registerFile.setFlags16Bits(flags);
        break;
    }
    case EFFECTIVE_32_BITS:
    {
        u32 flags;
        POP<u32>(flags,effectiveAddressSize,memory,registerFile);
        registerFile.setFlags32Bits(flags);
        break;
    }
    case EFFECTIVE_64_BITS:
    {
        u64 flags;
        POP<u64>(flags,effectiveAddressSize,memory,registerFile);
        registerFile.setFlags32Bits((u32)flags);
        break;
    }
    }
}

EXECUTE_FUNC(executeSAHF)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("SAHF");
    registerFile.setFlags8Bits(registerFile.getGPR8BitsHigh(RAX));
}

EXECUTE_FUNC(executeLAHF)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("LAHF");
    registerFile.setGPR8BitsHigh(RAX,registerFile.getFlags8Bits());
}

//0xa

void INCDECrSIrDI(DataSize dataSize,RegisterFile& registerFile,EffectiveSize effectiveAddressSize,
                  bool isrDI=true,bool isrSI=true)
{
    s64 offset=0;
    switch(dataSize)
    {
    case DATA_SIZE_BYTE:
    {
        offset=1;
        break;
    }
    case DATA_SIZE_WORD:
    {
        offset=2;
        break;
    }
    case DATA_SIZE_DWORD:
    {
        offset=4;
        break;
    }
    case DATA_SIZE_QWORD:
    {
        offset=8;
        break;
    }
    default:
        assert(0);
    }
    if(registerFile.getFlagsBits().DF==1)
        offset=-offset;

    switch(effectiveAddressSize)
    {
    case EFFECTIVE_16_BITS:
    {
        if(isrSI)
            registerFile.setGPR16Bits(RSI,registerFile.getGPR16Bits(RSI)+offset);
        if(isrDI)
            registerFile.setGPR16Bits(RDI,registerFile.getGPR16Bits(RDI)+offset);
        break;
    }
    case EFFECTIVE_32_BITS:
    {
        if(isrSI)
            registerFile.setGPR32Bits(RSI,registerFile.getGPR32Bits(RSI)+offset);
        if(isrDI)
            registerFile.setGPR32Bits(RDI,registerFile.getGPR32Bits(RDI)+offset);
        break;
    }
    case EFFECTIVE_64_BITS:
    {
        if(isrSI)
            registerFile.setGPR64Bits(RSI,registerFile.getGPR64Bits(RSI)+offset);
        if(isrDI)
            registerFile.setGPR64Bits(RDI,registerFile.getGPR64Bits(RDI)+offset);
        break;
    }
    }
}

//void MOVS(ExecReadWriteOperand* dest,ExecReadWriteOperand* src,RegisterFile& registerFile,
//          EffectiveSize effectiveAddressSize)
//{

//}
EXECUTE_FUNC(executeMOVS)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("MOVSB");
    MOVE(dest,src);
    INCDECrSIrDI(dest->getSize(),registerFile,effectiveAddressSize);
}

//EXECUTE_FUNC(executeMOVSWDQ)
//{
//    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("MOVSWDQ");
//    MOVS(dest,src,registerFile,effectiveAddressSize);
//}

EXECUTE_FUNC(executeCMPS)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("CMPS");
    CMP(dest,src,registerFile);
    INCDECrSIrDI(dest->getSize(),registerFile,effectiveAddressSize);
}

//EXECUTE_FUNC(executeCMPSWDQ)
//{
//    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("CMPSWDQ");
//}

EXECUTE_FUNC(executeSTOS)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("STOS");
    MOVE(dest,src);
    INCDECrSIrDI(dest->getSize(),registerFile,effectiveAddressSize,true,false);
}

//EXECUTE_FUNC(executeSTOSWDQ)
//{
//    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("STOSWDQ");
//}

EXECUTE_FUNC(executeLODS)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("LODS");
    MOVE(dest,src);
    INCDECrSIrDI(dest->getSize(),registerFile,effectiveAddressSize,false,true);
}

//EXECUTE_FUNC(executeLODSWDQ)
//{
//    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("LODSWDQ");
//}

EXECUTE_FUNC(executeSCAS)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("SCAS");
    CMP(dest,src,registerFile);
    INCDECrSIrDI(dest->getSize(),registerFile,effectiveAddressSize,true,false);
}

//EXECUTE_FUNC(executeSCASWDQ)
//{
//    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("SCASWDQ");
//}

//0xb
//0xc
//group2
template <typename T>
inline void ROL(FlagsBits& flags,T& value,u8 count)
{
    if(sizeof(T)==8)
        count&=0x3f;
    else
        count&=0x1f;
    u8 CF=0;
    u8 OF=0;
    for(int i=0; i<count; i++)
    {
        CF=(value>>(sizeof(T)*8-1))&0x1;
        value<<=1;
        value|=CF;
    }
    OF=((value>>(sizeof(T)*8-1))&0x1)^CF;

    if(count!=0)
    {
        flags.CF=CF;
        flags.OF=OF;
    }
}
EXECUTE_FUNC(executeROL)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("ROL");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        u8 value=dest->getU8();
        u8 count=src->getU8();
        ROL(registerFile.getFlagsBits(),value,count);
        dest->setU8(value);
        break;
    }
    case DATA_SIZE_WORD:
    {
        u16 value=dest->getU16();
        u8 count=src->getU8();
        ROL(registerFile.getFlagsBits(),value,count);
        dest->setU16(value);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        u32 value=dest->getU32();
        u8 count=src->getU8();
        ROL(registerFile.getFlagsBits(),value,count);
        dest->setU32(value);
        break;
    }
    case DATA_SIZE_QWORD:
    {
        u64 value=dest->getU64();
        u8 count=src->getU8();
        ROL(registerFile.getFlagsBits(),value,count);
        dest->setU64(value);
        break;
    }
    default:
        assert(0);
    }

}
template <typename T>
inline void ROR(FlagsBits& flags,T& value,u8 count)
{
    if(sizeof(T)==8)
        count&=0x3f;
    else
        count&=0x1f;
    u8 CF=0;
    u8 OF=0;
    for(int i=0; i<count; i++)
    {
        CF=(value)&0x1;
        value>>=1;
        value|=(T(CF)<<(sizeof(T)*8-1));
    }
    OF=((value>>(sizeof(T)*8-1))&0x1)^((value>>(sizeof(T)*8-2))&0x1);

    if(count!=0)
    {
        flags.CF=CF;
        flags.OF=OF;
    }
}
EXECUTE_FUNC(executeROR)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("ROR");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        u8 value=dest->getU8();
        u8 count=src->getU8();
        ROR(registerFile.getFlagsBits(),value,count);
        dest->setU8(value);
        break;
    }
    case DATA_SIZE_WORD:
    {
        u16 value=dest->getU16();
        u8 count=src->getU8();
        ROR(registerFile.getFlagsBits(),value,count);
        dest->setU16(value);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        u32 value=dest->getU32();
        u8 count=src->getU8();
        ROR(registerFile.getFlagsBits(),value,count);
        dest->setU32(value);
        break;
    }
    case DATA_SIZE_QWORD:
    {
        u64 value=dest->getU64();
        u8 count=src->getU8();
        ROR(registerFile.getFlagsBits(),value,count);
        dest->setU64(value);
        break;
    }
    default:
        assert(0);
    }
}
template <typename T>
inline void RCL(FlagsBits& flags,T& value,u8 count)
{
    if(sizeof(T)==8)
        count&=0x3f;
    else
        count&=0x1f;
    u8 CF=flags.CF;
    u8 OF=0;
    for(int i=0; i<count; i++)
    {
        u8 tempCF=(value>>(sizeof(T)*8-1))&0x1;
        value<<=1;
        value|=CF;
        CF=tempCF;
    }
    OF=((value>>(sizeof(T)*8-1))&0x1)^CF;

    if(count!=0)
    {
        flags.CF=CF;
        flags.OF=OF;
    }
}
EXECUTE_FUNC(executeRCL)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("RCL");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        u8 value=dest->getU8();
        u8 count=src->getU8();
        RCL(registerFile.getFlagsBits(),value,count);
        dest->setU8(value);
        break;
    }
    case DATA_SIZE_WORD:
    {
        u16 value=dest->getU16();
        u8 count=src->getU8();
        RCL(registerFile.getFlagsBits(),value,count);
        dest->setU16(value);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        u32 value=dest->getU32();
        u8 count=src->getU8();
        RCL(registerFile.getFlagsBits(),value,count);
        dest->setU32(value);
        break;
    }
    case DATA_SIZE_QWORD:
    {
        u64 value=dest->getU64();
        u8 count=src->getU8();
        RCL(registerFile.getFlagsBits(),value,count);
        dest->setU64(value);
        break;
    }
    default:
        assert(0);
    }
}
template <typename T>
inline void RCR(FlagsBits& flags,T& value,u8 count)
{
    if(sizeof(T)==8)
        count&=0x3f;
    else
        count&=0x1f;
    u8 CF=flags.CF;
    u8 OF=0;
    OF=((value>>(sizeof(T)*8-1))&0x1)^CF;
    for(int i=0; i<count; i++)
    {
        u8 tempCF=(value)&0x1;
        value>>=1;
        value|=(T(CF)<<(sizeof(T)*8-1));
        CF=tempCF;
    }

    if(count!=0)
    {
        flags.CF=CF;
        flags.OF=OF;
    }
}
EXECUTE_FUNC(executeRCR)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("RCR");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        u8 value=dest->getU8();
        u8 count=src->getU8();
        RCR(registerFile.getFlagsBits(),value,count);
        dest->setU8(value);
        break;
    }
    case DATA_SIZE_WORD:
    {
        u16 value=dest->getU16();
        u8 count=src->getU8();
        RCR(registerFile.getFlagsBits(),value,count);
        dest->setU16(value);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        u32 value=dest->getU32();
        u8 count=src->getU8();
        RCR(registerFile.getFlagsBits(),value,count);
        dest->setU32(value);
        break;
    }
    case DATA_SIZE_QWORD:
    {
        u64 value=dest->getU64();
        u8 count=src->getU8();
        RCR(registerFile.getFlagsBits(),value,count);
        dest->setU64(value);
        break;
    }
    default:
        assert(0);
    }
}
//EXECUTE_FUNC(executeSHL_SAL)
//{

//}
template <typename T>
inline void SHR(FlagsBits& flags,T& value,u8 count)
{
    if(sizeof(T)==8)
        count&=0x3f;
    else
        count&=0x1f;
    u8 CF=0;
    u8 OF=0;
    OF=((value>>(sizeof(T)*8-1))&0x1);
    for(int i=0; i<count; i++)
    {
        CF=(value)&0x1;
        value>>=1;
    }

    if(count!=0)
    {
        flags.CF=CF;
        flags.OF=OF;
    }
}
EXECUTE_FUNC(executeSHR)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("SHR");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        u8 value=dest->getU8();
        u8 count=src->getU8();
        SHR(registerFile.getFlagsBits(),value,count);
        dest->setU8(value);
        break;
    }
    case DATA_SIZE_WORD:
    {
        u16 value=dest->getU16();
        u8 count=src->getU8();
        SHR(registerFile.getFlagsBits(),value,count);
        dest->setU16(value);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        u32 value=dest->getU32();
        u8 count=src->getU8();
        SHR(registerFile.getFlagsBits(),value,count);
        dest->setU32(value);
        break;
    }
    case DATA_SIZE_QWORD:
    {
        u64 value=dest->getU64();
        u8 count=src->getU8();
        SHR(registerFile.getFlagsBits(),value,count);
        dest->setU64(value);
        break;
    }
    default:
        assert(0);
    }
}
template <typename T>
inline void SHL_SAL(FlagsBits& flags,T& value,u8 count)
{
    if(sizeof(T)==8)
        count&=0x3f;
    else
        count&=0x1f;
    u8 CF=0;
    u8 OF=0;
    for(int i=0; i<count; i++)
    {
        CF=(value>>(sizeof(T)*8-1))&0x1;
        value<<=1;
//        value|=CF;
//        CF=tempCF;
    }
    OF=((value>>(sizeof(T)*8-1))&0x1)^CF;

    if(count!=0)
    {
        flags.CF=CF;
        flags.OF=OF;
    }
}
EXECUTE_FUNC(executeSHL_SAL)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("SAL");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        u8 value=dest->getU8();
        u8 count=src->getU8();
        SHL_SAL(registerFile.getFlagsBits(),value,count);
        dest->setU8(value);
        break;
    }
    case DATA_SIZE_WORD:
    {
        u16 value=dest->getU16();
        u8 count=src->getU8();
        SHL_SAL(registerFile.getFlagsBits(),value,count);
        dest->setU16(value);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        u32 value=dest->getU32();
        u8 count=src->getU8();
        SHL_SAL(registerFile.getFlagsBits(),value,count);
        dest->setU32(value);
        break;
    }
    case DATA_SIZE_QWORD:
    {
        u64 value=dest->getU64();
        u8 count=src->getU8();
        SHL_SAL(registerFile.getFlagsBits(),value,count);
        dest->setU64(value);
        break;
    }
    default:
        assert(0);
    }
}
template <typename T>
inline void SAR(FlagsBits& flags,T& value,u8 count)
{
    if(sizeof(T)==8)
        count&=0x3f;
    else
        count&=0x1f;
    u8 CF=0;
    u8 OF=0;
//    OF=((value>>(sizeof(T)*8-1))&0x1);
    for(int i=0; i<count; i++)
    {
        CF=(value)&0x1;
        u8 msb=((value>>(sizeof(T)*8-1))&0x1);
        value>>=1;
        value|=T(msb)<<(sizeof(T)*8-1);
    }

    if(count!=0)
    {
        flags.CF=CF;
        flags.OF=OF;
    }
}
EXECUTE_FUNC(executeSAR)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("SAR");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        u8 value=dest->getU8();
        u8 count=src->getU8();
        SAR(registerFile.getFlagsBits(),value,count);
        dest->setU8(value);
        break;
    }
    case DATA_SIZE_WORD:
    {
        u16 value=dest->getU16();
        u8 count=src->getU8();
        SAR(registerFile.getFlagsBits(),value,count);
        dest->setU16(value);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        u32 value=dest->getU32();
        u8 count=src->getU8();
        SAR(registerFile.getFlagsBits(),value,count);
        dest->setU32(value);
        break;
    }
    case DATA_SIZE_QWORD:
    {
        u64 value=dest->getU64();
        u8 count=src->getU8();
        SAR(registerFile.getFlagsBits(),value,count);
        dest->setU64(value);
        break;
    }
    default:
        assert(0);
    }
}
EXECUTE_FUNC(executeRETNEAR)//only this one.
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("RETNEAR");
    switch(effectiveOperandSize)
    {
    case EFFECTIVE_16_BITS:
    {
        u16 IP;
        POP<u16>(IP,effectiveAddressSize,memory,registerFile);
        registerFile.setIP(IP);
        break;
    }
    case EFFECTIVE_32_BITS:
    {
        u32 IP;
        POP<u32>(IP,effectiveAddressSize,memory,registerFile);
        registerFile.setIP(IP);
        break;
    }
    case EFFECTIVE_64_BITS:
    {
        u64 IP;
        POP<u64>(IP,effectiveAddressSize,memory,registerFile);
        registerFile.setIP((u32)IP);
        break;
    }
    default:
        assert(0);
    }

    switch(effectiveAddressSize)
    {
    case EFFECTIVE_16_BITS:
        registerFile.setGPR16Bits(RSP,registerFile.getGPR16Bits(RSP)+dest->getU16());
        break;
    case EFFECTIVE_32_BITS:
        registerFile.setGPR32Bits(RSP,registerFile.getGPR32Bits(RSP)+dest->getU16());
        break;
    case EFFECTIVE_64_BITS:
        registerFile.setGPR64Bits(RSP,registerFile.getGPR64Bits(RSP)+dest->getU16());
        break;
    }
}
EXECUTE_FUNC(executeLES)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("LES");
    switch(dest->getSize())
    {
    case DATA_SIZE_WORD:
    {
        u32 value=src->getU32();
        u16 segment=(value>>16)&0xffff;
        u16 offset=(value&0xffff);

        registerFile.setSR(ES,segment);
        registerFile.setSSR(ES,u32(segment)<<4);
        dest->setU16(offset);

        break;
    }
    case DATA_SIZE_DWORD:
    {
        u48 value=src->getU48();
        u16 segment=(value>>32)&0xffff;
        u32 offset=(value&0xffffffff);

        registerFile.setSR(ES,segment);
        registerFile.setSSR(ES,u32(segment)<<4);
        dest->setU32(offset);
        break;
    }
    default:
        assert(0);
    }
}
EXECUTE_FUNC(executeLDS)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("LDS");
    switch(dest->getSize())
    {
    case DATA_SIZE_WORD:
    {
        u32 value=src->getU32();
        u16 segment=(value>>16)&0xffff;
        u16 offset=(value&0xffff);

        registerFile.setSR(DS,segment);
        registerFile.setSSR(DS,u32(segment)<<4);
        dest->setU16(offset);

        break;
    }
    case DATA_SIZE_DWORD:
    {
        u48 value=src->getU48();
        u16 segment=(value>>32)&0xffff;
        u32 offset=(value&0xffffffff);

        registerFile.setSR(DS,segment);
        registerFile.setSSR(DS,u32(segment)<<4);
        dest->setU32(offset);
        break;
    }
    default:
        assert(0);
    }
}

EXECUTE_FUNC(executeENTER)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("ENTER");
    u16 temp_ALLOC_SPACE=dest->getU16();
    u8 temp_LEVEL=src->getU8()&0x1f;

    switch(effectiveOperandSize)
    {
    case EFFECTIVE_16_BITS:
    {
        PUSH<u16>(registerFile.getGPR16Bits(RBP),effectiveAddressSize,memory,registerFile);
        u16 temp_RBP=registerFile.getGPR16Bits(RSP);
        if(temp_LEVEL>1)
        {
            for(int i=1; i<temp_LEVEL; i++)
            {
                switch(effectiveAddressSize)
                {
                case EFFECTIVE_16_BITS:
                {
                    ExecMemoryOperand memOperand(memory,registerFile.getSSR(SS),
                                             registerFile.getGPR16Bits(RBP)-i*2,DATA_SIZE_WORD);
                    PUSH<u16>(memOperand.getU16(),effectiveAddressSize,memory,registerFile);
                    break;
                }
                case EFFECTIVE_32_BITS:
                {
                    ExecMemoryOperand memOperand(memory,registerFile.getSSR(SS),
                                             registerFile.getGPR32Bits(RBP)-i*2,DATA_SIZE_WORD);
                    PUSH<u16>(memOperand.getU16(),effectiveAddressSize,memory,registerFile);
                    break;
                }
                case EFFECTIVE_64_BITS:
                    assert(0);
                    break;
                }
            }
            PUSH<u16>(temp_RBP,effectiveAddressSize,memory,registerFile);
        }
        registerFile.setGPR16Bits(RSP,registerFile.getGPR16Bits(RSP)-temp_ALLOC_SPACE);
        registerFile.setGPR16Bits(RBP,temp_RBP);
        break;
    }
    case EFFECTIVE_32_BITS:
    case EFFECTIVE_64_BITS:
        assert(0);
        break;
    }
}
EXECUTE_FUNC(executeLEAVE)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("LEAVE");
    switch(effectiveOperandSize)
    {
    case EFFECTIVE_16_BITS:
    {
        registerFile.setGPR16Bits(RSP,registerFile.getGPR16Bits(RBP));
        u16 bp;
        POP<u16>(bp,effectiveAddressSize,memory,registerFile);
        registerFile.setGPR16Bits(RBP,bp);
        break;
    }
    case EFFECTIVE_32_BITS:
    case EFFECTIVE_64_BITS:
        assert(0);
        break;
    }
}
EXECUTE_FUNC(executeRETFAR)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("RETFAR");
    switch(effectiveOperandSize)
    {
    case EFFECTIVE_16_BITS:
    {
        u16 IP;
        POP<u16>(IP,effectiveAddressSize,memory,registerFile);
        registerFile.setIP(IP);

        u16 segment;
        POP<u16>(segment,effectiveAddressSize,memory,registerFile);
        registerFile.setSR(CS,segment);
        registerFile.setSSR(CS,u32(segment)<<4);
        break;
    }
    case EFFECTIVE_32_BITS:
    {
        u32 IP;
        POP<u32>(IP,effectiveAddressSize,memory,registerFile);
        registerFile.setIP(IP);

        u16 segment;
        POP<u16>(segment,effectiveAddressSize,memory,registerFile);
        registerFile.setSR(CS,segment);
        registerFile.setSSR(CS,u32(segment)<<4);
        break;
    }
    case EFFECTIVE_64_BITS:
    {
        u64 IP;
        POP<u64>(IP,effectiveAddressSize,memory,registerFile);
        registerFile.setIP((u32)IP);

        u16 segment;
        POP<u16>(segment,effectiveAddressSize,memory,registerFile);
        registerFile.setSR(CS,segment);
        registerFile.setSSR(CS,u32(segment)<<4);
        break;
    }
    default:
        assert(0);
    }

    switch(effectiveAddressSize)
    {
    case EFFECTIVE_16_BITS:
        registerFile.setGPR16Bits(RSP,registerFile.getGPR16Bits(RSP)+dest->getU16());
        break;
    case EFFECTIVE_32_BITS:
        registerFile.setGPR32Bits(RSP,registerFile.getGPR32Bits(RSP)+dest->getU16());
        break;
    case EFFECTIVE_64_BITS:
        registerFile.setGPR64Bits(RSP,registerFile.getGPR64Bits(RSP)+dest->getU16());
        break;
    }

}
void INT(u8 intNumber,EffectiveSize effectiveAddressSize,Memory& memory,RegisterFile& registerFile)
{
    //!@todo only implement 16bit.
    PUSH<u16>(registerFile.getFlags16Bits(),effectiveAddressSize,memory,registerFile);
    PUSH<u16>(registerFile.getSR(CS),effectiveAddressSize,memory,registerFile);
    PUSH<u16>(u16(registerFile.getIP()),effectiveAddressSize,memory,registerFile);

    ExecMemoryOperand memOperand(memory,0,intNumber*4,DATA_SIZE_DWORD);
    u32 memValue = memOperand.getU32();
    u16 SR=(memValue>>16)&0xffff;
    u16 IP=(memValue&0xffff);
    registerFile.setSR(CS,SR);
    registerFile.setSSR(CS,u32(SR)<<4);
    registerFile.setIP(IP);

    registerFile.getFlagsBits().AC=0;
    registerFile.getFlagsBits().TF=0;
    registerFile.getFlagsBits().IF=0;
    registerFile.getFlagsBits().RF=0;
}
EXECUTE_FUNC(executeINT3)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("INT3");
    assert(operatingEnvironment==ENV_16_BITS);
    INT(3,effectiveAddressSize,memory,registerFile);
}
EXECUTE_FUNC(executeINT)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("INT");
    assert(operatingEnvironment==ENV_16_BITS);
    INT(dest->getU8(),effectiveAddressSize,memory,registerFile);
}
EXECUTE_FUNC(executeINTO)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("INTO");
    assert(operatingEnvironment==ENV_16_BITS);
    if(registerFile.getFlagsBits().OF==1)
    {
        INT(4,effectiveAddressSize,memory,registerFile);
    }

}
EXECUTE_FUNC(executeIRET_IRETD_IRETQ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("IRET_IRETD_IRETQ");
    assert(operatingEnvironment==ENV_16_BITS);
    //!@todo only implement 16bit.

    u16 flags;
    u16 SR;
    u16 IP;

    POP<u16>(IP,effectiveAddressSize,memory,registerFile);
    POP<u16>(SR,effectiveAddressSize,memory,registerFile);
    POP<u16>(flags,effectiveAddressSize,memory,registerFile);

    registerFile.setSR(CS,SR);
    registerFile.setSSR(CS,u32(SR)<<4);
    registerFile.setIP(IP);

    registerFile.setFlags16Bits(flags);
}

//0xd

EXECUTE_FUNC(executeAAM)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("AAM");
}

EXECUTE_FUNC(executeAAD)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("AAD");
}

EXECUTE_FUNC(executeSALC)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("SALC");
}

EXECUTE_FUNC(executeXLAT)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("XLAT");
    switch(effectiveAddressSize)
    {
    case EFFECTIVE_16_BITS:
    {
        ExecMemoryOperand memOperand(memory,registerFile.getSSR(effectiveSegmentRegister),
                                     registerFile.getGPR16Bits(RBX)+registerFile.getGPR8BitsLow(RAX),
                                     DATA_SIZE_BYTE);
        registerFile.setGPR8BitsLow(RAX,memOperand.getU8());
        break;
    }
    case EFFECTIVE_32_BITS:
    {
        ExecMemoryOperand memOperand(memory,registerFile.getSSR(effectiveSegmentRegister),
                                     registerFile.getGPR32Bits(RBX)+registerFile.getGPR8BitsLow(RAX),
                                     DATA_SIZE_BYTE);
        registerFile.setGPR8BitsLow(RAX,memOperand.getU8());
        break;
    }
    case EFFECTIVE_64_BITS:
    {
        ExecMemoryOperand memOperand(memory,registerFile.getSSR(effectiveSegmentRegister),
                                     registerFile.getGPR64Bits(RBX)+registerFile.getGPR8BitsLow(RAX),
                                     DATA_SIZE_BYTE);
        registerFile.setGPR8BitsLow(RAX,memOperand.getU8());
        break;
    }
    }
}


//0xe

EXECUTE_FUNC(executeLOOPNZ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("LOOPNZ");
    switch(effectiveAddressSize)
    {
    case EFFECTIVE_16_BITS:
        registerFile.setGPR16Bits(RCX,registerFile.getGPR16Bits(RCX)-1);
        if(registerFile.getGPR16Bits(RCX)!=0 && registerFile.getFlagsBits().ZF==0)
        {
            JUMP(effectiveOperandSize,dest,registerFile);
        }
        break;
    case EFFECTIVE_32_BITS:
        registerFile.setGPR32Bits(RCX,registerFile.getGPR32Bits(RCX)-1);
        if(registerFile.getGPR32Bits(RCX)!=0 && registerFile.getFlagsBits().ZF==0)
        {
            JUMP(effectiveOperandSize,dest,registerFile);
        }
        break;
    case EFFECTIVE_64_BITS:
        registerFile.setGPR64Bits(RCX,registerFile.getGPR64Bits(RCX)-1);
        if(registerFile.getGPR64Bits(RCX)!=0 && registerFile.getFlagsBits().ZF==0)
        {
            JUMP(effectiveOperandSize,dest,registerFile);
        }
        break;
    }
}

EXECUTE_FUNC(executeLOOPZ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("LOOPZ");
    switch(effectiveAddressSize)
    {
    case EFFECTIVE_16_BITS:
        registerFile.setGPR16Bits(RCX,registerFile.getGPR16Bits(RCX)-1);
        if(registerFile.getGPR16Bits(RCX)!=0 && registerFile.getFlagsBits().ZF==1)
        {
            JUMP(effectiveOperandSize,dest,registerFile);
        }
        break;
    case EFFECTIVE_32_BITS:
        registerFile.setGPR32Bits(RCX,registerFile.getGPR32Bits(RCX)-1);
        if(registerFile.getGPR32Bits(RCX)!=0 && registerFile.getFlagsBits().ZF==1)
        {
            JUMP(effectiveOperandSize,dest,registerFile);
        }
        break;
    case EFFECTIVE_64_BITS:
        registerFile.setGPR64Bits(RCX,registerFile.getGPR64Bits(RCX)-1);
        if(registerFile.getGPR64Bits(RCX)!=0 && registerFile.getFlagsBits().ZF==1)
        {
            JUMP(effectiveOperandSize,dest,registerFile);
        }
        break;
    }
}

EXECUTE_FUNC(executeLOOP)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("LOOP");
    switch(effectiveAddressSize)
    {
    case EFFECTIVE_16_BITS:
        registerFile.setGPR16Bits(RCX,registerFile.getGPR16Bits(RCX)-1);
        if(registerFile.getGPR16Bits(RCX)!=0)
        {
            JUMP(effectiveOperandSize,dest,registerFile);
        }
        break;
    case EFFECTIVE_32_BITS:
        registerFile.setGPR32Bits(RCX,registerFile.getGPR32Bits(RCX)-1);
        if(registerFile.getGPR32Bits(RCX)!=0)
        {
            JUMP(effectiveOperandSize,dest,registerFile);
        }
        break;
    case EFFECTIVE_64_BITS:
        registerFile.setGPR64Bits(RCX,registerFile.getGPR64Bits(RCX)-1);
        if(registerFile.getGPR64Bits(RCX)!=0)
        {
            JUMP(effectiveOperandSize,dest,registerFile);
        }
        break;
    }
}

EXECUTE_FUNC(executeJRCXZ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JRCXZ");
    switch(effectiveAddressSize)
    {
    case EFFECTIVE_16_BITS:
        if(registerFile.getGPR16Bits(RCX)==0)
        {
            JUMP(effectiveOperandSize,dest,registerFile);
        }
        break;
    case EFFECTIVE_32_BITS:
        if(registerFile.getGPR32Bits(RCX)==0)
        {
            JUMP(effectiveOperandSize,dest,registerFile);
        }
        break;
    case EFFECTIVE_64_BITS:
        if(registerFile.getGPR64Bits(RCX)==0)
        {
            JUMP(effectiveOperandSize,dest,registerFile);
        }
        break;
    }
}

EXECUTE_FUNC(executeIN)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("IN");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
        dest->setU8(ioPortList.readFromPort(src->getU16()));
        break;
    case DATA_SIZE_WORD:
        dest->setU16(ioPortList.readFromPort(src->getU16()));
        break;
    case DATA_SIZE_DWORD:
        dest->setU32(ioPortList.readFromPort(src->getU16()));
        break;
    default:
        assert(0);
    }
}

EXECUTE_FUNC(executeOUT)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("OUT");
    ioPortList.write2Port(dest->getU16(),src->getU32());
}


EXECUTE_FUNC(executeCALLNEAR_Jz)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("CALL_Jz");
    switch(effectiveOperandSize)
    {
    case EFFECTIVE_16_BITS:
        PUSH<u16>((u16)registerFile.getIP(),effectiveAddressSize,memory,registerFile);
        JUMP(effectiveOperandSize,dest,registerFile);
        break;
    case EFFECTIVE_32_BITS:
        PUSH<u32>((u32)registerFile.getIP(),effectiveAddressSize,memory,registerFile);
        JUMP(effectiveOperandSize,dest,registerFile);
        break;
    default:
        assert(0);
    }
}

EXECUTE_FUNC(executeJMPNEAR_J)//includes Jz & Jb
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JMP_J");
    JUMP(effectiveOperandSize,dest,registerFile);
}

EXECUTE_FUNC(executeCALLFAR_p)//includes Mp or Ap
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("CALL_Ap");
    switch(dest->getSize())
    {
    case DATA_SIZE_DWORD:
    {
        assert(effectiveOperandSize==EFFECTIVE_16_BITS);
        PUSH<u16>(registerFile.getSR(CS),effectiveAddressSize,memory,registerFile);
        PUSH<u16>((u16)registerFile.getIP(),effectiveAddressSize,memory,registerFile);

        u32 value=dest->getU32();
        u16 segment=(value>>16)&0xffff;
        u16 offset=(value&0xffff);

        registerFile.setSR(CS,segment);
        registerFile.setSSR(CS,u32(segment)<<4);
        registerFile.setIP(offset);

        break;
    }
    case DATA_SIZE_6BYTES:
    {
        assert(effectiveOperandSize==EFFECTIVE_32_BITS);
        PUSH<u16>(registerFile.getSR(CS),effectiveAddressSize,memory,registerFile);
        PUSH<u32>(registerFile.getIP(),effectiveAddressSize,memory,registerFile);

        u48 value=src->getU48();
        u16 segment=(value>>32)&0xffff;
        u32 offset=(value&0xffffffff);

        registerFile.setSR(CS,segment);
        registerFile.setSSR(CS,u32(segment)<<4);
        registerFile.setIP(offset);

        break;
    }
    default:
        assert(0);
    }
}

EXECUTE_FUNC(executeJMPFAR_p)//includes Mp or Ap
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JMP_p");
    switch(dest->getSize())
    {
    case DATA_SIZE_DWORD:
    {
        assert(effectiveOperandSize==EFFECTIVE_16_BITS);
        u32 value=dest->getU32();
        u16 segment=(value>>16)&0xffff;
        u16 offset=(value&0xffff);

        registerFile.setSR(CS,segment);
        registerFile.setSSR(CS,u32(segment)<<4);
        registerFile.setIP(offset);

        break;
    }
    case DATA_SIZE_6BYTES:
    {
        assert(effectiveOperandSize==EFFECTIVE_32_BITS);
        u48 value=src->getU48();
        u16 segment=(value>>32)&0xffff;
        u32 offset=(value&0xffffffff);

        registerFile.setSR(CS,segment);
        registerFile.setSSR(CS,u32(segment)<<4);
        registerFile.setIP(offset);

        break;
    }
    default:
        assert(0);
    }
}


//0xf

EXECUTE_FUNC(executeINT1)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("INT1");
    assert(operatingEnvironment==ENV_16_BITS);
    INT(1,effectiveAddressSize,memory,registerFile);
}
EXECUTE_FUNC(executeHLT)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("HLT");
}

EXECUTE_FUNC(executeCMC)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("CMC");
    u8 CF=registerFile.getFlagsBits().CF;
    registerFile.getFlagsBits().CF=~CF;
}
//group 3

EXECUTE_FUNC(executeNOT)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("NOT");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
        dest->setU8(~dest->getS8());
        break;
    case DATA_SIZE_WORD:
        dest->setU16(~dest->getS16());
        break;
    case DATA_SIZE_DWORD:
        dest->setU32(~dest->getS32());
        break;
    case DATA_SIZE_QWORD:
        dest->setU64(~dest->getS64());
        break;
    default:
        assert(0);
    }
}

EXECUTE_FUNC(executeNEG)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("NEG");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        s8 opt1=0;
        s8 opt2=dest->getS8();
        s8 result=opt1-opt2;
        dest->setU8(result);

        u8 msbOpt1=u8((opt1>>7)&1);
        u8 msbOpt2=u8((opt2>>7)&1);
        u8 msbResult=u8((result>>7)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    case DATA_SIZE_WORD:
    {
        s16 opt1=0;
        s16 opt2=dest->getS16();
        s16 result=opt1-opt2;
        dest->setU16(result);

        u8 msbOpt1=u8((opt1>>15)&1);
        u8 msbOpt2=u8((opt2>>15)&1);
        u8 msbResult=u8((result>>15)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        s32 opt1=0;
        s32 opt2=dest->getS32();
        s32 result=opt1-opt2;
        dest->setU32(result);

        u8 msbOpt1=u8((opt1>>31)&1);
        u8 msbOpt2=u8((opt2>>31)&1);
        u8 msbResult=u8((result>>31)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    case DATA_SIZE_QWORD:
    {
        s64 opt1=0;
        s64 opt2=dest->getS64();
        s64 result=opt1-opt2;
        dest->setU64(result);

        u8 msbOpt1=u8((opt1>>63)&1);
        u8 msbOpt2=u8((opt2>>63)&1);
        u8 msbResult=u8((result>>63)&1);
        setCarryFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        setParityFlag(registerFile.getFlagsBits(),u8(result&0xff));
        setAuxiliaryCarryFlag(registerFile.getFlagsBits(),u8((opt1>>3)&1),u8((opt2>>3)&1),false,u8((result>>3)&1));
        setZeroFlag(registerFile.getFlagsBits(),result);
        setSignFlag(registerFile.getFlagsBits(),msbResult);
        setOverflowFlag(registerFile.getFlagsBits(),msbOpt1,msbOpt2,false,msbResult);
        break;
    }
    default:
        assert(0);
    }
}

EXECUTE_FUNC(executeMUL1)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("MUL1");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        u16 a=u8(registerFile.getGPR8Bits(RAX));
        u16 b=dest->getU8();
        u16 c=a*b;
        u8 result=c&0xff;
        registerFile.setGPR16Bits(RAX,c);
        if(result==c)
        {
           registerFile.getFlagsBits().OF=0;
           registerFile.getFlagsBits().CF=0;
        }
        else
        {
            registerFile.getFlagsBits().OF=1;
            registerFile.getFlagsBits().CF=1;
        }
        break;
    }
    case DATA_SIZE_WORD:
    {
        u32 a=u16(registerFile.getGPR16Bits(RAX));
        u32 b=dest->getU16();
        u32 c=a*b;
        u16 result=c&0xffff;

        registerFile.setGPR16Bits(RAX,c&0xffff);
        registerFile.setGPR16Bits(RDX,(c>>16)&0xffff);
        if(result==c)
        {
           registerFile.getFlagsBits().OF=0;
           registerFile.getFlagsBits().CF=0;
        }
        else
        {
            registerFile.getFlagsBits().OF=1;
            registerFile.getFlagsBits().CF=1;
        }
        break;
    }
    case DATA_SIZE_DWORD:
    {
        u64 a=u32(registerFile.getGPR32Bits(RAX));
        u64 b=dest->getU32();
        u64 c=a*b;
        u32 result=c&0xffffffff;
//        dest->setU32(result);
        registerFile.setGPR32Bits(RAX,c&0xffffffff);
        registerFile.setGPR32Bits(RDX,(c>>32)&0xffffffff);
        if(result==c)
        {
           registerFile.getFlagsBits().OF=0;
           registerFile.getFlagsBits().CF=0;
        }
        else
        {
            registerFile.getFlagsBits().OF=1;
            registerFile.getFlagsBits().CF=1;
        }
        break;
    }
    case DATA_SIZE_QWORD:
        assert(0);
        break;
    default:
        assert(0);
    }
}

EXECUTE_FUNC(executeIMUL1)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("IMUL1");

    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        s16 a=s8(registerFile.getGPR8Bits(RAX));
        s16 b=dest->getS8();
        s16 c=a*b;
        s8 result=c&0xff;
        registerFile.setGPR16Bits(RAX,c);
        if(result==c)
        {
           registerFile.getFlagsBits().OF=0;
           registerFile.getFlagsBits().CF=0;
        }
        else
        {
            registerFile.getFlagsBits().OF=1;
            registerFile.getFlagsBits().CF=1;
        }
        break;
    }
    case DATA_SIZE_WORD:
    {
        s32 a=s16(registerFile.getGPR16Bits(RAX));
        s32 b=dest->getS16();
        s32 c=a*b;
        s16 result=c&0xffff;

        registerFile.setGPR16Bits(RAX,c&0xffff);
        registerFile.setGPR16Bits(RDX,(c>>16)&0xffff);
        if(result==c)
        {
           registerFile.getFlagsBits().OF=0;
           registerFile.getFlagsBits().CF=0;
        }
        else
        {
            registerFile.getFlagsBits().OF=1;
            registerFile.getFlagsBits().CF=1;
        }
        break;
    }
    case DATA_SIZE_DWORD:
    {
        s64 a=s32(registerFile.getGPR32Bits(RAX));
        s64 b=dest->getS32();
        s64 c=a*b;
        s32 result=c&0xffffffff;
//        dest->setU32(result);
        registerFile.setGPR32Bits(RAX,c&0xffffffff);
        registerFile.setGPR32Bits(RDX,(c>>32)&0xffffffff);
        if(result==c)
        {
           registerFile.getFlagsBits().OF=0;
           registerFile.getFlagsBits().CF=0;
        }
        else
        {
            registerFile.getFlagsBits().OF=1;
            registerFile.getFlagsBits().CF=1;
        }
        break;
    }
    case DATA_SIZE_QWORD:
        assert(0);
        break;
    default:
        assert(0);
    }
}

EXECUTE_FUNC(executeDIV1)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("DIV1");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        u16 dividend=registerFile.getGPR16Bits(RAX);
        u8 divisor=dest->getU8();
        if(divisor==0)
        {
            assert(0);
        }
        u8 quotient=dividend/divisor;
        u8 remainder=dividend%divisor;
        registerFile.setGPR8BitsLow(RAX,quotient);
        registerFile.setGPR8BitsHigh(RAX,remainder);
        break;
    }
    case DATA_SIZE_WORD:
    {
        u32 dividend=(u32(registerFile.getGPR16Bits(RDX))<<16)|registerFile.getGPR16Bits(RAX);
        u16 divisor=dest->getU16();
        if(divisor==0)
        {
            assert(0);
        }
        u16 quotient=dividend/divisor;
        u16 remainder=dividend%divisor;
        registerFile.setGPR16Bits(RAX,quotient);
        registerFile.setGPR16Bits(RDX,remainder);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        u64 dividend=(u64(registerFile.getGPR32Bits(RDX))<<32)|registerFile.getGPR32Bits(RAX);
        u32 divisor=dest->getU32();
        if(divisor==0)
        {
            assert(0);
        }
        u32 quotient=dividend/divisor;
        u32 remainder=dividend%divisor;
        registerFile.setGPR32Bits(RAX,quotient);
        registerFile.setGPR32Bits(RDX,remainder);
        break;
    }
    default:
        assert(0);
    }
}

EXECUTE_FUNC(executeIDIV1)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("IDIV1");
    switch(dest->getSize())
    {
    case DATA_SIZE_BYTE:
    {
        s16 dividend=s16(registerFile.getGPR16Bits(RAX));
        s8 divisor=dest->getS8();
        if(divisor==0)
        {
            assert(0);
        }
        s8 quotient=dividend/divisor;
        s8 remainder=dividend%divisor;
        registerFile.setGPR8BitsLow(RAX,quotient);
        registerFile.setGPR8BitsHigh(RAX,remainder);
        break;
    }
    case DATA_SIZE_WORD:
    {
        s32 dividend=s32((u32(registerFile.getGPR16Bits(RDX))<<16)|registerFile.getGPR16Bits(RAX));
        s16 divisor=dest->getS16();
        if(divisor==0)
        {
            assert(0);
        }
        s16 quotient=dividend/divisor;
        s16 remainder=dividend%divisor;
        registerFile.setGPR16Bits(RAX,quotient);
        registerFile.setGPR16Bits(RDX,remainder);
        break;
    }
    case DATA_SIZE_DWORD:
    {
        s64 dividend=s64((u64(registerFile.getGPR32Bits(RDX))<<32)|registerFile.getGPR32Bits(RAX));
        s32 divisor=dest->getS32();
        if(divisor==0)
        {
            assert(0);
        }
        s32 quotient=dividend/divisor;
        s32 remainder=dividend%divisor;
        registerFile.setGPR32Bits(RAX,quotient);
        registerFile.setGPR32Bits(RDX,remainder);
        break;
    }
    default:
        assert(0);
    }
}


EXECUTE_FUNC(executeCLC)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    registerFile.getFlagsBits().CF=0;
//    INSTRUCTION_NOT_IMPLEMENT("CLC");
}

EXECUTE_FUNC(executeSTC)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    registerFile.getFlagsBits().CF=1;
//    INSTRUCTION_NOT_IMPLEMENT("STC");
}

EXECUTE_FUNC(executeCLI)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    registerFile.getFlagsBits().IF=0;
//    INSTRUCTION_NOT_IMPLEMENT("CLI");
}

EXECUTE_FUNC(executeSTI)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    registerFile.getFlagsBits().IF=1;
//    INSTRUCTION_NOT_IMPLEMENT("STI");
}

EXECUTE_FUNC(executeCLD)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    registerFile.getFlagsBits().DF=0;
//    INSTRUCTION_NOT_IMPLEMENT("CLD");
}

EXECUTE_FUNC(executeSTD)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    registerFile.getFlagsBits().DF=1;
//    INSTRUCTION_NOT_IMPLEMENT("STD");
}


//group 4

//group 5

EXECUTE_FUNC(executeCALLNEAR_Ev)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("CALL_Ev");
    switch(effectiveOperandSize)
    {
    case EFFECTIVE_16_BITS:
        PUSH<u16>((u16)registerFile.getIP(),effectiveAddressSize,memory,registerFile);
        registerFile.setIP(dest->getU16());
        break;
    case EFFECTIVE_32_BITS:
        PUSH<u32>((u32)registerFile.getIP(),effectiveAddressSize,memory,registerFile);
        registerFile.setIP(dest->getU32());
        break;
    case EFFECTIVE_64_BITS:
        PUSH<u64>((u64)registerFile.getIP(),effectiveAddressSize,memory,registerFile);
        registerFile.setIP((u32)dest->getU64());
        break;
    default:
        assert(0);
    }
}

EXECUTE_FUNC(executeJMPNEAR_Ev)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)effectiveOperandSize;(void)effectiveSegmentRegister;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("JMP_Ev");
    switch(effectiveOperandSize)
    {
    case EFFECTIVE_16_BITS:
//        PUSH<u16>((u16)registerFile.getIP(),effectiveAddressSize,memory,registerFile);
        registerFile.setIP(dest->getU16());
        break;
    case EFFECTIVE_32_BITS:
//        PUSH<u32>((u32)registerFile.getIP(),effectiveAddressSize,memory,registerFile);
        registerFile.setIP(dest->getU32());
        break;
    case EFFECTIVE_64_BITS:
//        PUSH<u64>((u64)registerFile.getIP(),effectiveAddressSize,memory,registerFile);
        registerFile.setIP((u32)dest->getU64());
        break;
    default:
        assert(0);
    }
}

