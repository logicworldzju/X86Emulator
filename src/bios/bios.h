#ifndef BIOS_H
#define BIOS_H
#include <string>
#include "../memory/memory.h"

class BIOS
{
public:
    BIOS(Memory& memory,const std::string& path);
};

#endif // BIOS_H
