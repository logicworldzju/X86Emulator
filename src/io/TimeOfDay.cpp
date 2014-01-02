#include "TimeOfDay.h"
#include <QDateTime>
#include <iostream>
using namespace std;

const float TimeOfDay::TICK=54.9255f;
u8 TimeOfDay::carry[7]={100,60,60,24,31,12,100};

TimeOfDay::TimeOfDay()
    :_ioPort(*this)
{
    RTCTimerThread();

    _timer.setInterval(TICK);
    connect(&_timer,SIGNAL(timeout()),this,SLOT(RTCTimerThread()));
    _timer.start();
}

void TimeOfDay::TranslToBCD()
{
	for (int i=0;i<8;i++)
	{
		_bcdTime[i]=_binaryTime[i]/10;
		_bcdTime[i]<<=4;
		_bcdTime[i]+=_binaryTime[i]%10;
    }
}

u8 TimeOfDay::bcdToBin(u8 bcd)
{
    return ((bcd>>4)&0xf)*10+(bcd&0xf);
}

void TimeOfDay::RTCTimerThread()
{
	(_rtcTick)++;

	/*_binaryTime[7]++;
	for (int i=0;i<7;i++)
	{
		if (_binaryTime[i]>carry[i])
		{
			_binaryTime[i+1]++;
			_binaryTime[i]%=carry[i];
		}
	}
	switch(_binaryTime[5])		//Month
	{
	case 2:
		if ((_binaryTime[6]%4==0 && _binaryTime[7]%4) || (_binaryTime[6]==0 && _binaryTime[7]%4==0))
		{
			_binaryTime[5]+=_binaryTime[4]/29;
			_binaryTime[4]%=29;
		}
		else
		{
			_binaryTime[5]+=_binaryTime[4]/28;
			_binaryTime[4]%=28;
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		_binaryTime[5]+=_binaryTime[4]/30;
		_binaryTime[4]%=30;
		break;
	}*/
    QDateTime dateTime = QDateTime::currentDateTime();
    _binaryTime[0]=(u8)(dateTime.time().msec()/10);//st.wMilliseconds/10;
	_binaryTime[1]=u8(dateTime.time().second());//(unsigned char)st.wSecond;
	_binaryTime[2]=u8(dateTime.time().minute());//unsigned char)st.wMinute;
	_binaryTime[3]=u8(dateTime.time().hour());//unsigned char)st.wHour;
	_binaryTime[4]=u8(dateTime.date().day());//unsigned char)st.wDay;
	_binaryTime[5]=u8(dateTime.date().month());//unsigned char)st.wMonth;
	_binaryTime[6]=u8(dateTime.date().year()%100);//st.wYear%100;
	_binaryTime[7]=u8(dateTime.date().year()/100);//st.wYear/100;

	TranslToBCD();
}

void TimeOfDay::write2Port(u32 value,Memory& memory,RegisterFile& registerFile)
{
    cout<<"TimeOfDay:ah:"<<hex<<(int)registerFile.getGPR8BitsHigh(RAX)<<"h"<<endl;
    (void)value;(void)memory;

	switch(registerFile.getGPR8BitsHigh(RAX))
	{
	case 0:
		registerFile.setGPR16Bits(RDX,((_rtcTick)&0xffff));
		registerFile.setGPR16Bits(RCX,(((_rtcTick) >> 16) & 0xffff));
        registerFile.setGPR8BitsLow(RAX,(_rtcTick)/8640000);		//每天有8640000个Tick

        assert(0);
		break;
	case 1:
		(_rtcTick)=registerFile.getGPR16Bits(RCX);
		(_rtcTick)<<=16;
		(_rtcTick)+=registerFile.getGPR16Bits(RDX);
		registerFile.setGPR8BitsHigh(RAX,0);
		break;
	case 2:
	    registerFile.setGPR8BitsHigh(RAX,0);
	    registerFile.setGPR8BitsLow(RAX,_bcdTime[3]);
		registerFile.setGPR8BitsHigh(RCX,_bcdTime[3]);
		registerFile.setGPR8BitsLow(RCX,_bcdTime[2]);
		registerFile.setGPR8BitsHigh(RDX,_bcdTime[1]);
		registerFile.setGPR8BitsLow(RDX,0);
        registerFile.getFlagsBits().CF=0;
		break;
	case 3:
		_binaryTime[3]=bcdToBin(registerFile.getGPR8BitsHigh(RCX));
		_binaryTime[2]=bcdToBin(registerFile.getGPR8BitsLow(RCX));
		_binaryTime[1]=bcdToBin(registerFile.getGPR8BitsHigh(RDX));
		registerFile.setGPR8BitsHigh(RAX,0);
        registerFile.setGPR8BitsLow(RAX,2);
        registerFile.getFlagsBits().CF=0;
		break;
	case 4:
        registerFile.setGPR8BitsLow(RAX,_bcdTime[7]);
	    registerFile.setGPR8BitsHigh(RCX,_bcdTime[7]);
		registerFile.setGPR8BitsLow(RCX,_bcdTime[6]);
		registerFile.setGPR8BitsHigh(RDX,_bcdTime[5]);
		registerFile.setGPR8BitsLow(RDX,_bcdTime[4]);
		registerFile.getFlagsBits().ZF=0;
		registerFile.getFlagsBits().CF=0;
		break;
	case 5:
		_binaryTime[7]=bcdToBin(registerFile.getGPR8BitsHigh(RCX));
		_binaryTime[6]=bcdToBin(registerFile.getGPR8BitsLow(RCX));
		_binaryTime[5]=bcdToBin(registerFile.getGPR8BitsHigh(RDX));
		_binaryTime[4]=bcdToBin(registerFile.getGPR8BitsLow(RDX));
//		registerFile.setGPR8BitsLow(RDX,0); bug?
        registerFile.setGPR8BitsHigh(RAX,0);
        registerFile.setGPR8BitsLow(RAX,2);
		registerFile.getFlagsBits().CF=0;
		registerFile.getFlagsBits().ZF=0;
		break;
	case 6:
        cerr<<"Error:int 1ah function 06 set real-time clock alarm not implemented!"<<endl;
        assert(0);
//		registerFile.setGPR8BitsHigh(RAX,0);
//		registerFile.setGPR8BitsLow(RAX,0);
//		registerFile.getFlagsBits().CF=0;
		break;
    case 7:
        cerr<<"Error:int 1ah function 07 reset real-time clock alarm not implemented!"<<endl;
        assert(0);

	default:
		break;
    }
}

u32 TimeOfDay::readFromPort(Memory &memory, RegisterFile &registerFile)
{
    (void)memory;(void)registerFile;
    return 0xcccccccc;
}
