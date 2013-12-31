#ifndef MEMORY_H
#define MEMORY_H
#include "../type.h"
#include <assert.h>
/*
the layout and contents of the first Meg of memory[1][2]:
0x0 - 0x3ff: 256 bios interrupt vector
0x400 - 0x4ff: 255B BDA(BIOS Data Area)
        0x40E LPT4 I/O base address or EBDA(Extended Bios Data Area)
                (AcpiTbFindRsdp)
        0x410: Equipment Word
        0x472: Soft reset flag
        0x475: Number of hard disk drives(boot0)
0x500 - 0x9Fbff: dos, etc
0x9FC00 - 0x9feff: EBDA(Extended Bios Data Area) 768B
0x9ff00 -- 0x9ffff: boot device tables 256B

0xA0000 - 0xAffff: Graphics Video memory (EGA and above)
0xB0000 - 0xBffff: Graphics area for EGA and up
0xC0000 - 0xCffff: additional ROM-BIOS & video memory

0xD0000 - 0xDffff: ROM cartridges
0xE0000 - 0xEffff: ROM cartridges
0xF0000 - 0xFDfff: IBM PC ROM BASIC

0xFE000 - 0xFFFEF: ORIGINAL IBM PC ROM BIOS
        0xfe05b : POST Entry Point
0xFFFF0 - 0xFFFF4: Power-up Entry Point(RESET JUMP)

0xffff5 : ASCII Date ROM was built - 8 characters in MM/DD/YY
0xffffe : System Model ID
*/
#define VIDEO_MEMORY_ADDRESS 0xc0000

class Memory
{
public:
    Memory(u32 memorySize=((1<<20)+(1<<16)));
    ~Memory();
    u8* getMemoryAddress()
    {
        return _memory;
    }
    u8* getVideoMemoryAddress()
    {
        return _memory+VIDEO_MEMORY_ADDRESS;
    }
    u32 getMemorySize()
    {
        return _memorySize;
    }
    virtual u8 get8Bits(u32 address);
    virtual void set8Bits(u32 address,u8 value);

    virtual u16 get16Bits(u32 address);
    virtual void set16Bits(u32 address,u16 value);

    virtual u32 get32Bits(u32 address);
    virtual void set32Bits(u32 address,u32 value);

    virtual u64 get64Bits(u32 address);
    virtual void set64Bits(u32 address,u64 value);

    virtual void getBytes(u32 address,u32 length,u8* buffer);
    virtual void setBytes(u32 address,u32 length,const u8* buffer);
public:
    //all used in the statistic function of memory in debugmemory.h
    enum AccessMode
    {
        NOT_ACCESS_MODE,
        INST_ACCESS,
        CPU_DATA_ACCESS,
        DEVICE_DATA_ACCESS,
        SYSTEM_INIT_ACCESS,  //init system,like load bios rom code and
                            //other rom code into specific memory
                            //address.
        DEBUG_ACCESS
    };
    void startAccess(AccessMode accessMode)
    {
        assert(accessMode!=NOT_ACCESS_MODE);
        assert(_accessMode==NOT_ACCESS_MODE);
        _accessMode=accessMode;
    }
    void endAccess()
    {
        assert(_accessMode!=NOT_ACCESS_MODE);
        _accessMode=NOT_ACCESS_MODE;
    }
protected:
    AccessMode _accessMode;
protected:
    u32 _memorySize;
    u8* _memory;
};

#endif // MEMORY_H
