#include "autocorrelation.h"

#include <algorithm>
#include <QDebug>

AutoCorrelation::AutoCorrelation()
{
    _fft = new FFT();
    _ifft = new IFFT();
}

bool AutoCorrelation::init()
{
    if (!_size || !_fftSize) {
        qWarning() << "Autocorrelation: Error while loading required fields.";
        _initialized = false;
        return false;
    }

    _autocor = Frame(_size);
    _inputData = Frame(_size);
    _fft->setInputSize(_fftSize);
    _fft->setLogarithmicScale(false);
    _fft->setEstimateSpectrum(true);
    _fft->init();
    _ifft->setInputSize(_fft->fftSize());
    _ifft->init();
    _initialized = true;
    return true;
}

bool AutoCorrelation::unbiased() const
{
    return _unbiased;
}

void AutoCorrelation::setUnbiased(bool unbiased)
{
    _unbiased = unbiased;
}

int AutoCorrelation::size() const
{
    return _size;
}

void AutoCorrelation::setSize(int size)
{
    _size = size;
}

void AutoCorrelation::setInputData(const Frame &data)
{
    std::copy(data.begin(), data.end(), _inputData.begin());
}

bool AutoCorrelation::normalized() const
{
    return _normalized;
}

void AutoCorrelation::setNormalized(bool normalized)
{
    _normalized = normalized;
}

int AutoCorrelation::fftSize() const
{
    return _fftSize;
}

void AutoCorrelation::setFFTSize(int fftSize)
{
    _fftSize = fftSize;
}

void AutoCorrelation::processing()
{
    if (_autocor.size() != _inputData.size()) {
        qWarning() << "Autocorrelation: Error data must have " << _size << " points.";
        return;
    }

    //  Wiener–Khinchin theorem
    _fft->setInputData(_inputData);
    _fft->exec();
    _spectrum = _fft->outputFrame();
    square(_spectrum);
    _ifft->setInputData(_spectrum);
    _ifft->exec();
    Frame acor = _ifft->outputFrame();
    std::copy (acor.begin(), acor.begin()+_size, _autocor.begin());
}

void AutoCorrelation::postProcessing()
{
    if (_normalized && _unbiased) {
        for (int i=0; i<_size; i++) {
            _autocor[i] *= (1.0 / (_size-i));
        }
    } else if (_normalized && !_unbiased) {
        const int size = _autocor.size();
        std::for_each(_autocor.begin(), _autocor.end(), [&size](Sample &n) {n /= size;});
    }
}

const Frame& AutoCorrelation::outputFrame() const
{
    return _autocor;
}
