#ifndef SPECTROGRAM_H
#define SPECTROGRAM_H

#include <QWidget>
#include "qwt_plot_spectrogram.h"
#include "spectrogramdata.h"

class Spectrogram : public QwtPlotSpectrogram
{
public:
    enum ColorMap {
        Spectro = 0,
        Jet,
        Grey,
        Hot,
        Cooper,
        Default
    };

    explicit Spectrogram(const int rows, const int columns, const QString &title = QString::null);

    void setInterval(Qt::Axis axis, const QwtInterval &interval);
    void setColorMap(ColorMap m_colormap);
    void appendData(const FrameCollection &frames);
signals:

public slots:

private:
    SpectrogramData* _data;
};

#endif // SPECTROGRAM_H
