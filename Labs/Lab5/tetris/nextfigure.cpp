#include "nextfigure.h"
#include <QDebug>

NextFigure::NextFigure(QWidget *parent) : QWidget(parent)
{
    nextFigure = nullptr;
    qDebug() << "NextFigure obj created";
}

void NextFigure::drawNextFigure(Figure *nextFig)
{
    qDebug() << "NextFigure obj slot drawNextFigure";
    nextFigure = nextFig;
    repaint();
}

void NextFigure::paintEvent(QPaintEvent *event)
{

    if(nextFigure)
    {
        qDebug() << "NextFigure obj paintEvent";

        QPainter painter(this);
        int Xstart = this->width() / 2 - Width/2;

        int delta = 1;
        int i = 0;
        for(int pos = 0; pos < 3; pos++)
        {
            painter.fillRect(Xstart, i * Width + delta, Width - 1*delta, Width - 1*delta, nextFigure->getColor(pos));
            i++;
        }
    }

}
