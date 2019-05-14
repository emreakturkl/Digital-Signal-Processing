#include <iostream>
#include <cstring>
#include <cmath>

#define SAMPLE_RATE 20000

using namespace std;

// Generate Sinus Wave
double* sinWave(int N, double amp, double freq)
{
    double *data = new double[N];
    for(int i=0; i < N; i++)
        data[i] = amp * sin((2 * M_PI * freq) * ((double)i / SAMPLE_RATE));
    return data;
}
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

int main()
{
    // sin parameters
    int N    = 100;
    int amp  = 10;
    int freq = 5000;

    int s_size = N;
    int h_size = 5;
    int y_size = s_size + h_size - 1 ;

    double *s = sinWave(N, amp, freq);
    double *y = new double[y_size];

    double h[5];
    h[0] = 0.075037080444813233914835848281654762104;
	h[1] = 0.284218843522212105678903526495560072362;
	h[2] = 0.381488152065949326363636373571353033185;
	h[3] = 0.284218843522212105678903526495560072362;
	h[4] = 0.075037080444813233914835848281654762104;

    conv(s, s_size, h, h_size, y, y_size);

    for(int i=0; i<100; i++)
        printf("sin[%d] = %f \n",i, s[i]);

    for(int i=0; i<y_size; i++)
        printf("y[%d] = %f \n",i, y[i]);

    delete y;

    return 0;
}
