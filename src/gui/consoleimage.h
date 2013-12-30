#ifndef CONSOLEIMAGE_H
#define CONSOLEIMAGE_H
#include "../type.h"
#include <QImage>
#include <string>

class ConsoleImage //: public QImage
{
public:
    explicit ConsoleImage(const std::string& asciiFontPath,u32 width=80,u32 height=25);
    ~ConsoleImage();
    void resizeConsole(u32 width,u32 height);
    u32 getConsoleWidth(){return _consoleWidth;}
    u32 getConsoleHeight(){return _consoleHeight;}
    const QImage& getImage() const
    {
        return *_image;
    }
    void draw(const u8* textBuffer,const QPoint& cursorPosition,bool showCursor);
//    void setCursorType(u8 )
//signals:

//private slots:
private:
    void readFontFile(const std::string& asciiFontPath);
    void drawCharacter(u8 character, u8 attribute, const QPoint& position);
    void drawFont(u8 font[], u8 attribute, const QPoint &position, bool drawBackground=true);
    void drawCucrsor(const QPoint& cursorPosition);
    QRgb getColorFromAttribute(u8 attribute);
private:
    const static u8 CHARACTER_WIDTH=8;
    const static u8 CHARACTER_HEIGHT=16;
    u32 _consoleWidth;
    u32 _consoleHeight;
    QImage* _image;
    u8* _fontFile;
    const static u16 FONT_SIZE_PER_CHARACTER=CHARACTER_WIDTH*CHARACTER_HEIGHT/8;
    const static u16 FONT_FILE_SIZE=256*FONT_SIZE_PER_CHARACTER;
    static u8 _cursorFont[FONT_SIZE_PER_CHARACTER];
};

#endif // CONSOLEIMAGE_H
