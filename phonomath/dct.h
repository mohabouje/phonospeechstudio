#ifndef DCT_H
#define DCT_H
#include "mathalgorithm.h"

class DCT : public MathAlgorithm
{
public:
    DCT();
    bool init();
    const Frame& outputFrame() const;
    int inputSize() const;
    void setInputSize(int inputSize);
    void setInputData(const Frame &inputData);

private:
    FrameCollection _dctTable;
    int     _inputSize;
    Frame   _inputData;
    Frame   _dct;

    const Sample outputSample() const { return 0.0; }
    void preProcessing() {}
    void processing();
    void postProcessing() {}
    void initTable();
};

#endif // DCT_H
