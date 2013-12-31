#ifndef TESTVIDEO_H
#define TESTVIDEO_H
#include <QObject>
#include <QTest>

class TestVideo : public QObject
{
    Q_OBJECT
public:
    explicit TestVideo(QObject *parent = 0);

signals:

private slots:
    void test();
};


#endif // TESTVIDEO_H
