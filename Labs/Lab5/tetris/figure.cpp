#include "figure.h"

#include <QDebug>

Figure::Figure(int width)
{
    makeRandomColors();
    m_curRow = 0;
    m_curColumn = 0;
    m_Width = width;

}

void Figure::setNewPosition(int newRow, int newColumn)
{
    m_curRow = newRow;
    m_curColumn = newColumn;
}

void Figure::getCurPosition(int &curRow, int &curColumn)
{
    curRow = m_curRow;
    curColumn = m_curColumn;
}

void Figure::rotateColors(bool down)
{
    QColor temp;
    if(down)
    {
        temp = figureArray[2];
        figureArray[2] = figureArray[1];
        figureArray[1] = figureArray[0];
        figureArray[0] = temp;
    }
    else
    {
        temp = figureArray[0];
        figureArray[0] = figureArray[1];
        figureArray[1] = figureArray[2];
        figureArray[2] = temp;
    }
}

void Figure::makeRandomColors()
{
    QColor arrayColors[] = {Qt::red, Qt::green, Qt::blue, Qt::yellow};

    for(int i = 0; i < 3; i++)
    {
        figureArray[i] = arrayColors[rand()%4];
    }
}

void Figure::paintFigure(QPainter &painter)
{

    int delta = 1;
    int i = m_curRow;
    int j = m_curColumn;
    for(int pos = 0; pos < 3; pos++)
    {
        painter.fillRect(j * m_Width + delta, i * m_Width + delta, m_Width - 1*delta, m_Width - 1*delta, figureArray[pos]);
        i++;
    }

}

QColor Figure::getColor(int index)
{
    if(index < 0 || index > 3) return  Qt::black;
    return figureArray[index];
}

