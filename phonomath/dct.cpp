#include "dct.h"
#include <QDebug>
DCT::DCT()
{

}

bool DCT::init()
{
    if (!_inputSize) {
        qWarning() << "DCT: Error while loading required fields.";
        _initialized = false;
        return false;
    }
    _inputData = Frame(_inputSize);
    _dct = _inputData;

    initTable();
    _initialized = true;
    return true;
}

const Frame &DCT::outputFrame() const
{
    return _dct;
}

int DCT::inputSize() const
{
    return _inputSize;
}

void DCT::setInputSize(int inputSize)
{
    _inputSize = inputSize;
}

void DCT::setInputData(const Frame &inputData)
{
    _inputData = inputData;
}

void DCT::initTable()
{
    _dctTable = FrameCollection(_inputSize, Frame(_inputSize));
    Sample scale0 = 1.0 / sqrt(Sample(_inputSize));
    Sample scale1 = Sample(sqrt(2.0/_inputSize));
    for (int i=0; i<_inputSize; ++i) {
        Sample scale = ( i == 0 ) ? scale0 : scale1;
        Sample freqMultiplier = Sample(M_PI / _inputSize * i);
        for (int j=0; j<_inputSize; ++j) {
          _dctTable[i][j] = (Sample)(scale * cos( freqMultiplier * ((Sample)j + 0.5) ));
        }
    }
}

void DCT::processing() {
    for (int i=0; i<_inputSize; ++i) {
        _dct[i] = 0.0;
        for (int j=0; j<_inputSize; ++j) {
          _dct[i] += _inputData[j] * _dctTable[i][j];
        }
    }
}
