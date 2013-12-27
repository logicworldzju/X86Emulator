#ifndef TESTBIOS_H
#define TESTBIOS_H

#include <QObject>
#include <QtTest/QtTest>

class TestBIOS : public QObject
{
    Q_OBJECT
public:
    explicit TestBIOS(QObject *parent = 0);

signals:

private slots:
    void test();
};

#endif // TESTBIOS_H
