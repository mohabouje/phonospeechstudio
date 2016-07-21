#include "dcfilter.h"
#include <QDebug>
DCFilter::DCFilter()
{
    _iir = new IIR();
}

bool DCFilter::init()
{
    if (!_inputSize || !_sampleRate || !_cutOffFrequency) {
        qWarning() << "DCFilter: Error while loading required fields.";
        _initialized = false;
        return false;
    }
    Sample feedbackCoefficient = (Sample)(1.0 - 2.0*M_PI*_sampleRate/_cutOffFrequency);
    _denominator = Frame(2,0);
    _denominator[0] = 1;
    _denominator[1] = -feedbackCoefficient;

    _numerator = Frame(2,0);
    _numerator[0] = 1;
    _numerator[1] = -1;

    _inputData = Frame(_inputSize);
    _filteredData = Frame(_inputSize);
    _initialized = true;

    _iir->setInputSize(_inputSize);
    _iir->setNumerator(_numerator);
    _iir->setDenominator(_denominator);
    _iir->init();
    return true;
}

void DCFilter::setInputData(const Frame &inputData)
{
    _inputData = inputData;
}

int DCFilter::inputSize() const
{
    return _inputSize;
}

void DCFilter::setInputSize(int inputSize)
{
    _inputSize = inputSize;
}

const Frame &DCFilter::outputFrame() const
{
    return _filteredData;
}

int DCFilter::sampleRate() const
{
    return _sampleRate;
}

void DCFilter::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;
}

int DCFilter::cutOffFrequency() const
{
    return _cutOffFrequency;
}

void DCFilter::setCutOffFrequency(int cutOffFrequency)
{
    _cutOffFrequency = cutOffFrequency;
}

void DCFilter::preProcessing() {
    _iir->reset();
    _iir->setInputData(_inputData);
}

void DCFilter::processing() {
    _iir->exec();
    _filteredData = _iir->outputFrame();
}
