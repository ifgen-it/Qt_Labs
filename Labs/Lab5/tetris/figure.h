#ifndef FIGURE_H
#define FIGURE_H

#include <QColor>
#include <QPainter>


class Figure
{
public:
    Figure(int width);

    void setNewPosition(int newRow, int newColumn);
    void getCurPosition(int& curRow, int& curColumn);
    void rotateColors(bool down);
    void makeRandomColors();
    void paintFigure(QPainter& painter);
    QColor getColor(int index);



private:
    QColor figureArray[3];
    int m_curRow;
    int m_curColumn;
    int m_Width;

};

#endif // FIGURE_H
