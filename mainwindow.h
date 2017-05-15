#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"tempsetting.h"
#include <QObject>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_fromTemp_triggered();

private:
    Ui::MainWindow *ui;
    tempSetting * tempSettingPage;
};

#endif // MAINWINDOW_H
