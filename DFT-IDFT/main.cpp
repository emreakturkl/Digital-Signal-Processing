#include <iostream>
#include <cstring>
#include <cmath>

#define PI 3.14159265

using namespace std;

// Real Discrete Fourier Transform
void DFT(double *x, int n_size, double *ReX, double *ImX)
{
    int N = n_size;
    int K = N/2 + 1;
    for(int k=0; k < K; k++)
    {
        ReX[k] = 0;
        ImX[k] = 0;
        for(int i=0; i < N; i++)
        {
            ReX[k] += x[i] * cos(2*PI*k*i/N);
            ImX[k] -= x[i] * sin(2*PI*k*i/N);
        }
    }
}
//  Real Inverse Discrete Fourier Transform
void IDFT(double *ReX, double *ImX, double *x, int n_size)
{
    int N = n_size;
    int K = N/2 + 1;

    for(int k=0; k < K; k++)
    {
        ReX[k] =  ReX[k] / (N/2);
        ImX[k] = -ImX[k] / (N/2);
    }

    ReX[0]   /= 2;
    ReX[N/2] /= 2;

    for(int i=0; i<N; i++)
    {
        x[i] = 0;
        for(int k=0; k < K; k++)
        {
            x[i] += (ReX[k] * cos(2*PI*k*i/N) + ImX[k] * sin(2*PI*k*i/N));
        }
    }
}

int main()
{

    int N = 4;
    int K = N/2 + 1;
    double x[] = {17,0,0,0};

    double *ReX = new double[K];
    double *ImX = new double[K];

    DFT(x, N, ReX, ImX);


    double r[] = {2,2,2};
    double i[] = {0,0,0};
    double *y = new double[N];
    IDFT(r, i, y, N);


    for(int i=0; i < K; i++)
        printf("%.2lf\n",ReX[i]);

    cout<<endl;

    for(int i=0; i < N; i++)
        printf("%.2lf\n",y[i]);
    cout<<endl;


    delete ReX;
    delete Imx;
    delete y;
    return 0;
}
