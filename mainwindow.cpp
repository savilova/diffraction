#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap scheme("H:/diffraction/diffraction/img/scheme.jpg");
    ui->scheme_label->setPixmap(scheme);
}

MainWindow::~MainWindow()
{
    delete ui;
}



