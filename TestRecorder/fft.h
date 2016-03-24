#ifndef FFT_H
#define FFT_H

#include <qmath.h>

class FFT
{
public:
    FFT();

    void RealFFTf(float* xfftBuffer, float* yfftBuffer, int length);
};

#endif // FFT_H
