#ifndef RUNSPIDER_H
#define RUNSPIDER_H

#include <QWidget>

class RunSpider : public QWidget
{
    Q_OBJECT
private:
    QPixmap myPix;
    QPixmap mySpider;
    QImage myImage;
    QColor webColor, fillColor, marginColor;

    int myTimer;
    bool timerStarted;
    int timerInterval;

    int xSpider, ySpider, xDelta, yDelta, xLineStart, yLineStart;
    int pixWidth, pixHeight;


public:
    RunSpider(QWidget *parent = 0);
    ~RunSpider();

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;

    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;
};

#endif // RUNSPIDER_H
