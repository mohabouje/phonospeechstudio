#include "energy.h"
#include "numeric"

Energy::Energy()
{

}

bool Energy::init() {
    _initialized = true;
    return true;
}

bool Energy::logarithmicScale() const
{
    return _logarithmicScale;
}

void Energy::setLogarithmicScale(bool logarithmicScale)
{
    _logarithmicScale = logarithmicScale;
}

const Sample Energy::outputSample() const
{
    return _energy;
}

void Energy::setInputData(const Frame &data)
{
    _inputData = data;
}

void Energy::processing() {
    if (_inputData.isEmpty()) {
        _energy = 0;
        return;
    }
    _energy = std::inner_product(_inputData.begin(), _inputData.end(), _inputData.begin(), (Sample)0.0);
}

void Energy::postProcessing() {
    if (_logarithmicScale)
        _energy = 10*log10(_energy);
}
