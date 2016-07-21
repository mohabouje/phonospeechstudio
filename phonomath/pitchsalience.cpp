#include "pitchsalience.h"
#include <QDebug>

PitchSalience::PitchSalience()
{
    _fft = new FFT();
    _autocor = new AutoCorrelation();
}

bool PitchSalience::init() {
    if (!_inputSize || !_sampleRate || !_lowBoundary || !_highBoundary) {
        qWarning() << "PitchSalience: Error while loading required fields.";
        _initialized = false;
        return false;
    }
    _fft->setInputSize(_inputSize);
    _fft->setEstimateSpectrum(true);
    _fft->setLogarithmicScale(false);
    _fft->init();
    _autocor->setSize(_fft->fftSize());
    _autocor->setNormalized(false);
    _autocor->setUnbiased(false);
    _autocor->setFFTSize(1024);
    _autocor->init();
    _initialized = true;
    return _initialized;
}

void PitchSalience::setInputData(const Frame &inputData)
{
    _inputData = inputData;
}

const Sample PitchSalience::outputSample() const
{
    return _pitchSalience;
}

int PitchSalience::inputSize() const
{
    return _inputSize;
}

void PitchSalience::setInputSize(int inputSize)
{
    _inputSize = inputSize;
}

int PitchSalience::sampleRate() const
{
    return _sampleRate;
}

void PitchSalience::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;
}

Sample PitchSalience::lowBoundary() const
{
    return _lowBoundary;
}

void PitchSalience::setLowBoundary(const Sample &lowBoundary)
{
    _lowBoundary = lowBoundary;
}

Sample PitchSalience::highBoundary() const
{
    return _highBoundary;
}

void PitchSalience::setHighBoundary(const Sample &highBoundary)
{
    _highBoundary = highBoundary;
}


void PitchSalience::preProcessing() {
    _fft->setInputData(_inputData);
    _fft->exec();
    _spectrum = _fft->outputFrame();
    _autocor->setInputData(_spectrum);
    _autocor->exec();
    _autocorData = _autocor->outputFrame();
}

void PitchSalience::processing() {
    const int spectrumSize = _spectrum.size();
    int lowIndex = (_lowBoundary * spectrumSize / (_sampleRate/2));
    int highIndex = (_highBoundary * spectrumSize / (_sampleRate/2));
    _maxAutoCor = *std::max_element(_autocorData.begin() + lowIndex, _autocorData.begin() + highIndex);

}

void PitchSalience::postProcessing() {
    _pitchSalience = (_autocorData[0] == 0) ? 0.0 : _maxAutoCor / _autocorData[0];
}
