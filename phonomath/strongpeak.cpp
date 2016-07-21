#include "strongpeak.h"
#include "mathutil.h"

StrongPeak::StrongPeak()
{

}

bool StrongPeak::init()
{

}

void StrongPeak::setInputData(const Frame &data)
{
    _inputData = data;
}

const Sample StrongPeak::outputSample() const
{
    return _magnitud;
}

Sample StrongPeak::magnitud() const
{
    return _magnitud;
}

int StrongPeak::position() const
{
    return _position;
}

const Frame &StrongPeak::outputFrame() const {
    return Frame(0);
}

void StrongPeak::processing()
{
    const int maxIndex = maxPos(_inputData, 0, _inputData.size());
    Sample maxMag = _inputData[maxIndex];
    _position = maxIndex;
    _magnitud =  maxMag;
}
