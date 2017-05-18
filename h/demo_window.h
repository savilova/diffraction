#ifndef DEMO_WINDOW_H
#define DEMO_WINDOW_H

#include"diff_system.h"
#include <QDialog>

namespace Ui {
class demo_window;
}

class demo_window : public QDialog
{
    Q_OBJECT

public:
    explicit demo_window(QWidget *parent = 0);
    QImage obstacle_display;
    QImage screen_display;

    ~demo_window();
    void displayObstacle(diff_system * sys);
    void displayScreen(diff_system * sys);
private:
    Ui::demo_window *ui;


};

#endif // DEMO_WINDOW_H
