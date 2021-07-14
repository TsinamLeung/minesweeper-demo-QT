#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "widget_stage.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void setWindowSize(int w, int h) {
        this->setMinimumWidth(w);
        this->setMinimumHeight(h);
		this->resize(0, 0);
	}
	void setState(QString str)
	{
		this->ui->resetButton->setText(str);
	}
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
