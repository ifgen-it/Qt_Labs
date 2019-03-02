#ifndef SPIDER_H
#define SPIDER_H

#include <QWidget>

class Spider : public QWidget
{
    Q_OBJECT

private:
    // drawing Web
    bool isDrawing;
    int x0_spider;
    int y0_spider;
    QCursor spiderCursor;
    bool curWentOutOfWindow;
    QString windowTitle;

public:
    Spider(QWidget *parent = nullptr, Qt::WindowFlags f = nullptr);
    ~Spider() override;

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
};

#endif // SPIDER_H
