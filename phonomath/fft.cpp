#include "fft.h"
#include "math.h"
#include <QDebug>

FFT::FFT()
{

}

bool FFT::init() {
    if (!_inputSize) {
        qWarning() << "FFT: Error while loading required fields.";
        _initialized = false;
        return false;
    }
    _fftSize = (_inputSize/2) + 1;
    _absData = Frame(_fftSize);
    _inputData = new Sample[_inputSize];
    for (int i=0; i<_inputSize; i++) {
        _inputData[i] = 0.0;
    }
    _complexData = (ComplexSample*)fftw_malloc(sizeof(ComplexSample)*_fftSize);
    loadPlan();
    _initialized = true;
    return true;
}

void FFT::loadPlan() {
    _fftPlan = fftw_plan_dft_r2c_1d(_inputSize, _inputData, _complexData, FFTW_ESTIMATE);
}


void FFT::processing()
{

    fftw_execute(_fftPlan);
}


void FFT::postProcessing() {
    if (!_estimateSpectrum)
        return;

    if (_logarithmicScale) {
        for (int i=0; i<_fftSize; i++) {
            _absData[i]  = db_spl(absComplex(_complexData[i]));
        }
    } else {
        for (int i=0; i<_fftSize; i++) {
            _absData[i]  = absComplex(_complexData[i]);
        }
    }

}


int FFT::inputSize() const
{
    return _inputSize;
}

void FFT::setInputSize(int inputSize)
{
    _inputSize = inputSize;
}

void FFT::setInputData(const Frame &inputData)
{
    std::copy(inputData.begin(), inputData.end(), _inputData);
}

const Frame &FFT::outputFrame() const { return _absData;}


ComplexSample* FFT::outputComplex() const
{
    return _complexData;
}


bool FFT::logarithmicScale() const
{
    return _logarithmicScale;
}

void FFT::setLogarithmicScale(bool logarithmicScale)
{
    _logarithmicScale = logarithmicScale;
}

bool FFT::estimateSpectrum() const
{
    return _estimateSpectrum;
}

void FFT::setEstimateSpectrum(bool estimateSpectrum)
{
    _estimateSpectrum = estimateSpectrum;
}

void FFT::setInputData(Sample *data)
{
    _inputData = data;
    loadPlan();
}

int FFT::fftSize() const
{
    return _fftSize;
}

