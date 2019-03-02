#include "glass.h"
#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>


void Glass::makeCollapseRow(int row, int startIndex, int endIndex)
{
    qDebug() << "Collapse : startInd = " << startIndex << ", endIndex = " << endIndex;

    for(int j = startIndex; j <= endIndex; j++)
    {
        for(int i = row; i > 0 ; i--)
        {
            glassArray[i][j] = glassArray[i-1][j];
        }
    }
}

void Glass::makeCollapseCol(int col, int startIndex, int endIndex)
{
    for(int i = startIndex; i <= endIndex; i++)
    {
        glassArray[i][col] = emptyCell;
    }
    int source = startIndex - 1;
    int dest = endIndex;
    for(int i = source; i >= 0; i--)
    {
        glassArray[dest][col] = glassArray[source][col];
        glassArray[source][col] = emptyCell;
        dest--;
        source--;
    }


}

void Glass::acceptColors(int row, int column)
{
    // add figure in the glass

    for(int i = 0; i < 3; i++)
    {
        glassArray[row + i][column] = curFigure->getColor(i);
    }

    // analyze the glass
    while (true)
    {
        wasCollapsed = false;
        checkGlass();
        if(wasCollapsed == false) break;
    }


    Figure* temp = curFigure;
    curFigure = nextFigure;
    nextFigure = temp;

    curFigure->setNewPosition(0, m_columns/2);
    nextFigure->makeRandomColors();
    nextFigure->setNewPosition(0, 0);

    emit setScore(score);
    emit drawPattern(nextFigure);

    // check for available path for new figure
    if(checkAvailablePath() == false)
    {
        int curRow, curCol;
        curFigure->getCurPosition(curRow, curCol);
        for(int i = 0; i < 3; i++)
        {
            glassArray[curRow + i][curCol] = curFigure->getColor(i);
        }
        repaint();
        this->killTimer(idTimer);
        gameOn = false;
        QMessageBox::about(this, "Info", "Game Over!");
    }
}

void Glass::checkGlass()
{
    for(int i = 0; i < m_rows; i++)
    {
        int startIndex = 0, endIndex = 0;
        if(findSequence(true, i, startIndex, endIndex) == true)
        {
            qDebug() << "wanna Collapse : startInd = " << startIndex << ", endIndex = " << endIndex;
            makeCollapseRow(i, startIndex, endIndex);
            wasCollapsed = true;
        }


    }
    for(int j = 0; j < m_columns; j++)
    {
        int startIndex = 0, endIndex = 0;
        if(findSequence(false, j, startIndex, endIndex) == true)
        {
            qDebug() << "wanna Collapse column : startInd = " << startIndex << ", endIndex = " << endIndex;
            makeCollapseCol(j, startIndex, endIndex);
            wasCollapsed = true;
        }
    }
}

bool Glass::findSequence(bool row, int index, int& startIndex, int& endIndex)
{

    if(row) // find seq in row
    {
        bool seqFound = false;
        int counter = 1;
        int startInd = 0;
        int curInd = 1;
        while(curInd < m_columns)
        {
            if(glassArray[index][startInd]==emptyCell || glassArray[index][curInd] != glassArray[index][startInd])
            {
                if(seqFound) break;
                counter = 1;
                startInd = curInd;
                curInd++;
            }
            else
            {
                curInd++;
                counter++;
                if(counter >= 3) seqFound = true;
            }

        }

        if(seqFound)
        {
            startIndex = startInd;
            endIndex = curInd - 1;
            score += counter;
            qDebug() << "Find seq : startInd = " << startInd << ", endIndex = " << endIndex;
            return true;
        }
        else
        {
            return false;
        }

    }
    else    // find seq in column
    {

        bool seqFound = false;
        int counter = 1;
        int startInd = 0;
        int curInd = 1;
        while(curInd < m_rows)
        {
            if(glassArray[startInd][index]==emptyCell || glassArray[curInd][index] != glassArray[startInd][index])
            {
                if(seqFound) break;
                counter = 1;
                startInd = curInd;
                curInd++;
            }
            else
            {
                curInd++;
                counter++;
                if(counter >= 3) seqFound = true;
            }

        }

        if(seqFound)
        {
            startIndex = startInd;
            endIndex = curInd - 1;
            score += counter;
            qDebug() << "Find column seq : startInd = " << startInd << ", endIndex = " << endIndex;
            return true;
        }
        else
        {
            return false;
        }

    }
}

bool Glass::checkEmptyNeighbour(int row, int col)
{
    for(int i = row; i < row + 3; i++)
    {
        if(glassArray[i][col] != emptyCell) return  false;
    }
    return  true;
}

bool Glass::checkAvailablePath()
{
    int curRow, curCol;
    curFigure->getCurPosition(curRow, curCol);
    for(int i = curRow; i < curRow + 3; i++)
    {
        if(glassArray[i][curCol] != emptyCell) return false;
    }
    return true;
}

Glass::Glass(QWidget *parent) : QWidget(parent)
{

    wasCollapsed = false;
    gameOn = false;
    score = 0;
    timerInterval = 1000;
    glassArray = QVector<QVector<QColor>>();


    QMetaObject::Connection con1 = QObject::connect(this, SIGNAL(signalGlassInit()), this, SLOT(slotGlassInit()), Qt::QueuedConnection);
    if(con1) qDebug() << "con1 connected";
    else qDebug() << "con1 not connected";

    emit signalGlassInit();
    qDebug() << "signalGlassInit emitted";

    curFigure = new Figure(Width);
    nextFigure = new Figure(Width);




}

void Glass::clearGlass()
{
    for(int i = 0; i < glassArray.length(); i++)
    {
        for(int j = 0; j < glassArray[i].length(); j++)
        {
            glassArray[i][j] = emptyCell;
        }
    }

    score = 0;


}

void Glass::slotGlassInit()
{
    qDebug() << "slot GlassInit recieved";
    glassArray.resize(static_cast<int>(m_rows));
    for(int i = 0; i < glassArray.length(); i++)
    {
        glassArray[i] = QVector<QColor>(static_cast<int>(m_columns), emptyCell);
    }

    // glass size
    glassSize = QSize(m_columns * Width, m_rows * Width);
    this->setFixedSize(glassSize);

    qDebug() << m_rows << m_columns;
}

void Glass::slotNewGame()
{
    qDebug() << "New game started";
    if(gameOn)this->killTimer(idTimer);

    gameOn = true;
    score = 0;
    emit setScore(score);
    clearGlass();

    curFigure->setNewPosition(0, m_columns/2);

    idTimer = this->startTimer(timerInterval);
    emit drawPattern(nextFigure);

    this->setFocus();
    repaint();

}

void Glass::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int delta = 1;
    for(uint i = 0; i < m_rows; i++)
    {
        for(uint j = 0; j < m_columns; j++)
        {
            painter.fillRect(j * Width + delta, i * Width + delta, Width - 1*delta, Width - 1*delta, glassArray[i][j]);
        }
    }

    if(gameOn)
    {
        curFigure->paintFigure(painter);
    }
}

Glass::~Glass()
{
    delete curFigure;
    delete nextFigure;
}

void Glass::keyPressEvent(QKeyEvent *event)
{
    if(gameOn)
    {
        int curRow = 0, curCol = 0;
        int finder = 0;

        switch (event->key())
        {
        case Qt::Key_Left:
            curFigure->getCurPosition(curRow, curCol);
            if(curCol > 0)
            {
                if(checkEmptyNeighbour(curRow, curCol-1) == true)
                {
                    curFigure->setNewPosition(curRow, curCol-1);
                    repaint();
                }
            }
            break;

        case Qt::Key_Right:
            curFigure->getCurPosition(curRow, curCol);
            if(curCol < m_columns-1)
            {
                if(checkEmptyNeighbour(curRow, curCol+1) == true)
                {
                    curFigure->setNewPosition(curRow, curCol+1);
                    repaint();
                }
            }
            break;

        case Qt::Key_Down:
            curFigure->rotateColors(true);
            repaint();
            break;

        case Qt::Key_Up:
            curFigure->rotateColors(false);
            repaint();
            break;

        case Qt::Key_Space:
            curFigure->getCurPosition(curRow, curCol);

            // looking for row where can drop the figure

            finder = curRow + 3;
            for( ; finder < m_rows; finder++)
            {
               if(glassArray[finder][curCol] != emptyCell) break;
            }

            // found
            acceptColors(finder - 3, curCol);
            repaint();
            break;

        default:
            QWidget::keyPressEvent(event);
            break;
        }
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
}

void Glass::timerEvent(QTimerEvent *event)
{
    int curRow = 0, curCol = 0;

    curFigure->getCurPosition(curRow, curCol);


    int finder = curRow + 3;

    if(finder < m_rows && glassArray[finder][curCol] == emptyCell)
    {
        curFigure->setNewPosition(curRow + 1, curCol);
    }
    else
    {
        acceptColors(finder - 3, curCol);
    }
    repaint();

}
