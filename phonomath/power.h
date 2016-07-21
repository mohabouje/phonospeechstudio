#ifndef POWER_H
#define POWER_H
#include "mathalgorithm.h"

class Power : public MathAlgorithm
{
public:
    Power();
    bool init();
    bool logarithmicScale() const;
    void setLogarithmicScale(bool logarithmicScale);
    void setInputData(const Frame &data);
    const Sample outputSample() const;


private:
    bool _logarithmicScale;
    Frame _inputData;
    Sample _power;

    const Frame& outputFrame() const { return Frame(0);}
    void preProcessing() {}
    void processing();
    void postProcessing();
};
#endif // POWER_H
