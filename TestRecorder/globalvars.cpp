#include "globalvars.h"

int recordedSamplesLastSetted = 0;

short* recordedSamples = new short[RECORD_SAMPLE_SIZE];

float* window = new float[WINDOW_SIZE];

GlobalVars::GlobalVars()
{

}

