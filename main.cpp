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
    Widget x;
    x.show();

    return a.exec();
}
