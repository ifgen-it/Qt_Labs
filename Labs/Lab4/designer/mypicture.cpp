#include "mypicture.h"
#include <QPainter>
#include <QDebug>

MyPicture::MyPicture(QWidget *parent) : QWidget(parent)
{

    qDebug() << "MyPicture created";

    pixmap.load(":/MyImages/Images/WomenAndDog.jpg");

    //dimensPict = pixmap.rect();
    dimensPict = QRect(0, 0, 800, 566);

    scale = 50;



}

void MyPicture::scaleChanged(int sc)
{
    qDebug() << "scaleChanged ok" << sc ;
    scale = sc;
    this->repaint();
}

void MyPicture::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    tmpPix = pixmap.scaled(pixmap.width() * scale / 100, pixmap.height() * scale / 100);

   // painter.drawPixmap(0, 0, pixmap);
    painter.drawPixmap(0, 0, tmpPix);



}
