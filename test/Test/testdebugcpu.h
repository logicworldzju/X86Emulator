#ifndef TESTDEBUGCPU_H
#define TESTDEBUGCPU_H

#include <QObject>
#include <QtTest/QtTest>

class TestDebugCPU : public QObject
{
    Q_OBJECT
public:
    explicit TestDebugCPU(QObject *parent = 0);

signals:

private slots:
    void test();
};

#endif // TESTDEBUGCPU_H
