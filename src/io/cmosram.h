#ifndef COMSRAM_H
#define COMSRAM_H

#include "io/ioport.h"
#include <assert.h>

class CMOSRAM
{
public:
    CMOSRAM();
    IOPort& getIndexIOPort(){return _indexIOPort;}
    IOPort& getDataIOPort(){return _dataIOPort;}
    u32 indexReadFromPort(Memory &memory, RegisterFile &registerFile);
    void indexWrite2Port(u32 value, Memory &memory, RegisterFile &registerFile);
    u32 dataReadFromPort(Memory &memory, RegisterFile &registerFile);
    void dataWrite2Port(u32 value, Memory &memory, RegisterFile &registerFile);
private:
    //0x70
    class CMOSRAMIndexIOPort:public IOPort
    {
    public:
        CMOSRAMIndexIOPort(CMOSRAM& comsRAM):_cmosRAM(comsRAM){}
        u32 readFromPort(Memory &memory, RegisterFile &registerFile){return _cmosRAM.indexReadFromPort(memory,registerFile);}
        void write2Port(u32 value, Memory &memory, RegisterFile &registerFile){_cmosRAM.indexWrite2Port(value,memory,registerFile);}
    private:
        CMOSRAM& _cmosRAM;
    };
    CMOSRAMIndexIOPort _indexIOPort;
    //0x71
    class CMOSRAMDataIOPort:public IOPort
    {
    public:
        CMOSRAMDataIOPort(CMOSRAM& comsRAM):_cmosRAM(comsRAM){}
        u32 readFromPort(Memory &memory, RegisterFile &registerFile){return _cmosRAM.dataReadFromPort(memory,registerFile);}
        void write2Port(u32 value, Memory &memory, RegisterFile &registerFile){_cmosRAM. dataWrite2Port(value,memory,registerFile);}
    private:
        CMOSRAM& _cmosRAM;
    };
    CMOSRAMDataIOPort _dataIOPort;

    u8 _index;
    const static int RAM_SIZE=64;
    u8 _ram[RAM_SIZE];
};

#endif // COMSRAM_H
