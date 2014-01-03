#ifndef VIDEO_H
#define VIDEO_H
#include "../cpu/cpu.h"
#include "../io/ioport.h"
#include "../memory/memory.h"
#include "../cpu/register/registerfile.h"
#include "gui/consolewidget.h"


class Video : public IOPort
{
private:
    const static int MAXPAGENUMBER=8;
    const static int PAGESIZE=80*25*2;
    const static int COLUMN_SIZE=80;
    const static int ROW_SIZE=25;
public:
    Memory& memory;
    RegisterFile& registerFile;
    u8* VideoMemoryStart;			                            //虚拟显存的起始地址
    u8* MemoryStart;			                                    //虚拟内存的起始地址
    u8 CurColumn,CurRow,CurPage[MAXPAGENUMBER*2];	            //文本模式下当前的光标位置及各页光标位置
    bool CurVisible;                                        //光标是否可见
    u8 CurrentPage;                                         //当前页
    u8 CursorTop,CursorBottom;	                            //光标的顶线、底线
    u8 TextAttribute;                                       //文本属性
    u8 CurrentMode;                                         //当前显示模式

public:
    Video(Memory &m,RegisterFile &r,ConsoleWidget& consoleWidget);
    ~Video();
    void write2Port(u32 value,Memory& memory,RegisterFile& registerFile);
    u32 readFromPort(Memory& memory,RegisterFile& registerFile);
public:
    void InitializeCurPage();                               //初始化各页光标位置为左上角
    void DispModeChanged();                                 //00h
    void SetCursorType();                                   //01h
    void SetCursorPositon();                                //02h
    void ReadCurrentCursorPosition();                       //03h
    void ReadLightPenPosition();                            //04h
    void SelectNewVideoPage();                              //05h
    void ScrollCurrentPageUp();                             //06h
    void ScrollCurrentPageDown();                           //07h
    void ReadCharacter_AttributefromScreen();               //08h
    void WriteCharacter_AttributetoScreen();                //09h
    void WriteCharacterOnlytoScreen();                      //0Ah
    void SetColorPalette();                                 //0Bh
    void WritePixel();                                      //0Ch
    void ReadPixel();                                       //0Dh
    void WriteTeletypetoActivePage();                       //0Eh
    void ReturnVideoStatus();                               //0Fh
    void WriteString();                                     //13h
private:
    void scrollUp(int pageNumber, int rowCount, u8 attribute, int left, int top, int bottom, int right);
    void scrollUpOneRow(int pageNumber,u8 attribute, int left, int top, int bottom, int right);
    void scrollDown(int pageNumber, int rowCount, u8 attribute, int left, int top, int bottom, int right);
    void scrollDownOneRow(int pageNumber,u8 attribute, int left, int top, int bottom, int right);
    void blankOneRow(int pageNumber,u8 attribute,int row,int left,int right);

    void writeOneCharacter(int pageNumber, u8 attribute, bool shouldWriteAttribute, u8 character);
    void initVideoTextBuffer();
private:
    ConsoleWidget& _consoleWidget;
    const static u8 DEFAULT_ATTRIBUTE=0x7;
};


#endif // VIDEO_H
