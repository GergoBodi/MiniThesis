#ifndef PARAMETER_H
#define PARAMETER_H

#include <QtCore>
#include <globalvars.h>

class Parameter {

public:
    Parameter();

    void setParameter(float* melSpectrum, float length, float ampl);

    float spektrum[MEL_SPEKTRUM_SIZE];
    int length;
    float amplitude;
    bool inWord;

};

#endif // PARAMETER_H
