#include "testfloppy.h"
#include "io/floppy.h"

TestFloppy::TestFloppy(QObject *parent) :
    QObject(parent)
{
}

void TestFloppy::test()
{
    Floppy floppy("images/DOS.IMG");

    u8 buffer[512];
    floppy.readSectors(1,buffer,0,0,1);
    QCOMPARE((int)buffer[510],0x55);
    QCOMPARE((int)buffer[511],0xaa);

    floppy.readSectors(1,buffer,floppy.getTracksPerSide()-1,1,floppy.getSectorsPerTrack());
//    QCOMPARE((int))
    QCOMPARE((int)buffer[510],0x6a);
    QCOMPARE((int)buffer[511],0x00);

    floppy.writeSectors(1,buffer,0,0,1);
    floppy.readSectors(1,buffer,0,0,1);
    QCOMPARE((int)buffer[510],0x6a);
    QCOMPARE((int)buffer[511],0x00);

}
