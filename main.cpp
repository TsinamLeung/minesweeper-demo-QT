#include "mainwindow.h"
#include "model_game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
	Board b;
	b.CreateBoard(3,3,9,1,1);
    w.show();
    return a.exec();
}
