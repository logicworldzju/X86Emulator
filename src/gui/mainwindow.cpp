#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QKeySequence>
#include <QToolBar>
#include <QTimer>
#include <QStatusBar>
#include <QMessageBox>
#include <QLabel>
#include <time.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <stdio.h>


MainWindow::MainWindow(Memory& memory,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("X86Emulator"));

    numlock=capslock=false;
    powerAction = new QAction(tr("&POWER"),this);
    //powerAction->setShortcut(QKeySequence::Open);
    powerAction->setStatusTip(tr("Power On/Off."));
    resetAction = new QAction(tr("&RESET"), this);
    resetAction->setStatusTip(tr("Reset the machine."));
    capsAction = new QAction(tr("&Caps Lock"), this);
    capsAction->setStatusTip(tr("Click to Caps Lock the keyboard or unlock."));
    numlockAction = new QAction(tr("&Num Lock"), this);
    numlockAction->setStatusTip(tr("Click to Num Lock the keyboard or unlock."));

    QToolBar *toolBar = addToolBar(tr("&Button"));
    toolBar->addAction(powerAction);
    toolBar->addAction(resetAction);
    toolBar->addAction(capsAction);
    toolBar->addAction(numlockAction);

    msgLabel = new QLabel;
    //msgLabel->setMinimumSize(msgLabel->sizeHint());
    msgLabel->setMinimumSize(340,20);
    msgLabel->setAlignment(Qt::AlignLeft);
    statusBar()->addWidget(msgLabel);
    timelabel = new QLabel;
    //timelabel->setMinimumSize(timelabel->sizeHint());
    timelabel->setAlignment(Qt::AlignHCenter);
    statusBar()->addWidget(timelabel);
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    statusBar()->setSizeGripEnabled(false);

    QTimer *my_timer = new QTimer(this);
    connect(my_timer, SIGNAL(timeout()), this, SLOT(showTime()));
    my_timer->start(200);

    connect(powerAction, SIGNAL(triggered()), this, SLOT(start()));
    connect(resetAction, SIGNAL(triggered()), this, SLOT(reset()));
    connect(capsAction, SIGNAL(triggered()), this, SLOT(showStatus1()));
    connect(numlockAction, SIGNAL(triggered()), this, SLOT(showStatus2()));

    ui->centralWidget->setVideoMemoryAddress(memory.getVideoTextMemoryAddress());
}

MainWindow::~MainWindow()
{
    delete ui;
}

ConsoleWidget &MainWindow::getConsoleWidget()
{
    return *(ui->centralWidget);
}

void MainWindow::start()
{
    QMessageBox::information(NULL, tr("Open"), tr("Open a file"));
}

void MainWindow::reset()
{
    QMessageBox::information(NULL, tr("Open"), tr("Open"));
}


void MainWindow::showTime()
{
    tm * t;
    time_t long_time;
    time( &long_time );                //Get time as long integer
    t = localtime( &long_time );
    char ch[10];
    ::sprintf(ch,"%02d:%02d:%02d",t->tm_hour,t->tm_min,t->tm_sec);
    timelabel->setText(QString(ch));
}

void MainWindow::showStatus1()
{
    capslock=!capslock;
    if(capslock&&numlock)
        msgLabel->setText(QString("Caps Locked && Num Locked!"));
    else if(capslock)
        msgLabel->setText(QString("Caps Locked!"));
    else if(numlock)
        msgLabel->setText(QString("Num Locked!"));
    else
        msgLabel->setText(QString(""));
}

void MainWindow::showStatus2()
{
    numlock=!numlock;
    if(capslock&&numlock)
        msgLabel->setText(QString("Caps Locked && Num Locked!"));
    else if(capslock)
        msgLabel->setText(QString("Caps Locked!"));
    else if(numlock)
        msgLabel->setText(QString("Num Locked!"));
    else
        msgLabel->setText(QString(""));
}
