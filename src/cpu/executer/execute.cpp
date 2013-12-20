#include "execute.h"
#include <iostream>
#include <stdlib.h>
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
    if(!isPlus) msbOpt2=~msbOpt2;
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
    (void)effectiveAddressSize;
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
EXECUTE_FUNC(executePUSH)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("PUSH");
    //get data size.
    u8 dataSize=0;
    switch(dest->getSize())
    {
    case DATA_SIZE_WORD:
        dataSize=2;
        break;
    case DATA_SIZE_DWORD:
        dataSize=4;
        break;
    case DATA_SIZE_QWORD:
        dataSize=8;
    default:
        assert(0);
    }

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
    switch(dest->getSize())
    {
    case DATA_SIZE_WORD:
        memory.set16Bits(address,dest->getS16());
        break;
    case DATA_SIZE_DWORD:
        memory.set32Bits(address,dest->getS32());
        break;
    case DATA_SIZE_QWORD:
        memory.set64Bits(address,dest->getS64());
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
EXECUTE_FUNC(executePOP)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
//    INSTRUCTION_NOT_IMPLEMENT("POP");
    u32 address=registerFile.getSSR(SS);
    switch(effectiveAddressSize)
    {
    case EFFECTIVE_16_BITS:
        address+=registerFile.getGPR16Bits(RSP);
        break;
    case EFFECTIVE_32_BITS:
    case EFFECTIVE_64_BITS:
        address+=registerFile.getGPR32Bits(RSP);
        break;
    }

    u8 dataSize=0;
    memory.startAccess(memory.CPU_DATA_ACCESS);
    switch(dest->getSize())
    {
    case DATA_SIZE_WORD:
        dataSize=2;
        dest->setU16(memory.get16Bits(address));
        break;
    case DATA_SIZE_DWORD:
        dataSize=4;
        dest->setU32(memory.get32Bits(address));
        break;
    case DATA_SIZE_QWORD:
        dataSize=8;
        dest->setU64(memory.get64Bits(address));
        break;
    default:
        assert(0);
    }
    memory.endAccess();

    switch(effectiveAddressSize)
    {
    case EFFECTIVE_16_BITS:
        registerFile.setGPR16Bits(RSP,registerFile.getGPR16Bits(RSP)+dataSize);
        break;
    case EFFECTIVE_32_BITS:
    case EFFECTIVE_64_BITS:
        registerFile.setGPR32Bits(RSP,registerFile.getGPR32Bits(RSP)+dataSize);
        break;
    }
}
EXECUTE_FUNC(executeOR)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
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
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("ADC");
}
EXECUTE_FUNC(executeSBB)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("SBB");
}
//0x2
EXECUTE_FUNC(executeAND)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
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
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("DAA");
}
EXECUTE_FUNC(executeSUB)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("SUB");
}
EXECUTE_FUNC(executeDAS)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("DAS");
}
//0x3
EXECUTE_FUNC(executeXOR)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
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
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("AAA");
}
EXECUTE_FUNC(executeCMP)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("CMP");
}
EXECUTE_FUNC(executeAAS)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("AAS");
}
//0x4
EXECUTE_FUNC(executeINC)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("INC");
}
EXECUTE_FUNC(executeDEC)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("DEC");
}
//0x5
//0x6
EXECUTE_FUNC(executePUSHAD)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("PUSHAD");
}
EXECUTE_FUNC(executePOPAD)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("POPAD");
}
EXECUTE_FUNC(executeBOUND)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("BOUND");
}
EXECUTE_FUNC(executeARPL)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("ARPL");
}
EXECUTE_FUNC(executeIMUL3) //IMUL with 3 operands.
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("IMUL3");
}
EXECUTE_FUNC(executeINSB)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("INSB");
}
EXECUTE_FUNC(executeINSWD)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("INSWD");
}
EXECUTE_FUNC(executeOUTB)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("OUTB");
}
EXECUTE_FUNC(executeOUTSWD)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("OUTSWD");
}
//0x7
EXECUTE_FUNC(executeJO)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JO");
}
EXECUTE_FUNC(executeJNO)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JNO");
}
EXECUTE_FUNC(executeJB)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JB");
}
EXECUTE_FUNC(executeJNB)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JNB");
}
EXECUTE_FUNC(executeJZ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JZ");
}
EXECUTE_FUNC(executeJNZ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JNZ");
}
EXECUTE_FUNC(executeJBE)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JBE");
}
EXECUTE_FUNC(executeJNBE)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JNBE");
}
EXECUTE_FUNC(executeJS)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JS");
}
EXECUTE_FUNC(executeJNS)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JNS");
}
EXECUTE_FUNC(executeJP)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JP");
}
EXECUTE_FUNC(executeJNP)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JNP");
}
EXECUTE_FUNC(executeJL)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JL");
}
EXECUTE_FUNC(executeJNL)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JNL");
}
EXECUTE_FUNC(executeJLE)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JLE");
}
EXECUTE_FUNC(executeJNLE)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JNLE");
}
//0x8
EXECUTE_FUNC(executeTEST)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("TEST");
}
EXECUTE_FUNC(executeXCHG)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("XCHG");
}
EXECUTE_FUNC(executeMOVE)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("MOVE");
}
EXECUTE_FUNC(executeLEA)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("LEA");
}
//0x9
EXECUTE_FUNC(executeCBW_CWDE_CDQE)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("CBW_CWDE_CDQE");
}
EXECUTE_FUNC(executeCWD_CDQ_CQO)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("CWD_CDQ_CQO");
}
EXECUTE_FUNC(executeCALL_Ap)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("CALL_Ap");
}
EXECUTE_FUNC(executeWAIT_FWAIT)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("WAIT_FWAIT");
}
EXECUTE_FUNC(executePUSHFDQ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("PUSHFDQ");
}
EXECUTE_FUNC(executePOPFDQ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("POPFDQ");
}
EXECUTE_FUNC(executeSAHF)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("SAHF");
}
EXECUTE_FUNC(executeLAHF)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("LAHF");
}
//0xa
EXECUTE_FUNC(executeMOVSB)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("MOVSB");
}
EXECUTE_FUNC(executeMOVSWDQ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("MOVSWDQ");
}
EXECUTE_FUNC(executeCMPSB)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("CMPSB");
}
EXECUTE_FUNC(executeCMPSWDQ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("CMPSWDQ");
}
EXECUTE_FUNC(executeSTOSB)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("STOSB");
}
EXECUTE_FUNC(executeSTOSWDQ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("STOSWDQ");
}
EXECUTE_FUNC(executeLODSB)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("LODSB");
}
EXECUTE_FUNC(executeLODSWDQ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("LODSWDQ");
}
EXECUTE_FUNC(executeSCASB)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("SCASB");
}
EXECUTE_FUNC(executeSCASWDQ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("SCASWDQ");
}
//0xb
//0xc
//group2
EXECUTE_FUNC(executeROL)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("ROL");
}
EXECUTE_FUNC(executeROR)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("ROR");
}
EXECUTE_FUNC(executeRCL)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("RCL");
}
EXECUTE_FUNC(executeRCR)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("RCR");
}
//EXECUTE_FUNC(executeSHL_SAL)
//{

//}
EXECUTE_FUNC(executeSHR)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("SHR");
}
EXECUTE_FUNC(executeSHL_SAL)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("SAL");
}
EXECUTE_FUNC(executeSAR)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("SAR");
}
EXECUTE_FUNC(executeRETNEAR)//only this one.
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("RETNEAR");
}
EXECUTE_FUNC(executeLES)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("LES");
}
EXECUTE_FUNC(executeLDS)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("LDS");
}

EXECUTE_FUNC(executeENTER)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("ENTER");
}
EXECUTE_FUNC(executeLEAVE)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("LEAVE");
}
EXECUTE_FUNC(executeRETFAR)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("RETFAR");
}
EXECUTE_FUNC(executeINT3)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("INT3");
}
EXECUTE_FUNC(executeINT)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("INT");
}
EXECUTE_FUNC(executeINTO)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("INTO");
}
EXECUTE_FUNC(executeIRET_IRETD_IRETQ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("IRET_IRETD_IRETQ");
}

//0xd
EXECUTE_FUNC(executeAAM)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("AAM");
}
EXECUTE_FUNC(executeAAD)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("AAD");
}
EXECUTE_FUNC(executeSALC)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("SALC");
}
EXECUTE_FUNC(executeXLAT)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("XLAT");
}

//0xe
EXECUTE_FUNC(executeLOOPNZ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("LOOPNZ");
}
EXECUTE_FUNC(executeLOOPZ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("LOOPZ");
}
EXECUTE_FUNC(executeLOOP)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("LOOP");
}
EXECUTE_FUNC(executeJRCXZ)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JRCXZ");
}
EXECUTE_FUNC(executeIN)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("IN");
}
EXECUTE_FUNC(executeOUT)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("OUT");
}
EXECUTE_FUNC(executeCALL_Jz)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("CALL_Jz");
}
EXECUTE_FUNC(executeJMP_J)//includes Jz & Jb
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JMP_J");
}
EXECUTE_FUNC(executeJMP_p)//includes Mp or Ap
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JMP_p");
}
//0xf
EXECUTE_FUNC(executeINT1)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("INT1");
}
EXECUTE_FUNC(executeHLT)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("HLT");
}
EXECUTE_FUNC(executeCMC)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("CMC");
}
//group 3
EXECUTE_FUNC(executeNOT)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("NOT");
}
EXECUTE_FUNC(executeNEG)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("NEG");
}
EXECUTE_FUNC(executeMUL1)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("MUL1");
}
EXECUTE_FUNC(executeIMUL1)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("IMUL1");

}
EXECUTE_FUNC(executeDIV1)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("DIV1");
}
EXECUTE_FUNC(executeIDIV1)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("IDIV1");
}

EXECUTE_FUNC(executeCLC)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    registerFile.getFlagsBits().CF=0;
//    INSTRUCTION_NOT_IMPLEMENT("CLC");
}
EXECUTE_FUNC(executeSTC)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    registerFile.getFlagsBits().CF=1;
//    INSTRUCTION_NOT_IMPLEMENT("STC");
}
EXECUTE_FUNC(executeCLI)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    registerFile.getFlagsBits().IF=0;
//    INSTRUCTION_NOT_IMPLEMENT("CLI");
}
EXECUTE_FUNC(executeSTI)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    registerFile.getFlagsBits().IF=1;
//    INSTRUCTION_NOT_IMPLEMENT("STI");
}
EXECUTE_FUNC(executeCLD)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    registerFile.getFlagsBits().DF=0;
//    INSTRUCTION_NOT_IMPLEMENT("CLD");
}
EXECUTE_FUNC(executeSTD)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    registerFile.getFlagsBits().DF=1;
//    INSTRUCTION_NOT_IMPLEMENT("STD");
}

//group 4

//group 5
EXECUTE_FUNC(executeCALL_Ev)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("CALL_Ev");
}
EXECUTE_FUNC(executeJMP_Ev)
{
    (void)operatingEnvironment;(void)effectiveAddressSize;(void)dest;(void)src;(void)src2;(void)memory;(void)registerFile;(void)ioPortList;
    INSTRUCTION_NOT_IMPLEMENT("JMP_Ev");
}
