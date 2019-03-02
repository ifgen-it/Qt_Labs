#include "rect.h"
#include <QPalette>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>

Rect::Rect(QWidget *parent)
    : QWidget(parent)
{
    // Init
    startDrawingRect = false;
    canDraw = false;
    x0 = y0 = x1 = y1 = 0;
    rectList = QList<QRect>();


    // Design
    QPalette pal1 = this->palette();
    pal1.setColor(QPalette::Window, QColor(33,33,33));
    this->setPalette(pal1);





}

Rect::~Rect()
{

}

void Rect::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        startDrawingRect = true;
        canDraw = true;
        x0 = event->pos().x();
        y0 = event->pos().y();
        x1 = x0 + 1;
        y1 = y0 + 1;
        repaint();


    }
    else {
        QWidget::mousePressEvent(event);
    }
}

void Rect::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        startDrawingRect = false;

        int xLeft = x0 < x1 ? x0 : x1;
        xLeft = xLeft < 0 ? 1 : xLeft;

        int xRight = x0 > x1 ? x0 : x1;
        xRight = xRight > this->rect().width() ? this->rect().width() - 1 : xRight;

        int yTop = y0 < y1 ? y0 : y1;
        yTop = yTop < 0 ? 1 : yTop;

        int yBottom = y0 > y1 ? y0 : y1;
        yBottom = yBottom > this->rect().height() ? this->rect().height() - 1 : yBottom;

        QRect tempRect(xLeft, yTop, xRight - xLeft, yBottom - yTop);
        rectList.push_back(tempRect);

        x0 = y0 = x1 = y1 = 0;
    }
}

void Rect::mouseMoveEvent(QMouseEvent *event)
{
    if(startDrawingRect)
    {
        x1 = event->pos().x();
        y1 = event->pos().y();
        repaint();
    }
}

void Rect::paintEvent(QPaintEvent *event)
{

    if(canDraw)
    {
        qDebug() << "was repainted ";


        QPainter painter(this);
        QPen p1 = QPen(QBrush(Qt::green),2);
        painter.setPen(p1);

        // draw rectList
        QList<QRect>::iterator itb = rectList.begin(), ite = rectList.end();
        while (itb != ite) {

            painter.drawRect(*itb);
            ++itb;
        }


        // draw current drawing rect
        painter.drawRect(x0, y0, x1 - x0, y1 - y0);




    }
}
