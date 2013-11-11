#ifndef INSTRUCTIONSTREAMFROMFILE_H
#define INSTRUCTIONSTREAMFROMFILE_H

#include "instructionstream.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>

class InstructionStreamFromFile : public InstructionStream
{
public:
    InstructionStreamFromFile(const std::string& fileName)
        :_fileName(fileName),_file(fileName.c_str(),std::ios::binary)
    {
        if(!_file)
        {
            std::cerr<<"Error:"<<"Can't open file:"<<fileName<<std::endl;
            exit(-1);
        }
    }
    bool eof()
    {
        return _file.eof();
    }
public:
    virtual u8 get8Bits()
    {
        u8 buf=0xcc;
        _file.read(reinterpret_cast<char*>(&buf),sizeof(buf));
        _inst.push_back(buf);
        return buf;
    }
    virtual u16 get16Bits()
    {
        u16 buf=get8Bits();
        buf=(static_cast<u16>(get8Bits())<<8)|buf;
        return buf;
    }
    virtual u32 get32Bits()
    {
        u32 buf=get16Bits();
        buf=(static_cast<u32>(get16Bits())<<16)|buf;
        return buf;
    }
    virtual u64 get64Bits()
    {
        u64 buf=get32Bits();
        buf=(static_cast<u64>(get32Bits())<<32)|buf;
        return buf;
    }
    virtual void startReadOneInstruction()
    {
        _inst.clear();
    }
    virtual void endReadOneInstruction()
    {
        //do nothing.
    }
    virtual std::vector<u8> readLastInstruction()
    {
        return _inst;
    }
protected:
    std::string _fileName;
    std::ifstream _file;
    std::vector<u8> _inst;
};

#endif // INSTRUCTIONSTREAMFROMFILE_H
