#include "salary.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Salary w;
    w.show();

    return a.exec();
}
