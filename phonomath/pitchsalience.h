#ifndef PITCHSALIENCE_H
#define PITCHSALIENCE_H
#include "mathalgorithm.h"
#include "autocorrelation.h"
#include "fft.h"

class AutoCorrelation;
class FFT;
class PitchSalience : public MathAlgorithm
{
public:
    PitchSalience();
    bool init();


    void setInputData(const Frame &inputData);
    const Sample outputSample() const;
    int inputSize() const;
    void setInputSize(int inputSize);

    int sampleRate() const;
    void setSampleRate(int sampleRate);

    Sample lowBoundary() const;
    void setLowBoundary(const Sample &lowBoundary);

    Sample highBoundary() const;
    void setHighBoundary(const Sample &highBoundary);

private:
    int _inputSize;
    Frame _inputData;

    int _sampleRate;
    Sample _lowBoundary;
    Sample _highBoundary;

    Frame _spectrum;
    Frame _autocorData;

    FFT* _fft;
    AutoCorrelation* _autocor;
    Sample _pitchSalience;
    Sample _maxAutoCor;

    const Frame& outputFrame() const { return Frame(0);}
    void postProcessing();
    void processing();
    void preProcessing();
};

#endif // PITCHSALIENCE_H
