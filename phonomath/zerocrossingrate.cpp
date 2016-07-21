#include "zerocrossingrate.h"
#include <QDebug>
#include <boost/math/special_functions/sign.hpp>
ZeroCrossingRate::ZeroCrossingRate()
{

}

bool ZeroCrossingRate::init()
{
    _inputData = Frame(0);
    _inputSize = 0;
    _initialized = true;
    return true;
}


void ZeroCrossingRate::setInputData(const Frame &inputData)
{
    _inputData = inputData;
    _inputSize = _inputData.size();
}

const Sample ZeroCrossingRate::outputSample() const {
    return _zcr;
}

int ZeroCrossingRate::inputSize() const
{
    return _inputSize;
}

void ZeroCrossingRate::processing() {
    _zcr = 0;
    for (int i=1;i<_inputSize;i++) {
        if (boost::math::sign(_inputData[i]) != boost::math::sign(_inputData[i-1]))
            _zcr++;
    }
}

void ZeroCrossingRate::postProcessing() {
    _zcr /= (Sample)_inputSize;
}
