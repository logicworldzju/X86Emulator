#ifndef TESTKEYBOARD_H
#define TESTKEYBOARD_H

#include <QObject>
#include <QTest>

class TestKeyboard : public QObject
{
    Q_OBJECT
public:
    explicit TestKeyboard(QObject *parent = 0);
    
signals:
    
private slots:
    void test();
};

#endif // TESTKEYBOARD_H
