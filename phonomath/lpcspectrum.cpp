#include "lpcspectrum.h"
#include <QDebug>

void LPCSpectrum::setFftSize(int fftSize)
{
    _fftSize = fftSize;
}

int LPCSpectrum::fftSize() const
{
    return _fftSize;
}

int LPCSpectrum::inputSize() const
{
    return _inputSize;
}

void LPCSpectrum::setInputSize(int inputSize)
{
    _inputSize = inputSize;
}

int LPCSpectrum::order() const
{
    return _order;
}

void LPCSpectrum::setOrder(int orderLPC)
{
    _order = orderLPC;
}

bool LPCSpectrum::init()
{
    if (!_inputSize || !_order  || !_fftSize) {
        qWarning() << "LPC Spectrum: Error while loading required fields.";
        _initialized = false;
        return false;
    }

    _lpc->setInputSize(_inputSize);
    _lpc->setOrder(_order);
    _lpc->init();

    _fft->setInputSize(_fftSize);
    _fft->setEstimateSpectrum(true);
    _fft->setLogarithmicScale(false);
    _fft->init();
    _initialized = true;
    return _initialized;
}

void LPCSpectrum::setInputData(const Frame &data)
{
    _inputData = data;
}

const Frame &LPCSpectrum::outputFrame() const
{
    return _lpcSpectrum;
}

bool LPCSpectrum::logarithmicScale() const
{
    return _logarithmicScale;
}

void LPCSpectrum::setLogarithmicScale(bool logarithmicScale)
{
    _logarithmicScale = logarithmicScale;
}

void LPCSpectrum::processing()
{
    _lpc->setInputData(_inputData);
    _lpc->exec();
    _lpcData = _lpc->outputFrame();
    _fft->setInputData(_lpcData);
    _fft->exec();
    _lpcSpectrum = _fft->outputFrame();
    inv(_lpcSpectrum);

    if (_logarithmicScale)
        db20(_lpcSpectrum);
    else
        square(_lpcSpectrum);
}

LPCSpectrum::LPCSpectrum()
{
    _logarithmicScale = false;
    _fft = new FFT();
    _lpc = new LPC();
}
