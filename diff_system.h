#ifndef DIFF_SYS
#define DIFF_SYS

#include <iostream>
using namespace std;

void draw_mat(int w, int h, int *data);



class diff_system
{
public:
    int cell; //!физическая длина dx(d_ksi) и dy(d_eta), мкм
    int scale; //!отношение стороны экрана к стороне препятствия
    int wave; //!длина волны, нм
    double k; //!волновое число, 1/нм
    double z; //!расстояние от (0,0) на препятствии до (0,0) на экране, мкм
    int o_cols, o_rows, o_size; //! числа рассматриваемых отрезков d_ksi, d_eta и клеток в препятствии (obsticle)
    int s_cols, s_rows, s_size; //! числа рассматриваемых отрезков d_x, d_y и клеток на экране (screen)
    int *f_0; //! скалярная амплитуда поля в плоскости z_0+, единицы - ?
    int *f_z; //! интенсивность в плоскости экрана, единицы - ?

    //самый полный конструктор
    diff_system(int sc, int w, double z, int r, int c, int *f)
    {
        wave = w;
        k  = 2*3.1416/wave;
        this->z = z;
        o_rows = r;
        o_cols = c;
        o_size = o_rows*o_cols;
        //! FIXME (Аня#2#): на самом деле f сейчас задает пропукаемость, а в f_0 нам нужно поле
        f_0 = f;
        //! FIXME (Аня#1#): масштаб только для квадратов
        scale = sc;
        s_size = pow(scale,2)*o_size;
        s_cols = scale*o_cols;
        s_rows = scale*o_rows;
        f_z = new int [s_size];
        for(int i=0; i<s_size; i++) f_z[i]=0; //по умолчанию экран не освещен
        cell = 100; //микроны

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
        //! FIXME (Аня#1#): дифракционная картина пока повернута на 90 градусов
        //! FIXME (Аня#1#): что-то странное происходит на малых расстояниях до экрана
        //! FIXME (Аня#1#): возможно интенсивность слишком медленно падает в зависимости от R?


        cout << "Hello!This is transform function!" << endl;

        double * Re_G_table = new double [s_size]; //!Матрица поля G действительные значения
        double * Im_G_table = new double [s_size]; //!Матрица поля G мнимые значения

        double Re_Sum, Im_Sum;
        double Re_per_Sum = 0; //!Промежуточные значения суммы поля в каждой клетке
        double Im_per_Sum = 0;
        double R = z;

        int ksi = 0;
        int eta = 0;
        int x = 0;
        int y = 0;

        cout << "variables initialized" << endl;
        cout << "starting transform..." << endl;

        for (int i = 0; i < s_size; i++) //перебор точек в плоскости экрана (x,y)
        {
            //! FIXME (Аня#1#): отцентрировать экран - сейчас препятствие задвинуто в левый верхний угол проекции экрана

            // ищем физические координаты центра площадки dx*dy
            x =  cell/2 + cell*(i%s_cols);
            y =  cell/2 + cell*((i - i%s_cols)/s_cols);

            //обнуляем поле в данной точке экрана
            Re_Sum = 0;
            Im_Sum = 0;

            //интегрирование для одной точки экрана
            for (int j = 0; j < o_size; j++) //перебор точек в плоскости f_0 (ksi,eta)
            {

                // ищем физические координаты центра площадки d_ksi*d_eta
                ksi = cell/2 + cell*(j%o_cols);
                eta = cell/2 + cell*((j-j%o_cols)/o_cols);

                //считаем расстояние от точки на препятствии до точки на экране
                R = sqrt(pow(z,2)+pow(x-ksi,2)+pow(y-eta,2));

                //! (1/i*wave) внесен под знак интеграла

                Re_per_Sum = f_0[j] * z * sin(0.001*k*R)/(wave*R*R*1000); //вклад одной точки препятствия в поле текущей точки на экране в единицах B/мкм^2
                Re_Sum += Re_per_Sum; //суммирование по всем точкам препятствия

                Im_per_Sum = f_0[j] * z * cos(0.001*k*R)/(wave*R*R*1000); // то же для мнимой части амплитуды в единицах B/мкм^2
                Im_Sum += Im_per_Sum;

            }

            //значение суммарного поля в точке на экране
            Re_G_table[i] = Re_Sum;
            Im_G_table[i] = Im_Sum;

            // прогресс бар
            // it`s not stupid if it works :)
            if ((int)(100*i/s_size)!=((int)(100*(i-1)/s_size))) cout << (int)(100*i/s_size) << "% calculations completed"<< endl;
        }
        cout<<"End of field calculations"<< endl;

        //считаем интенсивность в плоскости экрана
        for (int i = 0; i < s_size; i++)
        {
            //! FIXME (Аня#1#): нужно сделать подгон интенсивностей, после того как разберемся с единицами измерения
            f_z[i] = (int)(pow(10,18)*(pow(Re_G_table[i],2) + pow(Im_G_table[i],2)));
     //       cout << "pow(10,12) * " << (pow(Re_G_table[i],2) + pow(Im_G_table[i],2)) << endl;
     //       cout << "f_z[" << i <<"] = " << f_z[i] << endl;
            // прогресс бар
            if ((int)(100*i/s_size)!=((int)(100*(i-1)/s_size))) cout << (int)(100*i/s_size) << "% intensity calculations completed"<< endl;

        }

        cout << "drawing..." << endl;

        draw_mat(s_cols, s_rows, f_z);

        cout << "still okay " << endl;
        delete [] Re_G_table;
        delete [] Im_G_table;
        cout << "still okay after matrix clean" << endl;


    }
};


#endif // DIFF_SYS
