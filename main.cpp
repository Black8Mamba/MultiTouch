#include "mainwindow.h"
#include <QApplication>
#include "widget.h"
#include <QDebug>
#include <string>
#include <QString>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    Widget x;
    x.show();

   // w.show();

    return a.exec();
}
