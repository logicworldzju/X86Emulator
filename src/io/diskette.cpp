#include "diskette.h"
#include <iostream>
using namespace std;
#include <stdlib.h>
#include <QDebug>

Diskette::Diskette(const string &floppyFileName0, const string &floppyFileName1)
    :_ioPort(*this),_floppy0(floppyFileName0),_floppy1(floppyFileName1)
{
}

u32 Diskette::readFromPort(Memory &memory, RegisterFile &registerFile)
{
    (void)memory;(void)registerFile;
    return 0xcccccccc;
}

void Diskette::write2Port(u32 value, Memory &memory, RegisterFile &registerFile)
{
    (void)value;
//    int t;
    switch(registerFile.getGPR8BitsHigh(RAX)) //AH
    {
    case 0:
//        (*(unsigned short*)((t=registerFile.getSR(SS),t<<=4)+registerFile.getGPR16Bits(RSP)+4+memory.getMemoryAddress())) &= ~CF;
        registerFile.getFlagsBits().CF=0;
        registerFile.setGPR8BitsHigh(RAX,0);     //AH=0;
        qDebug()<<"int 13h function 00h--reset diskette system called"<<endl;
        break;
    case 1:
        if (registerFile.getGPR8BitsLow(RDX)<0x80)   //DL
        {
            registerFile.setGPR8BitsHigh(RAX,0);    //AH=0;
            registerFile.getFlagsBits().CF=0;
        }
        else
        {
            registerFile.setGPR8BitsHigh(RAX,0x80); //AH=0x80;
            registerFile.getFlagsBits().CF=1;
        }
//        registerFile.getFlagsBits().CF=0;
//        registerFile.setGPR8BitsHigh(RAX,0);     //AH=0;
        qDebug()<<"int 13h function 01h--read diskette status called"<<endl;
        break;
    case 2:
    {
        u8 count=registerFile.getGPR8BitsLow(RAX);
        u8 trackNumber=registerFile.getGPR8BitsHigh(RCX);
        u8 sectorNumber=registerFile.getGPR8BitsLow(RCX);
        u8 headNumber=registerFile.getGPR8BitsHigh(RDX);
        u8 driveNumber=registerFile.getGPR8BitsLow(RDX);
        u8* buffer = memory.getMemoryAddress()+registerFile.getSR(ES)*16+
                registerFile.getGPR16Bits(RBX);
        qDebug()<<"Int 13h function 02h called with "<<
              "trackNumber:"<<(int)trackNumber<<
              ",sectorNumber:"<<(int)sectorNumber<<
              ",headNumber:"<<(int)headNumber<<
              ",driveNumber:"<<(int)driveNumber<<
              endl;
        if(driveNumber==0 /*|| driveNumber==0x80*/)//driveNumber==0x80 may be a bug.
        {
            _floppy0.readSectors(count,buffer,trackNumber,headNumber,sectorNumber);
        }
        else if(driveNumber==1 /*|| driveNumber==0x81*/)//driveNumber==0x81 may be a bug
        {
            _floppy1.readSectors(count,buffer,trackNumber,headNumber,sectorNumber);
        }
//        else if(driveNumber==0x80 || driveNumber==0x81)
//        {
//            registerFile.setGPR8BitsLow(RAX,count);
//            registerFile.setGPR8BitsHigh(RAX,0x0c);
//            registerFile.getFlagsBits().CF=1;
//            break;
//        }
        else
        {
            cerr<<"Error:No such driveNumber"<<(int)driveNumber<<" in int 13h function 02h"<<endl;
            exit(-1);
        }
        registerFile.setGPR8BitsLow(RAX,count);
        registerFile.setGPR8BitsHigh(RAX,0);
        registerFile.getFlagsBits().CF=0;

        break;
    }
    case 3:
    {
        u8 count=registerFile.getGPR8BitsLow(RAX);
        u8 trackNumber=registerFile.getGPR8BitsHigh(RCX);
        u8 sectorNumber=registerFile.getGPR8BitsLow(RCX);
        u8 headNumber=registerFile.getGPR8BitsHigh(RDX);
        u8 driveNumber=registerFile.getGPR8BitsLow(RDX);
        u8* buffer = memory.getMemoryAddress()+registerFile.getSR(ES)*16+
                registerFile.getGPR16Bits(RBX);
        if(driveNumber==0)
        {
            _floppy0.writeSectors(count,buffer,trackNumber,headNumber,sectorNumber);
        }
        else if(driveNumber==1)
        {
            _floppy1.writeSectors(count,buffer,trackNumber,headNumber,sectorNumber);
        }
        else
        {
            cerr<<"Error:No such driveNumber"<<(int)driveNumber<<" in int 13h function 03h"<<endl;
            exit(-1);
        }
        registerFile.setGPR8BitsLow(RAX,count);
        registerFile.setGPR8BitsHigh(RAX,0);
        registerFile.getFlagsBits().CF=0;
        qDebug()<<"Int 13h function 03h called with "<<
              "trackNumber:"<<(int)trackNumber<<
              ",sectorNumber:"<<(int)sectorNumber<<
              ",headNumber:"<<(int)headNumber<<
              ",driveNumber:"<<(int)driveNumber<<endl;
        break;
    }
      /*  if (floppy.isInsert(registerFile.getGPR8BitsLow(RDX)])&& registerFile.getGPR8BitsLow(RDX) <0x80 || registerFile.getGPR8BitsLow(RDX) >=0x80)
            //if (1)
        {
            if (registerFile.getGPR8BitsLow(RDX)<0x80)
            {
                floppy.IO_Write_03F0(0);
                floppy.IO_Write_03F1(registerFile.getGPR8BitsLow(RCX)&0x3f);    //CL
                floppy.IO_Write_03F0(1);
                floppy.IO_Write_03F1(registerFile.getGPR8BitsHigh(RDX)); //DH
                floppy.IO_Write_03F0(2);
                floppy.IO_Write_03F1(registerFile.getGPR8BitsHigh(RCX)+((registerFile.getGPR8BitsLow(RCX)&0xc0)<<2));
                floppy.IO_Write_03F0(3);
                floppy.IO_Write_03F1(registerFile.getGPR8BitsLow(RDX)); //DL
                IO_Write_0000(2);					//选择通道
            }
            else
            {
                hardDisk.IO_Write_03F6(0);
                hardDisk.IO_Write_03F7(registerFile.getGPR8BitsLow(RCX)&0x3f);    //CL
                hardDisk.IO_Write_03F6(1);
                hardDisk.IO_Write_03F7(registerFile.getGPR8BitsHigh(RDX)); //DH
                hardDisk.IO_Write_03F6(2);
                hardDisk.IO_Write_03F7(registerFile.getGPR8BitsHigh(RCX)+((registerFile.getGPR8BitsLow(RCX)&0xc0)<<2));
                hardDisk.IO_Write_03F6(3);
                hardDisk. IO_Write_03F7(registerFile.getGPR8BitsLow(RDX)-0x80);    //DL
                IO_Write_0000(3);					//选择通道
            }
            IO_Write_0001(registerFile.getGPR8BitsLow(RBX));				//BL    内存块起始地址
            IO_Write_0001(registerFile.getGPR8BitsHigh(RBX)); //BH
            IO_Write_0001(registerFile.getSR(ES)&0xff);    //ES
            IO_Write_0001((registerFile.getSR(ES)&0xff00)>>8);
            IO_Write_0001(0);					//传输的字节数，＝扇区数*200h
            IO_Write_0001(registerFile.getGPR8BitsLow(RAX)*2);   //AL
            IO_Write_0001((registerFile.getGPR8BitsLow(RAX)&0x80)>>7);   //AL
            IO_Write_0001(0);
            if (registerFile.getGPR8BitsLow(RDX)<0x80)   //DL
            {										//软盘
                if (registerFile.getGPR8BitsHigh(RAX)) //AH
                    IO_Write_0002(0x96);			//读磁盘
                else
                    IO_Write_0002(0x9a);			//写磁盘
            }
            else
            {										//硬盘
                if (registerFile.getGPR8BitsHigh(RAX)) //AH
                    IO_Write_0002(0x97);			//读磁盘
                else
                    IO_Write_0002(0x9b);			//写磁盘
            }
        }
        else
        {
            (*(unsigned short*)((t=registerFile.getSR(SS),t<<=4)+registerFile.getGPR16Bits(RSP)+4+memory.getMemoryAddress()))|=CF;
            registerFile.setGPR8BitsHigh(RAX)=0x80;   //AH
        }
        break;*/
    case 4:
    {
        u8 count=registerFile.getGPR8BitsLow(RAX);
        u8 trackNumber=registerFile.getGPR8BitsHigh(RCX);
        u8 sectorNumber=registerFile.getGPR8BitsLow(RCX);
        u8 headNumber=registerFile.getGPR8BitsHigh(RDX);
        u8 driveNumber=registerFile.getGPR8BitsLow(RDX);
//        u8* buffer = memory.getMemoryAddress()+registerFile.getSR(ES)*16+
//                registerFile.getGPR16Bits(RBX);
        if(driveNumber==0)
        {
//            _floppy0.writeSectors(count,buffer,trackNumber,headNumber,sectorNumber);
        }
        else if(driveNumber==1)
        {
//            _floppy1.writeSectors(count,buffer,trackNumber,headNumber,sectorNumber);
        }
        else
        {
            cerr<<"Error:No such driveNumber"<<(int)driveNumber<<" in int 13h function 04h"<<endl;
            exit(-1);
        }
        registerFile.setGPR8BitsLow(RAX,count);
        registerFile.setGPR8BitsHigh(RAX,0);
        registerFile.getFlagsBits().CF=0;
        qDebug()<<"Int 13h function 04h called with "<<
              "trackNumber:"<<(int)trackNumber<<
              ",sectorNumber:"<<(int)sectorNumber<<
              ",headNumber:"<<(int)headNumber<<
              ",driveNumber:"<<(int)driveNumber<<endl;
        break;
    }
//        break;
    case 5:
    {
        u8 count=registerFile.getGPR8BitsLow(RAX);
        u8 trackNumber=registerFile.getGPR8BitsHigh(RCX);
//        u8 sectorNumber=registerFile.getGPR8BitsLow(RCX);
        u8 headNumber=registerFile.getGPR8BitsHigh(RDX);
        u8 driveNumber=registerFile.getGPR8BitsLow(RDX);
//        u8* buffer = memory.getMemoryAddress()+registerFile.getSR(ES)*16+
//                registerFile.getGPR16Bits(RBX);
        if(driveNumber==0)
        {
//            _floppy0.writeSectors(count,buffer,trackNumber,headNumber,sectorNumber);
        }
        else if(driveNumber==1)
        {
//            _floppy1.writeSectors(count,buffer,trackNumber,headNumber,sectorNumber);
        }
        else
        {
            cerr<<"Error:No such driveNumber"<<(int)driveNumber<<" in int 13h function 05h"<<endl;
            exit(-1);
        }
        registerFile.setGPR8BitsLow(RAX,count);
        registerFile.setGPR8BitsHigh(RAX,0);
        registerFile.getFlagsBits().CF=0;
        qDebug()<<"Int 13h function 05h called with "<<
              ",trackNumber:"<<(int)trackNumber<<
              ",headNumber:"<<(int)headNumber<<
              ",driveNumber:"<<(int)driveNumber<<endl;
        break;
    }
    case 8:
    {
        u8 driveNumber=registerFile.getGPR8BitsLow(RDX);
        if(driveNumber==0)
        {
            registerFile.setGPR16Bits(RAX,0);//AX
            registerFile.setGPR8BitsHigh(RBX,0);//BH
            registerFile.setGPR8BitsLow(RBX,0x4);//BL
            registerFile.setGPR8BitsHigh(RCX,_floppy0.getTracksPerSide()-1);
            registerFile.setGPR8BitsLow(RCX,_floppy0.getSectorsPerTrack());
            registerFile.setGPR8BitsHigh(RDX,_floppy0.getSidesCount()-1);
            registerFile.setGPR8BitsLow(RDX,2);//DL

            registerFile.setSR(ES,0xf000);
            registerFile.setSSR(ES,0xf0000);
            registerFile.setGPR16Bits(RDI,0);

            registerFile.getFlagsBits().CF=0;
        }
        else if(driveNumber==1)
        {
            registerFile.setGPR16Bits(RAX,0);//AX
            registerFile.setGPR8BitsHigh(RBX,0);//BH
            registerFile.setGPR8BitsLow(RBX,0x4);//BL
            registerFile.setGPR8BitsHigh(RCX,_floppy1.getTracksPerSide()-1);
            registerFile.setGPR8BitsLow(RCX,_floppy1.getSectorsPerTrack());
            registerFile.setGPR8BitsHigh(RDX,_floppy1.getSidesCount()-1);
            registerFile.setGPR8BitsLow(RDX,2);//DL

            registerFile.setSR(ES,0xf000);
            registerFile.setSSR(ES,0xf0000);
            registerFile.setGPR16Bits(RDI,0);

            registerFile.getFlagsBits().CF=0;
        }
        else
        {
            registerFile.setGPR16Bits(RAX,0x0100);//AX
            registerFile.setGPR8BitsHigh(RBX,0);//BH
            registerFile.setGPR8BitsLow(RBX,0x0);//BL
            registerFile.setGPR8BitsHigh(RCX,0);
            registerFile.setGPR8BitsLow(RCX,0);
            registerFile.setGPR8BitsHigh(RDX,0);
            registerFile.setGPR8BitsLow(RDX,0);//DL

            registerFile.getFlagsBits().CF=1;
        }
        qDebug()<<"Int 13h funcion 08h read drive parameters,called with "<<
              "driveNumber:"<<(int)driveNumber<<endl;
        break;
    }
   /*     if (registerFile.getGPR8BitsLow(RDX)<0x80)   //DL
        {
            (*(unsigned short*)((t=registerFile.getSR(SS),t<<=4)+registerFile.getGPR16Bits(RSP)+4+memory.getMemoryAddress()))&=~CF;
            registerFile.setGPR8BitsHigh(RAX,0);  //AH
            registerFile.setGPR8BitsLow(RBX,4);  //BL
            registerFile.setGPR16Bits(RCX,0x4f12); //CX
            registerFile.setGPR16Bits(RDX,0x0102);  //DX
            eCPU.es=*(unsigned short*)(memory.getMemoryAddress()+0x1e*4+2);	//INT 1Eh,磁盘参数表
            eCPU.di=*(unsigned short*)(memory.getMemoryAddress()+0x1e*4);
        }
        else
        {
            if (*(unsigned char *)(memory.getMemoryAddress()+0x475))
            {												//有硬盘
                (*(unsigned short*)((t=registerFile.getSR(SS),t<<=4)+registerFile.getGPR16Bits(RSP)+4+memory.getMemoryAddress()))&=~CF;
                registerFile.setGPR8BitsHigh(RAX,0);  //AH
                registerFile.setGPR8BitsHigh(RCX,(HdCnt[registerFile.getGPR8BitsLow(RDX)-0x80][0]&0xff)-2);    //CH
                registerFile.setGPR8BitsLow(RCX,63+((HdCnt[registerFile.getGPR8BitsLow(RDX)-0x80][0]&0x300)>>2)); //CL
                registerFile.setGPR8BitsHigh(RDX,HdCnt[registerFile.getGPR8BitsLow(RDX)-0x80][1]-1);
                registerFile.setGPR8BitsLow(RDX,*(unsigned char *)(memory.getMemoryAddress()+0x475));
                // 				eCPU.es=*(unsigned short*)(MemoryStart+0x1e*4+2);	//INT 1Fh,磁盘参数表
                // 				eCPU.di=*(unsigned short*)(MemoryStart+0x1e*4);
            }
            else
            {												//无硬盘
                (*(unsigned short*)((t=registerFile.getSR(SS),t<<=4)+registerFile.getGPR16Bits(RSP)+4+memory.getMemoryAddress()))|=CF;
                registerFile.setGPR8BitsHigh(RAX,0x1);    //AH
            }
        }
        break;*/
//    case 0x10:
//        break;
    case 0x15:
    {
        u8 driveNumber=registerFile.getGPR8BitsLow(RDX);
        if (driveNumber<0x02)		//暂时只支持两个软盘
        {
//            (*(unsigned short*)((t=registerFile.getSR(SS),t<<=4)+registerFile.getGPR16Bits(RSP)+4+memory.getMemoryAddress()))&=~CF;
            registerFile.setGPR8BitsHigh(RAX,1); //AH
            registerFile.getFlagsBits().CF=0;
        }
        else
        {
//            (*(unsigned short*)((t=registerFile.getSR(SS),t<<=4)+registerFile.getGPR16Bits(RSP)+4+memory.getMemoryAddress()))&=~CF;
            registerFile.setGPR8BitsHigh(RAX,0);  //AH
            registerFile.getFlagsBits().CF=0;
        }
        qDebug()<<"Int 13h funcion 15h read drive type,called with "<<
              "driveNumber:"<<(int)driveNumber<<endl;
        break;
    }
    case 0x16:
    {
        u8 driveNumber=registerFile.getGPR8BitsLow(RDX);
        qDebug()<<"Int 13h funcion 16h detect media change,called with "<<
              "driveNumber:"<<(int)driveNumber<<endl;
        break;
    }
    case 0x17:
    {
        u8 driveNumber=registerFile.getGPR8BitsLow(RDX);
        qDebug()<<"Int 13h funcion 17h set diskette type,called with "<<
              "driveNumber:"<<(int)driveNumber<<endl;
        break;
    }
    case 0x18:
    {
        u8 driveNumber=registerFile.getGPR8BitsLow(RDX);
        qDebug()<<"Int 13h funcion 18h set media type for format,called with "<<
              "driveNumber:"<<(int)driveNumber<<endl;
        break;
    }
    default:
        assert(0);
    }
}
