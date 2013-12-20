#ifndef TESTEXECUTE_H
#define TESTEXECUTE_H

#include <QObject>
#include "cpu/executer/execute.h"
#include "memory/debugmemory.h"
#include <QtTest/QtTest>

class TestExecute : public QObject
{
    Q_OBJECT
public:
    explicit TestExecute(QObject *parent = 0);

signals:

private slots:
    void testADD();
private:
    void fillRegisterFile(RegisterFile& registerFile);
};

#endif // TESTEXECUTE_H
