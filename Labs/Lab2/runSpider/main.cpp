#include "runspider.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RunSpider w;
    w.show();

    return a.exec();
}
