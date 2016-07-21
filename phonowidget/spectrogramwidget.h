#ifndef SPECTROGRAMWIDGET_H
#define SPECTROGRAMWIDGET_H

#include "chartwidget.h"
#include "spectrogram.h"

#include <QWidget>

class SpectrogramWidget : public ChartWidget
{
    Q_OBJECT
public:
    explicit SpectrogramWidget(QWidget *parent = 0);
    void initData(const int rows, const int columns);
    void append(const FrameCollection &data);
signals:

public slots:

private:
    Spectrogram* _spectrogram;


};

#endif // SPECTROGRAMWIDGET_H
