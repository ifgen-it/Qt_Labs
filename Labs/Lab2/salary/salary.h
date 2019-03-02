#ifndef SALARY_H
#define SALARY_H

#include <QWidget>
#include <QPushButton>
#include <QRandomGenerator>

class Salary : public QWidget
{
    Q_OBJECT

private:
    QPushButton* btnYes, *btnNo;
    int btnNoX, btnNoY;
    int deltaX, deltaY;
    int btnWidth, btnHeight;
    int wWidth, wHeight;
    int counter;
    QRandomGenerator rand;

public:
    Salary(QWidget *parent = nullptr);
    ~Salary() override;

public slots:
    void yesOnClicked(bool checked);
    void noOnClicked(bool checked);


    // QObject interface
public:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
    void removeBtnNo();
};

#endif // SALARY_H
