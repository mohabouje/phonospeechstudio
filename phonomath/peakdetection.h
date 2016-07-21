#ifndef PEAKDETECTION_H
#define PEAKDETECTION_H
#include "mathalgorithm.h"
#include <QPair>

typedef QPair<Sample, Sample> Peak;
typedef QVector<Peak> PeakList;
class PeakDetection : public MathAlgorithm
{
public:
    PeakDetection();
    bool init();

    bool getInterpolate() const;
    void setInterpolate(bool getInterpolate);

    int minPos() const;
    void setMinPos(int minPos);

    int maxPos() const;
    void setMaxPos(int maxPos);

    int maxPeaks() const;
    void setMaxPeaks(int maxPeaks);

    Sample range() const;
    void setRange(const Sample &range);

    Sample threshold() const;
    void setThreshold(const Sample &threshold);

    const Frame& amplitudes() const;
    const Frame& positions() const;
    const Frame& outputFrame() const;

    int getInputSize() const;
    void setInputSize(int inputSize);
    void setInputData(const Frame &inputData);

private:
    int _inputSize;
    Frame _inputData;

    bool _interpolate;
    int  _minPos;
    int _maxPos;
    int _maxPeaks;
    Sample _range;
    Sample _threshold;
    Frame _amplitudes;
    Frame _positions;
    Sample _scale;
    PeakList _peaks;

    const Sample outputSample() const { return 0.0;}
    void preProcessing() {}
    void processing();
    void postProcessing();
    void interpolate(const Sample leftVal, const Sample middleVal, const Sample rightVal, int currentBin, Sample &resultVal, Sample &resultBin) const;
};

#endif // PEAKDETECTION_H
