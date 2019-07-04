#include "mainwindow.h"
#include <QApplication>
#include"board.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(1000, 1000);
    QSound *dial;
    dial = new QSound(":/Bgm/info.wav");
    dial->setLoops(-1);
    dial ->play();
    w.show();
    return a.exec();
}
