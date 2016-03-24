#include "voiceprocessor.h"

VoiceProcessor::VoiceProcessor(QObject *parent) : QObject(parent)
{
    m_recordedLength = RECORD_SAMPLE_SIZE;

    for(int i=0; i < WINDOW_SIZE;i++){
        window[i]=0.5*(1-qCos((2*M_PI*i)/(WINDOW_SIZE-1)));
    }
}

float* VoiceProcessor::getFFTBuffer() {

    static float fftBuffer[WINDOW_SIZE];

    static int lastSettedFFTBufferIndex = 0;

    static int lastProcessedSampleIndex = 0;

    if (lastProcessedSampleIndex == recordedSamplesLastSetted) {
        return 0;
    }

    while (lastSettedFFTBufferIndex != WINDOW_SIZE ){

        fftBuffer[lastSettedFFTBufferIndex]=recordedSamples[lastProcessedSampleIndex]
                * window[lastSettedFFTBufferIndex];

        lastSettedFFTBufferIndex++;
        lastProcessedSampleIndex++;

        if(lastProcessedSampleIndex == m_recordedLength){
            lastProcessedSampleIndex = 0;
        }

        if (lastProcessedSampleIndex == recordedSamplesLastSetted)
        {
            /*if (!m_loopActive) {
                lastProcessedSampleIndex = 0;
            }*/
            return 0;
        }
    }

    lastSettedFFTBufferIndex = 0;

    if(((int)lastProcessedSampleIndex - WINDOW_SHIFT) < 0) {
        int shift = (int)lastProcessedSampleIndex - WINDOW_SHIFT;
        lastProcessedSampleIndex = m_recordedLength + shift;
    } else {
        lastProcessedSampleIndex -= WINDOW_SHIFT;
    }

    return fftBuffer;
}

float*  VoiceProcessor::getSpektrum(float *fftBuffer) {
    static float spektrum[SPEKTRUM_SIZE];
    static FFT* fft = new FFT();

    float xFFTArray[WINDOW_SIZE];
    float yFFTArray[WINDOW_SIZE];

    memcpy(xFFTArray, fftBuffer, WINDOW_SIZE*sizeof(float));

    for(int i = 0; i < WINDOW_SIZE; i++){
        yFFTArray[i]=0;
    }

    fft->RealFFTf(xFFTArray, yFFTArray, WINDOW_SIZE);

    for(int i = 0; i < WINDOW_SIZE; i++) {
        float real = xFFTArray[i];
        float imag = yFFTArray[i];

        spektrum[i] = sqrt(real*real + imag*imag) ;
    }

    return spektrum;
}
/*
Parameter*  VoiceProcessor::getMelSpektrum(float *spektrum) {
    static float melSpektrum[MEL_SPEKTRUM_SIZE];
    static Parameter parameter;

    m_melFilter->melFiltering(spektrum, melSpektrum);

    float ampl = 0;

    for(int i = 0; i < MEL_SPEKTRUM_SIZE; i++) {
        ampl +=  melSpektrum[i];
    }
    ampl /= MEL_SPEKTRUM_SIZE;

    parameter.setParameter(melSpektrum, MEL_SPEKTRUM_SIZE-1, ampl);

    return &parameter;
}

bool VoiceProcessor::checkInWord(Parameter *parameter) {
    static float noiseBorder = 1.0f;

    if (noiseBorder == 0) {
        noiseBorder = 1.0;
    }

    if (noiseBorder > parameter->amplitude) {
        noiseBorder = parameter->amplitude;
        parameter->inWord = false;
    } else {
        if (NOISE_MULT * noiseBorder < parameter->amplitude) {
            parameter->inWord = true;
        }

        noiseBorder *= (NOISE_CONVERG);
    }
    return parameter->inWord;
}
*/
Parameter* VoiceProcessor::processSamples(){

    float *fftBuffer = getFFTBuffer();

    if(fftBuffer == 0){
        return 0;
    }

    Parameter* para = new Parameter();

    float spektr[30];
    for(int i = 0; i < 30; i++){
        spektr[i]=i+1;
    }
    para->setParameter(spektr, 30, 42);
/*
    float *spektrum = getSpektrum(fftBuffer);

    Parameter *parameter = getMelSpektrum(spektrum);

    bool inWord = checkInWord(parameter);
*/
    return para;
}
