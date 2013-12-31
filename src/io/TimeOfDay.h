#ifndef TIMEOFDAY_H_INCLUDED
#define TIMEOFDAY_H_INCLUDED

#include "ioport.h"
#define TICK 54.9255

Class TimeOfDay:IOPort
{
public
    void write2Port(u32 value,Memory& memory,RegisterFile& registerFile);
    u32 readFromPort(Memory& memory,RegisterFile& registerFile);

private
    //依次是 厘秒、秒、分、时、日、月、年、世纪
    unsigned char rTime[8];		//十六进制存放，方便运算
    unsigned char BCDTIme[8];	//BDC码存放
    unsigned int *RtcTick;
    unsigned char *RtcMidNight;
    char carry[7]={100,60,60,24,31,12,100};		//八个寄存器之间的进位关系

    unsigned int RWpnt;
   // bool A20Gate;								//A20地址线，只是为了92端口有个操作，其实它总是打开的。
    int t;
}




#endif // TIMEOFDAY_H_INCLUDED
