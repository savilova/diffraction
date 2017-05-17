#include "demo_window.h"
#include "ui_demo_window.h"
#include "diff_system.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2\core\core.hpp"
using namespace cv;

//Конструктор по умолчанию, создаем демонстрационную установку
demo_window::demo_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::demo_window)
{
    ui->setupUi(this);
<<<<<<< HEAD
    diff_system * demo_sys = new diff_system();
    displayObstacle(demo_sys->o->width,demo_sys->o->width,demo_sys->o->img_data);
=======
    int * o = new int[1];
    o[0]=0;
    diff_system * demo_sys = new diff_system(10, 1000, 532, 200000, 1, 1, o);
    displayObstacle(1,1,o);
>>>>>>> d7397fa84d4dfa6e66bacd18f4cdb4244656de94
}

demo_window::~demo_window()
{
    delete ui;
}

void demo_window::displayObstacle(int w, int l, int * data){

<<<<<<< HEAD
    IplImage * img = cvCreateImage(cvSize(w, l), IPL_DEPTH_8U, 1);
=======
   IplImage * img = cvCreateImage(cvSize(w, l), IPL_DEPTH_8U, 1);
>>>>>>> d7397fa84d4dfa6e66bacd18f4cdb4244656de94
    for (int i = 0; i < img->imageSize; i++)
        img->imageData[i] = data[i];
    IplImage* new_img = cvCreateImage(cvSize(100, 100), img->depth, img->nChannels);
    cvResize(img, new_img);
<<<<<<< HEAD
    QImage obstacle_display((uchar*)new_img->imageData, new_img->width, new_img->height, new_img->widthStep, QImage::Format_Grayscale8); //Converts the CV image into Qt standard format
    ui->o_preview->setPixmap(QPixmap::fromImage(obstacle_display));

}
=======
   QImage obstacle_display((uchar*)new_img->imageData, new_img->width, new_img->height, new_img->widthStep, QImage::Format_Grayscale8); //Converts the CV image into Qt standard format
   ui->o_preview->setPixmap(QPixmap::fromImage(obstacle_display));

 }
>>>>>>> d7397fa84d4dfa6e66bacd18f4cdb4244656de94
