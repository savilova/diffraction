#ifndef main_window_H
#define main_window_H

#include"temp_setting.h"
#include "demo_window.h"

#include <QObject>
#include <QMainWindow>

namespace Ui {
class main_window;
}

class main_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit main_window(QWidget *parent = 0);
    ~main_window();


private slots:
    void on_fromTemp_triggered();
    void on_demo_triggered();

private:
    Ui::main_window *ui;
    temp_setting *settingWin;
    demo_window * demoWin;
};

#endif // main_window_H
