#ifndef WINDOWING_H
#define WINDOWING_H
#include <mathalgorithm.h>

class Windowing : public MathAlgorithm
{
public:
    Windowing() {}
    bool init();
    void setInputData(const Frame& ) {}
    const Frame& outputFrame() const;

    enum WindowType {
        BlackmanHarris = 0,
        Hamming,
        Hann,
        Square,
        Triangular
    };
    unsigned int size() const;
    void setSize(unsigned int size);
    WindowType windowType() const;
    void setWindowType(const WindowType &windowType);

private:
    unsigned int _size;
    Frame _window;
    WindowType _windowType;

    void hamming();
    void hann();
    void triangular();
    void square();
    void blackmanHarris();

    const Sample outputSample() const { return 0.0;}
    void postProcessing() {}
    void processing();
    void preProcessing() {}
};

#endif // WINDOWING_H
