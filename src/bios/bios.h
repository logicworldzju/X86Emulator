#ifndef BIOS_H
#define BIOS_H
#include <string>
#include "../memory/memory.h"

class BIOS
{
public:
    BIOS(Memory& memory, const std::string& biosPath, const std::string &biosDataPath);
};

#endif // BIOS_H
