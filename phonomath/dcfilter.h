#ifndef DCFILTER_H
#define DCFILTER_H
#include "mathalgorithm.h"
#include "iir.h"
class IRR;
class DCFilter : public MathAlgorithm
{
public:
    DCFilter();
    bool init();
    void setInputData(const Frame &inputData);

    int inputSize() const;
    void setInputSize(int inputSize);
    const Frame& outputFrame() const;
    int sampleRate() const;
    void setSampleRate(int sampleRate);

    int cutOffFrequency() const;
    void setCutOffFrequency(int cutOffFrequency);

private:
    int _inputSize;
    Frame _inputData;
    Frame _filteredData;

    Frame _numerator;
    Frame _denominator;

    int _sampleRate;
    int _cutOffFrequency;
    IIR* _iir;
    const Sample outputSample() const { return 0.0; }

    void preProcessing();
    void processing();
    void postProcessing() {}


};

#endif // DCFILTER_H
