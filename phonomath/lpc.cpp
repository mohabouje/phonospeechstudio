#include "lpc.h"
#include <QDebug>

LPC::LPC()
{
    _autocor = new AutoCorrelation();
}

bool LPC::init()
{
    if (!_inputSize || !_order) {
        qWarning() << "LPC: Error while loading required fields.";
        _initialized = false;
        return false;
    }
    _autocor->setFFTSize(1024);
    _autocor->setSize(_inputSize);
    _autocor->setNormalized(false);
    _autocor->setUnbiased(false);
    _autocor->init();
    _inputData = Frame(_inputSize);
    _autocorData = _inputData;
    _initialized = true;
    _lpc = Frame(_order + 1);
    _reflection = Frame(_order + 1);
    return true;
}

void LPC::setInputData(const Frame &inputData)
{
    _inputData = inputData;
    _inputSize = _inputData.size();
}

const Frame &LPC::outputFrame() const
{
    return _lpc;
}

const Frame& LPC::reflection() const
{
    return _reflection;
}

int LPC::inputSize() const
{
    return _inputSize;
}

void LPC::setInputSize(int inputSize)
{
    _inputSize = inputSize;
}

int LPC::order() const
{
    return _order;
}

void LPC::setOrder(int order)
{
    _order = order;
}

void LPC::preProcessing() {
    _autocor->setInputData(_inputData);
    _autocor->exec();
    _autocorData = _autocor->outputFrame();
}

void LPC::processing() {
    // Levinson-Durbin algorithm
    Frame temp(_order);

    Sample k;
    Sample E = _autocorData[0];
    _lpc[0] = 1;

    for (int i=1; i<(_order+1); i++) {
        k = _autocorData[i];

        for (int j=1; j<i; j++) {
          k += _autocorData[i-j] * _lpc[j];
        }

        k /= E;

        _reflection[i-1] = k;
        _lpc[i] = -k;

        for (int j=1; j<i; j++) {
          temp[j] = _lpc[j] - k*_lpc[i-j];
        }

        for (int j=1; j<i; j++) {
          _lpc[j] = temp[j];
        }

        E *= (1-k*k);
    }

}

