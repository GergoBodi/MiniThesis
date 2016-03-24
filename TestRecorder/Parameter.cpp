#include "Parameter.h"

Parameter::Parameter()
{
    for(int i = 0; i < MEL_SPEKTRUM_SIZE; i++){
        this->spektrum[i]=0;
    }
    this->length = 0;
    this->amplitude = 0;
    this->inWord = false;
}

void Parameter::setParameter(float* melSpectrum, float length, float ampl)
{
    memcpy(this->spektrum, melSpectrum, length*sizeof(float));
    this->length = length;
    this->amplitude = ampl;
    this->inWord=true;
}
