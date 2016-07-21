#ifndef SPECTROGRAMDATA_H
#define SPECTROGRAMDATA_H
#include "mathalgorithm.h"
#include <QWidget>
#include <qwt_raster_data.h>
#include <qwt_matrix_raster_data.h>
#include "config.h"

class SpectrogramData : public QwtMatrixRasterData {
public:
    SpectrogramData(const int rows, const int columns);

    virtual double value( double x, double y ) const
    {
        return QwtMatrixRasterData::value( y, x );
    }
    int sampleCount() const;
    int rows() const;
    int columns() const;
    void append(const FrameCollection &frames);
private:
    int _rows;
    int _columns;
    int _sampleCount;
    Frame _data;
    CircularBuffer _temp;
};

#endif // SPECTROGRAMDATA_H
