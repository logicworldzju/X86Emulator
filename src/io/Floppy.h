#ifndef FLOPPY_H_INCLUDED
#define FLOPPY_H_INCLUDED

class Floppy{
public
    void IO_Write_03F0(WORD data);
    void IO_Write_03F1(WORD data);
    unsigned int getPoint();
    void setPoint(unsigned int point);
    bool isInsert(int num);

private
    unsigned int FloppyIOPoint; //当前读写数据的指针

    char FlpReg[4]; //当前读写扇区的指针
    char FlpCnt[3]={80,2,18};   //1.44MB的软盘有80个柱面，2个盘面（磁头），18个扇区
    char RegPointer=0;

    HANDLE hFloppy[4];				//一个软盘控制器最多连接4个驱动器
    HANDLE hMap[4];
    unsigned int SizeFloppy[4];
    char *pBufFloppy[4];
    bool FloppyInserted[4];
};



#endif // FLOPPY_H_INCLUDED
