#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "fftw3.h"
#include <QVector>

typedef QVector<double> Frame;
typedef QVector< QVector<double> > FrameCollection;
typedef double Sample;
typedef float AudioSample;
typedef fftw_complex ComplexSample;

class MathAlgorithm
{
public:
    MathAlgorithm();
    virtual bool init() = 0;
    void exec();
    bool initialized() const;

    virtual void setInputData(const Frame &data) = 0;
    virtual const Frame& outputFrame() const = 0;
    virtual const Sample outputSample() const = 0;


    virtual void preProcessing() = 0;
    virtual void processing() = 0;
    virtual void postProcessing() = 0;
protected:
    bool _initialized;

};


#endif // ALGORITHM_H
