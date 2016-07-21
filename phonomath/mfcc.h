#ifndef MFCC_H
#define MFCC_H
#include "mathalgorithm.h"
#include "dct.h"
#include "melbands.h"
class DCT;
class MelBands;

class MFCC : public MathAlgorithm
{
public:
    MFCC();
    bool init();

    int inputSize() const;
    void setInputSize(int inputSize);

    int fftSize() const;
    void setFftSize(int fftSize);

    void setInputData(const Frame &inputData);
    const Frame& outputFrame() const;
    int sampleRate() const;
    void setSampleRate(int sampleRate);

    int numBands() const;
    void setNumBands(int numBands);

    int highFrequencyBound() const;
    void setHighFrequencyBound(int highFrequencyBound);

    int lowFrequencyBound() const;
    void setLowFrequencyBound(int lowFrequencyBound);

private:
    int _inputSize;
    int _fftSize;
    Frame _inputData;
    Frame _energyBands;
    int _lowFrequencyBound;
    int _highFrequencyBound;
    int _numBands;
    int _sampleRate;
    Frame _mfcc;
    DCT* _dct;
    MelBands* _melBands;

    const Sample outputSample() const { return 0.0; }
    void preProcessing();
    void processing();
    void postProcessing() {}
};

#endif // MFCC_H
