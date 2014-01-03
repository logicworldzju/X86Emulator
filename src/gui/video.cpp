//#include <QPainter>
#include "video.h"
#include "../memory/memory.h"
#include "../cpu/register/registerfile.h"
#include "../io/ioportlist.h"
#include <iostream>
#include <stdlib.h>
#include <QDebug>

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

Video::Video(Memory &m, RegisterFile &r, ConsoleWidget &consoleWidget)
    :memory(m),registerFile(r),_consoleWidget(consoleWidget)
{
    CurColumn=CurRow=0;
    InitializeCurPage();
    CurVisible=true;
    CurrentPage=0;
    CursorTop=11;
    CursorBottom=12;

    CurrentMode=0x3;

    initVideoTextBuffer();
}

Video::~Video()
{

}

void Video::write2Port(u32 value,Memory& memory,RegisterFile& registerFile)
{
    (void)value;
//    this->memory=memory; that is a bug;
//    this->registerFile=registerFile; that is a bug;
    VideoMemoryStart=memory.getVideoTextMemoryAddress();
    MemoryStart=memory.getMemoryAddress();
    switch(registerFile.getGPR8BitsHigh(RAX))
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
    default:
        cerr<<"Int 10h function called,no such function code."<<registerFile.getGPR8BitsHigh(RAX)<<endl;
        exit(-1);
        break;
    }
}

u32 Video::readFromPort(Memory& memory,RegisterFile& registerFile)
{
    (void)registerFile;(void)memory;
    return 0xcccccccc;
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
    {
        CurVisible=false;
    }
    else
    {
        CurVisible=true;
    }
    _consoleWidget.setShowCursor(CurVisible);
    CursorTop=registerFile.getGPR8BitsHigh(RCX) & (u8)31;     //光标顶线在CH低五位
    CursorBottom=registerFile.getGPR8BitsLow(RCX) & (u8)31;   //光标底线在CL低五位
    return ;
}

void Video::SetCursorPositon()  //02h
{
    int pageNumber=registerFile.getGPR8BitsHigh(RBX);              //被设置的页号
    CurPage[2*pageNumber]=registerFile.getGPR8BitsHigh(RDX);       //光标行在DH
    CurPage[2*pageNumber+1]=registerFile.getGPR8BitsLow(RDX);      //光标列在DL
    if(CurrentPage==registerFile.getGPR8BitsHigh(RBX))    //被设置的是当前页
    {
        CurRow=registerFile.getGPR8BitsHigh(RDX);         //光标行在DH
        CurColumn=registerFile.getGPR8BitsLow(RDX);         //光标列在DL
        _consoleWidget.setCursorPosition(QPoint(CurColumn,CurRow));
    }
    return ;
}

void Video::ReadCurrentCursorPosition() //03h
{
    int pageNumber=registerFile.getGPR8BitsHigh(RBX);              //被选择的页号
    registerFile.setGPR8BitsHigh(RCX,CursorTop);          //光标顶线在CH
    registerFile.setGPR8BitsLow(RCX,CursorBottom);        //光标底线在CL
    registerFile.setGPR8BitsHigh(RDX,CurPage[2*pageNumber]);       //光标行在DH
    registerFile.setGPR8BitsLow(RDX,CurPage[2*pageNumber+1]);      //光标列在DL
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
    CurColumn=CurPage[2*CurrentPage+1];

    _consoleWidget.setCursorPosition(QPoint(CurColumn,CurRow));
    _consoleWidget.setVideoMemoryAddress(PAGESIZE*CurrentPage+memory.getVideoTextMemoryAddress());
}

void Video::ScrollCurrentPageUp()  //06h
{
    int rowCount=registerFile.getGPR8BitsLow(RAX);
    u8 attribute=registerFile.getGPR8BitsHigh(RBX);
    int top=registerFile.getGPR8BitsHigh(RCX);
    int left=registerFile.getGPR8BitsLow(RCX);
    int bottom=registerFile.getGPR8BitsHigh(RDX);
    int right=registerFile.getGPR8BitsLow(RDX);

    scrollUp(CurrentPage,rowCount,attribute,left,top,bottom,right);

    return ;
}

void Video::ScrollCurrentPageDown()  //07h
{
    int rowCount=registerFile.getGPR8BitsLow(RAX);
    u8 attribute=registerFile.getGPR8BitsHigh(RBX);
    int top=registerFile.getGPR8BitsHigh(RCX);
    int left=registerFile.getGPR8BitsLow(RCX);
    int bottom=registerFile.getGPR8BitsHigh(RDX);
    int right=registerFile.getGPR8BitsLow(RDX);

    scrollDown(CurrentPage,rowCount,attribute,left,top,bottom,right);

    return ;
}

void Video::ReadCharacter_AttributefromScreen() //08h
{
    int pageNumber=registerFile.getGPR8BitsHigh(RBX);              //被选择的页号
    int row=CurPage[pageNumber*2],column=CurPage[pageNumber*2+1];                  //被选中页的光标位置
    u8* z=VideoMemoryStart+pageNumber*PAGESIZE+row*80*2+column*2;              //被选中页光标所在位置对应字符地址
    registerFile.setGPR8BitsHigh(RAX,*(z+1));             //文本属性
    registerFile.setGPR8BitsLow(RAX,*z);                  //字符ASCII码
}

void Video::WriteCharacter_AttributetoScreen()  //09h
{
    u8 character=registerFile.getGPR8BitsLow(RAX);        //需要写入的字符ASCII码
    int pageNumber=registerFile.getGPR8BitsHigh(RBX);              //被选择的页号
    u8 textAttr=registerFile.getGPR8BitsLow(RBX);         //需要写入的字符属性
    int count=registerFile.getGPR16Bits(RCX);             //重复次数
    int row=CurPage[pageNumber*2],column=CurPage[pageNumber*2+1];                  //被选中页的光标位置
    u8* z=VideoMemoryStart+pageNumber*PAGESIZE+row*80*2+column*2;              //被选中页光标所在位置对应地址
    for(int j=0;j<count;j++)                              //向显存写入字符信息
    {
        *(z++)=character;
        *(z++)=textAttr;
    }
}

void Video::WriteCharacterOnlytoScreen()  //0Ah
{
    u8 character=registerFile.getGPR8BitsLow(RAX);        //需要写入的字符ASCII码
    int pageNumber=registerFile.getGPR8BitsHigh(RBX);              //被选择的页号
//    u8 textattr=TextAttribute;                            //需要写入的字符属性
    int count=registerFile.getGPR16Bits(RCX);             //重复次数
    int row=CurPage[pageNumber*2],column=CurPage[pageNumber*2+1];                  //被选中页的光标位置
    u8* z=VideoMemoryStart+pageNumber*PAGESIZE+row*80*2+column*2;              //被选中页光标所在位置对应地址
    for(int j=0;j<count;j++)                              //向显存写入字符信息
    {
        *(z++)=character;
//        *(z++)=textattr; bug here.
        z++;
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
    int pageNumber=registerFile.getGPR8BitsHigh(RBX);              //被选择的页号
//    int row=CurPage[pageNumber*2],column=CurPage[pageNumber*2+1];                  //被选中页的光标位置
/*    u8* z=MemoryStart+pageNumber*PAGESIZE+row*80*2+column*2;              //被选中页光标所在位置对应地址
    if(pageNumber==CurrentPage)                                    //被选中的为当前页
    {
        *(z++)=character;                                 //写入字符信息
        *(z++)=TextAttribute;
        if(CurRow==24&&CurColumn==79)                       //光标在页尾，移到下一页
        {
            CurPage[CurrentPage*2]=CurRow;
            CurPage[CurrentPage*2+1]=CurColumn;
            CurrentPage++;
            CurRow=CurColumn=0;
        }
        else
        {
            CurPage[CurrentPage*2]=CurRow=CurRow+(CurColumn+1)/80;
            CurPage[CurrentPage*2+1]=CurColumn=(CurColumn+1)%80;
        }
    }
    else                                                  //被选中的不是当前页
    {
        *(z++)=character;
        *(z++)=TextAttribute;
        if( CurPage[pageNumber*2]!=24|| CurPage[pageNumber*2+1]!=79)         //光标不在页尾，右移
        {
            CurPage[pageNumber*2]=CurPage[pageNumber*2]+(CurPage[pageNumber*2+1]+1)/80;
            CurPage[pageNumber*2+1]=(CurPage[pageNumber*2+1]+1)%80;
        }
    }
    return ;*/
    writeOneCharacter(pageNumber,0,false,character);
}

void Video::ReturnVideoStatus()  //0Fh
{
    registerFile.setGPR8BitsHigh(RAX,(u8)COLUMN_SIZE);          //列值在AH
    registerFile.setGPR8BitsLow(RAX,CurrentMode);          //显示模式在AL
    registerFile.setGPR8BitsHigh(RBX,CurrentPage);         //当前页在BH
    return ;
}

void Video::WriteString()  //13h
{
    int segment=registerFile.getSR(ES);                   //字符串的首地址
    int offset=registerFile.getGPR16Bits(RBP);
    u8* z=MemoryStart+segment*16+offset;
    int pageNumber=registerFile.getGPR8BitsHigh(RBX);               //被选择的页号
    u8 attribute=registerFile.getGPR8BitsLow(RBX);
    int count=registerFile.getGPR16Bits(RCX);              //字符串长度
    int oldRow=CurPage[pageNumber*2+0];//=registerFile.getGPR8BitsHigh(RDX);               //起始光标位置
    int oldColumn=CurPage[pageNumber*2+1];//registerFile.getGPR8BitsLow(RDX);

    CurPage[pageNumber*2+0]=registerFile.getGPR8BitsHigh(RDX);
    CurPage[pageNumber*2+1]=registerFile.getGPR8BitsLow(RDX);

    bool shouldCursorMove=registerFile.getGPR8BitsLow(RAX)&0x1;
    bool followByAttribute=registerFile.getGPR8BitsLow(RAX)&0x2;

    for(int i=0; i<count; i++)
    {
        if(followByAttribute)
        {
            u8 character=z[i*2+0];
            u8 attribute=z[i*2+1];
            writeOneCharacter(pageNumber,attribute,true,character);
        }
        else
        {
            u8 character=z[i];
            writeOneCharacter(pageNumber,attribute,true,character);
        }
    }

    if(!shouldCursorMove)
    {
        CurPage[pageNumber*2+0]=oldRow;
        CurPage[pageNumber*2+1]=oldColumn;
    }
    /*u8* c=VideoMemoryStart+pageNumber*PAGESIZE+row*80*2+column*2;               //被选中页光标所在位置对应地址
    if(registerFile.getGPR8BitsLow(RAX)==0x00)             //光标不移动，字符串中只有ASCII码
    {
        for(int j=0;j<count;count++)
        {
            *(c++)=*(z++);
            *(c++)=TextAttribute;
        }
        if(pageNumber==CurrentPage)
        {
            CurRow=CurPage[2*pageNumber]=row;
            CurColumn=CurPage[2*pageNumber+1]=column;
        }
        else
        {
            CurPage[2*pageNumber]=row;
            CurPage[2*pageNumber+1]=column;
        }

    }
    else if(registerFile.getGPR8BitsLow(RAX)==0x01)        //光标移动，字符串中只有ASCII码
    {
        for(int j=0;j<count;count++)
        {
            *(c++)=*(z++);
            *(c++)=TextAttribute;
        }
        if(pageNumber==CurrentPage)
        {
            CurRow=CurPage[2*pageNumber]=row+count/80+(column+count%80)/80;
            CurColumn=CurPage[2*pageNumber+1]=(column+count%80)%80;
            if(CurRow>24)
            {
                CurRow=CurPage[2*pageNumber]=24;
                CurColumn=CurPage[2*pageNumber+1]=79;
            }
        }
        else
        {
            CurPage[2*pageNumber]=row+count/80+(column+count%80)/80;
            CurPage[2*pageNumber+1]=(column+count%80)%80;
            if(CurPage[2*pageNumber]>24)
            {
                CurPage[2*pageNumber]=24;
                CurPage[2*pageNumber+1]=79;
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
        if(pageNumber==CurrentPage)
        {
            CurRow=CurPage[2*pageNumber]=row;
            CurColumn=CurPage[2*pageNumber+1]=column;
        }
        else
        {
            CurPage[2*pageNumber]=row;
            CurPage[2*pageNumber+1]=column;
        }

    }
    else if(registerFile.getGPR8BitsLow(RAX)==0x03)        //光标移动，字符串中有显示属性
    {
        for(int j=0;j<count;count++)
        {
            *(c++)=*(z++);
            *(c++)=*(z++);
        }
        if(pageNumber==CurrentPage)
        {
            CurRow=CurPage[2*pageNumber]=row+count/80+(column+count%80)/80;
            CurColumn=CurPage[2*pageNumber+1]=(column+count%80)%80;
            if(CurRow>24)
            {
                CurRow=CurPage[2*pageNumber]=24;
                CurColumn=CurPage[2*pageNumber+1]=79;
            }
        }
        else
        {
            CurPage[2*pageNumber]=row+count/80+(column+count%80)/80;
            CurPage[2*pageNumber+1]=(column+count%80)%80;
            if(CurPage[2*pageNumber]>24)
            {
                CurPage[2*pageNumber]=24;
                CurPage[2*pageNumber+1]=79;
            }
        }
    }

    return ;*/
}

void Video::scrollUp(int pageNumber,int rowCount, u8 attribute, int left, int top, int bottom, int right)
{
    assert(pageNumber>=0 && pageNumber<MAXPAGENUMBER);
    assert(left>=0 && left<COLUMN_SIZE);
    assert(right>=0 && right<COLUMN_SIZE);
    assert(top>=0 && top<ROW_SIZE);
    assert(bottom>=0 && bottom<ROW_SIZE);

    if(rowCount==0)
    {
        for(int i=top; i<=bottom; i++)
        {
            blankOneRow(pageNumber,attribute,i,left,right);
        }
    }
    else
    {
        for(int i=0; i<rowCount; i++)
        {
            scrollUpOneRow(pageNumber,attribute,left,top,bottom,right);
        }
    }
}

void Video::scrollUpOneRow(int pageNumber, u8 attribute, int left, int top, int bottom, int right)
{
    assert(pageNumber>=0 && pageNumber<MAXPAGENUMBER);
    assert(left>=0 && left<COLUMN_SIZE);
    assert(right>=0 && right<COLUMN_SIZE);
    assert(top>=0 && top<ROW_SIZE);
    assert(bottom>=0 && bottom<ROW_SIZE);

    u8* pageBase=memory.getVideoTextMemoryAddress()+PAGESIZE*pageNumber;
    for(int i=top; i<bottom; i++)
    {
        for(int j=left; j<=right; j++)
        {
            (pageBase+i*80*2+j*2)[0]=(pageBase+(i+1)*80*2+j*2)[0];
            (pageBase+i*80*2+j*2)[1]=(pageBase+(i+1)*80*2+j*2)[1];
        }
    }
    blankOneRow(pageNumber,attribute,bottom,left,right);
}

void Video::scrollDown(int pageNumber, int rowCount, u8 attribute, int left, int top, int bottom, int right)
{
    assert(pageNumber>=0 && pageNumber<MAXPAGENUMBER);
    assert(left>=0 && left<COLUMN_SIZE);
    assert(right>=0 && right<COLUMN_SIZE);
    assert(top>=0 && top<ROW_SIZE);
    assert(bottom>=0 && bottom<ROW_SIZE);

    if(rowCount==0)
    {
        for(int i=top; i<=bottom; i++)
        {
            blankOneRow(pageNumber,attribute,i,left,right);
        }
    }
    else
    {
        for(int i=0; i<rowCount; i++)
        {
            scrollDownOneRow(pageNumber,attribute,left,top,bottom,right);
        }
    }
}

void Video::scrollDownOneRow(int pageNumber, u8 attribute, int left, int top, int bottom, int right)
{
    assert(pageNumber>=0 && pageNumber<MAXPAGENUMBER);
    assert(left>=0 && left<COLUMN_SIZE);
    assert(right>=0 && right<COLUMN_SIZE);
    assert(top>=0 && top<ROW_SIZE);
    assert(bottom>=0 && bottom<ROW_SIZE);

    u8* pageBase=memory.getVideoTextMemoryAddress()+PAGESIZE*pageNumber;

    for(int i=bottom; i>=top+1; i--)
    {
        for(int j=left; j<=right; j++)
        {
            (pageBase+i*80*2+j*2)[0]=(pageBase+(i-1)*80*2+j*2)[0];
            (pageBase+i*80*2+j*2)[1]=(pageBase+(i-1)*80*2+j*2)[1];
        }
    }
    blankOneRow(pageNumber,attribute,top,left,right);
}

void Video::blankOneRow(int pageNumber, u8 attribute, int row, int left, int right)
{
    assert(pageNumber>=0 && pageNumber<MAXPAGENUMBER);
    assert(left>=0 && left<COLUMN_SIZE);
    assert(right>=0 && right<COLUMN_SIZE);
    assert(row>=0 && row<ROW_SIZE);

    u8* pageBase=memory.getVideoTextMemoryAddress()+PAGESIZE*pageNumber;

    int i=row;
    for(int j=left; j<=right; j++)
    {
        (pageBase+i*80*2+j*2)[0]=' ';
        (pageBase+i*80*2+j*2)[1]=attribute;
    }
}

void Video::writeOneCharacter(int pageNumber, u8 attribute,bool shouldWriteAttribute,u8 character)
{
    assert(pageNumber>=0 && pageNumber<MAXPAGENUMBER);

    u8* pageBase=memory.getVideoTextMemoryAddress()+PAGESIZE*pageNumber;

    int row=CurPage[pageNumber*2],column=CurPage[pageNumber*2+1];

    if(character==0x7)//bell
    {
        //do nothing.
    }
    else if(character==0x8)//backspace
    {
        if(column!=0) column--;
    }
    else if(character==0xa)//LF
    {
        if(row==ROW_SIZE-1)
        {
            scrollUp(pageNumber,1,0,0,0,ROW_SIZE-1,COLUMN_SIZE-1);
        }
        else
        {
            row++;
        }
    }
    else if(character==0xd)//CR
    {
        column=0;
    }
    else
    {
        (pageBase+row*COLUMN_SIZE*2+column*2)[0]=character;
        if(shouldWriteAttribute)
        {
            (pageBase+row*COLUMN_SIZE*2+column*2)[1]=attribute;
        }

        if(column==COLUMN_SIZE-1 && row==ROW_SIZE-1)
        {
            column=0;
            row=row;
            scrollUp(pageNumber,1,0,0,0,ROW_SIZE-1,COLUMN_SIZE-1);
        }
        else if(column==COLUMN_SIZE-1)
        {
            column=0;
            row++;
        }
        else
        {
            column++;
        }
    }
    CurPage[pageNumber*2+0]=row;
    CurPage[pageNumber*2+1]=column;
    if(pageNumber==CurrentPage)
    {
        CurColumn=column;
        CurRow=row;
        _consoleWidget.setCursorPosition(QPoint(CurColumn,CurRow));
    }
}

void Video::initVideoTextBuffer()
{
    for(int page=0;page<MAXPAGENUMBER;page++)
    {
        u8* pageBase = memory.getVideoTextMemoryAddress()+PAGESIZE*page;
        for(int i=0; i<PAGESIZE/2; i++)
        {
            pageBase[i*2+0]=' ';
            pageBase[i*2+1]=0xf;
        }
    }
}
