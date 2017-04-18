#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>
#include "diff_system.h"
using namespace std;

int main()
{

	//тестовая матрица для начального поля
	int **test = new int *[5];
	for(int i = 0; i <5; i++)
        test[i] = new int[5];

	for (int i = 0; i<5; i++){
		for(int j = 0; j<5; j++){
			if (j<2||j>3) {
				test[i][j]= 0;
			}
			else {
			test[i][j]= 1;
		}
		//ее вывод
			cout << test[i][j];
		}
		cout << endl;
	}

	diff_system test_sys(test);
	test_sys.transform();

	for (int i=0;i<5;i++)
        {
            delete [] test[i];
        }
    delete [] test;

       return 0;
}
