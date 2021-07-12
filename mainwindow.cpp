#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget_stage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	// can also initialize the other custom widget here

}

MainWindow::~MainWindow()
{
    delete ui;
}

