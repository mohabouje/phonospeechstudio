#include "ifft.h"
#include <QDebug>
IFFT::IFFT()
{

}

bool IFFT::init()
{
    if (!_inputSize) {
        qWarning() << "IFFt: Error while loading required fields.";
        _initialized = false;
        return false;
    }
    _realDataSize = 2*(_inputSize - 1);
    _realData = Frame(_realDataSize);
    _complexData = (ComplexSample*)fftw_malloc(sizeof(ComplexSample)*_realDataSize);
    loadPlan();
    _initialized = true;
    return true;

}

void IFFT::loadPlan() {
    _fftPlan = fftw_plan_dft_c2r_1d(_realDataSize, _complexData, _realData.data(), FFTW_ESTIMATE);
}



void IFFT::processing()
{
    fftw_execute(_fftPlan);
}

void IFFT::postProcessing() {
    const int size = _realData.size();
    std::for_each(_realData.begin(), _realData.end(), [size] (Sample& n) { n /= size;});
}


void IFFT::setInputData(const Frame &data) {
    for (int i=0; i<data.size(); i++) {
        _complexData[i][0] = data[i];
        _complexData[i][1] = 0.0;
    }
}

const Frame& IFFT::outputFrame() const {
    return _realData;
}

void IFFT::setComplexData(ComplexSample *complexData)
{
    _complexData = complexData;
    loadPlan();
}

int IFFT::inputSize() const
{
    return _inputSize;
}

void IFFT::setInputSize(int inputSize)
{
    _inputSize = inputSize;
}


