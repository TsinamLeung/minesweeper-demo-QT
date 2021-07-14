#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
