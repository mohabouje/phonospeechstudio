#include "portaudiohelper.h"
#include "wavreader.h"
#include <QDebug>





static int  apiCallback(   const void *inputBuffer, void *outputBuffer,
                                    unsigned long framesPerBuffer,
                                    const PaStreamCallbackTimeInfo* timeInfo,
                                    PaStreamCallbackFlags statusFlags,
                                    void *userData ){

    (void) timeInfo;
    (void) statusFlags;
    (void) userData;
    (void) userData;

    AUDIOMANAGER->updateBuffer((AudioSample*) inputBuffer, (AudioSample*) outputBuffer, framesPerBuffer);
    return paContinue;
}



PortAudioHelper* PortAudioHelper::s_portAudioHelper = 0;
PortAudioHelper* PortAudioHelper::instance(QObject *parent) {
    if (!s_portAudioHelper) {
        s_portAudioHelper = new PortAudioHelper(parent);
    }
    Q_ASSERT(s_portAudioHelper);
    return s_portAudioHelper;
}


PortAudioHelper::PortAudioHelper(QObject *parent) :
    QObject(parent),
    _supported(false),
    err(paNoError)
{
    initDevices();
    defaultParameters();
}




static double standardSampleRates[] = {8000.0, 9600.0, 11025.0,
                                       12000.0, 16000.0, 22050.0,
                                       24000.0, 32000.0, 44100.0,
                                       48000.0, 88200.0, 96000.0,
                                       192000.0, -1.0};

QVector<int> PortAudioHelper::getSupportedSampleRate(const PaDeviceIndex index) const {
    PaStreamParameters inputParameters;
    inputParameters.device = index;
    inputParameters.channelCount = DEFAULT_CHANNEL_COUNT;
    inputParameters.sampleFormat = DEFAULT_AUDIO_SAMPLE_FORMAT;
    inputParameters.suggestedLatency = 0;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    PaStreamParameters outputParameters;
    outputParameters.device = index;
    outputParameters.channelCount = DEFAULT_CHANNEL_COUNT;
    outputParameters.sampleFormat = DEFAULT_AUDIO_SAMPLE_FORMAT;
    outputParameters.suggestedLatency = 0;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    QVector<int> sampleRates;
    for (int i = 0; standardSampleRates[i] > 0; i++ ) {
         PaError err = Pa_IsFormatSupported( &inputParameters, &outputParameters, standardSampleRates[i] );
         if (err == paFormatIsSupported)
             sampleRates.append(standardSampleRates[i]);
    }
    return sampleRates;
}



void PortAudioHelper::initDevices() {
    if (!init()) {
       qDebug() << ("Error: Port audio not initialized.\n");
       return;
    }
    loadDevices();
}

bool PortAudioHelper::init() {
    err = Pa_Initialize();
    return  err == paNoError;
}

void PortAudioHelper::loadDevices() {
    DEVICE_COUNT = Pa_GetDeviceCount();
    DEFAULT_INPUT_DEVICE = Pa_GetDefaultInputDevice();
    DEFAULT_OUTPUT_DEVICE = Pa_GetDefaultOutputDevice();
    for (PaDeviceIndex i=0; i<DEVICE_COUNT; i++) {
        AudioDeviceInfo deviceInfo;
        deviceInfo.deviceInfo = *Pa_GetDeviceInfo(i);
        deviceInfo.supportedSampleRates = getSupportedSampleRate(i);
        DEVICES.append(deviceInfo);
    }

    CURRENT_INPUT_DEVICE = loadFromSettings(keyDefaultInputDevice, DEFAULT_INPUT_DEVICE).toInt();
    CURRENT_OUTPUT_DEVICE = loadFromSettings(keyDefaultOutputDevice, DEFAULT_OUTPUT_DEVICE).toInt();
}

#if ENABLE_WAV_READER
void PortAudioHelper::loadFile(const QString filePath) {
    const bool fileLoaded = wavReader.readFile(filePath);
    if (!fileLoaded)
        return;
    outputParameters.device = CURRENT_OUTPUT_DEVICE;
    if (outputParameters.device == paNoDevice) {
        qDebug() << ("Error: No default input device.\n");
        _supported = false;
    } else {
        outputParameters.channelCount = DEFAULT_CHANNEL_COUNT;
        outputParameters.sampleFormat = DEFAULT_AUDIO_SAMPLE_FORMAT;
        outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowInputLatency;
        outputParameters.hostApiSpecificStreamInfo = NULL;

        // Lets open audio input device
        err = Pa_OpenStream(&stream, NULL, &outputParameters,  wavReader.sampleRate(), DEFAULT_BUFFER_TIME * wavReader.sampleRate(), paClipOff, apiCallback, &data);
        if( err != paNoError ) {
            qDebug() << ("Error: No acces to input device.\n");
            _supported = false;
        } else {
            _supported = true;
        }
    }
}

bool PortAudioHelper::play() {
    err = Pa_StartStream( stream );
    if ( err != paNoError ) {
        qDebug() << ("Error: Device not responding.\n");
    }
    setState(Playing);
    err = Pa_WriteStream(stream, wavReader.buffer(), wavReader.availableSamples());
    if( err != paNoError )
        qDebug() << ("Error: No se puede reproducir el archivo.\n") << err;
    return err == paNoError;
}
#endif

void PortAudioHelper::setState(const State &state)
{
    _state = state;
}


void PortAudioHelper::updateDevice() {
    SAMPLE_RATE = loadFromSettings(keyDefaultSampleRate, DEFAULT_SAMPLERATE).toInt();
    CURRENT_INPUT_DEVICE = loadFromSettings(keyDefaultInputDevice, DEFAULT_INPUT_DEVICE).toInt();
    CURRENT_OUTPUT_DEVICE = loadFromSettings(keyDefaultOutputDevice, DEFAULT_OUTPUT_DEVICE).toInt();
    FRAMES_PER_BUFFER = DEFAULT_BUFFER_TIME * SAMPLE_RATE;

    inputParameters.device = CURRENT_INPUT_DEVICE;
    inputParameters.channelCount = DEFAULT_CHANNEL_COUNT;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    // Lets open audio input device
    err = Pa_OpenStream(&stream, &inputParameters, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, apiCallback, &data);
    if( err != paNoError ) {
        qDebug() << ("Error: No acces to input device.\n");
        _supported = false;
    } else {
        _supported = true;
    }
}

void PortAudioHelper::defaultParameters() {
    SAMPLE_RATE = loadFromSettings(keyDefaultSampleRate, DEFAULT_SAMPLERATE).toInt();
    FRAMES_PER_BUFFER = DEFAULT_BUFFER_TIME * SAMPLE_RATE;

    inputParameters.device = CURRENT_INPUT_DEVICE;
    if (inputParameters.device == paNoDevice) {
        qDebug() << ("Error: No default input device.\n");
        _supported = false;
    } else {
        inputParameters.channelCount = DEFAULT_CHANNEL_COUNT;
        inputParameters.sampleFormat = paFloat32;
        inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
        inputParameters.hostApiSpecificStreamInfo = NULL;

        // Lets open audio input device
        err = Pa_OpenStream(&stream, &inputParameters, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, apiCallback, &data);
        if( err != paNoError ) {
            qDebug() << ("Error: No acces to input device.\n");
            _supported = false;
        } else {
            _supported = true;
        }
    }
}

void PortAudioHelper::updateBuffer(AudioSample* input, AudioSample* output, const long sampleCount) {
    buffer.dataCount = sampleCount;
    switch(state()) {
    case PortAudioHelper::NotInitialized:
        return;
    case PortAudioHelper::Recording:
        buffer.data = (AudioSample*) input;
        free(output);
        break;
    case PortAudioHelper::Playing:
        buffer.data = (AudioSample*) output;
        free(input);
        break;
    default:
        return;
    }
    emit audioBufferReady(buffer);
}

bool PortAudioHelper::record() {
    if (!_supported)
        return false;

    err = Pa_StartStream( stream );
    if ( err != paNoError ) {
        qDebug() << ("Error: Device not responding.\n");
    }
    return isRecording();
}

bool PortAudioHelper::isRecording() const {
    return Pa_IsStreamActive( stream );
}

int PortAudioHelper::sampleRate() const {
    return SAMPLE_RATE;
}

int PortAudioHelper::framesPerBuffer() const {
    return FRAMES_PER_BUFFER;
}

int PortAudioHelper::deviceCount() const {
    return DEVICE_COUNT;
}

int PortAudioHelper::defaultInputDevice() const {
    return DEFAULT_INPUT_DEVICE;
}

int PortAudioHelper::defaultOutputDevice() const {
    return DEFAULT_OUTPUT_DEVICE;
}

const QList<AudioDeviceInfo>& PortAudioHelper::devices() const {
    return DEVICES;
}

PortAudioHelper::State PortAudioHelper::state() const {
    return (isRecording()) ? PortAudioHelper::Recording : PortAudioHelper::NotInitialized;
}

double PortAudioHelper::getCpuUsage() const {
    return Pa_GetStreamCpuLoad(stream);
}



