#ifndef DIFF_SYS
#define DIFF_SYS

#include <iostream>


class diff_system
{
public:
    int wave;
    float k;
    float z;
    int M;
    int N;
    int **f_0;
    int **f_z;

    
    //конструктор
    diff_system(int ** f){
        wave = 532;
        k  = 2*3.1416/wave;
        z = 2;
        M = 50;
        N = 50;
        f_0 = f;            
        //TODO


    }
     
    //деструктор 
    ~diff_system(){
        //TODO
    }

    //подсчет поля в плоскости z по принципу Гюйгенса-Френеля(интеграл)
    void transform(){
    std::cout << "Hello!This is transform function!" << std::endl; 
    for (int i = 0; i<M; i++){
        for(int j = 0; j<N; j++){
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
    /*
        int lyambda, z;
        const int Size = 10; 
        int row,col;
    
        ifstream fin ("painting.txt");
        string str;
        getline(fin, str);
        cout << str << endl;

        int ** data = new int * [row];
        for (int r=0; r < row; r++)
        {
        data [r] = new int [col];
        for (int c=0; c < col; c++)
        {

            fin >> data[r][c];

        }
        }
        fin.close();

        for (int r=0 ;r<row ;r++)
        {
        for (int c = 0; c < col; c++)
        {
            cout << data[r][c];
        }
        }
        
        const double PI =  3.141592;
        int ** Re_G_table = new int * [row];
        int ** Im_G_table = new int * [row];
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
                    int Re_per_Sum = data[r][c] * (cosinus/R) *cos(2*PI*pow(10,9)/(R*lyambda));
                    int Im_per_Sum = data[r][c] * (cosinus/R) *sin(2*PI*pow(10,9)/(R*lyambda)); 
                    Re_Sum += Re_per_Sum*pow((Size/1000),2);
                    Im_Sum += Im_per_Sum*pow((Size/1000),2);
                }
            }
            Re_G_table[x][y] = Re_Sum/lyambda;
            Im_G_table[x][y] = Im_Sum/lyambda;
        }
        }
        int ** intensive = new int * [row];
        for (int x = 0; x < row; x++)  
        {
        for (int y = 0; y < col; y++)
        {
            intensive[x][y] = pow(Re_G_table[x][y],2) + pow(Im_G_table[x][y],2);
        }
        }
    
        delete data;
        delete Re_G_table;
        delete Im_G_table;
        delete intensive;
    */
}
};

#endif // DIFF_SYS