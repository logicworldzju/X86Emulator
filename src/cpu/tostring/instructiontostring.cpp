#include "instructiontostring.h"
#include <assert.h>
#include <stdio.h>
InstructionToString::InstructionToString()
{
}

void InstructionToString::toString(InstructionHighLevelFormat &highFormat,
                                   std::string &inst)
{
    inst.clear();
    //--------------------------Legacy Prefix-----------------------------
    if(highFormat.legacyPrefix.lock)
    {
        inst+="lock ";
    }
    if(highFormat.legacyPrefix.repnz)
    {
        inst+="repnz ";
    }
    if(highFormat.legacyPrefix.rep_repz)
    {
        inst+="repz ";
    }
    //------------------------------Opcode---------------------------------
    inst+=highFormat.opcode->name+" ";
    //------------------------------DestOperand----------------------------
    if(highFormat.dest.isExists)
    {
        operandToString(highFormat,inst,highFormat.dest);
    }
    //-------------------------------SrcOperand----------------------------
    if(highFormat.src.isExists)
    {
        inst+=",";
        operandToString(highFormat,inst,highFormat.src);
    }
    //-------------------------------Src2Operand----------------------------
    if(highFormat.src2.isExists)
    {
        inst+=",";
        operandToString(highFormat,inst,highFormat.src2);
    }
}

void InstructionToString::operandToString(InstructionHighLevelFormat &highFormat,
                                          std::string &inst, IFOperand &operand)
{
    if(operand.isExists)
    {
        switch(operand.type)
        {
        case IFOperand::IMMEDIATE:
        {
            immediateToString(highFormat,inst,operand);
            break;
        }
        case IFOperand::GP_REGISTER:
        {
            gpRegisterToString(highFormat,inst,operand);
            break;
        }
        case IFOperand::SEGMENT_REGISTER:
        {
            segementRegisterToString(highFormat,inst,operand);
            break;
        }
        case IFOperand::MEMORY_MODRM:
        {
            memoryModRMToString(highFormat,inst,operand);
            break;
        }
        case IFOperand::MEMORY_OFFSETS:
        {
            moffsetsToString(highFormat,inst,operand);
            break;
        }
        default:
        {
            assert(0);
            break;
        }
        }
    }
}

void InstructionToString::immediateToString(InstructionHighLevelFormat &highFormat,
                                            std::string &inst, IFOperand &operand)
{
    assert(operand.isExists);
    assert(operand.type==IFOperand::IMMEDIATE);

    OTOperandType type;
    if(&operand==&highFormat.dest)
    {
        type=highFormat.opcode->dest.type;
    }
    else if(&operand==&highFormat.src)
    {
        type=highFormat.opcode->src.type;
    }
    else if(&operand==&highFormat.src2)
    {
        type=highFormat.opcode->src2.type;
    }
    else
    {
        assert(0);
    }
    switch(type)
    {
    case OT_A:
    {
        switch(operand.finalSize)
        {
        case DATA_SIZE_DWORD:
        {
            std::string selectorString;
            std::string dispString;
            u64ToString(u16(operand.content.immediate.valueU32>>16),selectorString);
            u64ToString(operand.content.immediate.valueU32&0xffff,dispString);
            inst+=selectorString+":"+dispString;
            break;
        }
        case DATA_SIZE_6BYTES:
        {
            std::string selectorString;
            std::string dispString;
            u64ToString(u16(operand.content.immediate.valueU48>>32),selectorString);
            u64ToString(u32(operand.content.immediate.valueU48&0xffffffff),dispString);
            inst+=selectorString+":"+dispString;
            break;
        }
        default:
            assert(0);
        }
        break;
    }
    case OT_J:
    {
        std::string relativeString;
        switch(operand.finalSize)
        {
        case DATA_SIZE_BYTE:
            relativeAddressToString(operand.content.immediate.valueS8,relativeString);
            break;
        case DATA_SIZE_WORD:
            relativeAddressToString(operand.content.immediate.valueS16,relativeString);
            break;
        case DATA_SIZE_DWORD:
            relativeAddressToString(operand.content.immediate.valueS32,relativeString);
            break;
        case DATA_SIZE_QWORD:
            relativeAddressToString(operand.content.immediate.valueS64,relativeString);
            break;
        default:
            assert(0);
            break;
        }
        inst+=relativeString;
        break;
    }
    default:
    {
        u8 index = static_cast<u8>(operand.finalSize);
        assert(index<7);
        inst=inst+_dataSizeString[index]+" ";
        std::string immString;
        dispImmSignedToString(operand.content.immediate,operand.finalSize,immString);
        inst+=immString;
        break;
    }
    }
}

void InstructionToString::segementRegisterToString(InstructionHighLevelFormat &highFormat,
                                                   std::string &inst, IFOperand &operand)
{
	(void)highFormat;

    assert(operand.isExists);
    assert(operand.type==IFOperand::SEGMENT_REGISTER);

    u8 index=static_cast<u8>(operand.content.segmentRegister);
    assert(index<6);
    inst+=_segmentRegisterString[index];
}

void InstructionToString::gpRegisterToString(InstructionHighLevelFormat &highFormat,
                                             std::string &inst, IFOperand &operand)
{
    assert(operand.isExists);
    assert(operand.type==IFOperand::GP_REGISTER);

    u8 index=static_cast<u8>(operand.content.gpregister);
    switch(operand.finalSize)
    {
    case DATA_SIZE_BYTE:
    {
        if(highFormat.hasRexPrefix)
        {
            assert(index<16);
            inst+=_gpRegister8BitsLowString[index];
        }
        else
        {
            assert(index<8);
            inst+=_gpRegister8BitsString[index];
        }
        break;
    }
    case DATA_SIZE_WORD:
        assert(index<16);
        inst+=_gpRegister16BitsString[index];
        break;
    case DATA_SIZE_DWORD:
        assert(index<16);
        inst+=_gpRegister32BitsString[index];
        break;
    case DATA_SIZE_QWORD:
        assert(index<16);
        inst+=_gpRegister64BitsString[index];
        break;
    default:
        break;
    }
}

void InstructionToString::memoryModRMToString(InstructionHighLevelFormat &highFormat,
                                              std::string &inst, IFOperand &operand)
{
    assert(operand.isExists);
    assert(operand.type==IFOperand::MEMORY_MODRM);

    //----------------Data Size Prefix------------------
    {
        u8 index=static_cast<u8>(operand.finalSize);
        assert(index<7);
        inst+=_dataSizeString[index];
    }
    //------------Segment Register Prefix---------------
    inst+="[";
    if(operand.content.memory.finalMemorySegmentRegister
            !=operand.content.memory.defaultMemorySegmentRegister)
    {
        u8 index=static_cast<u8>(operand.content.memory.finalMemorySegmentRegister);
        assert(index<6);
        inst+=_segmentRegisterString[index];
        inst+=":";
    }
    if(highFormat.effectiveAddressSize==EFFECTIVE_16_BITS)
    {
        memoryModRM16BitsToString(highFormat,inst,operand);
    }
    else
    {
        memoryModRM3264BitsToString(highFormat,inst,operand);
    }
    inst+="]";
}

void InstructionToString::moffsetsToString(InstructionHighLevelFormat &highFormat,
                                           std::string &inst, IFOperand &operand)
{
    assert(operand.isExists);
    assert(operand.type==IFOperand::MEMORY_OFFSETS);

    std::string dispString;
    DataSize moffsetSize;
    switch(highFormat.effectiveAddressSize)
    {
    case EFFECTIVE_16_BITS:
        moffsetSize=DATA_SIZE_WORD;
        break;
    case EFFECTIVE_32_BITS:
        moffsetSize=DATA_SIZE_DWORD;
        break;
    case EFFECTIVE_64_BITS:
        moffsetSize=DATA_SIZE_QWORD;
        break;
    }
    dispImmUnsignedToString(operand.content.memory.memoryMode.moffsets,moffsetSize,
                         dispString);
    {
        u8 index = static_cast<u8>(operand.finalSize);
        assert(index<7);
        inst+=_dataSizeString[index];
    }
    if(operand.content.memory.finalMemorySegmentRegister
            !=operand.content.memory.defaultMemorySegmentRegister)
    {
        u8 index = static_cast<u8>(operand.content.memory.finalMemorySegmentRegister);
        assert(index<6);
        inst=inst+"["+_segmentRegisterString[index]+":"+dispString+"]";
    }
    else
    {
        inst=inst+"["+dispString+"]";
    }

}

/*
enum SegmentRegister
{
    ES=0,CS,SS,DS,FS,GS
};
*/
const char* InstructionToString::_segmentRegisterString[6]=
{
    "es","cs","ss","ds","fs","gs"
};
/*
enum GPRegister
{
    RAX=0,RCX,RDX,RBX,RSP,RBP,RSI,RDI,R8,R9,R10,R11,R12,R13,R14,R15
};
*/
const char* InstructionToString::_gpRegister8BitsLowString[16]=
{
    "al","cl","dl","bl","spl","bpl","sil","dil","r8b","r9b","r10b","r11b","r12b"
    ,"r13b","r14b","r15b"
};
const char* InstructionToString::_gpRegister8BitsString[8]=
{
    "al","cl","dl","bl","ah","ch","dh","bh"
};
const char* InstructionToString::_gpRegister16BitsString[16]=
{
    "ax","cx","dx","bx","sp","bp","si","di","r8w","r9w","r10w","r11w","r12w"
    ,"r13w","r14w","r15w"
};
const char* InstructionToString::_gpRegister32BitsString[16]=
{
    "eax","ecx","edx","ebx","esp","ebp","esi","edi","r8d","r9d","r10d","r11d",
    "r12d","r13d","r14d","r15d"
};
const char* InstructionToString::_gpRegister64BitsString[16]=
{
    "rax","rcx","rdx","rbx","rsp","rbp","rsi","rdi","r8","r9","r10","r11","r12"
    ,"r13","r14","r15"
};
/*
enum ControlRegister
{
    CR0=0,CR1,CR2,CR3,CR4,CR5,CR6,CR7,CR8,CR9,CR10,CR11,CR12,CR13,CR14,CR15
};
*/
const char* InstructionToString::_controlRegisterString[16]=
{
    "CR0","CR1","CR2","CR3","CR4","CR5","CR6","CR7","CR8","CR9","CR10","CR11",
    "CR12","CR13","CR14","CR15"
};
/*
enum DebugRegister
{
    DR0=0,DR1,DR2,DR3,DR4,DR5,DR6,DR7,DR8,DR9,DR10,DR11,DR12,DR13,DR14,DR15
};
*/
const char* InstructionToString::_debugRegisterString[16]=
{
    "DR0","DR1","DR2","DR3","DR4","DR5","DR6","DR7","DR8","DR9","DR10","DR11"
    ,"DR12","DR13","DR14","DR15"
};
/*
enum MMXRegister
{
    MMX0=0,MMX1,MMX2,MMX3,MMX4,MMX5,MMX6,MMX7
};
*/
const char* InstructionToString::_mmxRegisterString[8]=
{
    "MMX0","MMX1","MMX2","MMX3","MMX4","MMX5","MMX6","MMX7"
};
/*
enum XMMRegister
{
    XMM0=0,XMM1,XMM2,XMM3,XMM4,XMM5,XMM6,XMM7,XMM8,XMM9,XMM10,XMM11,XMM12,XMM13,XMM14,XMM15
};
*/
const char* InstructionToString::_xmmRegisterString[16]=
{
    "XMM0","XMM1","XMM2","XMM3","XMM4","XMM5","XMM6","XMM7","XMM8","XMM9"
    ,"XMM10","XMM11","XMM12","XMM13","XMM14","XMM15"
};
/*
enum DataSize
{
    DATA_SIZE_BYTE=0,
    DATA_SIZE_WORD,
    DATA_SIZE_DWORD,
    DATA_SIZE_6BYTES,
    DATA_SIZE_QWORD,
    DATA_SIZE_DQWORD,
    DATA_SIZE_10BYTES
};
*/
const char* InstructionToString::_dataSizeString[7]=
{
    "byte","word","dword","6bytes","qword","dqword","10bytes"
};
const char* InstructionToString::_modrm16BitsString[3][8]=
{
    {"bx+si","bx+di","bp+si","bp+di","si","di","","bx"},
    {"bx+si","bx+di","bp+si","bp+di","si","di","bp","bx"},
    {"bx+si","bx+di","bp+si","bp+di","si","di","bp","bx"}
};
void InstructionToString::relativeAddressToString(s32 relativeAddress, std::string &str)
{
    str+="nextRIP";
    std::string addressString;
    s64ToString(relativeAddress,addressString,true);
    str+=addressString;
}

void InstructionToString::s64ToString(s64 value, std::string &str,bool withPlus)
{
    if(value<0)
    {
        u64ToString(-value,str);
        str="-"+str;
    }
    else
    {
        u64ToString(value,str);
        if(withPlus)
        {
            str="+"+str;
        }
    }
}

void InstructionToString::u64ToString(u64 value, std::string &str)
{
    bool didnotSeeOne=true;
    u8 dataLength=8;
    for(int i=2*dataLength-1; i>=0; i--)
    {
        u8 asciiHex=u8((value>>(i*4))&0xf);
        if(didnotSeeOne==true && asciiHex==0)
        {

        }
        else
        {
            didnotSeeOne=false;
            char ascii='0'+asciiHex;
            if(asciiHex>9)
            {
                ascii='a'+asciiHex-10;
            }
            str.push_back(ascii);
        }
    }
    if(didnotSeeOne)
    {
        str+="0";
    }
    str+="h";
}

void InstructionToString::dispImmSignedToString(DispImm dispImm, DataSize size,
                                                std::string &dispImmString
                                                ,bool withPlus)
{
    s64 value;
    switch(size)
    {
    case DATA_SIZE_BYTE:
        value=dispImm.valueS8;
        break;
    case DATA_SIZE_WORD:
        value=dispImm.valueS16;
        break;
    case DATA_SIZE_DWORD:
        value=dispImm.valueS32;
        break;
    case DATA_SIZE_6BYTES:
        value=dispImm.valueS48;
        break;
    case DATA_SIZE_QWORD:
        value=dispImm.valueS64;
        break;
    default:
        assert(0);
        break;
    }
    s64ToString(value,dispImmString,withPlus);
}

void InstructionToString::dispImmUnsignedToString(DispImm dispImm, DataSize size,
                                               std::string &dispImmString)
{
    u64 value;
    switch(size)
    {
    case DATA_SIZE_BYTE:
        value=dispImm.valueU8;
        break;
    case DATA_SIZE_WORD:
        value=dispImm.valueU16;
        break;
    case DATA_SIZE_DWORD:
        value=dispImm.valueU32;
        break;
    case DATA_SIZE_6BYTES:
        value=dispImm.valueU48;
        break;
    case DATA_SIZE_QWORD:
        value=dispImm.valueU64;
        break;
    default:
        assert(0);
        break;
    }
    u64ToString(value,dispImmString);
}

void InstructionToString::memoryModRM16BitsToString(InstructionHighLevelFormat &highFormat,
                                                    std::string &inst, IFOperand &operand)
{
    assert(operand.type==IFOperand::MEMORY_MODRM);
    assert(highFormat.effectiveAddressSize==EFFECTIVE_16_BITS);

    IFOperand::Content::Memory::MemoryMode::Bit16Mode&
            bit16Mode=operand.content.memory.memoryMode.bit16Mode;

    assert(bit16Mode.modRM.mod!=3);
    inst+=_modrm16BitsString[bit16Mode.modRM.mod][bit16Mode.modRM.rm];

    std::string dispString;
    if(bit16Mode.modRM.mod==1)
    {
        s64ToString(bit16Mode.disp.valueS8,dispString,true);
    }
    if(bit16Mode.modRM.mod==2)
    {
        s64ToString(bit16Mode.disp.valueS16,dispString,true);
    }
    if(bit16Mode.modRM.mod==0 && bit16Mode.modRM.rm==6)
    {
        u64ToString(bit16Mode.disp.valueU16,dispString);
    }
    inst+=dispString;
}
//const char* InstructionToString::_moderm3264BitsString[3][16]=
//{
//    {},
//    {},
//    {}
//};
void InstructionToString::memoryModRM3264BitsToString(
        InstructionHighLevelFormat &highFormat,
        std::string &inst, IFOperand &operand)
{
    assert(operand.type==IFOperand::MEMORY_MODRM);
    assert(highFormat.effectiveAddressSize!=EFFECTIVE_16_BITS);

    const char** gpRegister3264BitsString=NULL;
    if(highFormat.effectiveAddressSize==EFFECTIVE_32_BITS)
    {
        gpRegister3264BitsString=_gpRegister32BitsString;
    }
    else
    {
        gpRegister3264BitsString=_gpRegister64BitsString;
    }

    IFOperand::Content::Memory::MemoryMode::Bit3264Mode& bit3264Mode=
            operand.content.memory.memoryMode.bit3264Mode;
    u8 mod = bit3264Mode.modRM.mod;
    u8 rm = bit3264Mode.modRM.rm;
    u8 rm3Bits=rm&0x7;
    if(rm3Bits==4)//start with a SIB.
    {
        char buf[256];
        ::sprintf(buf,"%s+%d*%s",
                  gpRegister3264BitsString[bit3264Mode.sib.base],
                  bit3264Mode.sib.scale,
                  gpRegister3264BitsString[bit3264Mode.sib.index]);

        inst+=buf;
    }
    else if(mod==0 && rm3Bits==5) //start with nothing or rip.
    {
        if(highFormat.effectiveAddressSize==EFFECTIVE_32_BITS)
        {
        }
        else
        {
            inst+="rip";
        }
    }
    else    //start with register.
    {
        inst+=gpRegister3264BitsString[rm];
    }
    //Add disp part.
    std::string dispString;
    if(mod==2)
    {
        s64ToString(bit3264Mode.disp.valueS32,dispString,true);
    }
    if(mod==1)
    {
        s64ToString(bit3264Mode.disp.valueS8,dispString,true);
    }
    if(mod==0 && rm3Bits==5)
    {
        if(highFormat.effectiveAddressSize==EFFECTIVE_32_BITS)
        {
            u64ToString(bit3264Mode.disp.valueS32,dispString);
        }
        else
        {
            s64ToString(bit3264Mode.disp.valueS32,dispString,false);
        }
    }
    inst+=dispString;
}
