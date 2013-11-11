#ifndef TESTINSTRUCTIONSTREAM_H
#define TESTINSTRUCTIONSTREAM_H

#include <QObject>

class TestInstructionStream : public QObject
{
    Q_OBJECT
public:
    explicit TestInstructionStream(QObject *parent = 0);
private slots:
    void testStreamFromFile();
    void testStreamFromMemory();
};

#endif // TESTINSTRUCTIONSTREAM_H
