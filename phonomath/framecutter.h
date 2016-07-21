#ifndef FRAMECUTTER_H
#define FRAMECUTTER_H
#include "mathalgorithm.h"
#include "windowing.h"
#include "dcfilter.h"

class Windowing;
class DCFilter;

class FrameCutter : public MathAlgorithm
{
public:
    FrameCutter();
    bool init();
    void setInputData(const Frame &data);

    Windowing::WindowType windowType() const;
    void setWindowType(const Windowing::WindowType &windowType);
    double bufferTime() const;
    void setBufferTime(double bufferTime);
    double frameTime() const;
    void setFrameTime(double frameTime);
    double hopeTime() const;
    void setHopeTime(double hopeTime);
    double overlapTime() const;
    unsigned int sampleRate() const;
    void setSampleRate(unsigned int sampleRate);
    const FrameCollection& frames() const;

    unsigned int samplesPerFrame() const;

private:

    Windowing* _windowing;
    DCFilter* _dcFilter;
    Windowing::WindowType _windowType;
    Frame      _window;

    double _bufferTime;
    double _frameTime;
    double _hopeTime;
    double _overlapTime;

    unsigned int _samplesPerBuffer;
    unsigned int _samplesPerFrame;
    unsigned int _samplesPerOverlap;
    unsigned int _samplesPerHope;

    unsigned int _sampleRate;
    unsigned int _frameCount;
    unsigned int _tempBufferSize;
    Frame _tempBuffer;
    Frame _filteredBuffer;
    FrameCollection _frames;

    const Frame& outputFrame() const { return Frame(0);}
    const Sample outputSample() const { return 0.0;}
    void postProcessing();
    void processing();
    void preProcessing();
};

#endif // FRAMECUTTER_H
