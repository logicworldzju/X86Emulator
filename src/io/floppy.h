#ifndef FLOPPY_H
#define FLOPPY_H

#include "type.h"
#include <string>

class Floppy
{
public:
    Floppy(const std::string& fileName);
    ~Floppy();
    void readSectors(int count,u8* buffer,u8 trackNumber,u8 headNumber,
                     u8 sectorNumber);
    void writeSectors(int count,const u8* buffer,u8 trackNumber,u8 headNumber,
                      u8 sectorNumber);
    int getTracksPerSide(){return TRACKS_PER_SIDE;}
    int getSectorsPerTrack(){return SECTORS_PER_TRACK;}
    int getSidesCount(){return SIDES_COUNT;}
private:
    bool readFile(const std::string& fileName);
    int getLBAFromCHS(u8 trackNumber,u8 headNumber,u8 sectorNumber);
private:
    u8* _fileBuffer;
    const static int FILE_SIZE=0x168000;
    const static int TRACKS_PER_SIDE=80;
    const static int SECTORS_PER_TRACK=18;
    const static int SIDES_COUNT=2;
    const static int SECTOR_SIZE=512;
};

#endif // FLOPPY_H
