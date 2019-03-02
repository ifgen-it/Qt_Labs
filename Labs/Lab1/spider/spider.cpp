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

Spider::Spider(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent)
{


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

    QString title(QObject::tr("Spider"));

    this->setWindowTitle(title);

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
    setWindowOpacity(0.85);

    QPoint p1 = this->pos();
    qDebug() << p1;
    QRect r1 = this->frameGeometry();
    qDebug() << this->rect();

    setGeometry(50, 50, 500, 500);
    setMinimumSize(300, 300);
    setMaximumSize(800, 800);

    QDesktopWidget* pDeskTop = QApplication::desktop();
    QRect deskTopRect = pDeskTop->screenGeometry();

    setMaximumSize(deskTopRect.width(),deskTopRect.height());

    // quater
    resize(deskTopRect.width()/2,deskTopRect.height()/2);
   // move(deskTopRect.width()/2,deskTopRect.height()/2);
    move(deskTopRect.width()/2,deskTopRect.height()/2);

      setFixedSize(pix.size());

      QCursor curs1 = Qt::CrossCursor;

     // this->setCursor(curs1);

      QBitmap bmp("Images_lab1\\super_spy.bmp");
      QCursor curs2(bmp, bmp);
      this->setCursor(curs2);
      this->unsetCursor();

      QPixmap pix1("Images_lab1\\spider1.bmp");
      pix1.setMask(QBitmap("Images_lab1\\spider1.bmp"));
      QCursor curs3(pix1);
      this->setCursor(curs3);

      // DIALOGS

      //COLOR

      QColor selColor1 = QColorDialog::getColor();
      QPalette  palette4 = this->palette();

      if(selColor1.isValid())
      {
          palette4.setColor(QPalette::Active, QPalette::Window, selColor1);
          this->setPalette(palette4);
      }


      //PHOTO

      QString fNamePix =  QFileDialog::getOpenFileName(0, tr("Open picture dialog"), ".", "*.jpg *.jpeg *.png *.bmp *.gif *.tiff");

      if(!fNamePix.isEmpty())
      {
          QPixmap selPix1(fNamePix);
          QBrush selBrush1 = QBrush(selPix1);
          palette4.setBrush(QPalette::Inactive, QPalette::Window,selBrush1);
           this->setPalette(palette4);
          setFixedSize(selPix1.size());
      }






}

Spider::~Spider()
{


}
