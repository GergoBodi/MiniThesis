#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#include <QString>
#include <qmath.h>

#define MEL_SPEKTRUM_SIZE 30
#define MEL_MIN_FREQUENCY 300
#define MEL_MAX_FREQUENCY 3300

#define WINDOW_SIZE 512
#define WINDOW_SHIFT 256
#define SPEKTRUM_SIZE 256
#define SAMPLE_RATE 11025
#define RECORD_SAMPLE_SIZE 11025
#define WORD_MIN_LENGTH 100
#define LEARN_MAX_DIST 0.2
#define DEFAULT_COST 0.0
#define LISTENING 2
#define WORD_END 1

extern int recordedSamplesLastSetted;
extern short* recordedSamples;
extern float* window;

class GlobalVars
{
public:
    GlobalVars();
};

#endif // GLOBALVARS_H
