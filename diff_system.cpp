#include "diff_system.h"

#include <math.h>
#include <cmath>
#include <iostream>
using namespace std;

//Конструктор по умолчанию
diff_system::diff_system()
{
    magnitude = 100; // от балды
    wave = 532; // зеленый лазер
    k = 2*3.141593/wave;
    pixel = 10000; // стандартный экран 40х40 см
    width = 400;
    size = width*width;
    z = 2000000; // 2 м до экрана
    o = new obstacle(); //препятствие по умолчанию
    Intensity = new int[size];
    for (int i = 0; i < size; i++) Intensity[i] = 0; // по умолчанию экран не освещен

}

// Конструктор
diff_system::diff_system(int magnitude, int pixel, int wave, double z, obstacle * o)
{
    this->magnitude = magnitude; // от балды
    this->wave = wave; // зеленый лазер
    k = 2*3.141593/wave;
    this->pixel = pixel; // стандартный экран 40х40 см
    width = 400;
    size = width*width;
    this->z = z; // 2 м до экрана
    this->o = o;
    Intensity = new int[size];
    for (int i = 0; i < size; i++) Intensity[i] = 0; // по умолчанию экран не освещен

diff_system::~diff_system(void)
{
    delete [] Intensity;

}

void diff_system::transform(void)
{
    //! FIXME (Аня#1#): Дифракционная картина пока повернута на 90 градусов


    cout << "Hello!This is transform function!" << endl;

      double * Re_G_table = new double [size]; // Матрица поля G действительные значения
      double * Im_G_table = new double [size]; // Матрица поля G мнимые значения
      double * dIntensity = new double [size]; //Матрица интенсивностей в double

    double R = z; //мкм
    double ksi = 0;
    double eta = 0;
    double x = 0;
    double y = 0;

    cout << "starting transform..." << endl;

    for (int i = 0; i < size; i++) // Перебор точек в плоскости экрана (x,y)
    {

        // Ищем физические координаты центра площадки dx*dy
        x =  pixel/2 + pixel*(i%width);
        y =  pixel/2 + pixel*((i - i%width)/width);

        // Обнуляем поле в данной точке экрана
        Re_G_table[i] = 0;
        Im_G_table[i] = 0;

        // Интегрирование для одной точки экрана

        for (int j = 0; j < o->size; j++) // Перебор точек в плоскости (ksi,eta)
        {

            // Ищем физические координаты центра площадки d_ksi*d_eta
            ksi = pixel*(int)(width/2) - o->pixel*(int)(o->width/2) + o->pixel/2 + o->pixel*(j%o->width);
            eta = pixel*(int)(width/2) - o->pixel*(int)(o->width/2) + o->pixel/2 + o->pixel*((j-j%o->width)/o->width);


            //Считаем расстояние от точки на препятствии до точки на экране
            R = sqrt(pow(z,2)+pow(x-ksi,2)+pow(y-eta,2));

            //! (1/i*wave) внесен под знак интеграла
            // Вклад одной точки препятствия в поле текущей точки на экране в единицах B/мкм^2


            Re_G_table[i] +=o->calc_data[j]* magnitude * z * sin(0.001*k*R)/(wave*R*R*1000);


           // Теперь для мнимой части амплитуды в единицах B/мкм^2
            Im_G_table[i] +=o->calc_data[j]* magnitude * z * cos(0.001*k*R)/(wave*R*R*1000);
        }

        // Процентное выполнение подсчёта мнимой и действительной частей
        if ((100*i/size) != (100*(i-1)/size))
            cout << (int)(100*i/size) << "% calculations completed (Re and Im)"<< endl;
    }




    cout<<"End of field calculations"<< endl;

   // New! Ищем максимум и минимум, чтобы потом отнормировать, чтобы картина была контрастнее

    double MAX = pow(Re_G_table[0],2) + pow(Im_G_table[0],2);
    double MIN = MAX;

    // Считаем интенсивность в плоскости экрана

    for (int i = 0; i < size; i++)

    {
        //! FIXME (Аня#1#): нужно сделать подгон интенсивностей, после того как разберемся с единицами измерения
        dIntensity[i] = pow(Re_G_table[i],2) + pow(Im_G_table[i],2);
        if (dIntensity[i] > MAX)
            MAX = dIntensity[i];

        if (dIntensity[i] < MIN)
            MIN = dIntensity[i];

        // Процентное выполнение подсчёта double интенсивноси
      
        if ((100*i/size) != (100*(i-1)/size))
            cout << (int)(100*i/size) << "% calculations completed (dIntensity)"<< endl;
    }
    MAX -= MIN;
    //Проводим нормировку: максимум -> 255, минимум -> 0

    for (int i = 0; i < size; i++)
    {
      //  test[i]=(int)(100*dIntensity[i]);
        Intensity[i] = (int)(((dIntensity[i] - MIN)/MAX)*255);
        if ((100*i/size) != (100*(i-1)/size))
            cout << (int)(100*i/size) << "% calculations completed (Intensity)"<< endl;
    }

    cout << "drawing..." << endl;
    draw_mat(width, width, Intensity);
    //draw_mat(width, width, test);
    delete [] Re_G_table;
    delete [] Im_G_table;


}
