#include "runspider.h"
#include <QPixmap>
#include <QIcon>
#include <QPainter>
#include <QDebug>
#include <QImage>
#include <QKeyEvent>
#include <QBitmap>

RunSpider::RunSpider(QWidget *parent)
    : QWidget(parent)
{
    // Init
    timerStarted = false;
    timerInterval = 1;
    xSpider = 0;
    ySpider = 0;
    xDelta = 3;
    yDelta = 3;
    xLineStart = 0;
    yLineStart = 0;

    marginColor = QColor(100, 100, 100);
    webColor = QColor(110, 110, 110);
    fillColor = QColor(200, 200, 200);

    // Design
    QPalette pal1 = this->palette();
    pal1.setColor(QPalette::Window, marginColor);
    this->setPalette(pal1);

    int wWidth = 640;
    int wHeight = 480;

    this->setWindowTitle("Running spider");
    QIcon icon("Images_lab1\\icon1.ico");
    this->setWindowIcon(icon);
    this->setFixedSize(wWidth, wHeight);

    pixWidth = wWidth - 20;
    pixHeight = wHeight - 20;
    myPix = QPixmap(pixWidth, pixHeight);
    myPix.fill(fillColor);

    mySpider = QPixmap("Images_lab1\\spider1.bmp");
    mySpider.setMask(QBitmap("Images_lab1\\spider1.bmp"));


}

RunSpider::~RunSpider()
{

}

void RunSpider::paintEvent(QPaintEvent *event)
{
   // qDebug() << "was repainted ";

    QPainter painter(this);
    QPen p1 = QPen(QBrush(webColor),2);
    painter.setPen(p1);

    painter.drawPixmap(10, 10, myPix);
    painter.drawPixmap(4 + xSpider, 4 + ySpider, mySpider);

}

void RunSpider::keyPressEvent(QKeyEvent *event)
{
    if(!timerStarted)
    {
        if(event->key() == Qt::Key_Space)
        {
            timerStarted = true;
            myTimer = this->startTimer(timerInterval);
           // qDebug() << "timer started";
        }
    }
    else
    {
        if(event->key() == Qt::Key_Space)
        {
            timerStarted = false;
            this->killTimer(myTimer);
           // qDebug() << "timer killed";
        }
    }
}

void RunSpider::timerEvent(QTimerEvent *event)
{

    QPainter pixPainter(&myPix);
    QPen p1 = QPen(QBrush(webColor),2);
    pixPainter.setPen(p1);


    xSpider += xDelta;
    ySpider += yDelta;
    if(QRect(0, 0, pixWidth, pixHeight).contains(xSpider, ySpider))
    {
        pixPainter.drawLine(xLineStart, yLineStart, xSpider, ySpider);
       // qDebug() << "drawing web";
    }
    else
    {
       // qDebug() << "out of bounds";
        xLineStart = xSpider;
        yLineStart = ySpider;

        if(ySpider > pixHeight)
        {
            yDelta = -yDelta;
        }
        if(xSpider > pixWidth)
        {
            xDelta = -xDelta;
        }
        if(ySpider < 0)
        {
            yDelta = -yDelta;
        }
        if(xSpider < 0)
        {
            xDelta = -xDelta;
        }

        pixPainter.drawLine(xLineStart, yLineStart, xSpider, ySpider);
    }


    repaint();
}
