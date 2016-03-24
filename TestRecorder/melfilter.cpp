#include "melfilter.h"

float melFilter::melScale(float freq){
    float melvalue = 2595 * log10f(1+freq/700);
    return melvalue;
}

float melFilter::melScaleInverse(float melval){
    float valueHZ = (700*qPow(10,melval/2595))-700;
    return valueHZ;
}

float melFilter::m_filter(float* Centers, int i, float k){
    float val;
    if(Centers[i]==k){
        return 1;
    }else if(i<MEL_SPEKTRUM_SIZE-1 && k<Centers[i+1] && k>Centers[i]){
        val=1.0-((k-Centers[i])/(Centers[i+1]-Centers[i]));
        return val;
    }else if(i>0 && k>Centers[i-1] && k<Centers[i]){
        val=(k-Centers[i-1])/(Centers[i]-Centers[i-1]);
        return val;
    }else{
        return 0;
    }
}

melFilter::melFilter()
{
    // A mel-skála növekményét kiszámítja a melDelta
    // változóba, a melScale függvény visszaadja a
    // paraméterben kapott frekvencia mel-skálabeli értékét.
    float melDelta=(melScale(MEL_MAX_FREQUENCY)-melScale(MEL_MIN_FREQUENCY))/(MEL_SPEKTRUM_SIZE+1);

    // Ami a mel-skálán lineárisan nő, az a frekvencia
    // skálán logaritmikus. A m_filterCentersInHZ tömbben
    // eltárolja a keretek frekvencia tartománybeli
    // közép pontját.
    for(int i = 0; i < MEL_SPEKTRUM_SIZE; i++){
        m_filterCentersInHZ[i] = melScaleInverse(melDelta*i);
    }

    for(int i = 0; i < MEL_SPEKTRUM_SIZE; i++){
        m_filterCentersInHZ[i] = (m_filterCentersInHZ[i]/m_filterCentersInHZ[29])*(MEL_MAX_FREQUENCY-MEL_MIN_FREQUENCY);
    }

    // melFilter a keret súlyait ideiglenesen tároló tömb.
    float   melFilter[1024];
    int     begin = 0;
    int     end   = 0;

    int mfcount = 0;    // mel-filter count

    for(int i=0; i < 1024;i++){
        melFilter[i]=0;
    }

    // Minden mel-spektrum eleméhez létrehoz egy
    // keretet, mellyel a spektrum keretezését,
    // és súlyozott összegének, előállítását
    // végezzük.
    for(int i = 0; i < MEL_SPEKTRUM_SIZE; i++) {
        begin = -1;
        end   = -1;
        int c = 0;

        // Végig megy a spektrum frekvenciáin,
        // és meghatározza, az egyes frekvenciákhoz
        // tartozó súlyokat.
        for(int k = 0; k < SPEKTRUM_SIZE; k++) {

            // Adott frekvenciához tartozó súly kiszámítása.
            float step=0;
            step=k*(float)(MEL_MAX_FREQUENCY-MEL_MIN_FREQUENCY)/SPEKTRUM_SIZE;
            float filterWeight = m_filter(m_filterCentersInHZ, i,
                              //k*(1.0f /((float)WINDOW_SIZE/(SAMPLE_RATE/2))));
                                          step);

            // A keret kezdő és végpontjának meghatározása
            if(filterWeight>0){
                if(begin<0){
                    begin = k;
                    melFilter[c] = filterWeight;
                }else{
                    melFilter[c] = filterWeight;
                }
                end = k;
                c++;
            }
        }
        // a keret hossza
        int length = end-begin+1;

        // a keret súlyainak elmentése a filter struktúrákat
        // tartalmazó tömbbe.
        if(begin >= 0){
            m_melFilterStructs[mfcount].filterWeights = new float[length];
            m_melFilterStructs[mfcount].filterLength  = length;
            m_melFilterStructs[mfcount].startIndex    = begin;
            memcpy(m_melFilterStructs[mfcount].filterWeights, melFilter, length * sizeof(float));
        }else{
             m_melFilterStructs[mfcount].filterLength  = 0;
        }
        mfcount++;
    }
}

void melFilter::melFiltering(float* spectrum, float p_melSpektrum[MEL_SPEKTRUM_SIZE])
{
    // Bejár minden mel-szűrőt és a súlyokkal beszorozza és összegzi
    // a spektrum megfelelő indexű elemeit, előállítva a mel-
    // spektrumot.
    for (int i = 0; i < MEL_SPEKTRUM_SIZE; i++) {
    // Nullára Inicializálja az eredmény tömböt.
        p_melSpektrum[i] = 0;

        for (int k = 0; k < m_melFilterStructs[i].filterLength; k++)
        {
        // Hozzáadja az eredmény tömbhöz a súlyozott spektrum
        // összeget.
            p_melSpektrum[i] += m_melFilterStructs[i].filterWeights[k]*spectrum[m_melFilterStructs[i].startIndex+k];
        }
    }
}

