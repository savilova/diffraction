#ifndef DIFF_SYS
#define DIFF_SYS

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

#endif // DIFF_SYS
