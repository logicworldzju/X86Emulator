#include "Floppy.h"

Floppy::Floppy()
{

	char t[80];
	DWORD tDword;

	GetCurrentDirectory(sizeof(t),t);
	strcat(t,"\\easyVM.ini");
	GetPrivateProfileString("IMG","A","",t,sizeof(t),t);
	tDword=GetLastError();
	if (t[0]!=0)
	{
		hFloppy[0]=CreateFile(t, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
		SizeFloppy[0]=GetFileSize(hFloppy[0],&tDword);
		hMap[0]=CreateFileMapping(hFloppy[0],NULL,PAGE_READWRITE,0,SizeFloppy[0],"FloppyAMapping");
		pBufFloppy[0]=(char *)MapViewOfFile(hMap[0],FILE_MAP_ALL_ACCESS,0,0,SizeFloppy[0]);
		FloppyInserted[0]=true;
	}
	else
		FloppyInserted[0]=false;

}

void IO_Write_03F0(WORD data)	//参数都是通过栈传递的，所以要用WORD
{
	RegPointer=(BYTE)data;
}

void IO_Write_03F1(WORD data)
{
	FlpReg[RegPointer]=(BYTE)data;
	FloppyIOPoint=0;
	for (int i=0;i<3;i++)
	{
		FloppyIOPoint*=FlpCnt[i];
		FloppyIOPoint+=FlpReg[2-i];
	}
	FloppyIOPoint-=1;					//扇区从1开始编号，所以计算偏移的时候要先减1
	FloppyIOPoint*=512;					//每个扇区512个字节
	FloppyIOPoint+=(unsigned int)pBufFloppy[FlpReg[3]];
}

unsigned int getPoint()
{
    return FloppyIOPoint;
}

void setPoint(unsigned int point)
{
    FloppyIOPoint=point;
}

bool isInsert(int num)
{
    return FloppyInserted[num];
}

