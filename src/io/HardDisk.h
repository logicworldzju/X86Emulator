#ifndef HARDDISK_H_INCLUDED
#define HARDDISK_H_INCLUDED

class HardDisk{
public:

    void IO_Write_03F6(WORD data);	//参数都是通过栈传递的，所以要用WORD
    void IO_Write_03F7(WORD data);
    unsigned int getPoint();
    void setPoint(unsigned int point);

private:
    unsigned int HardDiskIOPoint;		//当前读写的数据的指针，供DMA使用
    // 内部寄存器
    unsigned int HdReg[4];		//当前读写扇区的指针。  扇区、磁头、柱面、驱动器
    char HdCnt[4][3]={
        {0,16,63},
        {0,16,63},
        {0,16,63},
        {0,16,63},
    };		//硬盘总是有16个盘面（磁头），63个扇区，柱面数依据硬盘容量而定。
}
#endif // HARDDISK_H_INCLUDED
