#ifndef CEPSTRUM_H
#define CEPSTRUM_H
#include "mathalgorithm.h"
#include "fft.h"
#include "ifft.h"
class FFT;
class IFFT;
class Cepstrum : public MathAlgorithm
{
public:
    Cepstrum();

    // MathAlgorithm interface
public:
    bool init();
    void setInputData(const Frame &data);
    const Frame &outputFrame() const;

    int inputSize() const;
    void setInputSize(int inputSize);
    int cepstrumSize() const;

private:
    int _inputSize;
    int _cepstrumSize;
    Frame _inputData;
    Frame _spectrum;
    Frame _cepstrum;

    FFT* _fft;
    IFFT* _ifft;
    ComplexSample* _tmp;

    const Sample outputSample() const { return 0.0;}
    void preProcessing() {}
    void processing();
    void postProcessing() {}
};

#endif // CEPSTRUM_H
