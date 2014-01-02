#ifndef TESTDISKETTE_H
#define TESTDISKETTE_H

#include <QObject>
#include <QTest>

class TestDiskette : public QObject
{
    Q_OBJECT
public:
    explicit TestDiskette(QObject *parent = 0);

signals:

private slots:
    void test();
};

#endif // TESTDISKETTE_H
