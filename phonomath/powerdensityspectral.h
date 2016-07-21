#ifndef POWERDENSITYSPECTRAL_H
#define POWERDENSITYSPECTRAL_H
#include "mathalgorithm.h"
#include "fft.h"

class FFT;
class PowerDensitySpectral : public MathAlgorithm
{
public:
    PowerDensitySpectral();

    // MathAlgorithm interface
public:
    bool init();
    void setInputData(const Frame &data);
    const Frame &outputFrame() const;
    int inputSize() const;
    void setInputSize(int inputSize);
    void setLogarithmicScale(bool logarithmicScale);
    bool logarithmicScale() const;

private:
    int _inputSize;
    bool _logarithmicScale;
    Frame _inputData;
    Frame _spectrum;
    FFT* _fft;




    const Sample outputSample() const;
    void preProcessing() {}
    void processing();
    void postProcessing() {}
};

#endif // POWERDENSITYSPECTRAL_H
