#ifndef IFFT_H
#define IFFT_H
#include "mathalgorithm.h"
#include "fftw3.h"
class IFFT : public MathAlgorithm
{
public:
    IFFT();
    bool init();
    void setInputData(const Frame &data);
    const Frame &outputFrame() const;
    void setComplexData(ComplexSample *complexData);
    int inputSize() const;
    void setInputSize(int inputSize);

private:

    int _inputSize;
    int _realDataSize;
    Frame _realData;
    ComplexSample* _complexData;
    fftw_plan       _fftPlan;

    void preProcessing() {}
    void processing();
    void postProcessing();
    const Sample outputSample() const { return 0.0;}
    void loadPlan();
};

#endif // IFFT_H
