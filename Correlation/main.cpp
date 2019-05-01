#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

// Cross Correlation
void xcorr(double *s, int s_size, double *h, int h_size, double *y, int y_size)
{
    double *s1 = new double[y_size];
    double *s2 = new double[y_size];

    for(int i=0; i < s_size; i++)
    {
        if(i > s_size-1)
            s1[0] = 0;
        else
            s1[i] = s[i];
    }

    for(int i=0; i < h_size; i++)
    {
        if(i > h_size-1)
            s2[0] = 0;
        else
            s2[i] = h[i];
    }

    for(int i=0; i < y_size; i++)
    {
        y[i] = 0;
        for(int j=0; j < y_size; j++)
        {
            if(j-i < 0)
                y[i] += s1[j] * s2[j-i + y_size];
            else
                y[i] += s1[j] * s2[j-i];
        }
    }

    delete s1;
    delete s2;
}

int main()
{
    int s_size = 4 , h_size = 3;
    int y_size = s_size + h_size - 1;

    double x[] = {4,3,1,6};
    double h[] = {5,2,3};
    double *y = new double[y_size];

    xcorr(x, s_size, h, h_size, y, y_size);

    for(int i=0; i < y_size; i++)
        cout<<y[i]<<"\t";
    cout<<endl;

    delete y;
    return 0;
}
