#ifndef RECT_H
#define RECT_H

#include <QWidget>
#include <QList>

class Rect : public QWidget
{
    Q_OBJECT

private:
    bool startDrawingRect, canDraw;
    int x0, y0, x1, y1;
    QList<QRect> rectList;

public:
    Rect(QWidget *parent = 0);
    ~Rect();

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // RECT_H
