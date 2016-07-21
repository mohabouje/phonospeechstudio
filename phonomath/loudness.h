#ifndef LOUDNESS_H
#define LOUDNESS_H
#include "mathalgorithm.h"
#include "energy.h"

#define STEVEN_LAW_LEVEL 0.67
class Loudness : public MathAlgorithm
{
public:
    Loudness();
    bool init();
    void setInputData(const Frame &inputData);
    const Sample outputSample() const;
private:
    int _inputSize;
    Frame _inputData;
    Sample _loudness;
    Energy* _energy;

    const Frame& outputFrame() const { return Frame(0); }
    void preProcessing() {}
    void processing();
    void postProcessing() {}
};

#endif // LOUDNESS_H
