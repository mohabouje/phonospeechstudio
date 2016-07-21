#include "spectrogramwidget.h"

SpectrogramWidget::SpectrogramWidget(QWidget *parent) : ChartWidget(parent)
{

}

void SpectrogramWidget::initData(const int rows, const int columns)
{
    _spectrogram = new Spectrogram(rows, columns);
    _spectrogram->attach(chart());

    chart()->setAxisScale(QwtPlot::xBottom, 0, columns, 0);
    chart()->setAxisScale(QwtPlot::yLeft, 0, columns, 0);
    _spectrogram->setInterval(Qt::XAxis,QwtInterval(0, columns));
    _spectrogram->setInterval(Qt::YAxis,QwtInterval(0, columns));
    _spectrogram->setInterval(Qt::ZAxis,QwtInterval(0,1));

}

void SpectrogramWidget::append(const FrameCollection& data) {
    _spectrogram->appendData(data);
    chart()->replot();
}
