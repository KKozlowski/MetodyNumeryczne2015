#include "mainwindow.h"
#include "plot.h"
#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //Plot p;
    Controller c;

    //p.show();
    //w.show();
    c.show();

    return a.exec();
}
