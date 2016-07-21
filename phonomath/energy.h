#ifndef ENERGY_H
#define ENERGY_H
#include "mathalgorithm.h"

class Energy : public MathAlgorithm
{
public:
    Energy();
    bool init();
    bool logarithmicScale() const;
    void setLogarithmicScale(bool logarithmicScale);
    void setInputData(const Frame &data);
    const Sample outputSample() const;


private:
    bool _logarithmicScale;
    Frame _inputData;
    Sample _energy;

    const Frame& outputFrame() const { return Frame(0);}
    void preProcessing() {}
    void processing();
    void postProcessing();
};

#endif // ENERGY_H
