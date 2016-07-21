#include "power.h"

Power::Power()
{

}


bool Power::init() {
    _initialized = true;
    return true;
}

bool Power::logarithmicScale() const
{
    return _logarithmicScale;
}

void Power::setLogarithmicScale(bool logarithmicScale)
{
    _logarithmicScale = logarithmicScale;
}

const Sample Power::outputSample() const
{
    return _power;
}

void Power::setInputData(const Frame &data)
{
    _inputData = data;
}

void Power::processing() {
    if (_inputData.isEmpty()) {
        _power = 0;
        return;
    }
    _power = std::inner_product(_inputData.begin(), _inputData.end(), _inputData.begin(), (Sample)0.0);
    _power /= _inputData.size();
}

void Power::postProcessing() {
    if (_logarithmicScale)
        _power = 10*log10(_power);
}
