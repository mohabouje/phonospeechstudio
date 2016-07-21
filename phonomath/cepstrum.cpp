#include "cepstrum.h"
#include <QDebug>
Cepstrum::Cepstrum()
{
    _fft = new FFT();
    _ifft = new IFFT();
}

bool Cepstrum::init()
{
    if (!_inputSize) {
        _initialized = false;
        return _initialized;
    }

    _fft->setInputSize(_inputSize);
    _fft->setEstimateSpectrum(true);
    _fft->setLogarithmicScale(false);
    _fft->init();

    _cepstrumSize = _fft->fftSize();
    _cepstrum = Frame(_cepstrumSize);
    _ifft->setInputSize(_cepstrumSize);
    _ifft->init();
    _initialized = true;
    return _initialized;
}



void Cepstrum::setInputData(const Frame &data)
{
    _inputData = data;
}

const Frame &Cepstrum::outputFrame() const
{
    return _cepstrum;
}

int Cepstrum::inputSize() const
{
    return _inputSize;
}

void Cepstrum::setInputSize(int inputSize)
{
    _inputSize = inputSize;
}

int Cepstrum::cepstrumSize() const
{
    return _cepstrumSize;
}


void Cepstrum::processing() {
    _fft->setInputData(_inputData);
    _fft->exec();
    _spectrum = _fft->outputFrame();
    ln(_spectrum);
    _ifft->setInputData(_spectrum);
    _ifft->exec();
    const Frame& tmp = _ifft->outputFrame();
    std::copy(tmp.begin(), tmp.begin()+_cepstrumSize, _cepstrum.begin());
}
