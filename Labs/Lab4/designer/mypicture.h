#ifndef MYPICTURE_H
#define MYPICTURE_H

#include <QWidget>
#include <QPixmap>

class MyPicture : public QWidget
{
    Q_OBJECT
public:
    explicit MyPicture(QWidget *parent = nullptr);

    QPixmap pixmap;

    QPixmap tmpPix;

    double scale;
    QRect dimensPict;

signals:

public slots:

    void scaleChanged(int sc);


    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // MYPICTURE_H
