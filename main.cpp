#include "mainwindow.hpp"

#include <QApplication>
#include <QLocalSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.refreshDisplays();
    return a.exec();
}
