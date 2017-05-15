#include "tempsetting.h"
#include "ui_tempsetting.h"

tempSetting::tempSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tempSetting)
{
    ui->setupUi(this);
}

tempSetting::~tempSetting()
{
    delete ui;
}
