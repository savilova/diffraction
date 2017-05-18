#include "h/main_window.h"
#include"h/demo_window.h"
#include "ui_main_window.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2\core\core.hpp"
#include<QPixmap>



main_window::main_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::main_window)
{
    ui->setupUi(this);
    QPixmap scheme("H:/diffraction/diffraction/img/scheme.jpg");
    ui->scheme_label->setPixmap(scheme);
}

main_window::~main_window()
{
    delete ui;
}


void main_window::on_fromTemp_triggered()
{
    settingWin = new temp_setting(this); //открываем окно настроек параметров
    settingWin->show();

}

void main_window::on_demo_triggered()
{

    demoWin = new demo_window(this); //вызываем конструктор по умолчанию
    demoWin->show();
}
