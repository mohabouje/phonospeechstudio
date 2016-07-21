#include "levelwidget.h"
#include <qwt_color_map.h>
#include <qwt_scale_engine.h>
#include <QDebug>
LevelWidget::LevelWidget(QWidget *parent) :
    QwtThermo(parent)
{
    applyStyle();
    setRange(0,1);
}


void LevelWidget::setRange(double min, double max) {
    setScale(min, max);
    updateColorMap();
}



void LevelWidget::updateColorMap() {
    QwtLinearColorMap* linearColorMap = new QwtLinearColorMap(Qt::black, Qt::red);
    linearColorMap->addColorStop(0.3, Qt::green);
    linearColorMap->addColorStop(0.6, Qt::yellow);
    setColorMap(linearColorMap);
}

void LevelWidget::applyStyle() {
    QPalette _palette = palette();
    _palette.setColor(QPalette::Base, Qt::transparent);
    setPalette(_palette);
}


