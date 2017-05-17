#include "main_window.h"
#include "ui_main_window.h"
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
        temp_settingPage = new temp_setting(this);
        temp_settingPage->show();
}
