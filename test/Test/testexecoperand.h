#ifndef TESTEXECOPERAND_H
#define TESTEXECOPERAND_H

#include <QObject>

class TestExecOperand : public QObject
{
    Q_OBJECT
public:
    explicit TestExecOperand(QObject *parent = 0);
private slots:
    void testExecOperandImmediate();
    void testExecOperandGPR();
    void testExecOperandCR();
    void testExecOperandMemory();

};

#endif // TESTEXECOPERAND_H
