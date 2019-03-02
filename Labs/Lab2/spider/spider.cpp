#include "spider.h"
#include <QDebug>
#include <QIcon>
#include <QPalette>
#include <QBrush>
#include <QApplication>
#include <QDesktopWidget>
#include <QBitmap>
#include <QColorDialog>
#include <QFileDialog>
#include <QObject>
#include <QMouseEvent>
#include <QToolTip>
#include <QPainter>

Spider::Spider(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent)
{

    // LAB2 begin
    isDrawing = false;
    x0_spider = 0;
    y0_spider = 0;
    curWentOutOfWindow = false;


    // LAB2 end


    //Qt::WindowFlags type1 = windowFlags() & Qt::WindowType_Mask;
    //qDebug() << type1;

    this->setWindowFlags(f);

    Qt::WindowFlags f1 =
          //  Qt::WindowStaysOnTopHint ;
          Qt::WindowMinimizeButtonHint
              |  Qt::WindowMaximizeButtonHint
            | Qt::WindowCloseButtonHint;



    this->setWindowFlags(f1);

    qDebug() << windowType();

    Qt::WindowState st = Qt::WindowActive;
            //Qt::WindowFullScreen;
    this->setWindowState(st);

    Qt::WindowStates state = this->windowState();
    qDebug() <<state;

    windowTitle = QString(QObject::tr("Spider"));

    this->setWindowTitle(windowTitle);

    QIcon icon("Images_lab1\\icon1.ico");
    this->setWindowIcon(icon);

    QPalette palet1 = this->palette();

    palet1.setColor(QPalette::Active,
                    QPalette::Window,
                    QColor(111,119,119));



    palet1.setColor(QPalette::Inactive,
                    QPalette::Window,
                    Qt::green);



    QPixmap pix("Images_lab1\\WomanAndDog.jpg");
    QBrush brush1 = QBrush(pix);
    palet1.setBrush(QPalette::Inactive, QPalette::Window,brush1);

    this->setPalette(palet1);
    setWindowOpacity(0.9);

    QPoint p1 = this->pos();
    qDebug() << p1;
    QRect r1 = this->frameGeometry();
    qDebug() << this->rect();

    setGeometry(50, 50, 500, 500);
    setMinimumSize(100, 100);
    //setMaximumSize(800, 800);

    QDesktopWidget* pDeskTop = QApplication::desktop();
    QRect deskTopRect = pDeskTop->screenGeometry();

    setMaximumSize(deskTopRect.width(),deskTopRect.height());

    // quater
    resize(deskTopRect.width()/2,deskTopRect.height()/2);
   // move(deskTopRect.width()/2,deskTopRect.height()/2);
    move(deskTopRect.width()/4,deskTopRect.height()/4);

      //setFixedSize(pix.size());
    resize(pix.size());

      QCursor curs1 = Qt::CrossCursor;

     // this->setCursor(curs1);

      QBitmap bmp("Images_lab1\\super_spy.bmp");
      QCursor curs2(bmp, bmp);
      this->setCursor(curs2);
      this->unsetCursor();

      QString spiderCursorPath = "Images_lab1\\super_spy.bmp";  // "Images_lab1\\spider1.bmp";
      QPixmap pix1(spiderCursorPath);
      pix1.setMask(QBitmap(spiderCursorPath));
      QCursor curs3(pix1);
      spiderCursor = curs3;
      //this->setCursor(curs3);

      // DIALOGS

      //COLOR

//      QColor selColor1 = QColorDialog::getColor();
//      QPalette  palette4 = this->palette();

//      if(selColor1.isValid())
//      {
//          palette4.setColor(QPalette::Active, QPalette::Window, selColor1);
//          this->setPalette(palette4);
//      }


      //PHOTO

//      QString fNamePix =  QFileDialog::getOpenFileName(0, tr("Open picture dialog"), ".", "*.jpg *.jpeg *.png *.bmp *.gif *.tiff");

//      if(!fNamePix.isEmpty())
//      {
//          QPixmap selPix1(fNamePix);
//          QBrush selBrush1 = QBrush(selPix1);
//          palette4.setBrush(QPalette::Inactive, QPalette::Window,selBrush1);
//           this->setPalette(palette4);
//          setFixedSize(selPix1.size());
//      }


      // LAB 2







}

Spider::~Spider()
{


}

void Spider::mousePressEvent(QMouseEvent* event)
{
//    int x, y;

//    Qt::MouseButton mb1 = event->button();
//    Qt::MouseButtons mbs = event->buttons();
//    qDebug() << "Button: " << mb1;
//    qDebug() << "Buttons: " << mbs;

//    QPoint p1 = event->pos();
//    qDebug() << "x = " << p1.x() <<" y = " << p1.y();

//    Qt::KeyboardModifiers kbMod = event->modifiers();
//    qDebug() << "key b mod: " << kbMod;

//    if(kbMod == Qt::ControlModifier)
//    {
//        qDebug() << "Ctrl pressed";
//    }
//    if(mb1 == Qt::LeftButton)
//    {
//        qDebug() << "Pressed Left MB";
//    }

    if(event->button() == Qt::RightButton && event->modifiers() == Qt::ControlModifier)
    {
        int x = event->pos().x();
        int y = event->pos().y();
        qDebug() << "x =" << x << "y =" << y;

        QString strTool = "";

        QString strX = QString().setNum(x);
        QString strY = QString::number(y);
        strTool += "x = " + strX + " y = " + strY;
        QToolTip::showText(event->globalPos(), strTool, this);


    }

    if(event->button() == Qt::LeftButton )
    {
        this->setCursor(spiderCursor);

        x0_spider = event->pos().x();
        y0_spider = event->pos().y();

        isDrawing = true;
        repaint();
    }

}

void Spider::mouseReleaseEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton )
    {
        this->unsetCursor();
        isDrawing = false;
        repaint();
    }
    qDebug() << "Mouse released ";
}

void Spider::mouseMoveEvent(QMouseEvent *event)
{

    x0_spider = event->pos().x();
    y0_spider = event->pos().y();

    bool CurPosInWindow = this->rect().contains(event->pos());

    if(!CurPosInWindow && !curWentOutOfWindow)
    {
        unsetCursor();
        curWentOutOfWindow = true;


//        QPoint pNew = QPoint(0, y0_spider);
//        QPoint pGlobalNew = QWidget::mapToGlobal(pNew);
//        QCursor::setPos(pGlobalNew);

    }
    else if(curWentOutOfWindow && CurPosInWindow)
    {
        setCursor(spiderCursor);
        curWentOutOfWindow = false;
    }
    else if(!CurPosInWindow && curWentOutOfWindow && event->modifiers() == Qt::ControlModifier)
    {

        // stop drawing Web
        if(x0_spider > this->rect().width())
        {
            x0_spider = this->rect().width();
        }
        if(x0_spider < 0)
        {
            x0_spider = 0;
        }

        if(y0_spider > this->rect().height())
        {
            y0_spider = this->rect().height();
        }
        if(y0_spider < 0)
        {
            y0_spider = 0;
        }
    }
    repaint();

    qDebug() << "Mouse moving"<< event->pos().x() << event->pos().y();
}

void Spider::paintEvent(QPaintEvent *event)
{

        if(isDrawing)
        {
            qDebug() << "was repainted ";

            QPainter painter(this);
            QPen p1 = QPen(QBrush(Qt::cyan),2);
            painter.setPen(p1);

            QRect dims = this->rect();
            int width = dims.width();
            int height = dims.height();

            int x0 = x0_spider;
            int y0 = y0_spider;

//            int x0 =  width/2;
//            int y0 =  height/2;

            painter.drawLine(0, 0, x0, y0);
            painter.drawLine(x0, y0, width, height);

            painter.drawLine(0, height, x0, y0);
            painter.drawLine(x0, y0, width, 0);

            painter.drawLine(width/2, 0, x0, y0);
            painter.drawLine(x0, y0, width/2, height);

            painter.drawLine(0, height/2, x0, y0);
            painter.drawLine(x0, y0, width, height/2);

            const int rings = 6;
            float kd = 0.71f;

            float k[rings][8] = {
                { 0.14f, 0.15f, 0.17f, 0.15f, 0.15f, 0.17f, 0.16f, 0.16f } ,
                { 0.23f, 0.26f, 0.28f, 0.3f, 0.28f, 0.3f, 0.31f, 0.31f } ,
                { 0.4f, 0.40f, 0.41f, 0.40f, 0.43f, 0.49f, 0.48f, 0.51f } ,
                { 0.61f, 0.72f, 0.7f, 0.72f, 0.67f, 0.7f, 0.73f, 0.71f } ,
                { 0.7f, 0.79f, 0.81f, 0.79f, 0.79f, 0.75f, 0.82f, 0.78f } ,
                { 0.84f, 0.86f, 0.89f, 0.86f, 0.88f, 0.82f, 0.89f, 0.85f }
            };

        //    float k[rings][8] = {
        //        { 0.15f, 0.15f, 0.15f, 0.15f, 0.15f, 0.15f, 0.15f, 0.15f } ,
        //        { 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f } ,
        //        { 0.47f, 0.47f, 0.47f, 0.47f, 0.47f, 0.47f, 0.47f, 0.47f } ,
        //        { 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f } ,
        //        { 0.79f, 0.79f, 0.79f, 0.79f, 0.79f, 0.79f, 0.79f, 0.79f } ,
        //        { 0.86f, 0.86f, 0.86f, 0.86f, 0.86f, 0.86f, 0.86f, 0.86f }
        //    };


            QPoint Web[rings][8];

            for(int i = 0; i < rings; i++)
            {
                int x1 = x0 + static_cast<int>(k[i][0] * (width - x0));
                int y1 = y0;
                if(y0 > height/2)
                {y1 -= static_cast<int>(k[i][0] * (y0 - height/2));}
                else
                {y1 += static_cast<int>(k[i][0] * (height/2 - y0));}

                int x3 = x0;
                if(x0 > width/2)
                {x3 -= static_cast<int>(k[i][2] * (x0 - width/2));}
                else
                {x3 += static_cast<int>(k[i][2] * (width/2 - x0));}
                int y3 = y0 - static_cast<int>(k[i][2] * y0);

                int x2 = x0 + static_cast<int>(kd * k[i][1] * (width - x0));
                int y2 = y0 - static_cast<int>(kd * k[i][1] * y0);

                int x5 = x0 - static_cast<int>(k[i][4] * x0);
                int y5 = y0;
                if(y0 > height/2)
                {y5 -= static_cast<int>(k[i][4] * (y0 - height/2));}
                else
                {y5 += static_cast<int>(k[i][4] * (height/2 - y0));}

                int x4 = x0 - static_cast<int>(kd * k[i][3] * x0);
                int y4 = y0 - static_cast<int>(kd * k[i][3] * y0);

                int x7 = x0;
                if(x0 > width/2)
                {x7 -= static_cast<int>(k[i][6] * (x0 - width/2));}
                else
                {x7 += static_cast<int>(k[i][6] * (width/2 - x0));}
                int y7 = y0 + static_cast<int>(k[i][6] * (height - y0));

                int x6 = x0 - static_cast<int>(kd * k[i][5] * x0);
                int y6 = y0 + static_cast<int>(kd * k[i][5] * (height - y0));

                int x8 = x0 + static_cast<int>(kd * k[i][7] * (width - x0));
                int y8 = y0 + static_cast<int>(kd * k[i][7] * (height - y0));

                Web[i][0] = QPoint(x1,y1);
                Web[i][1] = QPoint(x2,y2);
                Web[i][2] = QPoint(x3,y3);
                Web[i][3] = QPoint(x4,y4);
                Web[i][4] = QPoint(x5,y5);
                Web[i][5] = QPoint(x6,y6);
                Web[i][6] = QPoint(x7,y7);
                Web[i][7] = QPoint(x8,y8);

                if(i == 0)
                {
                    painter.drawLine(Web[i][7], Web[i][0]);
                }

                if(i > 0)
                {
                    painter.drawLine(Web[i - 1][7], Web[i][0]);
                }
                if(i == rings - 1)
                {
                    painter.drawLine(Web[rings - 1][7], Web[rings - 1][0]);
                }


                for(int j = 0; j < 7 ; j++)
                {
                    painter.drawLine(Web[i][j], Web[i][j + 1]);
                }
         }
    }
}

void Spider::resizeEvent(QResizeEvent *event)
{
    QString updateTitle = "";

    QString strW = QString::number(this->rect().width());
    QString strH = QString::number(this->rect().height());
    updateTitle += ": width=" + strW + " height=" + strH;
    qDebug() << updateTitle;

    QString tempWindowTitle = windowTitle + updateTitle;
    this->setWindowTitle(tempWindowTitle);

}
