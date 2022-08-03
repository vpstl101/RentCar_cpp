#include "mainwindow.h"
#include <QApplication>
#include "server.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    server server;
    w.show();
    return a.exec();
}
