#ifndef MATHMANAGER_H
#define MATHMANAGER_H

#include "phonoaudio/portaudiohelper.h"

#include "windowing.h"
#include "framecutter.h"
#include "energy.h"
#include "power.h"
#include "autocorrelation.h"
#include "fft.h"
#include "zerocrossingrate.h"
#include "loudness.h"
#include "lpc.h"
#include "dct.h"
#include "melbands.h"
#include "mfcc.h"
#include "cepstrum.h"
#include "powerdensityspectral.h"
#include "lpcspectrum.h"
#include "pitchsalience.h"
//#include "pitchyin.h"
#include "pitchautocor.h"
#include "pitchcepstrum.h"
#include <QObject>


#define keyWindowType "processing/window_type"
#define keyWindowTime "processing/window_time"
#define keyWindowHope "processing/window_hope"
#define keyBuffer "processing/buffer"
#define keySpectrumType "processing/spectrum_type"
#define keySpectrumSize "processing/spectrum_size"
#define keySpectrumLPC "processing/spectrum_lpc"
#define keySpectrumFilterBank "processing/spectrum_fb"
#define keySpectrumCepstrum "processing/spectrum_cepstrum"
#define keyPitchAlgorithm "processing/pitch_algorithm"


#define MATHMANAGER MathManager::instance()

class AutoCorrelation;
class FrameCutter;
class Energy;
class Power;
class FFT;
class ZeroCrossingRate;
class Loudness;
class LPC;
class DCT;
class MFCC;
class MelBands;
class PitchSalience;
//class PitchYin;
class PitchAutocor;
class PitchCepstrum;
class Cepstrum;
class PowerDensitySpectral;
class LPCSpectrum;
class MathManager : public QObject
{
    Q_OBJECT
private:
    static MathManager* s_mathManager;
    explicit MathManager(QObject *parent = 0);
public:
    static MathManager* instance(QObject *parent = 0);
    FrameCutter *frameCutter() const;
    Energy *energy() const;
    Power *power() const;
    AutoCorrelation *autocor() const;
    FFT *fft() const;
    ZeroCrossingRate *zcr() const;
    Loudness *loudness() const;
    LPC *lpc() const;
    DCT *dct() const;
    PitchSalience *pitchSalience() const;
   //PitchYin *pitchYin() const;

    bool initFrameCutter(const int sampleRate, const double bufferTime, const double frameTime, const double hopeTime, const Windowing::WindowType windowTipe);
    bool initAlgorithms(const bool logarithmscale);


    PitchAutocor *pitchAutocor() const;
    PitchCepstrum *pitchCepstrum() const;
    Cepstrum *cepstrum() const;
    PowerDensitySpectral *psd() const;
    LPCSpectrum *lpcSpectrum() const;

private:
    AutoCorrelation *_autocor;
    FrameCutter *_frameCutter;
    Energy *_energy;
    Power *_power;
    FFT   *_fft;
    ZeroCrossingRate* _zcr;
    Loudness *_loudness;
    LPC *_lpc;
    DCT *_dct;
    MFCC *_mfcc;
    MelBands *_melBands;
    PitchSalience* _pitchSalience;
    PitchAutocor* _pitchAutocor;
    PitchCepstrum* _pitchCepstrum;
    Cepstrum*   _cepstrum;
    PowerDensitySpectral* _psd;
    LPCSpectrum* _lpcSpectrum;
    //PitchYin* _pitchYin;
};


#endif // MATHMANAGER_H
