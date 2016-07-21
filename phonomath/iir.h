#ifndef IIR_H
#define IIR_H
#include "mathalgorithm.h"

class IIR : public MathAlgorithm
{
public:
    IIR();
    bool init();
    void setInputData(const Frame &inputData);
    void reset();

    int inputSize() const;
    void setInputSize(int inputSize);

    const Frame& denominator() const;
    void setDenominator(const Frame &denominator);

    const Frame& numerator() const;
    void setNumerator(const Frame &numerator);

    const Frame& outputFrame() const;

private:
    int _inputSize;
    Frame _inputData;
    Frame _filteredData;

    Frame _denominator;
    Frame _numerator;
    Frame _state;

    const Sample outputSample() const { return 0.0; }
    void normalize();
    void preProcessing();
    void postProcessing();
    void processing();
};

#endif // IIR_H
