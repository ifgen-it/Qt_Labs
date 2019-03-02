#include "salary.h"
#include <QPushButton>
#include <QFont>
#include <QStyle>
#include <QDebug>
#include <qobjectdefs.h>
#include <QMessageBox>
#include <QEvent>

Salary::Salary(QWidget *parent)
    : QWidget(parent)
{

    // Init
    btnYes = new QPushButton("Yes", this);
    btnYes->move(160, 215);
    btnWidth = 90;
    btnHeight = 40;
    btnYes->setFixedSize(btnWidth, btnHeight);
    QFont fontBtn = QFont("Times", 14);
    btnYes->setFont(fontBtn);
    btnYes->setStyleSheet("color:green");


    btnNo = new QPushButton("No", this);
    btnNoX = 400;
    btnNoY = 215;
    deltaX = 1;
    deltaY = 1;
    counter = 1;
    btnNo->move(btnNoX, btnNoY);
    btnNo->setFixedSize(btnWidth, btnHeight);
    btnNo->setFont(fontBtn);
    btnNo->setStyleSheet("color:red");


    rand = QRandomGenerator();



    // Design
    QPalette pal1 = this->palette();
    pal1.setColor(QPalette::Window, Qt::gray);
    this->setPalette(pal1);

    wWidth = 640;
    wHeight = 480;

    this->setWindowTitle("Is your salary arranged?");
    this->setFixedSize(wWidth, wHeight);




    // connect Signal - Slot

    QObject::connect(btnYes, SIGNAL(clicked(bool)), this, SLOT(yesOnClicked(bool)));


    btnNo->installEventFilter(this);
}


void Salary::yesOnClicked(bool checked)
{
    qDebug() << "was clicked Yes" << "checked:" << checked;
    QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("Message");
    msg->setText("We thought so");
    //msg->setFixedSize(800, 400);

    msg->show();

}

void Salary::noOnClicked(bool checked)
{
    qDebug() << "was clicked No" << "checked:" << checked;
    QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("Message");
    msg->setText("You Win!!!");
    //msg->setFixedSize(800, 400);

    msg->show();
}

bool Salary::eventFilter(QObject *watched, QEvent *event)
{

    if(watched == btnNo)
    {
        if(event->type() == QEvent::Enter)
        {
            qDebug() << "btnNo hovered" << counter;
            removeBtnNo();
            counter++;

            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        QWidget::eventFilter(watched, event);
    }

}

void Salary::removeBtnNo()
{
    bool goodRemove = false;
    int newBtnNoX, newBtnNoY;

    while(true)
    {
        newBtnNoX = btnNoX;
        newBtnNoY = btnNoY;

        int gen = abs(static_cast<int>(rand.generate()));
        int dir = 1 + gen % 4;
        qDebug() << dir;
        switch (dir)
        {
            case 1:
                newBtnNoY = btnNoY - btnHeight;
                break;
            case 2:
                newBtnNoY = btnNoY + btnHeight;
                break;
            case 3:
                newBtnNoX = btnNoX - btnWidth;
                break;
            case 4:
                newBtnNoX = btnNoX + btnWidth;
                break;
        }

        if(newBtnNoY < 0 || newBtnNoY + btnHeight > wHeight ||
                newBtnNoX < 0 || newBtnNoX + btnWidth > wWidth)
        {
            goodRemove = false;
            qDebug() << "goodRemove = " << goodRemove;
        }
        else
        {
            goodRemove = true;
            qDebug() << "goodRemove = " << goodRemove;
            btnNoX = newBtnNoX;
            btnNoY = newBtnNoY;
        }

        if(goodRemove)
        {
            btnNo->move(btnNoX, btnNoY);

            repaint();
            break;
        }
     }

}

Salary::~Salary()
{

}
