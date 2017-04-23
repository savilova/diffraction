#ifndef DIFF_SYS
#define DIFF_SYS

using namespace std;

double ** create_matrix(int row, int col)
{
        double **f = new double *[row];
        for(int i = 0; i <row; i++)
            f[i] = new double [col];

        return f;
}

class diff_system
{
public:
    int wave; //
    double k;
    double z;
    int row;
    int col;
    int **f_0;
    double **f_z;
    double Size;

    friend double ** create_matrix(int, int);


    //конструктор
    diff_system(int ** f){
        wave = 532;  // длина волны в нм
        k  = 2*3.1416/wave;   // волновой вектор
        z = 2;   // расстояние от препятствия до экрана
        row = 30;   // количество рядов в матрице изображений
        col = 30;  // количество столбцов в матрице изображений
        f_0 = f;
        Size = 10;
        f_z = create_matrix(row, col);
        cout << "Well done!" << endl;
    }

    //деструктор
    ~diff_system(){
        //TODO
    }

    //Подсчет поля в плоскости z по принципу Гюйгенса-Френеля(интеграл)
    void transform()
    {
        double ** Re_G_table = create_matrix(row, col);
        double ** Im_G_table = create_matrix(row, col);

        for (int x = 0; x < row; x++)
        {
            for (int y = 0; y < col; y++)
            {
                double Re_Sum = 0;
                double Im_Sum = 0;

                for (int r = 0; r < row; r++)
                {
                    for (int c = 0; c < col; c++)
                    {
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

        cout<<"For end!"<<endl;
        for (int x = 0; x < row; x++)
        {

            for (int y = 0; y < col; y++)
            {
                //cout << "f_z[x][y] = " << f_z[x][y] << endl;
                f_z[x][y] = pow(Re_G_table[x][y],2) + pow(Im_G_table[x][y],2);
               // cout<<"Hi!"<<endl;
                cout<<f_z[x][y]<<' ';
            }
            cout << endl;
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
