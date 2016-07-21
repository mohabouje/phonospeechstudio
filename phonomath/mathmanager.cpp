#include "mathmanager.h"
#include <QDebug>

MathManager* MathManager::s_mathManager = 0;
MathManager* MathManager::instance(QObject *parent) {
    if (!s_mathManager) {
        s_mathManager = new MathManager(parent);
    }
    Q_ASSERT(s_mathManager);
    return s_mathManager;
}

FrameCutter *MathManager::frameCutter() const
{
    return _frameCutter;
}

bool MathManager::initFrameCutter(const int sampleRate, const double bufferTime, const double frameTime, const double hopeTime, const Windowing::WindowType windowTipe)
{
    _frameCutter->setSampleRate(sampleRate);
    _frameCutter->setBufferTime(bufferTime);
    _frameCutter->setFrameTime(frameTime);
    _frameCutter->setHopeTime(hopeTime);
    _frameCutter->setWindowType(windowTipe);
    if (!_frameCutter->init())
        return false;

    _autocor->setSize(_frameCutter->samplesPerFrame());
    _autocor->setFFTSize(512);
    _autocor->setNormalized(false);
    _autocor->setUnbiased(false);

    _fft->setInputSize(512);
    _fft->setEstimateSpectrum(true);
    _fft->setLogarithmicScale(true);

    _lpc->setInputSize(_frameCutter->samplesPerFrame());
    _lpc->setOrder(10);

    _dct->setInputSize(_frameCutter->samplesPerFrame());

    _melBands->setInputSize(_frameCutter->samplesPerFrame());
    _melBands->setNumBands(20);
    _melBands->setLowFrequencyBound(0);
    _melBands->setHighFrequencyBound(sampleRate);
    _melBands->setSampleRate(sampleRate);
    _melBands->setFftSize(512);

    _mfcc->setInputSize(_frameCutter->samplesPerFrame());
    _mfcc->setNumBands(20);
    _mfcc->setLowFrequencyBound(0);
    _mfcc->setHighFrequencyBound(sampleRate);
    _mfcc->setSampleRate(sampleRate);
    _mfcc->setFftSize(512);

    _pitchSalience->setInputSize(_frameCutter->samplesPerFrame());
    _pitchSalience->setSampleRate(sampleRate);
    _pitchSalience->setLowBoundary(80);
    _pitchSalience->setHighBoundary(500);


    _pitchAutocor->setInputSize(_frameCutter->samplesPerFrame());
    _pitchAutocor->setMinFrequency(40);
    _pitchAutocor->setMaxFrequency(500);
    _pitchAutocor->setSampleRate(sampleRate);

    _pitchCepstrum->setInputSize(_frameCutter->samplesPerFrame());
    _pitchCepstrum->setMinFrequency(40);
    _pitchCepstrum->setMaxFrequency(500);
    _pitchCepstrum->setSampleRate(sampleRate);

    _cepstrum->setInputSize(512);
    _psd->setInputSize(512);
    _psd->setLogarithmicScale(true);

    _lpcSpectrum->setInputSize(_frameCutter->samplesPerFrame());
    _lpcSpectrum->setFftSize(512);
    _lpcSpectrum->setLogarithmicScale(true);
    _lpcSpectrum->setOrder(13);


    return _autocor->init()
            && _fft->init()
            && _zcr->init()
            && _loudness->init()
            && _lpc->init()
            && _dct->init()
            && _melBands->init()
            && _mfcc->init()
            && _pitchSalience->init()
            && _pitchAutocor->init()
            && _pitchCepstrum->init()
            && _cepstrum->init()
            && _psd->init()
            && _lpcSpectrum->init();
}

bool MathManager::initAlgorithms(const bool logarithmscale) {
    _energy->setLogarithmicScale(logarithmscale);
    _power->setLogarithmicScale(logarithmscale);
    return _energy->init() && _power->init();
}

PitchAutocor *MathManager::pitchAutocor() const
{
    return _pitchAutocor;
}

PitchCepstrum *MathManager::pitchCepstrum() const
{
    return _pitchCepstrum;
}

Cepstrum *MathManager::cepstrum() const
{
    return _cepstrum;
}

PowerDensitySpectral *MathManager::psd() const
{
    return _psd;
}

LPCSpectrum *MathManager::lpcSpectrum() const
{
    return _lpcSpectrum;
}



/*PitchYin *MathManager::pitchYin() const
{
    return _pitchYin;
}*/

PitchSalience *MathManager::pitchSalience() const
{
    return _pitchSalience;
}

DCT *MathManager::dct() const
{
    return _dct;
}

LPC *MathManager::lpc() const
{
    return _lpc;
}

Loudness *MathManager::loudness() const
{
    return _loudness;
}

ZeroCrossingRate *MathManager::zcr() const
{
    return _zcr;
}

FFT *MathManager::fft() const
{
    return _fft;
}

AutoCorrelation *MathManager::autocor() const
{
    return _autocor;
}

Power *MathManager::power() const
{
    return _power;
}

Energy *MathManager::energy() const
{
    return _energy;
}

MathManager::MathManager(QObject *parent) : QObject(parent)
{
    _frameCutter = new FrameCutter();
    _energy = new Energy();
    _power = new Power();
    _autocor = new AutoCorrelation();
    _fft = new FFT();
    _zcr = new ZeroCrossingRate();
    _loudness =  new Loudness();
    _lpc = new LPC();
    _dct = new DCT();
    _mfcc = new MFCC();
    _melBands = new MelBands();
    _pitchSalience = new PitchSalience();
    _pitchAutocor = new PitchAutocor();
    _pitchCepstrum = new PitchCepstrum();
    _cepstrum = new Cepstrum();
    _psd = new PowerDensitySpectral();
    _lpcSpectrum = new LPCSpectrum();
    //_pitchYin = new PitchYin();
}

