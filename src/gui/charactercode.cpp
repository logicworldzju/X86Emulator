#include "charactercode.h"
#include <iostream>
#include <stdlib.h>
#include <assert.h>
using namespace std;

CharacterCode::CharacterCode()
{
}

void CharacterCode::initTranslateTable()
{
    _normalTable['`']=0x2960;_shiftedTable['`']=0x297e;_controlTable['`']=0x0000;_altTable['`']=0x0000;
    _normalTable['~']=0x2960;_shiftedTable['~']=0x297e;_controlTable['~']=0x0000;_altTable['~']=0x0000;

    _normalTable['1']=0x0231;_shiftedTable['1']=0x0221;_controlTable['1']=0x0000;_altTable['1']=0x7800;
    _normalTable['!']=0x0231;_shiftedTable['!']=0x0221;_controlTable['!']=0x0000;_altTable['!']=0x7800;

    _normalTable['2']=0x0332;_shiftedTable['2']=0x0340;_controlTable['2']=0x0300;_altTable['2']=0x7900;
    _normalTable['@']=0x0332;_shiftedTable['@']=0x0340;_controlTable['@']=0x0300;_altTable['@']=0x7900;

    _normalTable['3']=0x0433;_shiftedTable['3']=0x0423;_controlTable['3']=0x0000;_altTable['3']=0x7a00;
    _normalTable['#']=0x0433;_shiftedTable['#']=0x0423;_controlTable['#']=0x0000;_altTable['#']=0x7a00;

    _normalTable['4']=0x0534;_shiftedTable['4']=0x0524;_controlTable['4']=0x0000;_altTable['4']=0x7b00;
    _normalTable['$']=0x0534;_shiftedTable['$']=0x0524;_controlTable['$']=0x0000;_altTable['$']=0x7b00;

    _normalTable['5']=0x0635;_shiftedTable['5']=0x0625;_controlTable['5']=0x0000;_altTable['5']=0x7c00;
    _normalTable['%']=0x0635;_shiftedTable['%']=0x0625;_controlTable['%']=0x0000;_altTable['%']=0x7c00;

    _normalTable['6']=0x0736;_shiftedTable['6']=0x075e;_controlTable['6']=0x071e;_altTable['6']=0x7d00;
    _normalTable['^']=0x0736;_shiftedTable['^']=0x075e;_controlTable['^']=0x071e;_altTable['^']=0x7d00;

    _normalTable['7']=0x0837;_shiftedTable['7']=0x0826;_controlTable['7']=0x0000;_altTable['7']=0x7e00;
    _normalTable['&']=0x0837;_shiftedTable['&']=0x0826;_controlTable['&']=0x0000;_altTable['&']=0x7e00;

    _normalTable['8']=0x0938;_shiftedTable['8']=0x092a;_controlTable['8']=0x0000;_altTable['8']=0x7f00;
    _normalTable['*']=0x0938;_shiftedTable['*']=0x092a;_controlTable['*']=0x0000;_altTable['*']=0x7f00;

    _normalTable['9']=0x0a39;_shiftedTable['9']=0x0a28;_controlTable['9']=0x0000;_altTable['9']=0x8000;
    _normalTable['(']=0x0a39;_shiftedTable['(']=0x0a28;_controlTable['(']=0x0000;_altTable['(']=0x8000;

    _normalTable['0']=0x0b30;_shiftedTable['0']=0x0b29;_controlTable['0']=0x0000;_altTable['0']=0x8100;
    _normalTable[')']=0x0b30;_shiftedTable[')']=0x0b29;_controlTable[')']=0x0000;_altTable[')']=0x8100;

    _normalTable['-']=0x0c2d;_shiftedTable['-']=0x0c5f;_controlTable['-']=0x0c1f;_altTable['-']=0x8200;
    _normalTable['_']=0x0c2d;_shiftedTable['_']=0x0c5f;_controlTable['_']=0x0c1f;_altTable['_']=0x8200;

    _normalTable['+']=0x0d3d;_shiftedTable['+']=0x0d2b;_controlTable['+']=0x0000;_altTable['+']=0x8300;
    _normalTable['=']=0x0d3d;_shiftedTable['=']=0x0d2b;_controlTable['=']=0x0000;_altTable['=']=0x8300;

    _normalTable2[Qt::Key_Backspace&0xff]=0x0e08;_shiftedTable2[Qt::Key_Backspace&0xff]=0x0e08;
    _controlTable2[Qt::Key_Backspace&0xff]=0x0e7f;_altTable2[Qt::Key_Backspace&0xff]=0x0000;

    _normalTable2[Qt::Key_Tab&0xff]=0x0f09;_shiftedTable2[Qt::Key_Tab&0xff]=0x0f00;
    _controlTable2[Qt::Key_Tab&0xff]=0x0000;_altTable2[Qt::Key_Tab&0xff]=0x0000;

    _normalTable['Q']=0x1071;_shiftedTable['Q']=0x1051;_controlTable['Q']=0x1011;_altTable['Q']=0x1000;
    _normalTable['W']=0x1177;_shiftedTable['W']=0x1157;_controlTable['W']=0x1117;_altTable['W']=0x1100;
    _normalTable['E']=0x1265;_shiftedTable['E']=0x1245;_controlTable['E']=0x1205;_altTable['E']=0x1200;
    _normalTable['R']=0x1372;_shiftedTable['R']=0x1352;_controlTable['R']=0x1312;_altTable['R']=0x1300;
    _normalTable['T']=0x1474;_shiftedTable['T']=0x1454;_controlTable['T']=0x1414;_altTable['T']=0x1400;
    _normalTable['Y']=0x1579;_shiftedTable['Y']=0x1559;_controlTable['Y']=0x1519;_altTable['Y']=0x1500;
    _normalTable['U']=0x1675;_shiftedTable['U']=0x1655;_controlTable['U']=0x1615;_altTable['U']=0x1600;
    _normalTable['I']=0x1769;_shiftedTable['I']=0x1749;_controlTable['I']=0x1709;_altTable['I']=0x1700;
    _normalTable['O']=0x186f;_shiftedTable['O']=0x184f;_controlTable['O']=0x180f;_altTable['O']=0x1800;
    _normalTable['P']=0x1970;_shiftedTable['P']=0x1950;_controlTable['P']=0x1910;_altTable['P']=0x1900;

    _normalTable['[']=0x1a5b;_shiftedTable['[']=0x1a7b;_controlTable['[']=0x1a1b;_altTable['[']=0x0000;
    _normalTable['{']=0x1a5b;_shiftedTable['{']=0x1a7b;_controlTable['{']=0x1a1b;_altTable['{']=0x0000;

    _normalTable[']']=0x1b5d;_shiftedTable[']']=0x1b7d;_controlTable[']']=0x1b1d;_altTable[']']=0x0000;
    _normalTable['}']=0x1b5d;_shiftedTable['}']=0x1b7d;_controlTable['}']=0x1b1d;_altTable['}']=0x0000;

    _normalTable['\\']=0x2b5c;_shiftedTable['\\']=0x2b7c;_controlTable['\\']=0x2b1c;_altTable['\\']=0x0000;
    _normalTable['|']=0x2b5c;_shiftedTable['|']=0x2b7c;_controlTable['|']=0x2b1c;_altTable['|']=0x0000;

    _normalTable['A']=0x1e61;_shiftedTable['A']=0xe941;_controlTable['A']=0x1e01;_altTable['A']=0x1e00;
    _normalTable['S']=0x1f73;_shiftedTable['S']=0xf953;_controlTable['S']=0x1f13;_altTable['S']=0x1f00;
    _normalTable['D']=0x2064;_shiftedTable['D']=0x0944;_controlTable['D']=0x2004;_altTable['D']=0x2000;
    _normalTable['F']=0x2166;_shiftedTable['F']=0x1946;_controlTable['F']=0x2106;_altTable['F']=0x2100;
    _normalTable['G']=0x2267;_shiftedTable['G']=0x2947;_controlTable['G']=0x2207;_altTable['G']=0x2200;
    _normalTable['H']=0x2368;_shiftedTable['H']=0x3948;_controlTable['H']=0x2308;_altTable['H']=0x2300;
    _normalTable['J']=0x246a;_shiftedTable['J']=0x494a;_controlTable['J']=0x240a;_altTable['J']=0x2400;
    _normalTable['K']=0x256b;_shiftedTable['K']=0x594b;_controlTable['K']=0x250b;_altTable['K']=0x2500;
    _normalTable['L']=0x266c;_shiftedTable['L']=0x694c;_controlTable['L']=0x260c;_altTable['L']=0x2600;

    _normalTable[';']=0x273b;_shiftedTable[';']=0x793a;_controlTable[';']=0x0000;_altTable[';']=0x0000;
    _normalTable[':']=0x273b;_shiftedTable[':']=0x793a;_controlTable[':']=0x0000;_altTable[':']=0x0000;

    _normalTable['\'']=0x2827;_shiftedTable['\'']=0x2822;_controlTable['\'']=0x0000;_altTable['\'']=0x0000;
    _normalTable['"']=0x2827;_shiftedTable['"']=0x2822;_controlTable['"']=0x0000;_altTable['"']=0x0000;

//    _normalTable2[Qt::Key_Enter&0xff]=0x1c0d;_shiftedTable2[Qt::Key_Enter&0xff]=0x1c0d;
//    _controlTable2[Qt::Key_Enter&0xff]=0x1c0a;_altTable2[Qt::Key_Enter&0xff]=0x0000;
    _normalTable2[Qt::Key_Return&0xff]=0x1c0d;_shiftedTable2[Qt::Key_Return&0xff]=0x1c0d;
    _controlTable2[Qt::Key_Return&0xff]=0x1c0a;_altTable2[Qt::Key_Return&0xff]=0x0000;

    _normalTable['Z']=0x2c7a;_shiftedTable['Z']=0x2c5a;_controlTable['Z']=0x2c1a;_altTable['Z']=0x2c00;
    _normalTable['X']=0x2d78;_shiftedTable['X']=0x2d58;_controlTable['X']=0x2d18;_altTable['X']=0x2d00;
    _normalTable['C']=0x2e63;_shiftedTable['C']=0x2e43;_controlTable['C']=0x2e03;_altTable['C']=0x2e00;
    _normalTable['V']=0x2f76;_shiftedTable['V']=0x2f56;_controlTable['V']=0x2f16;_altTable['V']=0x2f00;
    _normalTable['B']=0x3062;_shiftedTable['B']=0x3042;_controlTable['B']=0x3002;_altTable['B']=0x3000;
    _normalTable['N']=0x316e;_shiftedTable['N']=0x314e;_controlTable['N']=0x310e;_altTable['N']=0x3100;
    _normalTable['M']=0x326d;_shiftedTable['M']=0x324d;_controlTable['M']=0x320d;_altTable['M']=0x3200;

    _normalTable[',']=0x332c;_shiftedTable[',']=0x333c;_controlTable[',']=0x0000;_altTable[',']=0x0000;
    _normalTable['<']=0x332c;_shiftedTable['<']=0x333c;_controlTable['<']=0x0000;_altTable['<']=0x0000;

    _normalTable['.']=0x342e;_shiftedTable['.']=0x343e;_controlTable['.']=0x0000;_altTable['.']=0x0000;
    _normalTable['>']=0x342e;_shiftedTable['>']=0x343e;_controlTable['>']=0x0000;_altTable['>']=0x0000;

    _normalTable['?']=0x352f;_shiftedTable['?']=0x353f;_controlTable['?']=0x0000;_altTable['?']=0x0000;
    _normalTable['/']=0x352f;_shiftedTable['/']=0x353f;_controlTable['/']=0x0000;_altTable['/']=0x0000;

    _normalTable[' ']=0x3920;_shiftedTable[' ']=0x3920;_controlTable[' ']=0x3920;_altTable[' ']=0x3920;

    _normalTable2[Qt::Key_Insert&0xff]=0x5200;_shiftedTable2[Qt::Key_Insert&0xff]=0x5200;
    _controlTable2[Qt::Key_Insert&0xff]=0x0000;_altTable2[Qt::Key_Insert&0xff]=0x0000;

    _normalTable2[Qt::Key_Delete&0xff]=0x5300;_shiftedTable2[Qt::Key_Delete&0xff]=0x5300;
    _controlTable2[Qt::Key_Delete&0xff]=0x0000;_altTable2[Qt::Key_Delete&0xff]=0x0000;

    _normalTable2[Qt::Key_Left&0xff]=0x4b00;_shiftedTable2[Qt::Key_Left&0xff]=0x4b00;
    _controlTable2[Qt::Key_Left&0xff]=0x7300;_altTable2[Qt::Key_Left&0xff]=0x0000;

    _normalTable2[Qt::Key_Home&0xff]=0x4700;_shiftedTable2[Qt::Key_Home&0xff]=0x4700;
    _controlTable2[Qt::Key_Home&0xff]=0x7700;_altTable2[Qt::Key_Home&0xff]=0x0000;

    _normalTable2[Qt::Key_End&0xff]=0x4f00;_shiftedTable2[Qt::Key_End&0xff]=0x4f00;
    _controlTable2[Qt::Key_End&0xff]=0x7500;_altTable2[Qt::Key_End&0xff]=0x0000;

    _normalTable2[Qt::Key_Up&0xff]=0x4800;_shiftedTable2[Qt::Key_Up&0xff]=0x4800;
    _controlTable2[Qt::Key_Up&0xff]=0x0000;_altTable2[Qt::Key_Up&0xff]=0x0000;

    _normalTable2[Qt::Key_Down&0xff]=0x5000;_shiftedTable2[Qt::Key_Down&0xff]=0x5000;
    _controlTable2[Qt::Key_Down&0xff]=0x0000;_altTable2[Qt::Key_Down&0xff]=0x0000;

    _normalTable2[Qt::Key_PageUp&0xff]=0x4900;_shiftedTable2[Qt::Key_PageUp&0xff]=0x4900;
    _controlTable2[Qt::Key_PageUp&0xff]=0x8400;_altTable2[Qt::Key_PageUp&0xff]=0x0000;

    _normalTable2[Qt::Key_PageDown&0xff]=0x5100;_shiftedTable2[Qt::Key_PageDown&0xff]=0x5100;
    _controlTable2[Qt::Key_PageDown&0xff]=0x7600;_altTable2[Qt::Key_PageDown&0xff]=0x0000;

    _normalTable2[Qt::Key_Right&0xff]=0x4d00;_shiftedTable2[Qt::Key_Right&0xff]=0x4d00;
    _controlTable2[Qt::Key_Right&0xff]=0x7400;_altTable2[Qt::Key_Right&0xff]=0x0000;

    _normalTable2[Qt::Key_Escape&0xff]=0x011b;_shiftedTable2[Qt::Key_Escape&0xff]=0x011b;
    _controlTable2[Qt::Key_Escape&0xff]=0x011b;_altTable2[Qt::Key_Escape&0xff]=0x0000;
}

u16 CharacterCode::fromQtKey(int key, Qt::KeyboardModifiers modifiers, bool isPressed)
{
    assert(_normalTable['A']);//assert the translate table is initialized.
    u16 code=0;
    if(key<0x100)
    {
        if(_normalTable[key]==0) goto Error;
        if(modifiers&Qt::ShiftModifier)
        {
            code=_shiftedTable[key];
        }
        else if(modifiers&Qt::ControlModifier)
        {
            code=_controlTable[key];
        }
        else if(modifiers&Qt::AltModifier)
        {
            code=_altTable[key];
        }
        else
        {
            code=_normalTable[key];
        }
    }
    else if(key&0x01000000)
    {
        if(_normalTable2[key&0xff]==0) goto Error;
        if(modifiers&Qt::ShiftModifier)
        {
            code=_shiftedTable2[key&0xff];
        }
        else if(modifiers&Qt::ControlModifier)
        {
            code=_controlTable2[key&0xff];
        }
        else if(modifiers&Qt::AltModifier)
        {
            code=_altTable2[key&0xff];
        }
        else
        {
            code=_normalTable2[key&0xff];
        }
    }
    else
    {
        goto Error;
    }
    if(!isPressed) code|=0x8000;
    return code;
Error:
    cerr<<"Error:Don't know the key "<<hex<<key<<"h"<<endl;
    exit(-1);
}
u16 CharacterCode::_normalTable[256];
u16 CharacterCode::_shiftedTable[256];
u16 CharacterCode::_controlTable[256];
u16 CharacterCode::_altTable[256];

//used for the key>0x100;
u16 CharacterCode::_normalTable2[256];
u16 CharacterCode::_shiftedTable2[256];
u16 CharacterCode::_controlTable2[256];
u16 CharacterCode::_altTable2[256];
