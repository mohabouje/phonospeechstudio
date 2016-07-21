#include "mathutil.h"
#include "math.h"
#include <QDebug>

Sample absComplex(const ComplexSample sample) {
    return sqrt( squared(sample[0]) + squared(sample[1]));
}

Sample hz2mel(const Sample f) {
    return 2595 * log10(1 + f/700);
}

Sample mel2Hz(const Sample mel) {
   return 700*(pow(10, (mel/2595.0))-1);
}

static bool abs_compare(int a, int b) {
    return (std::abs(a) < std::abs(b));
}


Sample max(const FrameCollection& frames) {
    Sample _max = -SHRT_MAX;
    for (const Frame& frame : frames) {
        const Sample localMax = *std::max_element(frame.begin(), frame.end());
        if (localMax > _max)
            _max  = localMax;
    }
    return _max;
}

Sample min(const FrameCollection& frames) {
    Sample _min = SHRT_MAX;
    for (const Frame& frame : frames) {
        const Sample localMin = *std::min_element(frame.begin(), frame.end());
        if (localMin < _min)
            _min  = localMin;
    }
    return _min;
}

void Normalize(Frame &frame) {
    const Sample _max = *std::max_element(frame.begin(), frame.end());
    const Sample _min = *std::min_element(frame.begin(), frame.end());
    std::for_each(frame.begin(),
                  frame.end(),
                  [&_max, &_min](double& value){ value = (value-_min)/(_max-_min);
                                         });
}

void Normalize(FrameCollection &frames) {

}

void ln(Frame &frame)
{
    std::for_each(frame.begin(), frame.end(), [](Sample& value) {value = log(value);});
}

int maxPos(const Frame &frame, const int begin, const int end)
{
    return std::distance(frame.begin() , std::max_element(frame.begin() + begin, frame.begin() + end));
}

int minPos(const Frame &frame, const int begin, const int end)
{
    return std::distance(frame.begin() , std::min_element(frame.begin() + begin, frame.begin() + end));
}

void inv(Frame& frame) {
    std::for_each(frame.begin(), frame.end(), [](Sample& value) {value = (Sample) 1.0/value;});
}

void square(Frame &frame)
{
    std::for_each(frame.begin(), frame.end(), [](Sample& value) {value = squared(value);});
}

void db20(Frame &frame)
{
    std::for_each(frame.begin(), frame.end(), [](Sample& value) {value = db_20(value);});

}
