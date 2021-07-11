#include "mainwindow.h"
#include "model_game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Board b;
    b.CreateBoard(10,10,10,2,2);
    w.show();
    return a.exec();
}
