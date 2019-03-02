#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mainWindow w(&a, nullptr);

    w.show();
    //a.setStyle(QStyleFactory::create("Fusion"));


    return a.exec();
}
