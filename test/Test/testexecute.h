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
    void testPOP();
    void testPUSH();
    void testOR();
    void testAND();
    void testXOR();
    void testADC();
    void testSBB();
    void testSUB();
    void testCMP();
    void testINC();
    void testDEC();
    void testNOT();
    void testNEG();
    /*
        EXECUTE_FUNC(executeROL);
        EXECUTE_FUNC(executeROR);
        EXECUTE_FUNC(executeRCL);
        EXECUTE_FUNC(executeRCR);
        EXECUTE_FUNC(executeSHR);
        EXECUTE_FUNC(executeSHL_SAL);
        EXECUTE_FUNC(executeSAR);
    */
    void testROL();
    void testROR();
    void testRCL();
    void testRCR();
    void testSHR();
    void testSHL_SAL();
    void testSAR();
    /*
    EXECUTE_FUNC(executeJO);
    EXECUTE_FUNC(executeJNO);
    EXECUTE_FUNC(executeJB);
    EXECUTE_FUNC(executeJNB);
    EXECUTE_FUNC(executeJZ);
    EXECUTE_FUNC(executeJNZ);
    EXECUTE_FUNC(executeJBE);
    EXECUTE_FUNC(executeJNBE);
    EXECUTE_FUNC(executeJS);
    EXECUTE_FUNC(executeJNS);
    EXECUTE_FUNC(executeJP);
    EXECUTE_FUNC(executeJNP);
    EXECUTE_FUNC(executeJL);
    EXECUTE_FUNC(executeJNL);
    EXECUTE_FUNC(executeJLE);
    EXECUTE_FUNC(executeJNLE);
    */
    void testJx();
    void testJRCXZ();
    void testLOOP();
    void testIN();
    void testOUT();
    void testIMUL3();
    void testIMUL1();
    void testMUL();
    void testIDIV();
    void testDIV();
    void testXCHG();
    void testMove();
    void testLEA();
    void testCBW();
    void testCWD();
    void testSAHF();
    void testLAHF();
private:
    void fillRegisterFile(RegisterFile& registerFile);
};

#endif // TESTEXECUTE_H
