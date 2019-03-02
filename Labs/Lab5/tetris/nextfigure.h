#ifndef NEXTFIGURE_H
#define NEXTFIGURE_H

#include <QWidget>
#include "figure.h"

class NextFigure : public QWidget
{
    Q_OBJECT
public:
    explicit NextFigure(QWidget *parent = nullptr);

    static const uint Width = 20;

private:
    Figure* nextFigure;

signals:

public slots:

void drawNextFigure(Figure* nextFig);

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // NEXTFIGURE_H
