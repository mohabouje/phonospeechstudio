#include "spectrogramdata.h"
#include "mathutil.h"
#include <math.h>



int SpectrogramData::sampleCount() const
{
    return _sampleCount;
}

int SpectrogramData::rows() const
{
    return _rows;
}

int SpectrogramData::columns() const
{
    return _columns;
}

SpectrogramData::SpectrogramData(const int rows, const int columns) :
    _rows(rows),
    _columns(columns),
    _sampleCount(rows*columns),
    _data(_sampleCount, 0),
    _temp(CircularBuffer(_sampleCount))
{

}



void SpectrogramData::append(const FrameCollection& frames) {
    foreach (const Frame& frame, frames) {
        foreach(const Sample& val, frame) {
            _temp.push_back(val);
        }
    }
    std::copy(_temp.begin(), _temp.end(), _data.begin());
    //Normalize(_data);
    auto result = std::minmax_element(_data.begin(), _data.end());
    setInterval(Qt::ZAxis, QwtInterval( std::isinf(*result.first) ? -90 : *result.first, *result.second));
    setValueMatrix(_data, _columns);
}
