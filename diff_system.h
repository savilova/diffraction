#ifndef DIFF_SYS
#define DIFF_SYS

#include <iostream>


class diff_system
{
public:
    int wave;
    float k;
    float z;
    int row;
    int col;
    int **f_0;
    int **f_z;
    int Size;

    
    //конструктор
    diff_system(int ** f){
        wave = 532;
        k  = 2*3.1416/wave;
        z = 2;
        row = 50;
        col = 50;
        f_0 = f;     
        Size = 10;
        //TODO


    }
     
    //деструктор 
    ~diff_system(){
        //TODO
    }

    //подсчет поля в плоскости z по принципу Гюйгенса-Френеля(интеграл)
    void transform(){
    std::cout << "Hello!This is transform function!" << std::endl; 
    for (int i = 0; i<row; i++){
        for(int j = 0; j<col; j++){
            std::cout << f_0[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "Done!" << std::endl;
    
        //TO DO
        /*
        интенсивность (вещ. число от 0 до 1) предлагаю пока умножать на 100 и округлять до интов.
        распечатывать пока только матрицу интенсивностей, как обычно в ostream.
        */
        //в длинном комменте - первая версия интеграла

        
    
        double PI =  3.141592;
        int ** Re_G_table = new int * [50];
        int ** Im_G_table = new int * [50];
        for (int x = 0; x < row; x++)
        {
        for (int y = 0; y < col; y++)
        {
            int Re_Sum = 0;
            int Im_Sum = 0;
            for (int r = 0; r < row; r++)  
            {
                for (int c = 0; c < col; c++)
                {
                    int R = sqrt(pow(z,2)+pow((Size/1000)*(x-r),2)+pow((Size/1000)*(y-c),2));  
                    int cosinus = z/R;   
                    int Re_per_Sum = f_0[r][c] * (cosinus/R) *cos(k*pow(10,9)/R);
                    int Im_per_Sum = f_0[r][c] * (cosinus/R) *sin(k*pow(10,9)/R); 
                    Re_Sum += Re_per_Sum*pow((Size/1000),2);
                    Im_Sum += Im_per_Sum*pow((Size/1000),2);
                }
            }
            Re_G_table[x][y] = Re_Sum/wave;
            Im_G_table[x][y] = Im_Sum/wave;
        }
        }
        
        for (int x = 0; x < row; x++)  
        {
        for (int y = 0; y < col; y++)
        {
            f_z[x][y] = pow(Re_G_table[x][y],2) + pow(Im_G_table[x][y],2);
            std::cout<<f_z[x][y];
        }
            std::cout << std::endl;
        }

        for (int i = 0; i < row; i++) 
        {
        delete [] Re_G_table[i];
        }
        delete [] Re_G_table;

        for (int i = 0; i < row; i++) 
        {
        delete [] Im_G_table[i];
        }
        delete [] Im_G_table;
    
}
};

#endif // DIFF_SYS