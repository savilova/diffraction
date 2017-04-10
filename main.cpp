#include <iostream>
#include <fstream>
#include <math.h>
#include "diff_system.h"
using namespace std;

int main()
{

	//тестовая матрица для начального поля
	int **test = new int *[50];
	for(int i = 0; i <50; i++) test[i] = new int[50];

	for (int i = 0; i<50; i++){
		for(int j = 0; j<50; j++){
			if (j<25||j>30) {
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

       return 0;
}
