#ifndef TESTCONSOLEWIDGET_H
#define TESTCONSOLEWIDGET_H

#include <QObject>
#include <QTest>

class TestConsoleWidget : public QObject
{
    Q_OBJECT
public:
    explicit TestConsoleWidget(QObject *parent = 0);

signals:

private slots:
    void test();
};

#endif // TESTCONSOLEWIDGET_H
