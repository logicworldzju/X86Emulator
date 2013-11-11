#ifndef TESTIOPORTLIST_H
#define TESTIOPORTLIST_H

#include <QObject>



class TestIOPortList : public QObject
{
    Q_OBJECT
public:
    explicit TestIOPortList(QObject *parent = 0);
private slots:
    void testAll();
};

#endif // TESTIOPORTLIST_H
