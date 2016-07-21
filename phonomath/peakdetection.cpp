#include "peakdetection.h"
#include <QDebug>

PeakDetection::PeakDetection()
{
    _maxPeaks = 100;

}

bool PeakDetection::getInterpolate() const
{
    return _interpolate;
}

void PeakDetection::setInterpolate(bool interpolate)
{
    _interpolate = interpolate;
}

int PeakDetection::minPos() const
{
    return _minPos;
}

void PeakDetection::setMinPos(int minPos)
{
    _minPos = minPos;
}

int PeakDetection::maxPos() const
{
    return _maxPos;
}

void PeakDetection::setMaxPos(int maxPos)
{
    _maxPos = maxPos;
}

int PeakDetection::maxPeaks() const
{
    return _maxPeaks;
}

void PeakDetection::setMaxPeaks(int maxPeaks)
{
    _maxPeaks = maxPeaks;

}

Sample PeakDetection::range() const
{
    return _range;
}

void PeakDetection::setRange(const Sample &range)
{
    _range = range;
    _scale = _range / (Sample)(_inputSize - 1);
}

Sample PeakDetection::threshold() const
{
    return _threshold;
}

void PeakDetection::setThreshold(const Sample &threshold)
{
    _threshold = threshold;
}

const Frame& PeakDetection::amplitudes() const
{
    return _amplitudes;
}

const Frame& PeakDetection::positions() const
{
    return _positions;
}

const Frame &PeakDetection::outputFrame() const
{
    return _positions;
}

int PeakDetection::getInputSize() const
{
    return _inputSize;
}

void PeakDetection::setInputSize(int inputSize)
{
    _inputSize = inputSize;
}

void PeakDetection::setInputData(const Frame &inputData)
{
    _inputData = inputData;
}

bool PeakDetection::init() {

    if (!_inputSize ) {
        qWarning() << "PeakDetection: Error while loading required fields.";
        _initialized = false;
        return false;
    }
    _initialized = true;
    return _initialized;
}



void PeakDetection::processing() {
    int i = std::max(0, int(ceil(_minPos / _scale)));
    // first check the boundaries:
    if (i+1 < _inputSize && _inputData[i] > _inputData[i+1] && _inputData[i] > _threshold)
        _peaks.append(Peak(i*_scale, _inputData[i]));

    while(true) {
        // going down
        while (i+1 < _inputSize-1 && _inputData[i] >= _inputData[i+1]) {
          i++;
        }

        // now we're climbing
        while (i+1 < _inputSize-1 && _inputData[i] < _inputData[i+1]) {
          i++;
        }

        // not anymore, go through the plateau
        int j = i;
        while (j+1 < _inputSize-1 && (_inputData[j] == _inputData[j+1])) {
          j++;
        }

        // end of plateau, do we go up or down?
        if (j+1 < _inputSize-1 && _inputData[j+1] < _inputData[j] && _inputData[j] > _threshold) { // going down again
            Sample resultBin = 0.0;
            Sample resultVal = 0.0;
            if (j != i) { // plateau peak between i and j
                resultBin = (_interpolate) ? (i + j) * 0.5 : i;
                resultVal = _inputData[i];
            } else { // interpolate peak at i-1, i and i+1
                if (_interpolate) {
                  interpolate(_inputData[j-1], _inputData[j], _inputData[j+1], j, resultVal, resultBin);
                } else {
                  resultBin = j;
                  resultVal = _inputData[j];
                }
            }


            Sample resultPos = resultBin * _scale;
            if (resultPos > _maxPos)
                break;
            _peaks.append(Peak(resultPos, resultVal));
        }

        // nothing found, start loop again
        i = j;

        if (i+1 >= _inputSize-1) { // check the one just before the last position
          if (i == _inputSize-2 && _inputData[i-1] < _inputData[i] &&
              _inputData[i+1] < _inputData[i] &&
              _inputData[i] > _threshold) {
            Sample resultBin = 0.0;
            Sample resultVal = 0.0;
            if (_interpolate) {
              interpolate(_inputData[i-1], _inputData[i], _inputData[i+1], j, resultVal, resultBin);
            }
            else {
              resultBin = i;
              resultVal = _inputData[i];
            }
            _peaks.append(Peak(resultBin*_scale, resultVal));
          }
          break;
        }
      }
    // check upper boundary here, so peaks are already sorted by position
    Sample pos = _maxPos/_scale;
    if (_inputSize-2 <pos && pos <= _inputSize-1 && _inputData[_inputSize-1] > _inputData[_inputSize-2]) {
        if (_inputData[_inputSize-1] > _threshold) {
          _peaks.append(Peak((_inputSize-1)*_scale, _inputData[_inputSize-1]));
        }
    }
}

void PeakDetection::postProcessing() {
    qSort(_peaks.begin(), _peaks.end(), [](Peak& a, Peak &b){return a.second > b.second;});
    int nWantedPeaks = std::min((int)_maxPeaks, (int)_peaks.size());
    _positions.resize(nWantedPeaks);
    _amplitudes.resize(nWantedPeaks);

    for (int k=0; k<nWantedPeaks; k++) {
        _positions[k] = _peaks[k].first;
        _amplitudes[k] = _peaks[k].second;
    }
}


/**
* http://ccrma.stanford.edu/~jos/parshl/Peak_Detection_Steps_3.html
*
* Estimating the "true" maximum peak (frequency and magnitude) of the detected local maximum
* using a parabolic curve-fitting. The idea is that the main-lobe of spectrum of most analysis
* windows on a dB scale looks like a parabola and therefore the maximum of a parabola fitted
* through a local maximum bin and it's two neighboring bins will give a good approximation
* of the actual frequency and magnitude of a sinusoid in the input signal.
*
* The parabola f(x) = a(x-n)^2 + b(x-n) + c can be completely described using 3 points;
* f(n-1) = A1, f(n) = A2 and f(n+1) = A3, where
* A1 = 20log10(|X(n-1)|), A2 = 20log10(|X(n)|), A3 = 20log10(|X(n+1)|).
*
* Solving these equation yields: a = 1/2*A1 - A2 + 1/2*A3, b = 1/2*A3 - 1/2*A1 and
* c = A2.
*
* As the 3 bins are known to be a maxima, solving d/dx f(x) = 0, yields the fractional bin
* position x of the estimated peak. Substituting delta_x for (x-n) in this equation yields
* the fractional offset in bins from n where the peak's maximum is.
*
* Solving this equation yields: delta_x = 1/2 * (A1 - A3)/(A1 - 2*A2 + A3).
*
* Computing f(n+delta_x) will estimate the peak's magnitude (in dB's):
* f(n+delta_x) = A2 - 1/4*(A1-A3)*delta_x.
*/
void PeakDetection::interpolate(const Sample leftVal, const Sample middleVal, const Sample rightVal, int currentBin, Sample& resultVal, Sample& resultBin) const {
  Sample delta_x = 0.5 * ((leftVal - rightVal) / (leftVal - 2*middleVal + rightVal));
  resultBin = currentBin + delta_x;
  resultVal = middleVal - 0.25 * (leftVal - rightVal) * delta_x;
}
