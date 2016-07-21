#ifndef LPCSPECTRUM_H
#define LPCSPECTRUM_H
#include "mathalgorithm.h"
#include "lpc.h"
#include "fft.h"

class LPC;
class FFT;
class LPCSpectrum : public MathAlgorithm
{
public:
    LPCSpectrum();

    void setFftSize(int fftSize);
    int fftSize() const;

    int inputSize() const;
    void setInputSize(int inputSize);

    int order() const;
    void setOrder(int order);

    bool init();
    void setInputData(const Frame &data);
    const Frame &outputFrame() const;

    bool logarithmicScale() const;
    void setLogarithmicScale(bool logarithmicScale);

private:
    int _inputSize;
    int _fftSize;
    int _order;
    bool _logarithmicScale;
    Frame _inputData;
    Frame _lpcData;
    Frame _lpcSpectrum;

    LPC* _lpc;
    FFT* _fft;




    const Sample outputSample() const { return 0.0;}
    void preProcessing() {}
    void processing();
    void postProcessing() {}
};

#endif // LPCSPECTRUM_H
