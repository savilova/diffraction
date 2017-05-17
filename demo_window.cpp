#include "demo_window.h"
#include "ui_demo_window.h"

demo_window::demo_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::demo_window)
{
    ui->setupUi(this);
}

demo_window::~demo_window()
{
    delete ui;
}
