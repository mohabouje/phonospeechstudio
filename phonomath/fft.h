#ifndef FFT_H
#define FFT_H
#include "mathmanager.h"
#include "fftw3.h"
#include "mathutil.h"
class FFT : public  MathAlgorithm
{
public:
    FFT();
    bool init();
    int inputSize() const;
    int fftSize() const;
    void setInputSize(int inputSize);
    void setInputData(const Frame &inputData);
    const Frame& outputFrame() const;
    ComplexSample* outputComplex() const;
    bool logarithmicScale() const;
    void setLogarithmicScale(bool logarithmicScale);
    bool estimateSpectrum() const;
    void setEstimateSpectrum(bool estimateSpectrum);

    Sample* inputData() const { return _inputData; }
    void setInputData(Sample* data);

private:
    bool            _logarithmicScale;
    bool            _estimateSpectrum;
    int             _inputSize;
    int             _fftSize;
    Frame           _absData;
    fftw_plan       _fftPlan;

    Sample*         _inputData;
    ComplexSample*    _complexData;




    void loadPlan();
    const Sample outputSample() const { return 0.0; }
    void preProcessing() {}
    void processing();
    void postProcessing();
};

#endif // FFT_H
