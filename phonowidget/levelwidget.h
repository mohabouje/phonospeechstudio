#ifndef LEVELWIDGET_H
#define LEVELWIDGET_H

#include <QWidget>
#include <qwt_thermo.h>



class LevelWidget : public QwtThermo
{
    Q_OBJECT

public:
    LevelWidget(QWidget *parent = 0);
private:
    void setRange(double min, double max);
    void updateColorMap();
    void applyStyle();
};

#endif // LEVELWIDGET_H
