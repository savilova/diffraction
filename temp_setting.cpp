#include "temp_setting.h"
#include "ui_temp_setting.h"

temp_setting::temp_setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::temp_setting)
{
    ui->setupUi(this);
}

temp_setting::~temp_setting()
{
    delete ui;
}
