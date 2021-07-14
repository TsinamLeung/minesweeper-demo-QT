#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	// can also initialize the other custom widget here
	connect(ui->stage, SIGNAL(resizeWindow(int,int)), this, SLOT(setWindowSize(int,int)));
	connect(ui->stage, SIGNAL(changeState(QString)), this, SLOT(setState(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

