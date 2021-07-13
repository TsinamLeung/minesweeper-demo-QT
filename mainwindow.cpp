#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget_stage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	// can also initialize the other custom widget here
	connect(ui->stage, SIGNAL(resizeWindow(int,int)), this, SLOT(setWindowSize(int,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

