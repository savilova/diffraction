#include <iostream>
#include <fstream>
#include <math.h>
#include "diff_system.h"
using namespace std;

int main()
{
	//тестовая матрица для начального поля
	int **test = new int *[100];
	for(int i = 0; i <100; i++)
        test[i] = new int[100];

	for (int i = 0; i<100; i++){
		for(int j = 0; j<100; j++){
			if (j<20||j>30) {
				test[i][j]= 0;
			}
			else {
			test[i][j]= 255;
		}
	}



    draw_2d(test);



    for (int i=0;i<100;i++)
        {
            delete [] test[i];
        }
    delete [] test;


       return 0;
}
