#ifndef DIFF_SYS
#define DIFF_SYS

#include <iostream>
using namespace std;

void draw_mat(int Wave, int h, int *data);
class diff_system
{
public:
    int o_pixel_size; // Размер пикселя препядствия в микронах
    int s_pixel_size; // Размер пикселя результирующей картины в микронах
    int wave; // Длина волны в нанометрах
    double k; // Волновое число, 1/нм
    double z; // Расстояние от (0,0) на препятствии до (0,0) на экране, мкм
    int o_cols, o_rows, o_size; // Числа рассматриваемых отрезков d_ksi, d_eta и клеток в препятствии (obsticle)
    int s_cols, s_rows, s_size; // Числа рассматриваемых отрезков d_x, d_y и клеток на экране (screen)
    int *Obstacle;  // Матрица препядствия
    int *Intensity; // Матрица интенсивности

    // Конструктор
    diff_system(int o_pixel_size, int s_pixel_size, int wave, double z, int o_cols, int o_rows, int *Obstacle);

    // Деструктор
    ~diff_system(void);

    // Подсчет поля в плоскости z по принципу Гюйгенса-Френеля
    void transform(void);

};

// Конструктор
diff_system::diff_system(int o_pixel_size, int s_pixel_size, int wave, double z, int o_cols, int o_rows, int *Obstacle)
{
    this->o_pixel_size = o_pixel_size;
    this->s_pixel_size = s_pixel_size;
    this->wave = wave;
    this->z = z;
    this->o_cols = o_cols;
    this->o_rows = o_rows;
    this->Obstacle = Obstacle;
    k  = 2*3.1416/wave;
    //! FIXME (Аня#2#): На самом деле obstacle сейчас задает пропукаемость, а в Obstacle нам нужно поле
    //! FIXME (Аня#1#): Масштаб только для квадратов
    o_size = o_cols*o_rows;
    s_cols = 1920;
    s_rows = 1080;
    s_size = s_cols*s_rows;
    Intensity = new int [s_size]; // Full HD 1920X1080
    for(int i = 0; i < s_size; i++)
        Intensity[i] = 0; // По умолчанию экран не освещен
}

diff_system::~diff_system(void)
{
    delete [] Obstacle;
    delete [] Intensity;
}

void diff_system::transform(void)
{
    //! FIXME (Аня#1#): Дифракционная картина пока повернута на 90 градусов
    //! FIXME (Аня#1#): Что-то странное происходит на малых расстояниях до экрана
    //! FIXME (Аня#1#): Возможно интенсивность слишком медленно падает в зависимости от R?

    cout << "Hello!This is transform function!" << endl;

    double * Re_G_table = new double [s_size]; // Матрица поля G действительные значения
    double * Im_G_table = new double [s_size]; // Матрица поля G мнимые значения
    double * dIntensity = new double [s_size]; //Матрица интенсивностей в double

    double R = z;

    int ksi = 0;
    int eta = 0;
    int x = 0;
    int y = 0;

    cout << "variables initialized" << endl;
    cout << "starting transform..." << endl;

    for (int i = 0; i < s_size; i++) // Перебор точек в плоскости экрана (x,y)
    {
        //! FIXME (Аня#1#): Отцентрировать экран - сейчас препятствие задвинуто в левый верхний угол проекции экрана

        // Ищем физические координаты центра площадки dx*dy
        x =  s_pixel_size/2 + s_pixel_size*(i%s_cols);
        y =  s_pixel_size/2 + s_pixel_size*((i - i%s_cols)/s_cols);

        // Обнуляем поле в данной точке экрана
        Re_G_table[i] = 0;
        Im_G_table[i] = 0;

        // Интегрирование для одной точки экрана
        for (int j = 0; j < o_size; j++) // Перебор точек в плоскости Obstacle (ksi,eta)
        {

            // Ищем физические координаты центра площадки d_ksi*d_eta
            ksi = o_pixel_size/2 + o_pixel_size*(j%o_cols);
            eta = o_pixel_size/2 + o_pixel_size*((j-j%o_cols)/o_cols);

            //Считаем расстояние от точки на препятствии до точки на экране
         //   R = sqrt(pow(z,2)+pow(x-ksi,2)+pow(y-eta,2));

            //! (1/i*wave) внесен под знак интеграла
            // Вклад одной точки препятствия в поле текущей точки на экране в единицах B/мкм^2
           // Re_G_table[i] += Obstacle[j] * z * sin(0.001*k*R)/(wave*R*R*1000);

            // Теперь для мнимой части амплитуды в единицах B/мкм^2
            //Im_G_table[i] += Obstacle[j] * z * cos(0.001*k*R)/(wave*R*R*1000);

            // Вклад одной точки препятствия в поле текущей точки на экране в единицах B/мкм^2
            Re_G_table[i] += Obstacle[j] * sin(0.001*k*z+0.0005*k*(pow(x-ksi,2)+pow(y-eta,2))/z)/(wave*z);

            // Теперь для мнимой части амплитуды в единицах B/мкм^2
            Im_G_table[i] += Obstacle[j] * cos(0.001*k*z+0.0005*k*(pow(x-ksi,2)+pow(y-eta,2))/z)/(wave*z);


        }

        // Процентное выполнение подсчёта мнимой и действительной частей
        if ((100*i/s_size) != (100*(i-1)/s_size))
            cout << (int)(100*i/s_size) << "% calculations completed (Re and Im)"<< endl;
    }
    cout<<"End of field calculations"<< endl;

    // New! Ищем максимум и минимум, чтобы потом отнормировать, чтобы картина была контрастнее
    double MAX = pow(Re_G_table[0],2) + pow(Im_G_table[0],2);
    double MIN = MAX;

    // Считаем интенсивность в плоскости экрана
    for (int i = 0; i < s_size; i++)
    {
        //! FIXME (Аня#1#): нужно сделать подгон интенсивностей, после того как разберемся с единицами измерения
        dIntensity[i] = pow(Re_G_table[i],2) + pow(Im_G_table[i],2);
        if (dIntensity[i] > MAX)
            MAX = dIntensity[i];

        if (dIntensity[i] < MIN)
            MIN = dIntensity[i];

        // Процентное выполнение подсчёта double интенсивности
        if ((100*i/s_size) != (100*(i-1)/s_size))
            cout << (int)(100*i/s_size) << "% calculations completed (dIntensity)"<< endl;
    }
    MAX -= MIN;
    //Проводим нормировку: максимум -> 255, минимум -> 0
    for (int i = 0; i < s_size; i++)
    {
        Intensity[i] = (int)(((dIntensity[i] - MIN)/MAX)*255);
        if ((100*i/s_size) != (100*(i-1)/s_size))
            cout << (int)(100*i/s_size) << "% calculations completed (Intensity)"<< endl;
    }

    cout << "drawing..." << endl;

  //  draw_mat(s_cols, s_rows, Intensity);

    cout << "still okay " << endl;
    delete [] Re_G_table;
    delete [] Im_G_table;
    cout << "still okay after matrix clean" << endl;

}

#endif // DIFF_SYS
