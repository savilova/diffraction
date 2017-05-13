#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>
#include "diff_system.h"
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

int main()
{
    return 0;
}
