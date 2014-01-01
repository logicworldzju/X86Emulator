#ifndef DMA_H_INCLUDED
#define DMA_H_INCLUDED

#include "memory/memory.h"
#include "Floppy.h"
#include "HardDisk.h"
#include "ioport.h"
#include <memory.h>

class DMA:IOPort{
public
    void write2Port(u32 value,Memory& memory,RegisterFile& registerFile);
    u32 readFromPort(Memory& memory,RegisterFile& registerFile);

public
    void IO_Write_0000(WORD data);
    void IO_Write_0001(WORD data);
    void IO_Write_0002(WORD data);

private
    //	I/O
    //	0000(byte)	--	选择通道
    //	0001(byte)	--	连接写四个字节的起始地址，再连续写四个字节的字节数，从低位到高位
    //	0002(byte)	--	模式寄存器，可读写，在向其写数据后立即开始传送。
    // 内部寄存器
    char ChnReg[4][2][4];		//四通道的起始地址和字节数，四字节的寄存器
    char CmdReg;				//命令寄存器
    char ModReg;				//模式寄存器
    char *CurChn;				//I/O 1通道 要写的寄存器的指针
    unsigned int Src,Des,tAd;				//数据复制的起始地址，内部使用
    unsigned int BlockLen;		//数据复制的字节数，内部使用
    HardDisk hardDisk;
    Floppy floppy;


};


#endif // DMA_H_INCLUDED
