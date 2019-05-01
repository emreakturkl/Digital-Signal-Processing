#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

// The Input Side Algorithm
void conv(double *s, int s_size, double *h, int h_size, double *y, int y_size)
{
    memset(y, 0, y_size * sizeof(double));
    for(int i=0; i < s_size; i++)
    {
        for(int j=0; j<h_size; j++){
            y[i+j] += s[i] * h[j];
        }
    }
}

// The Output Side Algorithm
void conv1(double *s, int s_size, double *h, int h_size, double *y, int y_size)
{
    memset(y, 0, y_size * sizeof(double));
    for(int i=0; i<y_size; i++)
    {
        for(int j=0; j<h_size; j++){
            if(i-j < 0 || i-j > s_size)
                continue;
            else
                y[i] = y[i] + h[j] * s[i-j];
        }
    }
}

int main()
{
    int s_size = 5 , h_size = 2;
    int y_size = s_size + h_size - 1;

    double x[] = {1,2,3,4,5};
    double h[] = {1,2};
    double *y = new double[y_size];

    conv(x, s_size, h, h_size, y, y_size);

    for(int i=0; i < y_size; i++)
        cout<<y[i]<<"\t";
    cout<<endl;

    delete y;
    return 0;
}
