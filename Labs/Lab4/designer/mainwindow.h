#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

signals:
    void mySignalInt(int);


public slots:
    void slotEditChanged(QString s);
private slots:
    void on_action_About_triggered();
};

#endif // MAINWINDOW_H
