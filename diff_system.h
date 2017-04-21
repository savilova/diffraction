#ifndef DIFF_SYS
#define DIFF_SYS

#include <iostream>
using namespace std;

void draw_mat(int w, int h, int *data);



class diff_system
{
public:
    int scale, n_cols, n_rows;
    int n_size;
    int wave; //длина волны, нм
    double k; //волновое число, 1/нм
    double z; //расстояние от (0,0) на препятствии до (0,0) на экране, мкм
    int rows; //число рассматриваемых отрезков dy
    int cols; //число рассматриваемых отрезков dx
    int m_size; //размер массива
    int *f_0; //матрица прозрачности препятствия, единицы - ?
    int *f_z; // матрица интенсивности в плоскости экрана, единицы - ?
    int cell; //длина dx и dy, мкм



    //самый полный конструктор
    diff_system(int sc, int w, double z, int r, int c, int *f)
    {
        wave = w;
        k  = 2*3.1416/wave;
        this->z = z;
        rows = r;
        cols = c;
        m_size = rows*cols;
        f_0 = f;
        scale = sc;
        n_size = scale*scale*m_size;
        n_cols = scale*cols;
        n_rows = scale*rows;
        f_z = new int [n_size];
        for(int i=0; i<n_size; i++) f_z[i]=255;
        cell = 10;
        draw_mat(cols,rows,f_0);
        draw_mat(n_cols,n_rows,f_z);

        //TODO
    }

    //деструктор
    ~diff_system()
    {
        delete [] f_0;
        delete [] f_z;
    }

    //подсчет поля в плоскости z по принципу Гюйгенса-Френеля
    void transform()
    {
        cout << "Hello!This is transform function!" << endl;

        double * Re_G_table = new double [n_size];
        double * Im_G_table = new double [n_size];

        cout << "tables initialized" << endl;

        double Re_Sum = 0;
        double Im_Sum = 0;
        double Re_per_Sum = 0;
        double Im_per_Sum = 0;
        double R = z;


        int ksi = 0;
        int eta = 0;
        int x = 0;
        int y = 0;

        cout << "variables initialized" << endl;
        cout << "starting transform..." << endl;

        for (int i = 0; i < n_size; i++) //перебор точек в плоскости экрана (x,y)
        {

            x = cell*(i%n_cols);
            y = cell*((i - x)/n_cols);





            for (int j = 0; j < m_size; j++) //перебор точек в плоскости f_0 (ksi,eta)
            {
                ksi = cell*(j%cols);
                eta = cell*((j-ksi)/cols);

                R = sqrt(pow(z,2)+pow(x-ksi,2)+pow(y-eta,2));


                Re_per_Sum = f_0[j] * z * sin(1000*k*R)/(wave*R*R);
                Re_Sum += Re_per_Sum;

                Im_per_Sum = f_0[j] * z * cos(1000*k*R)/(wave*R*R);
                Im_Sum += Im_per_Sum;

            }

            Re_G_table[i] = Re_Sum;
            Im_G_table[i] = Im_Sum;
            Re_Sum = 0;
            Im_Sum = 0;

        if ((int)(100*i/n_size)!=((int)(100*(i-1)/n_size))) cout << (int)(100*i/n_size) << "% calculations completed"<< endl;
        }
        cout<<"End of field calculations"<< endl;

        for (int i = 0; i < n_size; i++)
        {
              f_z[i] = (int)(pow(10,9)*(pow(Re_G_table[i],2) + pow(Im_G_table[i],2)));
               if ((int)(100*i/n_size)!=((int)(100*(i-1)/n_size))) cout << (int)(100*i/n_size) << "% intensity calculations completed"<< endl;

        }

        cout << "drawing..." << endl;

       draw_mat(n_cols, n_rows, f_z);

        cout << "still okay " << endl;
        delete [] Re_G_table;
        delete [] Im_G_table;
        cout << "still okay after matrix clean" << endl;


    }
};


#endif // DIFF_SYS
