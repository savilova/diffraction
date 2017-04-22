#include <iostream>
#include <fstream>
#include <cmath>
#include "diff_system.h"
using namespace std;

int main()
{

	int length = 30;
	int **test;
	create_matrix(&test, length, length);

	for (int i = 0; i<length; i++)
	{
		for(int j = 0; j<length; j++)
		{
			if (j<(length/2)||j>(length/2))
				test[i][j]= 0;
			else
			test[i][j]= 1;

			//Вывод матрицы
			cout << test[i][j];
		}
		cout << endl;
	}

	diff_system test_sys(test);
	test_sys.transform();

	delete_matrix(&test, length);

       return 0;
}
