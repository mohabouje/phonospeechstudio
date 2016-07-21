#ifndef LPC_H
#define LPC_H
#include "mathalgorithm.h"
#include "autocorrelation.h"
class AutoCorrelation;
class LPC : public MathAlgorithm
{
public:
    LPC();
    bool init();
    void setInputData(const Frame &inputData);
    const Frame& outputFrame() const;
    const Frame& reflection() const;

    int inputSize() const;
    void setInputSize(int inputSize);

    int order() const;
    void setOrder(int order);

private:
    int _inputSize;
    Frame _inputData;
    Frame _autocorData;
    int _order;
    Frame _lpc;
    Frame _reflection;
    AutoCorrelation* _autocor;

    const Sample outputSample() const { return 0.0; }
    void preProcessing();
    void processing();
    void postProcessing() {}
};

#endif // LPC_H
