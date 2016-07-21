#include "melbands.h"
#include "mathutil.h"
#include <QDebug>
#include <QFile>

MelBands::MelBands()
{
    _fft = new FFT();
}

bool MelBands::init()
{
    if (!_inputSize || !_fftSize || !_numBands || !_sampleRate) {
        qWarning() << "MelBands: Error while loading required fields.";
        _initialized = false;
        return false;
    }
    _inputData = Frame(_inputSize);
    _energyBands = Frame(_numBands);
    _fft->setEstimateSpectrum(true);
    _fft->setLogarithmicScale(false);
    _fft->setInputSize(_fftSize);
    _fft->init();
    loadFilterFrequencies();
    loadFilterCoefficients();
    _initialized = true;
    return true;
}

int MelBands::numBands() const
{
    return _numBands;
}

void MelBands::setNumBands(int numBands)
{
    _numBands = numBands;
}

int MelBands::sampleRate() const
{
    return _sampleRate;
}

void MelBands::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;
}

void MelBands::setInputData(const Frame &inputData)
{
    _inputData = inputData;
}

const Frame &MelBands::outputFrame() const
{
    return _energyBands;
}

int MelBands::inputSize() const
{
    return _inputSize;
}

void MelBands::setInputSize(int inputSize)
{
    _inputSize = inputSize;
}

int MelBands::fftSize() const
{
    return _fftSize;
}

void MelBands::setFftSize(int fftSize)
{
    _fftSize = fftSize;
}

int MelBands::lowFrequencyBound() const
{
    return _lowFrequencyBound;
}

void MelBands::setLowFrequencyBound(int lowFrequencyBound)
{
    _lowFrequencyBound = lowFrequencyBound;
}

int MelBands::highFrequencyBound() const
{
    return _highFrequencyBound;
}

void MelBands::setHighFrequencyBound(int highFrequencyBound)
{
    _highFrequencyBound = highFrequencyBound;
}

void MelBands::preProcessing()
{
    _fft->setInputData(_inputData);
    _fft->exec();
    _spectrum = _fft->outputFrame();
}

void MelBands::processing()
{
    const int spectrumSize = _spectrum.size();
    Sample frequencyScale = ((Sample) _sampleRate) / (spectrumSize - 1);
    for (int i=0; i<_numBands; ++i) {
        _energyBands[i] = 0;
        int jbegin = int(_filterFrequencies[i] / frequencyScale + 0.5);
        int jend = int(_filterFrequencies[i+2] / frequencyScale + 0.5);
        for (int j=jbegin; j<jend; ++j) {
          _energyBands[i] += _spectrum[j] * _filterCoefficients[i][j];
        }
    }
}



void MelBands::loadFilterFrequencies()
{
    const int filterSize =  _numBands + 2;
    _filterFrequencies = Frame(filterSize);
    Sample highMelFrequencyBound = hz2mel(_highFrequencyBound);
    Sample lowMelFrequencyBound = hz2mel(_lowFrequencyBound);
    Sample melFrequencyIncrement = (highMelFrequencyBound - lowMelFrequencyBound)/(_numBands + 1);

    Sample melFreq = lowMelFrequencyBound;
    for (int i=0; i<filterSize; ++i) {
      _filterFrequencies[i] = mel2Hz(melFreq);
      melFreq += melFrequencyIncrement; // increment linearly in mel-scale
    }

}

void MelBands::loadFilterCoefficients()
{

    const int spectrumSize = _fft->fftSize();
    _filterCoefficients = FrameCollection(_numBands, Frame(spectrumSize, 0.0));
    Sample frequencyScale = (((Sample) _sampleRate)) / (spectrumSize - 1);
    for (int i=0; i<_numBands; ++i) {
        Sample fstep1 = hz2mel(_filterFrequencies[i+1]) - hz2mel(_filterFrequencies[i]);
        Sample fstep2 = hz2mel(_filterFrequencies[i+2]) - hz2mel(_filterFrequencies[i+1]);

        int jbegin = int(_filterFrequencies[i] / frequencyScale + 0.5);
        int jend = int(_filterFrequencies[i+2] / frequencyScale + 0.5);
        for (int j=jbegin; j<jend; ++j) {
            if (j < 0 || j > spectrumSize)
                continue;
            Sample binfreq = j*frequencyScale;
            if ((binfreq >= _filterFrequencies[i]) && (binfreq < _filterFrequencies[i+1])) {
                _filterCoefficients[i][j] = (hz2mel(binfreq) - hz2mel(_filterFrequencies[i])) / fstep1;
            }
            else if ((binfreq >= _filterFrequencies[i+1]) && (binfreq < _filterFrequencies[i+2])) {
                _filterCoefficients[i][j] = (hz2mel(_filterFrequencies[i+2]) - hz2mel(binfreq)) / fstep2;
            }
        }
    }

    for (int i=0; i<_numBands; ++i) {
        Sample weight = 0.0;
        for (int j=0; j<spectrumSize; ++j)
            weight += _filterCoefficients[i][j];
        if (weight == 0)
            continue;
        for (int j=0; j<spectrumSize; ++j)
             _filterCoefficients[i][j] = _filterCoefficients[i][j] / weight;
    }
}
