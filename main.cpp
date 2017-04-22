#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>
#include "diff_system.h"
#include "cv.h"
#include "highgui.h"
using namespace std;





void draw_mat(int w, int h, int *data)
{
    IplImage *img = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);
    int i;
    for (i = 0; i < img->imageSize; i++) img->imageData[i] = data[i];

    // создаем окно с заголовком image
    cvNamedWindow ("image", 1);
    // показываем в этом окне картинку img
    cvShowImage ("image", img);
    // ждем нажатия юбой клавиши
    cvWaitKey (0);

    // освобождаем память перд выходм из программы
    cvReleaseImage (&img);
    cvDestroyWindow("image");

}

int main()
{

    //тестовая матрица для начального поля
    int h = 4;
    int w = 4;
    int *test = new int[h*w];

    for (int i = 0; i<h*w; i++)
    {

        if (i%w==1)
        {
            test[i]=200;
        }
        else
        {
            test[i]=0;
        }
    }

    diff_system * test_sys = new diff_system(400, 532, 1000000, h, w, test);
    draw_mat(test_sys->o_cols,test_sys->o_rows,test_sys->f_0);
    draw_mat(test_sys->s_cols,test_sys->s_rows,test_sys->f_z);

    test_sys->transform();
    cout << "transform sucseeded " << endl;

    delete [] test;
    cout << "deleted test " << endl;
//   delete test_sys;
    // cout << " deleted system " << endl;

    return 0;
}
