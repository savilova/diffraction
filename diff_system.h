#ifndef DIFF_SYS
#define DIFF_SYS
#include "obstacle.h"

class diff_system
{
public:
    //Свойства света
    double magnitude; //амплитуда падающей плоской волны
    double wave; // Длина волны в нанометрах
    double k; // Волновое число, 1/нм
    //Свойства экрана
    double pixel; // Физический размер пикселя результирующей картины в микронах
    int width, size; // Числа рассматриваемых отрезков d_x, d_y и клеток на экране
    //Прочее
    double z; // Расстояние от (0,0) на препятствии до (0,0) на экране, мкм
    obstacle * o; // препятствие, которое мы ставим в систему
    int * Intensity; // Матрица интенсивности (конечная картинка)

    // Конструктор по умолчанию
    diff_system();
    // Конструктор
    diff_system(int magnitude, int pixel, int wave, double z, obstacle * o);

    // Деструктор
    ~diff_system(void);

    // Подсчет поля в плоскости z по принципу Гюйгенса-Френеля
    void transform(void);

};
#endif // DIFF_SYS
