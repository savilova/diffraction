#ifndef DIFF_SYS
#define DIFF_SYS

#include <cmath>
using namespace std;

//Шаблон функции create_matrix
template <typename T>
void create_matrix(T *** Matrix, int lines, int columns)
{
    (*Matrix) = new T * [lines];

    for (int i = 0; i < lines; i++)
        (*Matrix)[i] = new T [columns];
}

//Шаблон функции delete_matrix
template <typename T>
void delete_matrix(T *** Matrix, int columns)
{
    for (int i = 0; i < columns; i++)
    {
        delete [] ((*Matrix)[i]);
    }
    delete [] (*Matrix);

}

class diff_system
{
public:
    int wave; //
    double k;
    double z;
    int row;
    int col;
    int **f_0;
    double **f_z;
    double Size;

    template <typename T> friend void create_matrix(T *** Matrix, int lines, int columns);
    template <typename T> friend void delete_matrix(T *** Matrix, int columns);
    //конструктор
    diff_system(int ** f)
    {
        wave = 532;  // длина волны в нм
        k  = 2*3.1416/wave;   // волновой вектор
        z = 2;   // расстояние от препятствия до экрана
        row = 30;   // количество рядов в матрице изображений
        col = 30;  // количество столбцов в матрице изображений
        f_0 = f;
        Size = 10;
        create_matrix(&f_z, row, col);
        cout << "Well done!" << endl;
    }

    //деструктор
    ~diff_system()
    {
        delete_matrix(&f_z, col);
    }

    //Подсчет поля в плоскости z по принципу Гюйгенса-Френеля(интеграл)
    void transform()
    {
        double ** Re_G_table;
        create_matrix(&Re_G_table, row, col);
        double ** Im_G_table;
        create_matrix(&Im_G_table, row, col);

        for (int x = 0; x < row; x++)
        {
            for (int y = 0; y < col; y++)
            {
                double Re_Sum = 0;
                double Im_Sum = 0;

                for (int r = 0; r < row; r++)
                {
                    for (int c = 0; c < col; c++)
                    {
                        double R = sqrt(pow(z,2)+pow((Size/1000)*abs((x-r)),2)+pow((Size/1000)*abs((y-c)),2));
                        double cosinus = z/R;
                        double Re_per_Sum = f_0[r][c] * (cosinus/R) *cos(k*pow(10,9)*R);
                        double Im_per_Sum = f_0[r][c] * (cosinus/R) *sin(k*pow(10,9)*R);
                        Re_Sum += Re_per_Sum*pow((Size/1000),2);
                        Im_Sum += Im_per_Sum*pow((Size/1000),2);
                    }
                }

                Re_G_table[x][y] = Re_Sum*pow(10,9)/wave;
                Im_G_table[x][y] = Im_Sum*pow(10,9)/wave;
            }
        }

        cout<<"For end!"<<endl;
        for (int x = 0; x < row; x++)
        {

            for (int y = 0; y < col; y++)
            {
                f_z[x][y] = pow(Re_G_table[x][y],2) + pow(Im_G_table[x][y],2);
                cout<<f_z[x][y]<<' ';
            }
            cout << endl;
        }

        delete_matrix(&Re_G_table, col);
        delete_matrix(&Im_G_table, col);
    }
};

#endif // DIFF_SYS
