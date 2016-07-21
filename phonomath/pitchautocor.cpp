#include "pitchautocor.h"
#include <boost/lambda/lambda.hpp>
#include <QDebug>

PitchAutocor::PitchAutocor()
{
    _autocor = new AutoCorrelation;
    _peakDetector = new PeakDetection;
}

bool PitchAutocor::init()
{
    if (!_inputSize || !_sampleRate || !_minFrequency || !_maxFrequency) {
        _initialized = false;
        return _initialized;
    }

    _tauMax = std::min(int(ceil(_sampleRate / _minFrequency)), _inputSize);
    _tauMin = std::min(int(floor(_sampleRate / _maxFrequency)), _inputSize);
    _pitch = 0;
    _pitchConfidence = 0;

    _autocor->setSize(_inputSize);
    _autocor->setFFTSize(1024);
    _autocor->setNormalized(true);
    _autocor->setUnbiased(false);
    _autocor->init();

    _peakDetector->setInputSize(_inputSize);
    _peakDetector->setRange(_inputSize);
    _peakDetector->setMaxPeaks(5);
    _peakDetector->setMinPos(_tauMin);
    _peakDetector->setMaxPos(_tauMax);
    _peakDetector->setInterpolate(true);
    _peakDetector->setThreshold(0.5);
    _peakDetector->init();

    _initialized = true;
    return _initialized;

}



void PitchAutocor::preProcessing() {
    _autocor->setInputData(_inputData);
    _autocor->exec();
    _autocorData = _autocor->outputFrame();
    Normalize(_autocorData);
}

void PitchAutocor::processing() {
    _peakDetector->setInputData(_autocorData);
    _peakDetector->exec();
    _positions = _peakDetector->positions();
    _amplitudes = _peakDetector->amplitudes();
}

void PitchAutocor::postProcessing() {
    if (_positions.isEmpty()) {
        _pitch = 0.;
        _pitchConfidence = 0.;
    } else {

         Sample mean = std::accumulate(_positions.begin(), _positions.end(), 0.0) / _positions.size();
         _pitchConfidence = (_positions[0] - mean)/ _positions[0];
         _pitch = (Sample) _sampleRate/mean;
    }
}

const Frame &PitchAutocor::outputFrame() const
{
    return Frame(0);
}

void PitchAutocor::setInputData(const Frame &inputFrame)
{
    _inputData = inputFrame;
}

const Sample PitchAutocor::outputSample() const
{
    return _pitch;
}

int PitchAutocor::inputSize() const
{
    return _inputSize;
}

void PitchAutocor::setInputSize(int inputSize)
{
    _inputSize = inputSize;
}

int PitchAutocor::sampleRate() const
{
    return _sampleRate;
}

void PitchAutocor::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;
}

int PitchAutocor::minFrequency() const
{
    return _minFrequency;
}

void PitchAutocor::setMinFrequency(int minFrequency)
{
    _minFrequency = minFrequency;
}

int PitchAutocor::maxFrequency() const
{
    return _maxFrequency;
}

void PitchAutocor::setMaxFrequency(int maxFrequency)
{
    _maxFrequency = maxFrequency;
}
