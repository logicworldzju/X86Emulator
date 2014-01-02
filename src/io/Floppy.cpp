#include "floppy.h"
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <string.h>
using namespace std;

Floppy::Floppy(const std::string &fileName)
{
    readFile(fileName);
}

Floppy::~Floppy()
{
    if(_fileBuffer)
    {
        delete _fileBuffer;
    }
}

void Floppy::readSectors(int count, u8 *buffer, u8 trackNumber, u8 headNumber, u8 sectorNumber)
{
    assert(trackNumber<TRACKS_PER_SIDE);
    assert(headNumber<SIDES_COUNT);
    assert(sectorNumber<SECTORS_PER_TRACK);

    int lba=getLBAFromCHS(trackNumber,headNumber,sectorNumber);
    ::memcpy(buffer,_fileBuffer+SECTOR_SIZE*lba,SECTOR_SIZE*count);
}

void Floppy::writeSectors(int count, const u8 *buffer, u8 trackNumber, u8 headNumber, u8 sectorNumber)
{
    assert(trackNumber<TRACKS_PER_SIDE);
    assert(headNumber<SIDES_COUNT);
    assert(sectorNumber<SECTORS_PER_TRACK);

    int lba=getLBAFromCHS(trackNumber,headNumber,sectorNumber);
    ::memcpy(_fileBuffer+SECTOR_SIZE*lba,buffer,SECTOR_SIZE*count);
}

bool Floppy::readFile(const std::string &fileName)
{
    ifstream fin(fileName.c_str(),ios::binary);
    if(!fin.is_open())
    {
        cerr<<"Error:Can't open "<<fileName<<endl;
        exit(-1);
    }
    _fileBuffer=new u8[FILE_SIZE];
    fin.read((char*)_fileBuffer,FILE_SIZE);
    if(fin.gcount()!=FILE_SIZE)
    {
        cerr<<"Error:Can't read enough "<<fileName<<endl;
        exit(-1);
    }
    return true;
}

int Floppy::getLBAFromCHS(u8 trackNumber, u8 headNumber, u8 sectorNumber)
{
    assert(trackNumber<TRACKS_PER_SIDE);
    assert(headNumber<SIDES_COUNT);
    assert(sectorNumber<SECTORS_PER_TRACK);
    return (trackNumber*SIDES_COUNT+headNumber)*SECTORS_PER_TRACK+sectorNumber;
}
