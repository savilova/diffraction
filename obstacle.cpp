#include "obstacle.h"

obstacle::obstacle()
{
    pixel = 10;
    width = 1;
    size = 1;
    calc_data = new int[1];
    calc_data[0] = 1;
    img_data = new int[1];
    img_data[0] = 255;
}

obstacle::obstacle(int w, int * data)
{
    pixel = 10;
    width = w;
    size = width*width;
    this->calc_data = data;

}
