#ifndef FRAMESANALYZER_H
#define FRAMESANALYZER_H
#include "mathalgorithm.h"

class FramesAnalyzer
{
public:
    FramesAnalyzer();
    static Frame applyForFrame(const FrameCollection& input, MathAlgorithm* algorithm);
    static FrameCollection applyForFrameCollection(const FrameCollection &input, MathAlgorithm *algorithm);
};

#endif // FRAMESANALYZER_H
