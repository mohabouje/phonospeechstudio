#include "mfcc.h"
#include <QDebug>

MFCC::MFCC()
{
    _dct = new DCT();
    _melBands = new MelBands();
}


bool MFCC::init()
{
    if (!_inputSize || !_fftSize || !_numBands || !_sampleRate) {
        qWarning() << "MFCC: Error while loading required fields.";
        _initialized = false;
        return false;
    }
    _mfcc = Frame(_numBands);
    _inputData = Frame(_inputSize);
    _melBands->setInputSize(_inputSize);
    _melBands->setSampleRate(_sampleRate);
    _melBands->setNumBands(_numBands);
    _melBands->setFftSize(_fftSize);
    _melBands->setLowFrequencyBound(_lowFrequencyBound);
    _melBands->setHighFrequencyBound(_highFrequencyBound);
    _dct->setInputSize(_numBands);
    _initialized = true;
    return _melBands->init() && _dct->init();
}

int MFCC::inputSize() const
{
    return _inputSize;
}

void MFCC::setInputSize(int inputSize)
{
    _inputSize = inputSize;
}

int MFCC::fftSize() const
{
    return _fftSize;
}

void MFCC::setFftSize(int fftSize)
{
    _fftSize = fftSize;
}

void MFCC::setInputData(const Frame &inputData)
{
    _inputData = inputData;
}

const Frame &MFCC::outputFrame() const
{
    return _mfcc;
}

int MFCC::sampleRate() const
{
    return _sampleRate;
}

void MFCC::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;
}

int MFCC::numBands() const
{
    return _numBands;
}

void MFCC::setNumBands(int numBands)
{
    _numBands = numBands;
}

int MFCC::highFrequencyBound() const
{
    return _highFrequencyBound;
}

void MFCC::setHighFrequencyBound(int highFrequencyBound)
{
    _highFrequencyBound = highFrequencyBound;
}

int MFCC::lowFrequencyBound() const
{
    return _lowFrequencyBound;
}

void MFCC::setLowFrequencyBound(int lowFrequencyBound)
{
    _lowFrequencyBound = lowFrequencyBound;
}

void MFCC::preProcessing() {
    _melBands->setInputData(_inputData);
    _melBands->exec();
    _energyBands = _melBands->outputFrame();
    for (int i=0; i<_energyBands.size(); i++) {
        _energyBands[i] = 10*log10(_energyBands[i]);
        qDebug() << _energyBands[i];
    }
}

void MFCC::processing() {
    _dct->setInputData(_energyBands);
    _dct->exec();
    _mfcc = _dct->outputFrame();
}


