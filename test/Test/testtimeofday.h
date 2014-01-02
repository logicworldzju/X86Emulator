#ifndef TESTTIMEOFDAY_H
#define TESTTIMEOFDAY_H

#include <QObject>
#include <QTest>

class TestTimeOfDay : public QObject
{
    Q_OBJECT
public:
    explicit TestTimeOfDay(QObject *parent = 0);

signals:

private slots:
    void test();
};

#endif // TESTTIMEOFDAY_H
