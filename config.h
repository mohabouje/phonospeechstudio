#ifndef CONFIG_H
#define CONFIG_H
#include "boost/circular_buffer.hpp"
#include <QVector>
#include "portaudio.h"

#define ENABLE_WAV_READER 0
#define ENABLE_TESTING 1
#define VERBOSE 1
#define VERBOSE_FRAMES 0
#define DEFAULT_BUFFER_TIME 0.08
#define DEFAULT_CHANNEL_COUNT 1
#define DEFAULT_AUDIO_SAMPLE_FORMAT paFloat32;
#define DEFAULT_SAMPLERATE 8000
typedef float AudioSample;
typedef boost::circular_buffer<double>  CircularBuffer;
typedef QVector<double> Frame;
typedef QVector<Frame> FrameCollection;


enum ChartActions {
    EnergyChart = 0,
    PowerChart,
    LoudnessChart,
    ZeroCrossingRateChart,
    PowerDensitySpectralChart,
    LPCSpectrumChart,
    CepstrumChart,
    SpectrumCepstrumChart
};

#endif // CONFIG_H
