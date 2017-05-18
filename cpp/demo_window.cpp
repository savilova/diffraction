#include "h/demo_window.h"
#include "ui_demo_window.h"
#include "h/diff_system.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2\core\core.hpp"
#include<cstring>
using namespace cv;

//Конструктор по умолчанию, создаем демонстрационную установку
demo_window::demo_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::demo_window)
{
    ui->setupUi(this);
    diff_system * demo_sys = new diff_system();

    QString b = "Характерный размер отверстия " + QString::number(demo_sys->o->pixel) + " мкм";
    ui->param_b->setText(b);
    QString l = "Длина волны " + QString::number(demo_sys->wave) + " нм";
    ui->param_l->setText(l);
    QString z = "Расстояние до экрана " + QString::number(demo_sys->z/10000) + " cм";
    ui->param_z->setText(z);
    QString p = "Волновой параметр p = " + QString::number(sqrt(demo_sys->wave*demo_sys->z)/demo_sys->pixel);
    ui->param_p->setText(p);
    QString s = QString::number(demo_sys->pixel*demo_sys->width/10000);
    s = "Размер экрана " + s + " см x " + s + " см";
    ui->param_s->setText(s);

    displayObstacle(demo_sys);
    demo_sys->transform();
    displayScreen(demo_sys);
}

demo_window::~demo_window()
{
    delete ui;
}

void demo_window::displayObstacle(diff_system * sys){
    const int preview_size = 200;
    IplImage * img = cvCreateImage(cvSize(sys->o->width, sys->o->width), IPL_DEPTH_8U, 1);
    for (int i = 0; i < img->imageSize; i++)
        img->imageData[i] = sys->o->img_data[i];
    IplImage* new_img = cvCreateImage(cvSize(preview_size, preview_size), img->depth, img->nChannels);
    cvResize(img, new_img);
    QImage obstacle_display((uchar*)new_img->imageData, new_img->width, new_img->height, new_img->widthStep, QImage::Format_Grayscale8); //Converts the CV image into Qt standard format
    ui->o_preview->setPixmap(QPixmap::fromImage(obstacle_display));

}

void demo_window::displayScreen(diff_system * sys){
    const int preview_size = 400;
    IplImage * img = cvCreateImage(cvSize(sys->width, sys->width), IPL_DEPTH_8U, 1);
    for (int i = 0; i < img->imageSize; i++)
        img->imageData[i] = sys->Intensity[i];
    IplImage* new_img = cvCreateImage(cvSize(preview_size, preview_size), img->depth, img->nChannels);
    cvResize(img, new_img);
    QImage screen_display((uchar*)new_img->imageData, new_img->width, new_img->height, new_img->widthStep, QImage::Format_Grayscale8);
    ui->pic_2d->setPixmap(QPixmap::fromImage(screen_display));

}
