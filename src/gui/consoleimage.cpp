#include "consoleimage.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
using namespace std;

ConsoleImage::ConsoleImage(const string& asciiFontPath, u32 width, u32 height)
{
    _image=NULL;
    resizeConsole(width,height);
    readFontFile(asciiFontPath);
}

ConsoleImage::~ConsoleImage()
{
    if(_image)
    {
        delete _image;
    }
    if(_fontFile)
    {
        delete _fontFile;
    }
}

void ConsoleImage::resizeConsole(u32 width, u32 height)
{
    _consoleWidth=width;
    _consoleHeight=height;

    if(_image)
    {
        delete _image;
    }
    _image=new QImage(_consoleWidth*CHARACTER_WIDTH,_consoleHeight*CHARACTER_HEIGHT,QImage::Format_RGB32);
}

void ConsoleImage::draw(const u8 *textBuffer, const QPoint &cursorPosition, bool showCursor)
{
    for(u32 i=0; i<_consoleHeight; i++)
    {
        for(u32 j=0; j<_consoleWidth; j++)
        {
            u8 character = textBuffer[2*(i*_consoleWidth+j)+0];
            u8 attribute = textBuffer[2*(i*_consoleWidth+j)+1];
            drawCharacter(character,attribute,QPoint(j,i));
        }
    }
    if(showCursor)
    {
        drawCucrsor(cursorPosition);
    }
}

void ConsoleImage::readFontFile(const string &asciiFontPath)
{
    _fontFile = new u8[FONT_FILE_SIZE];
    ifstream fin(asciiFontPath.c_str(),ios::binary);
    if(!fin.is_open())
    {
        cerr<<"Error:Can't open file "<<asciiFontPath<<endl;
        exit(-1);
    }
    fin.read((char*)_fontFile,FONT_FILE_SIZE);
    if(fin.gcount()!=FONT_FILE_SIZE)
    {
        cerr<<"Error:Can't read enough data from "<<asciiFontPath<<endl;
        exit(-1);
    }
}

void ConsoleImage::drawCharacter(u8 character, u8 attribute, const QPoint &position)
{
    u8* font = &_fontFile[character*FONT_SIZE_PER_CHARACTER];
    drawFont(font,attribute,position,true);
}

void ConsoleImage::drawFont(u8 font[],u8 attribute, const QPoint &position,
                                 bool drawBackground)
{
    for(u32 i=0; i<CHARACTER_HEIGHT; i++)
    {
        u8 fontScanLine = font[i];
        QRgb foregroundColor = getColorFromAttribute(attribute&0xf);
        QRgb backgroundColor = getColorFromAttribute((attribute>>4)&0x7);

        int pixelX = position.x()*CHARACTER_WIDTH;
        int pixelY = position.y()*CHARACTER_HEIGHT+i;
        for(u32 j=0; j<CHARACTER_WIDTH; j++)
        {
            if(fontScanLine&(1<<(7-j)))
            {
                //foreground
                _image->setPixel(pixelX+j,pixelY,foregroundColor);
            }
            else
            {
                //background
                if(drawBackground)
                {
                    _image->setPixel(pixelX+j,pixelY,backgroundColor);
                }
            }
        }
    }
}

QRgb ConsoleImage::getColorFromAttribute(u8 attribute)
{
    switch(attribute)
    {
    case 0://black
        return qRgb(0,0,0);
    case 1://blue
        return qRgb(0,0,255);
    case 2://green
        return qRgb(0,255,0);
    case 3://cyan
        return qRgb(0,255,255);
    case 4://red
        return qRgb(255,0,0);
    case 5://magenta
        return qRgb(255,0,255);
    case 6://brown
        return qRgb(255,64,64);
    case 7://lightgray
        return qRgb(0xd3,0xd3,0xd3);
    case 8://darkgray
        return qRgb(0x40,0x40,0x40);
    case 9://lightblue
        return qRgb(0x87,0xce,0xfa);
    case 10://lightgreen
        return qRgb(0x9a,0xff,0x9a);
    case 11://lightcyan
        return qRgb(0xe0,0xff,0xff);
    case 12://lightred
        return qRgb(255,193,193);
    case 13://lightmagenta
        return qRgb(0,255,0);
    case 14://yellow
        return qRgb(255,255,0);
    case 15://white
        return qRgb(255,255,255);
    default:
        assert(0);
    }
    assert(0);
    return qRgb(0,0,0);
}

void ConsoleImage::drawCucrsor(const QPoint &cursorPosition)
{
    if(cursorPosition.x()>=0 && cursorPosition.x()<int(_consoleWidth) &&
            cursorPosition.y()>=0 && cursorPosition.y()<int(_consoleHeight))
    {
        drawFont(_cursorFont,0xf,cursorPosition,false);
    }
}
u8 ConsoleImage::_cursorFont[FONT_SIZE_PER_CHARACTER]={0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
                                                      0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xff};
