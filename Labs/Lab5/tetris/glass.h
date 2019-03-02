#ifndef GLASS_H
#define GLASS_H

#define emptyCell QColor(150,150,150) //серый цвет

#include <QWidget>
#include "figure.h"

class Glass : public QWidget
{
    Q_OBJECT

private:


    int timerInterval;
    bool gameOn;
    uint score;
    QVector<QVector<QColor>> glassArray;
    QSize glassSize;

    uint m_rows;
    uint m_columns;


    Figure* curFigure;
    Figure* nextFigure;

    int idTimer;

    bool wasCollapsed;

    void makeCollapseRow(int row, int startIndex, int endIndex);
    void makeCollapseCol(int col, int startIndex, int endIndex);

    void acceptColors(int row, int column);
    void checkGlass();
    bool findSequence(bool row, int index, int& startIndex, int& endIndex);
    bool checkEmptyNeighbour(int row, int col);

    bool checkAvailablePath();

public:
    static const uint Width = 20;       // size of square

    Q_PROPERTY(uint rows READ rows WRITE setRows)
    Q_PROPERTY(uint columns READ columns WRITE setColumns)

    explicit Glass(QWidget *parent = nullptr);

    uint rows() const
    {
        return m_rows;
    }

    uint columns() const
    {
        return m_columns;
    }

    void clearGlass();


signals:

    void signalGlassInit();
    void drawPattern(Figure* nextFig);
    void setScore(int);


public slots:

    void slotGlassInit();

    void setRows(uint rows)
    {
        m_rows = rows;
    }
    void setColumns(uint columns)
    {
        m_columns = columns;
    }

    void slotNewGame();

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;

    ~Glass() override;

    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;
};

#endif // GLASS_H
