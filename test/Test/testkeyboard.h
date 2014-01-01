#ifndef TESTKEYBOARD_H
#define TESTKEYBOARD_H

#include <QObject>
#include <QTest>

class testkeyboard : public QObject
{
    Q_OBJECT
public:
    explicit testkeyboard(QObject *parent = 0);
    
signals:
    
private slots:
    void test();
};

#endif // TESTKEYBOARD_H
