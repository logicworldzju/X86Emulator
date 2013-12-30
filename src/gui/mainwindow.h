#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "memory/memory.h"
#include "consolewidget.h"

class QAction;
class QLabel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Memory& memory,QWidget *parent = 0);
    ~MainWindow();
    ConsoleWidget& getConsoleWidget();

private slots:
    void start();
    void reset();
    void showTime();
    void showStatus1();
    void showStatus2();

private:
    Ui::MainWindow *ui;
    QAction *powerAction;
    QAction *resetAction;
    QAction *capsAction;
    QAction *numlockAction;
    QLabel  *msgLabel;
    QLabel  *timelabel;
    bool    numlock,capslock;
};

#endif // MAINWINDOW_H
