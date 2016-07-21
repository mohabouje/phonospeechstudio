#include "loudness.h"

Loudness::Loudness()
{
    _energy = new Energy;
}

bool Loudness::init()
{
    _inputData = Frame(0);
    _inputSize = 0;
    _energy->setLogarithmicScale(false);
    _energy->init();
    _initialized = true;
    return true;
}

void Loudness::setInputData(const Frame &inputData)
{
    _inputData = inputData;
    _inputSize = _inputData.size();
}

const Sample Loudness::outputSample() const
{
    return _loudness;
}

void Loudness::processing()
{
    _energy->setInputData(_inputData);
    _energy->exec();
    const Sample energyLevel = _energy->outputSample();
    _loudness = pow(energyLevel, STEVEN_LAW_LEVEL);
}
