#ifndef WAVREADER_H
#define WAVREADER_H

#include "config.h"
#if ENABLE_WAV_READER

#include "util.h"
#include <QString>
#include <sndfile.h>

class WavReader
{
public:
    WavReader();
    bool readFile(const QString filePath);
    AudioSample *buffer() const;
    int channelCount() const;
    int frameCount() const;
    int sampleRate() const;
    int sampleCount() const;
    int availableSamples() const;

private:
    SNDFILE *sf;
    SF_INFO info;
    AudioSample* _buffer;
    int _channelCount;
    int _frameCount;
    int _sampleRate;
    int _sampleCount;
    int _availableSamples;


};
#endif

#endif // WAVREADER_H
