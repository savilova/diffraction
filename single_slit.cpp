#include "obstacle.h"
#include "single_slit.h"

void single_slit::generate_data(double horizontal, double vertical){
    bool isVertical = false;
    if (horizontal == 0 || vertical == 0) break; //нельзя задавать размеры 0
    int min = 1; //минимальный размер щели определяет физический размер единичной площадки
    int max = 1; //при отношении 1:1 в матрице будет 1 элемент
    if (horizontal > vertical) {
        max = horizontal;
        min = vertical;
    }
    else {
        isVertical = true;
        max =vertical;
        min = horizontal;
    }
    int size =(int)(max/min);
    while(abs(max/min - (int)(max/min))>0.02*(max/min)){
        size*=2; // точность отношения 2%
    }

    if (size % 2 == 0) size++;
    int * data = new int [size*size];
    if (isVertical){
        for (int i = 0; i<size*size; i++){
            if (i%size + 1 == (size-1)/2 + 1) data[i] = 255;
            else data[i] = 0;
        }
    }
    else{
        for (int i = 0; i<size*size; i++){
            if((i-i%size)%size+1 == (size-1)/2 + 1) data[i]=255;
            else data[i]=0;
        }
    }
   this->data = data;
}

