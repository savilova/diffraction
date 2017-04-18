#include <cv.h>
#include <highgui.h>
#include<iostream>

void draw_2d(int **f)

{
        cvMat ** matrix = cvMat(size,CV_64FC1,&f);
        CvSize size;
        // задаём высоту и ширину картинки
        size.height = 100;
        size.width = 100;






        // создаём окошко
        cvNamedWindow("Diffraction 2D output", 0);
        // показываем картинку в созданном окне
        cvShowImage("Diffraction 2D output", matrix);
        // ждём нажатия клавиши
        cvWaitKey(0);
        // освобождаем ресурсы
        cvReleaseMat(matrix);
        cvDestroyWindow("Diffraction 2D output");

}
