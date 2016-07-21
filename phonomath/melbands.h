#ifndef MELBANDS_H
#define MELBANDS_H
#include "mathalgorithm.h"
#include "fft.h"

class FTT;
class MelBands : public MathAlgorithm
{
public:
    MelBands();
    bool init();

    int numBands() const;
    void setNumBands(int numBands);

    int sampleRate() const;
    void setSampleRate(int sampleRate);

    void setInputData(const Frame &inputData);
    const Frame& outputFrame() const;

    int inputSize() const;
    void setInputSize(int inputSize);

    int fftSize() const;
    void setFftSize(int fftSize);

    int lowFrequencyBound() const;
    void setLowFrequencyBound(int lowFrequencyBound);

    int highFrequencyBound() const;
    void setHighFrequencyBound(int highFrequencyBound);

private:
    int _inputSize;
    int _fftSize;
    Frame _inputData;
    Frame _energyBands;

    int _lowFrequencyBound;
    int _highFrequencyBound;
    int _numBands;
    int _sampleRate;
    FrameCollection _filterCoefficients;
    Frame _filterFrequencies;
    Frame _spectrum;
    FFT* _fft;

    const Sample outputSample() const { return 0.0; }
    void preProcessing();
    void processing();
    void postProcessing() {}

    void loadFilterFrequencies();
    void loadFilterCoefficients();

};

#endif // MELBANDS_H
