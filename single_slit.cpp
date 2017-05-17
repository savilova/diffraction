#include "obstacle.h"
#include "single_slit.h"
#include <math.h>
#include <cmath>


void single_slit::generate_calc_data(){

    int * calc_data = new int[1000];
    for (int i = 0; i<1000; i++ ) calc_data[i] = 1;
    this->calc_data=calc_data;

   }

void single_slit::generate_img_data(){
    int l = 200;
    size = l*l;
    int * img_data = new int[size];
    for (int i = 0; i<size; i++) {
        if (i%size == l/2) img_data[i] = 255;
        else img_data[i] = 0;
    }
    this->img_data = img_data;
}

