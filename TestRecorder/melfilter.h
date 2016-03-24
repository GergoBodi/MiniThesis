#ifndef MELFILTER_H
#define MELFILTER_H

#include <globalvars.h>

class melFilter
{

public:
    explicit melFilter();

    float m_filterCentersInHZ[MEL_SPEKTRUM_SIZE];

    struct melFilterStruct{
      int startIndex;
      int filterLength;
      float* filterWeights;
    };

    melFilterStruct m_melFilterStructs[MEL_SPEKTRUM_SIZE];

    float melScale(float freq);
    float melScaleInverse(float melval);
    void melFiltering(float* spectrum, float p_melSpektrum[MEL_SPEKTRUM_SIZE]);
    float m_filter(float *Centers, int i, float k);
};

#endif // MELFILTER_H
