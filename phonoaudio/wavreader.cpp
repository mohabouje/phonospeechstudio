#include "config.h"
#if ENABLE_WAV_READER
#include "wavreader.h"
#include <QDebug>
#include <QFile>
#include <QFileInfo>

WavReader::WavReader()
{

}



bool WavReader::readFile(const QString filePath) {
    qDebug() << "Enter inside!";
    QFile file(filePath);
    if (!file.exists()) {
        qDebug() << "File no exist";
        return false;
    }

    sf = sf_open(filePath.toStdString().data(), SFM_READ, &info);
    if (sf == NULL) {
        qDebug() << "Error loading SNDFILE";
        return false;
    }

    _frameCount = info.frames;
    _sampleRate = info.samplerate;
    _channelCount = info.channels;
    _sampleCount = _channelCount * _frameCount;
    _buffer = (AudioSample *) malloc(_sampleCount*sizeof(AudioSample));
    _availableSamples = sf_read_float(sf, _buffer, _sampleCount);
    qDebug() << "File " << filePath << QString(" . SampleRate = %1, SampleCount = %2, ReadSample = %3").arg(_sampleRate, _sampleCount, _availableSamples);
    sf_close(sf);
    return _availableSamples == _sampleCount;
}

AudioSample *WavReader::buffer() const
{
    return _buffer;
}

int WavReader::channelCount() const
{
    return _channelCount;
}

int WavReader::frameCount() const
{
    return _frameCount;
}

int WavReader::sampleRate() const
{
    return _sampleRate;
}

int WavReader::sampleCount() const
{
    return _sampleCount;
}

int WavReader::availableSamples() const
{
    return _availableSamples;
}

#endif
