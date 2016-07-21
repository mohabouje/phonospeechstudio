#ifndef AUTOCORRELATION_H
#define AUTOCORRELATION_H
#include "mathmanager.h"
#include "fft.h"
#include "ifft.h"

class FFT;
class IFFT;

class AutoCorrelation : public MathAlgorithm
{
public:
    AutoCorrelation();
    bool init();

    bool unbiased() const;
    void setUnbiased(bool unbiased);

    int size() const;
    void setSize(int size);

    void setInputData(const Frame &data);
    const Frame& outputFrame() const;

    bool normalized() const;
    void setNormalized(bool normalized);

    int fftSize() const;
    void setFFTSize(int fftSize);

private:
    bool _unbiased;
    bool _normalized;
    int  _size;
    int _fftSize;
    Frame _inputData;
    Frame _spectrum;
    Frame _autocor;
    FFT* _fft;
    IFFT* _ifft;



    const Sample outputSample() const { return 0.0; }
    void preProcessing() {}
    void processing();
    void postProcessing();
};

#endif // AUTOCORRELATION_H
