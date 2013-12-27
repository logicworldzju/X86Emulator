#ifndef TESTINSTRUCTIONDECODER_H
#define TESTINSTRUCTIONDECODER_H

#include <QObject>
#include <QtTest/QtTest>

class TestInstructionExecuter : public QObject
{
    Q_OBJECT
public:
    explicit TestInstructionExecuter(QObject *parent = 0);

signals:

private slots:
    void testAll();
    void testAll2();
};

#endif // TESTINSTRUCTIONDECODER_H
