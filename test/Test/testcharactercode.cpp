#include "testcharactercode.h"
#include "gui/charactercode.h"
TestCharacterCode::TestCharacterCode(QObject *parent) :
    QObject(parent)
{
}

void TestCharacterCode::test()
{
    CharacterCode::initTranslateTable();

    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_1,Qt::NoModifier,true),u16(0x0231));
    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_1,Qt::ShiftModifier,true),u16(0x0221));
    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_1,Qt::ControlModifier,true),u16(0x0000));
    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_1,Qt::AltModifier,true),u16(0x7800));

    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_1,Qt::NoModifier,false),u16(0x8231));
    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_1,Qt::ShiftModifier,false),u16(0x8221));
    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_1,Qt::ControlModifier,false),u16(0x8000));
    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_1,Qt::AltModifier,false),u16(0xf800));

    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_Backspace,Qt::NoModifier,true),u16(0x0e08));
    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_Backspace,Qt::ShiftModifier,true),u16(0x0e08));
    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_Backspace,Qt::ControlModifier,true),u16(0x0e7f));
    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_Backspace,Qt::AltModifier,true),u16(0x0000));

    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_Backspace,Qt::NoModifier,false),u16(0x8e08));
    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_Backspace,Qt::ShiftModifier,false),u16(0x8e08));
    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_Backspace,Qt::ControlModifier,false),u16(0x8e7f));
    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_Backspace,Qt::AltModifier,false),u16(0x8000));

    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_Exclam,Qt::NoModifier,true),u16(0x0231));
    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_Exclam,Qt::ShiftModifier,true),u16(0x0221));
    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_Exclam,Qt::ControlModifier,true),u16(0x0000));
    QCOMPARE(CharacterCode::fromQtKey((int)Qt::Key_Exclam,Qt::AltModifier,true),u16(0x7800));
}
