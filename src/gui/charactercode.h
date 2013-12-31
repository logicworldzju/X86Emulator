#ifndef CHARACTERCODE_H
#define CHARACTERCODE_H
#include "type.h"
#include <QKeyEvent>

class CharacterCode
{
public:
    CharacterCode();
    //Call initTranslate() before any fromQtKey(),but calling initTranslate() only once globally is enough.
    static void initTranslateTable();
    static u16 fromQtKey(int key,Qt::KeyboardModifiers modifiers,bool isPressed);

    static u16 _normalTable[256];
    static u16 _shiftedTable[256];
    static u16 _controlTable[256];
    static u16 _altTable[256];

    //used for the key>0x100;
    static u16 _normalTable2[256];
    static u16 _shiftedTable2[256];
    static u16 _controlTable2[256];
    static u16 _altTable2[256];
};

#endif // CHARACTERCODE_H
