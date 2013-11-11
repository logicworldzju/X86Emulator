#ifndef TESTREGISTERFILE_H
#define TESTREGISTERFILE_H

#include <QObject>

class TestRegisterFile : public QObject
{
    Q_OBJECT
public:
    explicit TestRegisterFile(QObject *parent = 0);
private slots:
    void testGPR();
    void testSR();
    void testFlag();
    void testIP();

};

#endif // TESTREGISTERFILE_H
