#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{



    ui->setupUi(this);


    QIntValidator* intV = new QIntValidator(0, 100);
    ui->lineEdit->setValidator(intV);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotEditChanged(QString s)
{
    int n;
    n = s.toInt();
    qDebug() << "slotEditChanged ok" << n ;
    emit(mySignalInt(n));
    qDebug() << this->sender();
}

void MainWindow::on_action_About_triggered()
{
    QMessageBox::about(this, "About program", "Qt practice 4\nSmirnov Evgeniy");
}
