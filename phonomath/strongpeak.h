#ifndef STRONGPEAK_H
#define STRONGPEAK_H
#include "mathalgorithm.h"

class StrongPeak : public MathAlgorithm
{
public:
    StrongPeak();

    // MathAlgorithm interface
public:
    bool init();
    void setInputData(const Frame &data);
    const Sample outputSample() const;
    Sample magnitud() const;
    int position() const;

private:
    Frame   _inputData;
    Sample  _magnitud;
    int     _position;

    const Frame &outputFrame() const;
    void preProcessing() {}
    void processing();
    void postProcessing() {}
};

#endif // STRONGPEAK_H
