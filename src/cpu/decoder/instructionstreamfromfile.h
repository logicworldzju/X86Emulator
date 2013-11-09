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
        _file.read(&buf,sizeof(buf));
//        _file.readsome(&buf)
        return buf;
    }
    virtual u16 get16Bits()
    {
        u16 buf=0xcccc;
        _file.read(&buf,sizeof(buf));
        return buf;
    }
    virtual u32 get32Bits()
    {
        u32 buf=0xcccccccc;
        _file.read(&buf,sizeof(buf));
        return buf;
    }
    virtual u64 get64Bits()
    {
        u64 buf=0xcccccccccccccccc;
        _file.read(&buf,sizeof(buf));
        return buf;
    }
protected:
    std::string _fileName;
    std::ifstream _file;
};

#endif // INSTRUCTIONSTREAMFROMFILE_H
