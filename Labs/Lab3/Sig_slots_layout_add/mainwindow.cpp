#include "mainwindow.h"
#include <QPushButton>

#include <QHBoxLayout>
#include <QSpinBox>
#include <QSlider>
#include <QLabel>
#include <QLineEdit>
#include <QSize>
#include <QIntValidator>
#include <QDebug>
#include <QSizePolicy>
#include <QSignalMapper>
#include <QStyleFactory>
#include <QStyle>
#include <QApplication>

mainWindow::mainWindow(QApplication* app, QWidget *parent)
    : QWidget(parent)
{
    //Design

    //this->setFixedSize(640, 480);

//    buttonExit.setText("Exit");
//    buttonExit.setParent(this);

   // QPushButton* buttonExit = new QPushButton(QObject::tr("Exit"), this);

    myApp = app;

    mapper = new QSignalMapper(nullptr);

    mainLayout = new QHBoxLayout(/*this*/);
    //this->setLayout(mainLayout);
    frameLayout = new QHBoxLayout();
    this->setLayout(frameLayout);

    spacerStack = new QSpacerItem(80, 70);
    spacerVert = new QSpacerItem(80, 50);

    QPushButton* buttonExit = new QPushButton("Exit");
    buttonDisable = new QPushButton("Disable");
    buttonStyle = new QPushButton("Style: Vista");


    QPushButton* buttonVertical = new QPushButton("Vertical");
    QPushButton* buttonHorizontal = new QPushButton("Horizontal");
    QPushButton* buttonGrid = new QPushButton("Grid");
    QPushButton* buttonStack = new QPushButton("Stack");

    mainFrame = new QFrame();


    buttonsLayout = new QVBoxLayout();
    buttonsLayout->addWidget(buttonVertical);
    buttonsLayout->addWidget(buttonHorizontal);
    buttonsLayout->addWidget(buttonGrid);
    buttonsLayout->addWidget(buttonStack);

    //buttonExit->move(20, 20);
    //mainLayout->addWidget(buttonExit);

    spinBox = new QSpinBox();
    slider = new QSlider(Qt::Horizontal);   // orientation - Horizontal || Vetrical

    label = new QLabel("Not set");

    lineEdit = new QLineEdit();

    hLayout = new QHBoxLayout();
    hLayout->addWidget(spinBox);
    hLayout->addWidget(slider);
    hLayout->addWidget(label);
    hLayout->addWidget(lineEdit);

    vLayout = new QVBoxLayout();
    vLayout->addWidget(spinBox);
    vLayout->addWidget(slider);
    vLayout->addWidget(label);
    vLayout->addWidget(lineEdit);
    vLayout->addItem(spacerVert);

    gLayout = new QGridLayout();
    gLayout->addWidget(spinBox, 0, 0);
    gLayout->addWidget(slider, 0, 1);
    gLayout->addWidget(lineEdit, 1, 0);
    gLayout->addWidget(label, 1, 1);

    demoStackLayout = new QVBoxLayout();
    combo = new QComboBox();
    combo->addItem("spinBox");
    combo->addItem("slider");
    combo->addItem("lineEdit");
    combo->hide();

    stackLayout = new QStackedLayout();
    stackLayout->addWidget(spinBox);
    stackLayout->addWidget(slider);
    stackLayout->addWidget(lineEdit);


    stackLayout->setStackingMode(QStackedLayout::StackAll);

    demoStackLayout->addWidget(combo,0, Qt::AlignTop);
    demoStackLayout->addWidget(label, 0, Qt::AlignTop);
    demoStackLayout->addLayout(stackLayout);
    demoStackLayout->addItem(spacerStack);


    buttonsExitDisLayout = new QVBoxLayout();
    buttonsExitDisLayout->addWidget(buttonExit);
    buttonsExitDisLayout->addWidget(buttonStyle);
    buttonsExitDisLayout->addWidget(buttonDisable);

    //mainLayout->addLayout(hLayout);
    //mainLayout->addLayout(vLayout);
    mainLayout->addLayout(gLayout);
    //mainLayout->addLayout(demoStackLayout);
    mainLayout->addLayout(buttonsLayout);

    mainFrame->setLayout(mainLayout);
    mainFrame->setFrameStyle(1);

    frameLayout->addWidget(mainFrame);
    frameLayout->addLayout(buttonsExitDisLayout);
   // mainLayout->addLayout(buttonsExitDisLayout);


    // Set properties of widgets

    minRange = 1;
    maxRange = 10;
    startRange = 5;

    label->setText(QString::number(startRange));
    lineEdit->setText(QString::number(startRange));

    spinBox->setRange(minRange, maxRange);  // range
    spinBox->setValue(startRange);          // init value
    // signal // spinBox->valueChanged(int);


    slider->setRange(minRange, maxRange);
    slider->setSliderPosition(startRange);
    slider->setTickInterval(1);

    slider->setTickPosition(QSlider::TicksBelow);
    slider->setSingleStep(1);
    //signal // slider->valueChanged(int);


    QIntValidator* intV = new QIntValidator(minRange, maxRange);
    lineEdit->setValidator(intV);


    label->setFrameStyle(1);
    label->setMinimumWidth(40);
    label->setMinimumHeight(20);
    label->setAlignment(Qt::AlignmentFlag::AlignCenter);
  //  label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);



    // connect button
   // QObject::connect(buttonExit, SIGNAL(clicked(bool)), this, SLOT(close()));
    QObject::connect(buttonExit, &QAbstractButton::clicked, this, &mainWindow::close);

    // connect spinBox
    QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    QObject::connect(spinBox, SIGNAL(valueChanged(int)), label, SLOT(setNum(int)));

    // don't work  // QObject::connect(spinBox, &QSpinBox::valueChanged), lineEdit, &QLineEdit::setText);


    // connect slider
    QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
    QObject::connect(slider, SIGNAL(valueChanged(int)), label, SLOT(setNum(int)));

    QObject::connect(slider, &QSlider::valueChanged, this, &mainWindow::mySlotIntToString);
    QObject::connect(this, SIGNAL(mySignalString(QString)), lineEdit, SLOT(setText(QString)));


    // connect lineEdit
    // don't work: //
    QMetaObject::Connection con1 = QObject::connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(mySlotStringToInt(QString)));
   // QMetaObject::Connection con1 = QObject::connect(lineEdit,&QLineEdit::textChanged, this, &mainWindow::mySlotStringToInt);
    if(!con1) qDebug() << "con1 not connected";
    else qDebug() << "con1 connected";

    QObject::connect(this, SIGNAL(mySignalInt(int)), label, SLOT(setNum(int)));
    QObject::connect(this, SIGNAL(mySignalInt(int)), spinBox, SLOT(setValue(int)));
    QObject::connect(this, SIGNAL(mySignalInt(int)), slider, SLOT(setValue(int)));


    // connect buttonVertical
    // dont work //
    //QMetaObject::Connection con2 = QObject::connect(buttonVertical, &QPushButton::clicked, mapper, &QSignalMapper::map);

    QMetaObject::Connection con2 = QObject::connect(buttonVertical, SIGNAL(clicked(bool)), mapper, SLOT(map()));
    if(!con2) qDebug() << "con2 not connected";
    else qDebug() << "con2 connected";

    // test Slot
    // QObject::connect(buttonVertical, &QAbstractButton::clicked, this, &mainWindow::myTestSlot);


    // connect buttonHorizontal
    QMetaObject::Connection con3 = QObject::connect(buttonHorizontal, SIGNAL(clicked(bool)), mapper, SLOT(map()));
    if(!con3) qDebug() << "con3 not connected";
    else qDebug() << "con3 connected";

    // connect buttonGrid
    QMetaObject::Connection con5 = QObject::connect(buttonGrid, SIGNAL(clicked(bool)), mapper, SLOT(map()));
    if(!con5) qDebug() << "con5 not connected";
    else qDebug() << "con5 connected";

    // connect buttonStack
    QMetaObject::Connection con6 = QObject::connect(buttonStack, SIGNAL(clicked(bool)), mapper, SLOT(map()));
    if(!con6) qDebug() << "con6 not connected";
    else qDebug() << "con6 connected";

    // mapper
    mapper->setMapping(buttonVertical, vLayout);
    mapper->setMapping(buttonHorizontal, hLayout);
    mapper->setMapping(buttonGrid, gLayout);
    mapper->setMapping(buttonStack, demoStackLayout);

    QMetaObject::Connection con4 = QObject::connect(mapper, SIGNAL(mapped(QObject*)), this, SLOT(changeLayoutSlot(QObject*)));
    if(!con4) qDebug() << "con4 not connected";
    else qDebug() << "con4 connected";



    // Disable button
    QObject::connect(buttonDisable, &QAbstractButton::clicked, this, &mainWindow::disableSlot);

    // stackLayout connect
    QObject::connect(combo, SIGNAL(activated(int)), stackLayout, SLOT(setCurrentIndex(int)));

    // Style button
    QObject::connect(buttonStyle, &QAbstractButton::clicked, this, &mainWindow::styleSlot);

    QObject::dumpObjectTree();

    qDebug() << hLayout->sizeHint();

}


mainWindow::~mainWindow()
{

    // не понял доконца как работает : по идее все должно удаляться само кроме компоновок отключенных
    //this->setLayout(nullptr);

    //delete frameLayout;
   // delete mainFrame;
   // delete buttonsExitDisLayout;

   // delete frameLayout;
    //frameLayout = nullptr;

    delete vLayout;
    delete hLayout;
    delete gLayout;
    delete demoStackLayout;


    qDebug() << "After delete:";
    QObject::dumpObjectTree();
}

void mainWindow::mySlotStringToInt(const QString s)
{
    int n;
    n = s.toInt();
    qDebug() << "slot ok" << n ;
    emit(mySignalInt(n));
    qDebug() << this->sender();
}

void mainWindow::mySlotIntToString(int n)
{
    QString s = QString::number(n);
    qDebug() << "slot ok" << s ;
    emit(mySignalString(s));
    qDebug() << this->sender();
}

void mainWindow::changeLayoutSlot(QObject* pNewLayout)
{
    qDebug() << "myLayoutSlot works";

    QLayout* Layout = static_cast<QLayout*>(pNewLayout);

    if (Layout == demoStackLayout)
    {
        qDebug() << pNewLayout << "demoStackLayout";
        combo->setVisible(true);
        // эти методы отображают все Виджеты на Стековой компоновке !?
        lineEdit->setVisible(false);
        spinBox->setVisible(false);
        slider->hide();
        stackLayout->currentWidget()->show();
        stackLayout->setStackingMode(QStackedLayout::StackOne);
    }
    else
    {
        qDebug() << pNewLayout << "not demoStackLayout";
        combo->setVisible(false);
        stackLayout->setStackingMode(QStackedLayout::StackAll);

    }

    mainLayout->takeAt(0);
    mainLayout->insertLayout(0, Layout);

}

void mainWindow::disableSlot()
{
    qDebug() << "disable works";
    if (enabled)
    {
        buttonDisable->setText("Enable");
        mainFrame->setEnabled(false);

    }
    else
    {
        buttonDisable->setText("Disable");
        mainFrame->setEnabled(true);
    }

    enabled = !enabled;
}

void mainWindow::styleSlot()
{
    qDebug() << "style works";
    qDebug() << QStyleFactory::keys();

    switch (windowStyle)
    {
    case 1: // windowsvista
        windowStyle++;
        myApp->setStyle(QStyleFactory::create("Fusion"));
        buttonStyle->setText("Style: Fusion");
        break;

    case 2: // Fusion
        windowStyle++;
        myApp->setStyle(QStyleFactory::create("Windows"));
        buttonStyle->setText("Style: Windows");
        break;

    case 3: // Windows
        windowStyle = 1;
        myApp->setStyle(QStyleFactory::create("windowsvista"));
        buttonStyle->setText("Style: Vista");
        break;
    default:
        qDebug() << "error";
        break;
    }

}

void mainWindow::myTestSlot()
{
    qDebug() << "myTestSlot works";
    qDebug() << this->sender();
}
