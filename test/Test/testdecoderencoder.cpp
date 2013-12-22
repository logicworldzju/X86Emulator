#include "testdecoderencoder.h"
#include <QtTest/QTest>
#include "cpu/decoder/instructiondecoder.h"
#include "cpu/encoder/instructionencoder.h"
#include "cpu/decoder/instructionstreamfromfile.h"
#include "cpu/tostring/instructiontostring.h"
#include <iostream>

TestDecoderEncoder::TestDecoderEncoder(QObject *parent) :
    QObject(parent)
{
}
static void hex2Ascii(const std::vector<u8>& hex,std::string& ascii)
{
    for(uint i=0; i<hex.size(); i++)
    {
        {
            u8 t=(hex[i]>>4);
            ascii+=t>9?t-10+'a':t+'0';
        }
        {
            u8 t=(hex[i]&0xf);
            ascii+=t>9?t-10+'a':t+'0';
        }
        ascii+=" ";
    }
}
void TestDecoderEncoder::testAll()
{
    InstructionStreamFromFile fromFile("../asm/1.com");

    std::ofstream fout("../asm/1.txt");

    while(!fromFile.eof())
    {

        InstructionLowLevelFormat lowFormat;
        InstructionHighLevelFormat highFormat;

        fromFile.startReadOneInstruction();
        InstructionDecoder::decode(fromFile,ENV_16_BITS,lowFormat,highFormat);
        fromFile.endReadOneInstruction();

        std::vector<u8> instOriginal=fromFile.readLastInstruction();
        std::vector<u8> instCreated;

        InstructionEncoder::encode(lowFormat,instCreated);

        {
            std::string ascii;
            hex2Ascii(instOriginal,ascii);
            fout<<"OriginalBinary:"<<ascii<<std::endl;
            std::cout<<"OriginalBinary:"<<ascii<<std::endl;;
        }
        {
            std::string ascii;
            hex2Ascii(instCreated,ascii);
            fout<<"OriginalCreated:"<<ascii<<std::endl;
            std::cout<<"OriginalCreated:"<<ascii<<std::endl;
        }

        QCOMPARE(instCreated.size(),instOriginal.size());
        for(uint i=0; i<instCreated.size(); i++)
        {
            QCOMPARE(instCreated[i],instOriginal[i]);
        }

        {
            InstructionToString toString;
            std::string inst;
            toString.toString(highFormat,inst);
            fout<<"ASM:"<<inst<<std::endl;
            std::cout<<"ASM:"<<inst<<std::endl;
        }

    }
}
