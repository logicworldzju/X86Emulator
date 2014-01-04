#include "registerfile.h"


std::string RegisterFile::toString()
{
    std::ostringstream stream;
    //------------GPRegister------------
    const char*gpregisterName[]={"RAX","RCX","RDX","RBX","RSP","RBP","RSI","RDI",
                                 "R8","R9","R10","R11","R12","R13","R14","R15"};
    stream<<std::hex;
    stream.fill('0');

    for(int i=0; i<16; i++)
    {
        stream<<gpregisterName[i]<<":";
        stream.width(16);
        stream<<_gpRegisters[i].get64Bits()<<"h ";
        if(i%4==3) stream<<std::endl;
    }
    //----------SegmentRegister---------
    const char* segmentRegisterName[]={"ES","CS","SS","DS","FS","GS"};
    for(int i=0; i<6; i++)
    {
        stream<<segmentRegisterName[i]<<":";
        stream.width(4);
        stream<<_segmentRegisters[i]<<"h ";
        //            if(i%3==2) stream<<std::endl;
    }
    stream<<std::endl;
    //--------------IP------------------

    stream<<"IP:";
    stream.width(8);
    stream<<_ip<<"h"<<std::endl;
    //-------------flags----------------
    stream<<_flags.flagBits.toString();

    return stream.str();
}

u16 RegisterFile::getGPR16Bits(u8 index)
{
    if(index>=16)
    {
        qDebug()<<"index:"<<index;
    }
    Q_ASSERT(index<16);
    //        assert(index<16);
    return _gpRegisters[index].get16Bits();
}
