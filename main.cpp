#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>
#include "diff_system.h"
#include "cv.h"
#include "highgui.h"
using namespace std;





void draw_mat(int w, int h, int *data){
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
	int h = 100;
	int w = 100;
	int *test = new int[h*w];

	for (int i = 0; i<h*w; i++) test[i]=0;

	for (int i = 0; i<h*w; i++){
        //if((i%w>40) & (i%w<47)){
        if(i%w==45){

            for(int j=0;j<10;j++){
                test[i+j]=255;}
        }
		}

   diff_system * test_sys = new diff_system(5,532, 2000000.0, h, w, test);
   test_sys->transform();
    cout << "transform sucseeded " << endl;

    delete [] test;
    cout << "deleted test " << endl;

    cout << "not deleted sys " << endl;

    return 0;
}
