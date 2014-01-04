#include "bios.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

BIOS::BIOS(Memory &memory, const std::string &biosPath,const std::string &biosDataPath)
{
    memory.startAccess(memory.SYSTEM_INIT_ACCESS);

    //BIOS ROM
    {
        ifstream fin(biosPath.c_str(),ios::binary);
        if(!fin.is_open())
        {
            cerr<<"Error:Can't open "<<biosPath<<endl;
            ::exit(-1);
        }
        u8 buffer[0x10000];
        fin.read((char*)buffer,0x10000);
        if(fin.gcount()!=0x10000)
        {
            cerr<<"Error:Can't read enough "<<biosPath<<endl;
            ::exit(-1);
        }
        memory.setBytes(0xf0000,0x10000,buffer);
    }
    //BIOS Data Area
    {
        ifstream fin(biosDataPath.c_str(),ios::binary);
        if(!fin.is_open())
        {
            cerr<<"Error:Can't open "<<biosDataPath<<endl;
            ::exit(-1);
        }
        u8 buffer[0x100];
        fin.read((char*)buffer,0x100);
        if(fin.gcount()!=0x100)
        {
            cerr<<"Error:Can't read enough "<<biosDataPath<<endl;
            ::exit(-1);
        }
        memory.setBytes(0x400,0x100,buffer);
    }

    //BIOS Data Area
    //two 0x61?
    memory.set16Bits(0x410,0x61);//number of devices installed.
    memory.set16Bits(0x413,0x27f);//memory size.

//    memory.set16Bits(0x8e473,0x4000);//trick.

    memory.endAccess();
}
