#include "spider.h"
#include <QApplication>
#include <QDebug>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "hello";

    QTranslator translator;
    // SIMPLE METHOD
    //translator.load("spider_ru.qm", ".");
    //QApplication::installTranslator(&translator);

    QString fileSpec = QString("spider_");
    fileSpec += QLocale::system().name();
    translator.load(fileSpec, ".");
    QApplication::installTranslator(&translator);

    // translator for dialogs
    QString directory = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    QTranslator translatorDialogs;
    translatorDialogs.load("qt_" + QLocale::system().name()  ,directory);
    QApplication::installTranslator(&translatorDialogs);

    Spider w(0, Qt::CustomizeWindowHint);
    w.show();

   // Qt::WindowFlags type1 = w.windowType();
   // qDebug() << type1;



    return a.exec();
}
