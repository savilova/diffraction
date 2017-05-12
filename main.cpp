#include "mainwindow.h"
#include "diff_system.h"
#include <QApplication>

#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;

void draw_mat(int width, int length, int *data)
{
    IplImage *img = cvCreateImage(cvSize(width, length), IPL_DEPTH_8U, 1);
    int i;
    for (i = 0; i < img->imageSize; i++)
        img->imageData[i] = data[i];

    // Создаем окно с заголовком image
    cvNamedWindow ("image", 1);
    // Показываем в этом окне картинку img
    cvShowImage ("image", img);
    // Ждем нажатия юбой клавиши
    cvWaitKey (0);

    // Освобождаем память перд выходм из программы
    cvReleaseImage (&img);
    cvDestroyWindow("image");

}

int main(int argc, char *argv[])
{

    // Матрица препядствия, где светлые точки это отверстие
    // Всё остальное это тёмные отверстия
    // В данной версии отверстие прямоугольное

    // Размер пикселя препядствия в микронах
    int o_pixel_size = 25;

    // Размер пикселя результирующей картины в микронах
    int s_pixel_size = 100;

    int wave = 532;  // Длина волны в нанометрах
    int R = 1000000; // Расстояние до экрана в мкм
    int length = 6; // Длина отверстия
    int width = 6;  // Ширина отверстия
    int *obstacle = new int[length*width]; // Матрица препядствия

    for (int i = 0; i < length*width; i++)
        obstacle[i] = 200; // Яркость точек отверстия 200

    diff_system * Screen = new diff_system(o_pixel_size, s_pixel_size, wave, R, length, width, obstacle);
    draw_mat(Screen->o_cols,Screen->o_rows,Screen->Obstacle);
    draw_mat(Screen->s_cols,Screen->s_rows,Screen->Intensity);

    Screen->transform();
    cout << "transform sucseeded " << endl;

    delete [] obstacle;
    cout << "deleted obstacle " << endl;

    return  0;
}
