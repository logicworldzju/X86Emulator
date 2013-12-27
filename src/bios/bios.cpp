#include "bios.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

BIOS::BIOS(Memory &memory, const std::string &path)
{
    memory.startAccess(memory.SYSTEM_INIT_ACCESS);

    ifstream fin(path.c_str(),ios::binary);
    if(!fin.is_open())
    {
        cerr<<"Error:Can't open "<<path<<endl;
        ::exit(-1);
    }
    u8 buffer[0x10000];
    if(fin.readsome((char*)buffer,0x10000)!=0x10000)
    {
        cerr<<"Error:Can't read enough "<<path<<endl;
        ::exit(-1);
    }
    memory.setBytes(0xf0000,0x10000,buffer);

    memory.endAccess();
}
