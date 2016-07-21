#include "powerdensityspectral.h"
#include <QDebug>
PowerDensitySpectral::PowerDensitySpectral()
{
    _fft = new FFT();
    _logarithmicScale = true;

}

bool PowerDensitySpectral::init()
{
    if (!_inputSize) {
        qWarning() << "PSD Error while loading required fields.";
        _initialized = false;
        return false;
    }

    _fft->setInputSize(_inputSize);
    _fft->setEstimateSpectrum(true);
    _fft->setLogarithmicScale(false);
    _fft->init();
    _initialized = true;
    return _initialized;
}


void PowerDensitySpectral::setInputData(const Frame &data)
{
    _inputData = data;
}

const Frame &PowerDensitySpectral::outputFrame() const
{
    return _spectrum;
}

int PowerDensitySpectral::inputSize() const
{
    return _inputSize;
}

void PowerDensitySpectral::setInputSize(int inputSize)
{
    _inputSize = inputSize;
}

void PowerDensitySpectral::setLogarithmicScale(bool logarithmicScale)
{
    _logarithmicScale = logarithmicScale;
}

bool PowerDensitySpectral::logarithmicScale() const
{
    return _logarithmicScale;
}

const Sample PowerDensitySpectral::outputSample() const
{
    return 0.0;
}

void PowerDensitySpectral::processing()
{
    _fft->setInputData(_inputData);
    _fft->exec();
    _spectrum = _fft->outputFrame();
    (!_logarithmicScale) ? square(_spectrum) : db20(_spectrum);
}
