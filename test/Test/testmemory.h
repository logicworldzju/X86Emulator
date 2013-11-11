#ifndef TESTMEMORY_H
#define TESTMEMORY_H

#include <QObject>
#include <QtTest/QTest>
#include "memory/debugmemory.h"
class TestMemory : public QObject
{
    Q_OBJECT
public:
    explicit TestMemory(QObject *parent = 0);
private slots:
    void testGetSet();
    void testStaticstic();
};

#endif // TESTMEMORY_H
