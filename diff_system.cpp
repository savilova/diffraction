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

    pixel = 1000; // стандартный экран 40х40 см
    width = 400;
    size = width*width;
    z = 2000000; // 2 м до экрана
    obs = new obstacle(); //препятствие по умолчанию
    intensity = new int[size];
    for (int i = 0; i < size; i++) intensity[i] = 0; // по умолчанию экран не освещен
}

// Конструктор
diff_system::diff_system(int magnitude, int pixel, int wave, double z, obstacle * obs)
{
    this->magnitude = magnitude; // от балды
    this->wave = wave; // зеленый лазер
    k = 2*3.141593/wave;
    this->pixel = pixel; // стандартный экран 40х40 см
    width = 400;
    size = width*width;
    this->z = z; // 2 м до экрана
    this->obs = obs;
    intensity = new int[size];
    for (int i = 0; i < size; i++) intensity[i] = 0; // по умолчанию экран не освещен
}

diff_system::~diff_system(void)
{
}

void diff_system::transform(void)
{
    //! FIXME (Аня#1#): Дифракционная картина пока повернута на 90 градусов
    //! FIXME (Аня#1#): Что-то странное происходит на малых расстояниях до экрана

    cout << "Hello!This is transform function!" << endl;

//    double * Re_G_table = new double [s_size]; // Матрица поля G действительные значения
//    double * Im_G_table = new double [s_size]; // Матрица поля G мнимые значения
//    double * dIntensity = new double [s_size]; //Матрица интенсивностей в double

//    double R = z;

//    int ksi = 0;
//    int eta = 0;
//    int x = 0;
//    int y = 0;

//    cout << "variables initialized" << endl;
//    cout << "starting transform..." << endl;

//    for (int i = 0; i < s_size; i++) // Перебор точек в плоскости экрана (x,y)
//    {
//        //! FIXME (Аня#1#): Отцентрировать экран - сейчас препятствие задвинуто в левый верхний угол проекции экрана

//        // Ищем физические координаты центра площадки dx*dy
//        x =  s_pixel_size/2 + s_pixel_size*(i%s_cols);
//        y =  s_pixel_size/2 + s_pixel_size*((i - i%s_cols)/s_cols);

//        // Обнуляем поле в данной точке экрана
//        Re_G_table[i] = 0;
//        Im_G_table[i] = 0;

//        // Интегрирование для одной точки экрана
//        for (int j = 0; j < o_size; j++) // Перебор точек в плоскости Obstacle (ksi,eta)
//        {

//            // Ищем физические координаты центра площадки d_ksi*d_eta
//            ksi = o_pixel_size/2 + o_pixel_size*(j%o_cols);
//            eta = o_pixel_size/2 + o_pixel_size*((j-j%o_cols)/o_cols);

//            //Считаем расстояние от точки на препятствии до точки на экране
//           // R = sqrt(pow(z,2)+pow(x-ksi,2)+pow(y-eta,2));

//            //! (1/i*wave) внесен под знак интеграла
//            // Вклад одной точки препятствия в поле текущей точки на экране в единицах B/мкм^2
//            Re_G_table[i] += Obstacle[j] * sin(0.001*k*z+0.0005*k*(pow(x-ksi,2)+pow(y-eta,2))/z)/(wave*z*1000);

//            // Теперь для мнимой части амплитуды в единицах B/мкм^2
//            Im_G_table[i] += Obstacle[j] * cos(0.001*k*z+0.0005*k*(pow(x-ksi,2)+pow(y-eta,2))/z)/(wave*z*1000);
//            // Вклад одной точки препятствия в поле текущей точки на экране в единицах B/мкм^2
//           // Re_G_table[i] += Obstacle[j] * z * sin(0.001*k*R)/(wave*R*R*1000);

//            // Теперь для мнимой части амплитуды в единицах B/мкм^2
//            //Im_G_table[i] += Obstacle[j] * z * cos(0.001*k*R)/(wave*R*R*1000);


//        }

//        // Процентное выполнение подсчёта мнимой и действительной частей
//        if ((100*i/s_size) != (100*(i-1)/s_size))
//            cout << (int)(100*i/s_size) << "% calculations completed (Re and Im)"<< endl;
//    }
//    cout<<"End of field calculations"<< endl;

//    // New! Ищем максимум и минимум, чтобы потом отнормировать, чтобы картина была контрастнее
//    double MAX = pow(Re_G_table[0],2) + pow(Im_G_table[0],2);
//    double MIN = MAX;

//    // Считаем интенсивность в плоскости экрана
//    for (int i = 0; i < s_size; i++)
//    {
//        //! FIXME (Аня#1#): нужно сделать подгон интенсивностей, после того как разберемся с единицами измерения
//        dIntensity[i] = pow(Re_G_table[i],2) + pow(Im_G_table[i],2);
//        if (dIntensity[i] > MAX)
//            MAX = dIntensity[i];

//        if (dIntensity[i] < MIN)
//            MIN = dIntensity[i];

//        // Процентное выполнение подсчёта double интенсивности
//        if ((100*i/s_size) != (100*(i-1)/s_size))
//            cout << (int)(100*i/s_size) << "% calculations completed (dIntensity)"<< endl;
//    }
//    MAX -= MIN;
//    //Проводим нормировку: максимум -> 255, минимум -> 0
//    for (int i = 0; i < s_size; i++)
//    {
//        Intensity[i] = (int)(((dIntensity[i] - MIN)/MAX)*255);
//        if ((100*i/s_size) != (100*(i-1)/s_size))
//            cout << (int)(100*i/s_size) << "% calculations completed (Intensity)"<< endl;
//    }

//    cout << "drawing..." << endl;

//    draw_mat(s_cols, s_rows, Intensity);

//    cout << "still okay " << endl;
//    delete [] Re_G_table;
//    delete [] Im_G_table;
//    cout << "still okay after matrix clean" << endl;

}
