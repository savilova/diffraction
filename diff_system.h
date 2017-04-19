#ifndef DIFF_SYS
#define DIFF_SYS

#include <iostream>


using namespace std;

class diff_system
{
public:
    int wave;
    double k;
    double z;
    int row;
    int col;
    int **f_0;
    double **f_z;
    double Size;


    //конструктор
    diff_system(int ** f){
        wave = 532;
        k  = 2*3.1416/wave;
        z = 2;
        row = 5;
        col = 5;
        f_0 = f;
        f_z = new double *[5];
        for(int i = 0; i <5; i++)
        {
            f_z[i] = new double [5];
        }
        Size = 10;
        //TODO
    }

    //деструктор
    ~diff_system(){
        //TODO
    }

    //подсчет поля в плоскости z по принципу Гюйгенса-Френеля(интеграл)
    void transform(){
   // std::cout << "Hello!This is transform function!" << std::endl;
    //for (int i = 0; i<row; i++){
      //  for(int j = 0; j<col; j++){
        //    std::cout << f_0[i][j];
        //}
       // std::cout << std::endl;
    //}
    //std::cout << "Done!" << std::endl;

        //TO DO
        /*
        интенсивность (вещ. число от 0 до 1) предлагаю пока умножать на 100 и округлять до интов.
        распечатывать пока только матрицу интенсивностей, как обычно в ostream.
        */
        //в длинном комменте - первая версия интеграла


        int ** Re_G_table = new int * [row];
        for (int i = 0; i< row; i++)
        {
            Re_G_table[i] = new int[col];
        }

        int ** Im_G_table = new int * [row];
        for (int i = 0; i< row; i++)
        {
            Im_G_table[i] = new int[col];
        }


        for (int x = 0; x < row; x++)
        {
//            cout << "X = " << x << " Row = " << row << endl;
        for (int y = 0; y < col; y++)
        {
  //          cout << "Y = " << y << " Col = " << col << endl;
            double Re_Sum = 0;
            double Im_Sum = 0;
            for (int r = 0; r < row; r++)
            {
  //              cout << "R = " << r << " Row = " << row << endl;
                for (int c = 0; c < col; c++)
                {
  //                  cout << "C = " << c << " Col = " << col << endl;
                    double R = sqrt(pow(z,2)+pow((Size/1000)*abs((x-r)),2)+pow((Size/1000)*abs((y-c)),2));
                    double cosinus = z/R;
                    double Re_per_Sum = f_0[r][c] * (cosinus/R) *cos(k*pow(10,9)*R);
                    double Im_per_Sum = f_0[r][c] * (cosinus/R) *sin(k*pow(10,9)*R);
                    Re_Sum += Re_per_Sum*pow((Size/1000),2);
                    Im_Sum += Im_per_Sum*pow((Size/1000),2);
                }
            }
            Re_G_table[x][y] = Re_Sum*pow(10,9)/wave;
            Im_G_table[x][y] = Im_Sum*pow(10,9)/wave;
        }
        }
        std::cout<<"For end!"<<std::endl;
        for (int x = 0; x < row; x++)
        {
  //          cout << "X = " << x << " Row = " << row << endl;
        for (int y = 0; y < col; y++)
        {
          //  cout << "pow(Re_G_table[x][y],2) = " << pow(Re_G_table[x][y],2) << endl;
          //  cout << "pow(Im_G_table[x][y],2) = " << pow(Im_G_table[x][y],2) << endl;
         //   cout << "f_z[x][y] = " << f_z[x][y] << endl;
            f_z[x][y] = pow(Re_G_table[x][y],2) + pow(Im_G_table[x][y],2);
         //   std::cout<<"Hi!"<<std::endl;
            std::cout<<f_z[x][y]<<' ';
        }
            std::cout << std::endl;
        }

        for (int i=0;i<row;i++)
        {
            delete [] Re_G_table[i];
        }
        delete [] Re_G_table;


        for (int i=0;i<row;i++)
        {
            delete [] Im_G_table[i];
        }
        delete [] Im_G_table;

}
};

#endif // DIFF_SYS
