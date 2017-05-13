#ifndef OBSTACLE_H
#define OBSTACLE_H


class obstacle
{
public:
    int pixel_size, cols, size;
    int * data;
    obstacle();
    ~obstacle();

    int * generate_data();
};

#endif // OBSTACLE_H
