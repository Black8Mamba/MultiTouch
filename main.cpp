#include "mainwindow.h"
#include <QApplication>
#include "widget.h"
#include <QDebug>
#include <string>
#include <QString>
#include <iostream>
#include "device_node_identify.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Widget x(&w);
    w.show();

    return a.exec();
}
