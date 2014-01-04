#ifndef TIMEOFDAY_H_INCLUDED
#define TIMEOFDAY_H_INCLUDED

#include "ioport.h"
#include <QTimer>
#include <QObject>

class TimeOfDay :public QObject
{
    Q_OBJECT
public:
    TimeOfDay();
    IOPort& getIOPort(){return _ioPort;}
    void write2Port(u32 value,Memory& memory,RegisterFile& registerFile);
    u32 readFromPort(Memory& memory,RegisterFile& registerFile);
private:
    void TranslToBCD();
    u8 bcdToBin(u8 bcd);
private slots:
    void RTCTimerThread();
private:
    //依次是 厘秒、秒、分、时、日、月、年、世纪
    u8 _binaryTime[8];		//十六进制存放，方便运算
    u8 _bcdTime[8];	//BDC码存放
    u32 _rtcTick;
//    unsigned char *RtcMidNight;
    static u8 carry[7];		//八个寄存器之间的进位关系

    unsigned int RWpnt;
   // bool A20Gate;								//A20地址线，只是为了92端口有个操作，其实它总是打开的。
    int t;
    static const float TICK;
    QTimer _timer;


private:
    class TimeOfDayIOPort:public IOPort
    {
    public:
        TimeOfDayIOPort(TimeOfDay& timeOfDay):_timeOfDay(timeOfDay){}
        void write2Port(u32 value,Memory& memory,RegisterFile& registerFile){_timeOfDay.write2Port(value,memory,registerFile);}
        u32 readFromPort(Memory& memory,RegisterFile& registerFile){return _timeOfDay.readFromPort(memory,registerFile);}
    private:
        TimeOfDay& _timeOfDay;
    };
    TimeOfDayIOPort _ioPort;
};

#endif // TIMEOFDAY_H_INCLUDED
