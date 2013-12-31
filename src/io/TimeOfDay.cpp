#include "TimeOfDay.h"


TimeOfDay::TimeOfDay(IOPortList ioPortList)
{
    SYSTEMTIME st;
    GetLocalTime(&st);
    rTime[0]=st.wMilliseconds/10;
	rTime[1]=(unsigned char)st.wSecond;
	rTime[2]=(unsigned char)st.wMinute;
	rTime[3]=(unsigned char)st.wHour;
	rTime[4]=(unsigned char)st.wDay;
	rTime[5]=(unsigned char)st.wMonth;
	rTime[6]=st.wYear%100;
	rTime[7]=st.wYear/100;
	TranslToBCD();
	SetTimer(NULL,NULL,TICK,(TIMERPROC)RTCTimerThread);
	ioPortList.add2PortList(13h,this);
}

void TranslToBCD()
{
	for (int i=0;i<8;i++)
	{
		BCDTIme[i]=rTime[i]/10;
		BCDTIme[i]<<=4;
		BCDTIme[i]+=rTime[i]%10;
	}
}

void RTCTimerThread()
{
	(*RtcTick)++;

	rTime[7]++;
	for (int i=0;i<7;i++)
	{
		if (rTime[i]>carry[i])
		{
			rTime[i+1]++;
			rTime[i]%=carry[i];
		}
	}
	switch(rTime[5])		//Month
	{
	case 2:
		if ((rTime[6]%4==0 && rTime[7]%4) || (rTime[6]==0 && rTime[7]%4==0))
		{
			rTime[5]+=rTime[4]/29;
			rTime[4]%=29;
		}
		else
		{
			rTime[5]+=rTime[4]/28;
			rTime[4]%=28;
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		rTime[5]+=rTime[4]/30;
		rTime[4]%=30;
		break;
	}
	TranslToBCD();
}

void write2Port(u32 value,Memory& memory,RegisterFile& registerFile)
{
	switch(registerFile.getGPR8BitsHigh(RAX))
	{
	case 0:
		registerFile.setGPR16Bits(RDX,((*RtcTick)&0xffff));
		registerFile.setGPR16Bits(RCX,(((*RtcTick) >> 16) & 0xffff));
        registerFile.setGPR8BitsLow(RAX,(*RtcTick)/8640000);		//每天有8640000个Tick
		break;
	case 1:
		(*RtcTick)=registerFile.getGPR16Bits(RCX);
		(*RtcTick)<<=16;
		(*RtcTick)+=registerFile.getGPR16Bits(RDX);
		registerFile.setGPR8BitsHigh(RAX,1);
		break;
	case 2:
	    registerFile.setGPR8BitsHigh(RAX,0);
	    registerFile.setGPR8BitsLow(RAX,BCDTIme[3]);
		registerFile.setGPR8BitsHigh(RCX,BCDTIme[3]);
		registerFile.setGPR8BitsLow(RCX,BCDTIme[2]);
		registerFile.setGPR8BitsHigh(RDX,BCDTIme[1]);
		registerFile.setGPR8BitsLow(RDX,0);
		break;
	case 3:
		rTime[3]=BCDtoBin(registerFile.getGPR8BitsHigh(RCX));
		rTime[2]=BCDtoBin(registerFile.getGPR8BitsLow(RCX));
		rTime[1]=BCDtoBin(registerFile.getGPR8BitsHigh(RDX));
		registerFile.setGPR8BitsHigh(RAX,0);
		break;
	case 4:
	    registerFile.setGPR8BitsHigh(RCX,BCDTIme[7]);
		registerFile.setGPR8BitsLow(RCX,BCDTIme[6]);
		registerFile.setGPR8BitsHigh(RDX,BCDTIme[5]);
		registerFile.setGPR8BitsLow(RDX,BCDTIme[4]);
		registerFile.getFlagsBits().ZF=0;
		registerFile.getFlagsBits().CF=0;
		break;
	case 5:
		rTime[7]=BCDtoBin(registerFile.getGPR8BitsHigh(RCX));
		rTime[6]=BCDtoBin(registerFile.getGPR8BitsLow(RCX));
		rTime[5]=BCDtoBin(registerFile.getGPR8BitsHigh(RDX));
		rTime[4]=BCDtoBin(registerFile.getGPR8BitsLow(RDX));
		registerFile.setGPR8BitsLow(RDX,0);
		registerFile.getFlagsBits().CF=0;
		registerFile.getFlagsBits().ZF=0;
		break;
	case 6:
		registerFile.setGPR8BitsHigh(RAX,0);
		registerFile.setGPR8BitsLow(RAX,0);
		registerFile.getFlagsBits().CF=0;
		break;
	default:
		break;
	}
}
