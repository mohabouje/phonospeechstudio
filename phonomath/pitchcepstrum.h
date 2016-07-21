#ifndef PITCHCEPSTRUM_H
#define PITCHCEPSTRUM_H
#include "mathalgorithm.h"
#include "cepstrum.h"

class Cepstrum;
class PitchCepstrum : public MathAlgorithm
{
public:
    PitchCepstrum();

private:
    int _inputSize;
    Frame _inputData;

    int _sampleRate;
    int _minFrequency;
    int _maxFrequency;

    int _minPos;
    int _maxPos;


    Sample _pitch;
    Frame _cepstrumData;

    Cepstrum* _cepstrum;



    // MathAlgorithm interface
public:
    bool init();
    void setInputData(const Frame &data);
    const Sample outputSample() const;
    int inputSize() const;
    void setInputSize(int inputSize);

    int sampleRate() const;
    void setSampleRate(int sampleRate);

    int minFrequency() const;
    void setMinFrequency(int minFrequency);

    int maxFrequency() const;
    void setMaxFrequency(int maxFrequency);

private:
    const Frame &outputFrame() const;
    void preProcessing();
    void processing();
    void postProcessing() {}
};

#endif // PITCHCEPSTRUM_H
