#ifndef OBSTACLE_H
#define OBSTACLE_H


class obstacle
{
public:
    double pixel;
    int width;
    int size;
    int * data;
    obstacle();
    ~obstacle();

    int * generate_data();
};

#endif // OBSTACLE_H
