#include "framecutter.h"
#include <QDebug>

FrameCutter::FrameCutter()
{
    _windowing = new Windowing;
    _dcFilter = new DCFilter();
}


bool FrameCutter::init() {

    if (!_windowType || !_sampleRate || !_bufferTime || !_frameTime || !_hopeTime) {
        qWarning() << "Frame Cutter: Error while loading required fields.";
        _initialized = false;
        return false;
    }
    _overlapTime = _frameTime - _hopeTime;

    _samplesPerBuffer = std::ceil(_sampleRate * _bufferTime);
    _samplesPerFrame = std::ceil(_sampleRate * _frameTime);
    _samplesPerOverlap = std::ceil(_sampleRate * _overlapTime);
    _samplesPerHope = std::ceil(_sampleRate * _hopeTime);

    _frameCount = std::ceil(_bufferTime / _hopeTime);
    _tempBufferSize = (_frameCount - 1) * _samplesPerHope + _samplesPerFrame;
    _tempBuffer = Frame(_tempBufferSize);
    _filteredBuffer = Frame(_tempBufferSize);
    _frames = FrameCollection(_frameCount, Frame(_samplesPerFrame,0));

    _dcFilter->setInputSize(_tempBufferSize);
    _dcFilter->setSampleRate(_sampleRate);
    _dcFilter->setCutOffFrequency(40);
    _dcFilter->init();

    _windowing->setSize(_samplesPerFrame);
    _windowing->setWindowType(Windowing::Hamming);
    _windowing->init();
    _windowing->exec();
    _window = _windowing->outputFrame();

    _initialized = true;
    return true;
}

void FrameCutter::setInputData(const Frame& data) {
    std::copy(_tempBuffer.begin() + data.size(), _tempBuffer.end(), _tempBuffer.begin());
    std::copy(data.begin(), data.end(), _tempBuffer.end() - data.size());
}

void FrameCutter::preProcessing() {
    // Remove DC Component and pre-emphasis;
    _dcFilter->setInputData(_tempBuffer);
    _dcFilter->exec();
    _filteredBuffer = _tempBuffer;// _dcFilter->outputFrame();
}

void FrameCutter::processing() {
    unsigned int indexBegin = 0, indexEnd = 0;
    for (unsigned int i = 0; i < _frameCount; ++i) {
        indexBegin = i * _samplesPerHope;
        indexEnd = indexBegin + _samplesPerFrame;
        if (indexEnd <= _tempBufferSize)
            std::copy( _filteredBuffer.begin()+indexBegin,  _filteredBuffer.begin()+indexEnd, _frames[i].begin());
        else
            break;
    }
}

void FrameCutter::postProcessing() {
    /*for (unsigned int i = 0; i < _frameCount; ++i) {
        for (unsigned int j = 0; j< _samplesPerFrame; j++)
            _frames[i][j] *= _window[j];
    }*/
}

Windowing::WindowType FrameCutter::windowType() const
{
    return _windowType;
}

void FrameCutter::setWindowType(const Windowing::WindowType &windowType)
{
    _windowType = windowType;
}

double FrameCutter::bufferTime() const
{
    return _bufferTime;
}

void FrameCutter::setBufferTime(double bufferTime)
{
    _bufferTime = bufferTime;
}

double FrameCutter::frameTime() const
{
    return _frameTime;
}

void FrameCutter::setFrameTime(double frameTime)
{
    _frameTime = frameTime;
}

double FrameCutter::hopeTime() const
{
    return _hopeTime;
}

void FrameCutter::setHopeTime(double hopeTime)
{
    _hopeTime = hopeTime;
}

double FrameCutter::overlapTime() const
{
    return _overlapTime;
}


unsigned int FrameCutter::sampleRate() const
{
    return _sampleRate;
}

void FrameCutter::setSampleRate(unsigned int sampleRate)
{
    _sampleRate = sampleRate;
}

const FrameCollection& FrameCutter::frames() const
{
    return _frames;
}

unsigned int FrameCutter::samplesPerFrame() const
{
    return _samplesPerFrame;
}

