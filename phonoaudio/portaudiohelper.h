#ifndef PORTAUDIOHELPER_H
#define PORTAUDIOHELPER_H

#include "util.h"
#include "wavreader.h"

#include <QObject>
#include <QVector>
#include "portaudio.h"

#define AUDIOMANAGER PortAudioHelper::instance()

#define keyDefaultInputDevice "audio/input_device"
#define keyDefaultOutputDevice "audio/output_device"
#define keyDefaultSampleRate "audio/sample_rate"

struct AudioConf {

};

namespace AM {
    struct AudioDeviceInfo {
        PaDeviceInfo deviceInfo;
        QVector<int> supportedSampleRates;
    };

    struct AudioBuffer {
        AudioSample         *data;
        unsigned long       dataCount;
    };
}

typedef  AM::AudioDeviceInfo AudioDeviceInfo;
typedef  AM::AudioBuffer AudioBuffer;
Q_DECLARE_METATYPE(AudioBuffer)
Q_DECLARE_METATYPE(AudioDeviceInfo)


class PortAudioHelper : public QObject
{
    Q_OBJECT
private:
    static PortAudioHelper* s_portAudioHelper;
    explicit PortAudioHelper(QObject *parent = 0);
public:
    enum State {
        NotInitialized = 0,
        Recording,
        Playing
    };



    static PortAudioHelper* instance(QObject *parent = 0);
    bool isRecording() const;
    void updateDevice();
    int framesPerBuffer() const;
    int sampleRate() const;
    int deviceCount() const ;
    int defaultInputDevice() const;
    int defaultOutputDevice()const;
    const QList<AudioDeviceInfo> &devices() const;
    PortAudioHelper::State state() const;
    double getCpuUsage() const;
    void updateBuffer(AudioSample *input, AudioSample *output, const long sampleCount);

#if ENABLE_WAV_READER
    void loadFile(const QString filePath);
public slots:
    bool play();
private:
    WavReader wavReader;
#endif

signals:
    void audioBufferReady(const AudioBuffer& buffer);
public slots:
    bool record();
private:
    bool _supported;
    State _state;
    PaStreamParameters inputParameters;
    PaStreamParameters outputParameters;
    PaError            err;
    PaStream*          stream;
    AudioConf          data;
    AudioBuffer        buffer;
    // Configure input device
    PaDeviceIndex DEVICE_COUNT;
    PaDeviceIndex DEFAULT_INPUT_DEVICE;
    PaDeviceIndex DEFAULT_OUTPUT_DEVICE;
    PaDeviceIndex CURRENT_INPUT_DEVICE;
    PaDeviceIndex CURRENT_OUTPUT_DEVICE;
    unsigned int SAMPLE_RATE;
    unsigned int FRAMES_PER_BUFFER;
    QList<AudioDeviceInfo> DEVICES;


    void defaultParameters();
    void initDevices();
    void loadDevices();
    bool init();
    void setState(const State &state);
    QVector<int> getSupportedSampleRate(const PaDeviceIndex index) const;


};

#endif // PORTAUDIOHELPER_H
