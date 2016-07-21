#ifndef PITCHAUTOCOR_H
#define PITCHAUTOCOR_H
#include "mathalgorithm.h"
#include "mathutil.h"
#include "autocorrelation.h"
#include "peakdetection.h"

class AutoCorrelation;
class PeakDetection;
class PitchAutocor : public MathAlgorithm
{
public:
    PitchAutocor();
    bool init();

    void setInputData(const Frame &inputFrame);
    const Sample outputSample() const;
    int inputSize() const;
    void setInputSize(int inputSize);

    int sampleRate() const;
    void setSampleRate(int sampleRate);

    int minFrequency() const;
    void setMinFrequency(int minFrequency);

    int maxFrequency() const;
    void setMaxFrequency(int maxFrequency);

private:
    int _inputSize;
    Frame _inputData;

    int _sampleRate;
    int _minFrequency;
    int _maxFrequency;

    Sample _tauMax;
    Sample _tauMin;

    Sample _pitch;
    Sample _pitchConfidence;
    Frame _autocorData;
    Frame _positions;
    Frame _amplitudes;

    AutoCorrelation* _autocor;
    PeakDetection* _peakDetector;

    void preProcessing();
    void processing();
    void postProcessing();
    const Frame &outputFrame() const;


};

#endif // PITCHAUTOCOR_H
