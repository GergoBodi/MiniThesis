#include "fft.h"

FFT::FFT()
{

}

void FFT::RealFFTf(float *xfftBuffer, float *yfftBuffer, int length)
{
    int m = ceil(log(length)/log(2));

    /* Calculate the number of points */
    int n = 1;
    for (int i = 0; i < m; i++) {
        n *= 2;
    }

    /* Do the bit reversal */
    int i1, i2 = n >> 1; // i2 = n/2;
    int j = 0, k = 0;
    float tx, ty;

    for (int i = 0; i < n-1; i++) {
        if (i < j) {
            tx = xfftBuffer[i];
            ty = yfftBuffer[i];
            xfftBuffer[i] = xfftBuffer[j];
            yfftBuffer[i] = yfftBuffer[j];
            xfftBuffer[j] = tx;
            yfftBuffer[j] = ty;
        }
        k = i2;
        while (k <= j) {
            j -= k;
            k /= 2;
        }
        j += k;
    }

    /* Compute the FFT */
    float c1 = -1.0;
    float c2 = 0.0;
    float l1 = 0.0;
    int l2 = 1;
    float u1, u2, t1, t2, z;
    for (int l = 0; l < m; l++) {
        l1 = l2;
        l2 *= 2;
        u1 = 1.0;
        u2 = 0.0;
        for (int j = 0; j < l1; j++) {
            for (int i = j; i < n; i+=l2) {
                i1 = i + l1;
                t1 = u1 * xfftBuffer[i1] - u2 * yfftBuffer[i1];
                t2 = u1 * yfftBuffer[i1] + u2 * xfftBuffer[i1];
                xfftBuffer[i1] = xfftBuffer[i] - t1;
                yfftBuffer[i1] = yfftBuffer[i] - t2;
                xfftBuffer[i] += t1;
                yfftBuffer[i] += t2;
            }
            z =  u1 * c1 - u2 * c2;
            u2 = u1 * c2 + u2 * c1;
            u1 = z;
        }
        c2 = sqrt((1.0 - c1) / 2.0);
        c2 = -c2;
        c1 = sqrt((1.0 + c1) / 2.0);
    }
}
