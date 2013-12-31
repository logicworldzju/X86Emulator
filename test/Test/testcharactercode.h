#ifndef TESTCHARACTERCODE_H
#define TESTCHARACTERCODE_H

#include <QObject>
#include <QtTest/QtTest>

class TestCharacterCode : public QObject
{
    Q_OBJECT
public:
    explicit TestCharacterCode(QObject *parent = 0);

signals:

private slots:
    void test();
};

#endif // TESTCHARACTERCODE_H
