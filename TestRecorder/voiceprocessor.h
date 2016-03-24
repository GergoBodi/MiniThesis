#ifndef VOICEPROCESSOR_H
#define VOICEPROCESSOR_H

#include <QObject>
#include <Parameter.h>
#include <globalvars.h>
#include <fft.h>
#include <melfilter.h>

class VoiceProcessor : public QObject
{
    Q_OBJECT
public:
    explicit VoiceProcessor(QObject *parent = 0);

private:
    int m_recordedLength;

    melFilter* m_melFilter = new melFilter();

    float* getFFTBuffer();
    float* getSpektrum(float *fftBuffer);
    Parameter* getMelSpektrum(float *spektrum);
    /*bool checkInWord(Parameter *parameter);
    */
public slots:
    Parameter* processSamples();

};

#endif // VOICEPROCESSOR_H
