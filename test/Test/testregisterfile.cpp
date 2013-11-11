#include "testregisterfile.h"
#include "cpu/register/registerfile.h"
#include <QtTest/QTest>

TestRegisterFile::TestRegisterFile(QObject *parent) :
    QObject(parent)
{
}

void TestRegisterFile::testGPR()
{
    RegisterFile file;
    file.setGPR64Bits(RAX,0);
    file.setGPR32Bits(RAX,0x12345678);
    QCOMPARE(file.getGPR16Bits(RAX),ushort(0x5678));
    QCOMPARE(file.getGPR8Bits(RAX),uchar(0x78));
    QCOMPARE(file.getGPR8BitsLow(RAX),uchar(0x78));
    QCOMPARE(file.getGPR8BitsHigh(RAX),uchar(0x56));

    file.setGPR8Bits(RAX,0xff);

    QCOMPARE(file.getGPR8Bits(RAX),uchar(0xff));
    QCOMPARE(file.getGPR8BitsLow(RAX),uchar(0xff));
    QCOMPARE(file.getGPR8BitsHigh(RAX),uchar(0x56));
    QCOMPARE(file.getGPR16Bits(RAX),ushort(0x56ff));
    QCOMPARE(file.getGPR32Bits(RAX),uint(0x123456ff));

    file.setGPR16Bits(RAX,0xddff);

    QCOMPARE(file.getGPR8Bits(RAX),uchar(0xff));
    QCOMPARE(file.getGPR8BitsLow(RAX),uchar(0xff));
    QCOMPARE(file.getGPR8BitsHigh(RAX),uchar(0xdd));
    QCOMPARE(file.getGPR16Bits(RAX),ushort(0xddff));
    QCOMPARE(file.getGPR32Bits(RAX),uint(0x1234ddff));

    file.setGPR64Bits(RAX,(0x1122334455667788LL));

    QCOMPARE(file.getGPR8Bits(RAX),uchar(0x88));
    QCOMPARE(file.getGPR8BitsLow(RAX),uchar(0x88));
    QCOMPARE(file.getGPR8BitsHigh(RAX),uchar(0x77));
    QCOMPARE(file.getGPR16Bits(RAX),ushort(0x7788));
    QCOMPARE(file.getGPR32Bits(RAX),uint(0x55667788));
}

void TestRegisterFile::testSR()
{
    RegisterFile file;
    file.setSR(CS,0xcc);
    QCOMPARE(file.getSR(CS),ushort(0xcc));

    file.setSR(ES,0xcd);
    QCOMPARE(file.getSR(ES),ushort(0xcd));
}

void TestRegisterFile::testFlag()
{
    RegisterFile file;
    file.setFlags32Bits(0x12345678);
    QCOMPARE(file.getFlags16Bits(),ushort(0x5678));

    file.setFlags16Bits(0xffff);
    QCOMPARE(file.getFlags32Bits(),uint(0x1234ffff));

    file.getFlagsBits().CF=0;
    QCOMPARE(file.getFlags16Bits(),ushort(0xfffe));
}

void TestRegisterFile::testIP()
{
    RegisterFile file;
    file.setIP(0xcccc);
    QCOMPARE(file.getIP(),uint(0xcccc));
}
