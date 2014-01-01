#include <QPainter>
#include "video.h"
#include "../memory/memory.h"
#include "../cpu/register/registerfile.h"
#include "../io/ioportlist.h"
#include <iostream>

using namespace std;
//extern IOPortList ioPortList;
/*
Memory memory;
RegisterFile registerFile;
u8* MemoryStart=memory.getVideoMemoryAddress();			//虚拟显存的起始地址
u8* Start=memory.getMemoryAddress();			        //虚拟内存的起始地址
u8 CurLine,CurRow,CurPage[MAXPAGENUMBER*2];	            //文本模式下当前的光标位置及各页光标位置
bool CurVisible;                                        //光标是否可见
u8 CurrentPage;                                         //当前页
u8 CursorTop,CursorBottom;	                            //光标的顶线、底线
u8 TextAttribute;                                       //文本属性
u8 CurrentMode;                                         //当前显示模式
*/

Video::Video(Memory &m,RegisterFile &r):memory(m),registerFile(r)
{
    CurLine=CurRow=0;
    InitializeCurPage();
    CurVisible=true;
    CurrentPage=0;
    CursorTop=11;
    CursorBottom=12;
}

Video::~Video()
{

}

void Video::write2Port(u32 value,Memory& memory,RegisterFile& registerFile)
{
    this->memory=memory;
    this->registerFile=registerFile;
    MemoryStart=memory.getVideoMemoryAddress();
    Start=memory.getMemoryAddress();
    switch(value)
    {
    case 0:DispModeChanged();break;
    case 1:SetCursorType();break;
    case 2:SetCursorPositon();break;
    case 3:ReadCurrentCursorPosition();break;
    case 4:ReadLightPenPosition();break;
    case 5:SelectNewVideoPage();break;
    case 6:ScrollCurrentPageUp();break;
    case 7:ScrollCurrentPageDown();break;
    case 8:ReadCharacter_AttributefromScreen();break;
    case 9:WriteCharacter_AttributetoScreen();break;
    case 0xA:WriteCharacterOnlytoScreen();break;
    case 0xB:SetColorPalette();break;
    case 0xC:WritePixel();break;
    case 0xD:ReadPixel();break;
    case 0xE:WriteTeletypetoActivePage();break;
    case 0xF:ReturnVideoStatus();break;
    case 0x13:WriteString();break;
    default:DispModeChanged();break;
    }
}

u32 Video::readFromPort(Memory& memory,RegisterFile& registerFile)
{
    return 32;
}

void Video::InitializeCurPage()                                //初始化各页光标位置为左上角
{
    for(int i=0;i<MAXPAGENUMBER;i++)
        CurPage[2*i]=CurPage[2*i+1]=0;
}

void Video::DispModeChanged()  //00h
{
    cout<<"Int 10h function 00h called."<<endl;
    return ;
}

void Video::SetCursorType()    //01h
{
    if(registerFile.getGPR8BitsHigh(RCX) & (u8)32)            //CH第五位为1时，光标不可见
        CurVisible=false;
    else
        CurVisible=true;
    CursorTop=registerFile.getGPR8BitsHigh(RCX) & (u8)31;     //光标顶线在CH低五位
    CursorBottom=registerFile.getGPR8BitsLow(RCX) & (u8)31;   //光标底线在CL低五位
    return ;
}

void Video::SetCursorPositon()  //02h
{
    int i=registerFile.getGPR8BitsHigh(RBX);              //被设置的页号
    CurPage[2*i]=registerFile.getGPR8BitsHigh(RDX);       //光标行在DH
    CurPage[2*i+1]=registerFile.getGPR8BitsLow(RDX);      //光标列在DL
    if(CurrentPage==registerFile.getGPR8BitsHigh(RBX))    //被设置的是当前页
    {
        CurRow=registerFile.getGPR8BitsHigh(RDX);         //光标行在DH
        CurLine=registerFile.getGPR8BitsLow(RDX);         //光标列在DL
    }
    return ;
}

void Video::ReadCurrentCursorPosition() //03h
{
    int i=registerFile.getGPR8BitsHigh(RBX);              //被选择的页号
    registerFile.setGPR8BitsHigh(RCX,CursorTop);          //光标顶线在CH
    registerFile.setGPR8BitsLow(RCX,CursorBottom);        //光标底线在CL
    registerFile.setGPR8BitsHigh(RDX,CurPage[2*i]);       //光标行在DH
    registerFile.setGPR8BitsLow(RDX,CurPage[2*i+1]);      //光标列在DL
    registerFile.setGPR16Bits(RAX,0);                     //AX=00H
}

void Video::ReadLightPenPosition()  //04h
{
    cout<<"Int 10h function 04h called."<<endl;
    return ;
}

void Video::SelectNewVideoPage()  //05h
{
    CurrentPage=registerFile.getGPR8BitsLow(RAX);         //新的当前页在AL
    CurRow=CurPage[2*CurrentPage];                        //设置新光标位置
    CurLine=CurPage[2*CurrentPage+1];
}

void Video::ScrollCurrentPageUp()  //06h
{
    return ;
}

void Video::ScrollCurrentPageDown()  //07h
{
    return ;
}

void Video::ReadCharacter_AttributefromScreen() //08h
{
    int i=registerFile.getGPR8BitsHigh(RBX);              //被选择的页号
    int x=CurPage[i*2],y=CurPage[i*2+1];                  //被选中页的光标位置
    u8* z=MemoryStart+i*PAGESIZE+x*80*2+y*2;              //被选中页光标所在位置对应字符地址
    registerFile.setGPR8BitsHigh(RAX,*(z+1));             //文本属性
    registerFile.setGPR8BitsLow(RAX,*z);                  //字符ASCII码
}

void Video::WriteCharacter_AttributetoScreen()  //09h
{
    u8 character=registerFile.getGPR8BitsLow(RAX);        //需要写入的字符ASCII码
    int i=registerFile.getGPR8BitsHigh(RBX);              //被选择的页号
    u8 textattr=registerFile.getGPR8BitsLow(RBX);         //需要写入的字符属性
    int count=registerFile.getGPR16Bits(RCX);             //重复次数
    int x=CurPage[i*2],y=CurPage[i*2+1];                  //被选中页的光标位置
    u8* z=MemoryStart+i*PAGESIZE+x*80*2+y*2;              //被选中页光标所在位置对应地址
    for(int j=0;j<count;j++)                              //向显存写入字符信息
    {
        *(z++)=character;
        *(z++)=textattr;
    }
}

void Video::WriteCharacterOnlytoScreen()  //0Ah
{
    u8 character=registerFile.getGPR8BitsLow(RAX);        //需要写入的字符ASCII码
    int i=registerFile.getGPR8BitsHigh(RBX);              //被选择的页号
    u8 textattr=TextAttribute;                            //需要写入的字符属性
    int count=registerFile.getGPR16Bits(RCX);             //重复次数
    int x=CurPage[i*2],y=CurPage[i*2+1];                  //被选中页的光标位置
    u8* z=MemoryStart+i*PAGESIZE+x*80*2+y*2;              //被选中页光标所在位置对应地址
    for(int j=0;j<count;j++)                              //向显存写入字符信息
    {
        *(z++)=character;
        *(z++)=textattr;
    }
}

void Video::SetColorPalette()  //0Bh
{
    cout<<"Int 10h function 0Bh called."<<endl;
    return ;
}

void Video::WritePixel()      //0Ch
{
    cout<<"Int 10h function 0Ch called."<<endl;
    return ;
}

void Video::ReadPixel()    //0Dh
{
    cout<<"Int 10h function 0Dh called."<<endl;
    return ;
}

void Video::WriteTeletypetoActivePage()  //0Eh
{
    u8 character=registerFile.getGPR8BitsLow(RAX);        //需要写入的字符ASCII码
    int i=registerFile.getGPR8BitsHigh(RBX);              //被选择的页号
    int x=CurPage[i*2],y=CurPage[i*2+1];                  //被选中页的光标位置
    u8* z=MemoryStart+i*PAGESIZE+x*80*2+y*2;              //被选中页光标所在位置对应地址
    if(i==CurrentPage)                                    //被选中的为当前页
    {
        *(z++)=character;                                 //写入字符信息
        *(z++)=TextAttribute;
        if(CurRow==24&&CurLine==79)                       //光标在页尾，移到下一页
        {
            CurPage[CurrentPage*2]=CurRow;
            CurPage[CurrentPage*2+1]=CurLine;
            CurrentPage++;
            CurRow=CurLine=0;
        }
        else
        {
            CurPage[CurrentPage*2]=CurRow=CurRow+(CurLine+1)/80;
            CurPage[CurrentPage*2+1]=CurLine=(CurLine+1)%80;
        }
    }
    else                                                  //被选中的不是当前页
    {
        *(z++)=character;
        *(z++)=TextAttribute;
        if( CurPage[i*2]!=24|| CurPage[i*2+1]!=79)         //光标不在页尾，右移
        {
            CurPage[i*2]=CurPage[i*2]+(CurPage[i*2+1]+1)/80;
            CurPage[i*2+1]=(CurPage[i*2+1]+1)%80;
        }
    }
    return ;
}

void Video::ReturnVideoStatus()  //0Fh
{
    registerFile.setGPR8BitsHigh(RAX,(u8)COLUMN);          //列值在AH
    registerFile.setGPR8BitsLow(RAX,CurrentMode);          //显示模式在AL
    registerFile.setGPR8BitsHigh(RBX,CurrentPage);         //当前页在BH
    return ;
}

void Video::WriteString()  //13h
{
    int x=registerFile.getGPR16Bits(ES);                   //字符串的首地址
    int y=registerFile.getGPR16Bits(RBP);
    u8* z=Start+x*16+y;
    int i=registerFile.getGPR8BitsHigh(RBX);               //被选择的页号
    int count=registerFile.getGPR16Bits(RCX);              //字符串长度
    int a=registerFile.getGPR8BitsHigh(RDX);               //起始光标位置
    int b=registerFile.getGPR8BitsLow(RDX);
    u8* c=MemoryStart+i*PAGESIZE+a*80*2+b*2;               //被选中页光标所在位置对应地址
    if(registerFile.getGPR8BitsLow(RAX)==0x00)             //光标不移动，字符串中只有ASCII码
    {
        for(int j=0;j<count;count++)
        {
            *(c++)=*(z++);
            *(c++)=TextAttribute;
        }
        if(i==CurrentPage)
        {
            CurRow=CurPage[2*i]=a;
            CurLine=CurPage[2*i+1]=b;
        }
        else
        {
            CurPage[2*i]=a;
            CurPage[2*i+1]=b;
        }

    }
    else if(registerFile.getGPR8BitsLow(RAX)==0x01)        //光标移动，字符串中只有ASCII码
    {
        for(int j=0;j<count;count++)
        {
            *(c++)=*(z++);
            *(c++)=TextAttribute;
        }
        if(i==CurrentPage)
        {
            CurRow=CurPage[2*i]=a+count/80+(b+count%80)/80;
            CurLine=CurPage[2*i+1]=(b+count%80)%80;
            if(CurRow>24)
            {
                CurRow=CurPage[2*i]=24;
                CurLine=CurPage[2*i+1]=79;
            }
        }
        else
        {
            CurPage[2*i]=a+count/80+(b+count%80)/80;
            CurPage[2*i+1]=(b+count%80)%80;
            if(CurPage[2*i]>24)
            {
                CurPage[2*i]=24;
                CurPage[2*i+1]=79;
            }
        }
    }
    else if(registerFile.getGPR8BitsLow(RAX)==0x02)        //光标不移动，字符串中有显示属性
    {
        for(int j=0;j<count;count++)
        {
            *(c++)=*(z++);
            *(c++)=*(z++);
        }
        if(i==CurrentPage)
        {
            CurRow=CurPage[2*i]=a;
            CurLine=CurPage[2*i+1]=b;
        }
        else
        {
            CurPage[2*i]=a;
            CurPage[2*i+1]=b;
        }

    }
    else if(registerFile.getGPR8BitsLow(RAX)==0x03)        //光标移动，字符串中有显示属性
    {
        for(int j=0;j<count;count++)
        {
            *(c++)=*(z++);
            *(c++)=*(z++);
        }
        if(i==CurrentPage)
        {
            CurRow=CurPage[2*i]=a+count/80+(b+count%80)/80;
            CurLine=CurPage[2*i+1]=(b+count%80)%80;
            if(CurRow>24)
            {
                CurRow=CurPage[2*i]=24;
                CurLine=CurPage[2*i+1]=79;
            }
        }
        else
        {
            CurPage[2*i]=a+count/80+(b+count%80)/80;
            CurPage[2*i+1]=(b+count%80)%80;
            if(CurPage[2*i]>24)
            {
                CurPage[2*i]=24;
                CurPage[2*i+1]=79;
            }
        }
    }

    return ;
}
