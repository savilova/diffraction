#ifndef OBSTACLE_H
#define OBSTACLE_H


class obstacle
{
public:
    double pixel;
    int width;
    int size;
    int * calc_data;
    int * img_data;
    obstacle();
    obstacle(int width, int * data);
    ~obstacle();
    int * generate_calc_data();
    int * generate_img_data();
};

#endif // OBSTACLE_H
