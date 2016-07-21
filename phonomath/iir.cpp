#include "iir.h"
#include <QDebug>
IIR::IIR()
{

}

bool IIR::init()
{
    if (!_inputSize || _numerator.isEmpty()  || _denominator.isEmpty()) {
        qWarning() << "DCFilter: Error while loading required fields.";
        _initialized = false;
        return false;
    }
    _inputData = Frame(_inputSize);
    _filteredData = Frame(_inputSize);
    normalize();
    _initialized = true;
    return true;
}

void IIR::setInputData(const Frame &inputData)
{
    _inputData = inputData;
}

int IIR::inputSize() const
{
    return _inputSize;
}

void IIR::setInputSize(int inputSize)
{
    _inputSize = inputSize;
}

const Frame& IIR::denominator() const
{
    return _denominator;
}

void IIR::setDenominator(const Frame &denominator)
{
    _denominator = denominator;
}

const Frame& IIR::numerator() const
{
    return _numerator;
}

void IIR::setNumerator(const Frame &numerator)
{
    _numerator = numerator;
}

const Frame &IIR::outputFrame() const
{
    return _filteredData;
}

void IIR::reset() {
    for (int i=0; i<_state.size(); ++i) {
        _state[i] = 0.0;
    }
}


void IIR::normalize()
{
    const int numSize = _numerator.size();
    const int denSize = _denominator.size();

    for (int i=0; i<numSize; i++) {
        _numerator[i] /= _denominator[0];
    }
    for (int i=0; i<denSize; i++) {
        _denominator[i] /= _denominator[0];
    }

    int wantedSize = std::max(_numerator.size(), _denominator.size());
    if (_state.size() != wantedSize) {
        _state.resize(wantedSize);
        reset();
    }
}

inline bool isDenormal(const Sample& x) {
  auto val = std::fpclassify(x) ;
  return val == FP_INFINITE || val == FP_NAN || val == FP_SUBNORMAL;
}

inline void renormalize(Sample& x) {
    x = Sample(0.0);
}


inline void updateStateLine(Frame& state, int size,
                            const Frame& a, const Frame& b,
                            const Sample& x, const Sample& y) {
  for (int k=1; k<size; ++k) {
    state[k-1] = (b[k]*x - a[k]*y) + state[k];
    renormalize(state[k-1]);
  }
}

template <int n>
void updateStateLineUnrolled(Frame& state,
                            const Frame& a, const Frame& b,
                            const Sample& x, Sample& y) {
  for (int k=1; k<n; ++k) {
    state[k-1] = b[k]*x - a[k]*y + state[k];
  }

  for (int k=1; k<n; ++k) {
    renormalize(state[k-1]);
  }

}

template <int filterSize>
void filterABEqualSize(const Frame& x, Frame& y,
                       const Frame& a, const Frame& b,
                       Frame& state) {
  for (int n=0; n < int(y.size()); ++n) {
    y[n] = b[0]*x[n] + state[0];
    updateStateLineUnrolled<filterSize>(state, a, b, x[n], y[n]);
  }
}

void IIR::preProcessing() {

}

void IIR::postProcessing() {

}

void IIR::processing() {


  if (_numerator.size() == _denominator.size()) {
    switch (_denominator.size()) {
    case 2:  filterABEqualSize<2> (_inputData, _filteredData, _denominator, _numerator, _state); break;
    case 3:  filterABEqualSize<3> (_inputData, _filteredData, _denominator, _numerator, _state); break;
    case 4:  filterABEqualSize<4> (_inputData, _filteredData, _denominator, _numerator, _state); break;
    case 5:  filterABEqualSize<5> (_inputData, _filteredData, _denominator, _numerator, _state); break;
    case 6:  filterABEqualSize<6> (_inputData, _filteredData, _denominator, _numerator, _state); break;
    case 7:  filterABEqualSize<7> (_inputData, _filteredData, _denominator, _numerator, _state); break;
    case 8:  filterABEqualSize<8> (_inputData, _filteredData, _denominator, _numerator, _state); break;
    case 9:  filterABEqualSize<9> (_inputData, _filteredData, _denominator, _numerator, _state); break;
    case 10: filterABEqualSize<10>(_inputData, _filteredData, _denominator, _numerator, _state); break;
    case 11: filterABEqualSize<11>(_inputData, _filteredData, _denominator, _numerator, _state); break;
    case 12: filterABEqualSize<12>(_inputData, _filteredData, _denominator, _numerator, _state); break;
    case 13: filterABEqualSize<13>(_inputData, _filteredData, _denominator, _numerator, _state); break;
    case 14: filterABEqualSize<14>(_inputData, _filteredData, _denominator, _numerator, _state); break;
    case 15: filterABEqualSize<15>(_inputData, _filteredData, _denominator, _numerator, _state); break;
    case 16: filterABEqualSize<16>(_inputData, _filteredData, _denominator, _numerator, _state); break;

    default:
      for (int n=0; n < _filteredData.size(); ++n) {
        _filteredData[n] = _numerator[0]*_inputData[n] + _state[0];
        updateStateLine(_state, _state.size(), _denominator, _numerator, _inputData[n], _filteredData[n]);
      }
    }
  }

  else if (_numerator.size() > _denominator.size()) {
    for (int n=0; n < _filteredData.size(); ++n) {
      _filteredData[n] = _numerator[0]*_inputData[n]  + _state[0];
      updateStateLine(_state, _denominator.size(), _denominator, _numerator, _inputData[n], _filteredData[n]);

      for (int k=_denominator.size(); k < int(_state.size()); ++k) {
        _state[k-1] = _numerator[k]*_inputData[n]  + _state[k];
        renormalize(_state[k-1]);
      }
    }
  }

  else { //if (a.size() > b.size()) {
    for (int n=0; n < _filteredData.size(); ++n) {
      _filteredData[n] = _numerator[0]*_inputData[n]  + _state[0];
      updateStateLine(_state, _numerator.size(), _denominator, _numerator, _inputData[n], _filteredData[n]);

      for (int k=_numerator.size(); k < int(_state.size()); ++k) {
        _state[k-1] = (-_denominator[k]*_filteredData[n])  + _state[k];
        renormalize(_state[k-1]);
      }
    }
  }
}

