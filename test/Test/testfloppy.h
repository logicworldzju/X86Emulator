#ifndef TESTFLOPPY_H
#define TESTFLOPPY_H

#include <QObject>
#include <QTest>

class TestFloppy : public QObject
{
    Q_OBJECT
public:
    explicit TestFloppy(QObject *parent = 0);

signals:

private slots:
    void test();
};

#endif // TESTFLOPPY_H
