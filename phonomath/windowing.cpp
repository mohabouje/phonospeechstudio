#include "windowing.h"
#include <QDebug>

bool Windowing::init()
{
    if (!_size || !_windowType) {
        qWarning() << "Windowing: Error while loading required fields.";
        _initialized = false;
        return false;
    }
    _window = Frame(_size);
    _initialized = true;
    return true;
}

unsigned int Windowing::size() const
{
    return _size;
}

void Windowing::setSize(unsigned int size)
{
    _size = size;
}

const Frame& Windowing::outputFrame() const
{
    return _window;
}

Windowing::WindowType Windowing::windowType() const
{
    return _windowType;
}

void Windowing::setWindowType(const WindowType &windowType)
{
    _windowType = windowType;
}

void Windowing::hamming() {
  const int size = _window.size();

  for (int i=0; i<size; i++) {
    _window[i] = 0.53836 - 0.46164 * cos((2.0*M_PI*i) / (size - 1.0));
  }
}

void Windowing::hann() {
  const int size = _window.size();

  for (int i=0; i<size; i++) {
    _window[i] = 0.5 - 0.5 * cos((2.0*M_PI*i) / (size - 1.0));
  }
}

void Windowing::triangular() {
  int size = int(_window.size());

  for (int i=0; i<size; i++) {
    _window[i] = 2.0/size * (size/2.0 - abs((Sample)(i - (size-1.)/2.)));
  }
}

void Windowing::square() {
  for (int i=0; i<int(_window.size()); i++) {
    _window[i] = 1.0;
  }
}


void Windowing::blackmanHarris() {
  double a0 = .40217, a1 = .49703, a2 = .09892, a3 = .00188;
  int size = _window.size();

  double fConst = 2.0 * M_PI / (size-1);

  if (size % 2 !=0) {
    _window[size/2] = a0 - a1 * cos(fConst * (size/2)) + a2 *
      cos(fConst * 2 * (size/2)) - a3 * cos(fConst * 3 * (size/2));
  }

  for (int i=0; i<size/2; i++) {
    _window[i] = _window[size-i-1] = a0 - a1 * cos(fConst * i) +
      a2 * cos(fConst * 2 * i) - a3 * cos(fConst * 3 * i);
  }
}

void Windowing::processing()
{
    switch (_windowType) {
    case BlackmanHarris:
        blackmanHarris();
        break;
    case Hamming:
        hamming();
        break;
    case Hann:
        hann();
        break;
    case Square:
        square();
        break;
    case Triangular:
        triangular();
        break;
    default:
        hamming();
        break;
    }

}


