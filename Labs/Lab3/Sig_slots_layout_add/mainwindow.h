#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QSlider>
#include <QLabel>
#include <QLineEdit>
#include <QSignalMapper>
#include <QStackedLayout>
#include <QComboBox>
#include <QSpacerItem>
#include <QApplication>


class mainWindow : public QWidget
{
    Q_OBJECT

private:
   // QPushButton buttonExit;

    QHBoxLayout* mainLayout;
    QHBoxLayout* hLayout;
    QVBoxLayout* vLayout;
    QGridLayout* gLayout;
    QVBoxLayout* buttonsLayout;
    QVBoxLayout* buttonsExitDisLayout;
    QFrame* mainFrame;
    QHBoxLayout* frameLayout;
    QVBoxLayout* demoStackLayout;
    QStackedLayout* stackLayout;
    QComboBox* combo;
    QSpacerItem* spacerStack;
    QSpacerItem* spacerVert;

    QSpinBox* spinBox;
    QSlider* slider;
    QLabel* label;
    QLineEdit* lineEdit;

    QSignalMapper* mapper;

    int minRange, maxRange, startRange;
    QPushButton* buttonDisable;
    bool enabled = true;

    QPushButton* buttonStyle;
    int windowStyle = 1;

    QApplication* myApp;

public:
    explicit mainWindow(QApplication* app, QWidget *parent = nullptr);
    ~mainWindow();


signals:
    void mySignalInt(int);
    void mySignalString(QString);


public slots:
    void mySlotStringToInt(const QString s);
    void mySlotIntToString(int n);
    void changeLayoutSlot(QObject* pNewLayout);
    void disableSlot();
    void styleSlot();

    void myTestSlot();


};

#endif // MAINWINDOW_H
