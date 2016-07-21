#ifndef ZEROCROSSINGRATE_H
#define ZEROCROSSINGRATE_H
#include "mathalgorithm.h"

class ZeroCrossingRate : public MathAlgorithm
{
public:
    ZeroCrossingRate();
    bool init();
    void setInputData(const Frame &inputData);
    const Sample outputSample() const;
    int inputSize() const;

private:
    int _inputSize;
    Frame _inputData;
    Sample _zcr;

    const Frame& outputFrame() const { return Frame(0); }
    void preProcessing() {}
    void processing();
    void postProcessing();
};

#endif // ZEROCROSSINGRATE_H
