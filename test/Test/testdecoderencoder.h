#ifndef TESTDECODERENCODER_H
#define TESTDECODERENCODER_H

#include <QObject>

class TestDecoderEncoder : public QObject
{
    Q_OBJECT
public:
    explicit TestDecoderEncoder(QObject *parent = 0);
private slots:
    void testAll();
};

#endif // TESTDECODERENCODER_H
