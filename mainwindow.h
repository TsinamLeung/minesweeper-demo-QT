#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "widget_stage.h"
#include <QDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
signals:
	void setMap(int, int, int);
public slots:
	void setWindowSize(int w, int h)
	{
		this->setMinimumWidth(w);
		this->setMinimumHeight(h);
		this->resize(0, 0);
	}
	void setState(QString str)
	{
		this->ui->resetButton->setText(str);
	}
	void difficultDialog();
private:
	Ui::MainWindow *ui;
};

class DifficultDialog : public QDialog
{
	Q_OBJECT
public:
	explicit DifficultDialog(QWidget *parent = nullptr);
	static void GetCustomDiffcult(QWidget* parent, int& row, int& col, int& num_mine, bool *ok = nullptr);
private:
	QList<QLineEdit*> fields;
};
#endif // MAINWINDOW_H
