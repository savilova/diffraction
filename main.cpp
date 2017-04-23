#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>
#include "diff_system.h"
using namespace std;

int main()
{

	int length = 30;
	int **test = new int *[length];
	for(int i = 0; i <length; i++)
        test[i] = new int[length];

	for (int i = 0; i<length; i++){
		for(int j = 0; j<length; j++){
			if (j<(length/2)||j>(length/2)) {
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

	for (int i=0;i<length;i++)
        {
            delete [] test[i];
        }
    delete [] test;

       return 0;
}
