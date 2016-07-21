#include "pitchcepstrum.h"
#include <QDebug>

PitchCepstrum::PitchCepstrum()
{
    _cepstrum = new Cepstrum();
}

int PitchCepstrum::maxFrequency() const
{
    return _maxFrequency;
}

void PitchCepstrum::setMaxFrequency(int maxFrequency)
{
    _maxFrequency = maxFrequency;
}

int PitchCepstrum::minFrequency() const
{
    return _minFrequency;
}

void PitchCepstrum::setMinFrequency(int minFrequency)
{
    _minFrequency = minFrequency;
}

int PitchCepstrum::sampleRate() const
{
    return _sampleRate;
}

void PitchCepstrum::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;
}

int PitchCepstrum::inputSize() const
{
    return _inputSize;
}

void PitchCepstrum::setInputSize(int inputSize)
{
    _inputSize = inputSize;
}

bool PitchCepstrum::init()
{
    if (!_inputSize || !_sampleRate || !_minFrequency || !_maxFrequency) {
        _initialized = false;
        return _initialized;
    }

    _cepstrum->setInputSize(1024);
    _cepstrum->init();

    _minPos = std::max(0, _sampleRate/_maxFrequency);
    _maxPos = std::max(_inputSize, _sampleRate/_minFrequency);

    _initialized = true;
    return _initialized;
}

void PitchCepstrum::setInputData(const Frame &data)
{
    _inputData = data;
}

const Sample PitchCepstrum::outputSample() const
{
    return _pitch;
}

const Frame &PitchCepstrum::outputFrame() const
{
    return Frame(0);
}

void PitchCepstrum::preProcessing()
{
    _cepstrum->setInputData(_inputData);
    _cepstrum->exec();
    _cepstrumData = _cepstrum->outputFrame();

}

void PitchCepstrum::processing()
{
    const int pos = maxPos(_cepstrumData, _minPos, _maxPos);
    _pitch = Sample(_sampleRate / pos);
}





