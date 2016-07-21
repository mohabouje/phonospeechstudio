#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include "util.h"
#include "config.h"

#include <QWidget>
#include <QButtonGroup>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <QToolButton>
#include <boost/circular_buffer.hpp>
#define DEFAULT_MAX_XBOTTOM 5
namespace Ui {
class ChartWidget;
}

typedef boost::circular_buffer<double>  CircularBuffer;
class ChartWidget : public QWidget
{
    Q_OBJECT

    struct ChartData {
        CircularBuffer  circular;
        double* xData;
        double* yData;
        int count;
    };

public:
    explicit ChartWidget(QWidget *parent = 0);
    ~ChartWidget();    
    void append(double *newData, const int count);
    void initData(const int count);
    void setAxisScale(const QwtPlot::Axis axis, const double min, const double max);
    void addButton(QToolButton *button);
    void setCurrentAction(const int index);
    ChartActions currentAction() const;
    QwtPlot *chart() const;
private slots:
    void populateContextMenu(const QPoint &pos);
    void print();
    void save();
    void buttonClicked(const int index);
private:
    Ui::ChartWidget *ui;
    int _dataCount;
    QwtPlotCurve* plot;
    QwtPlotGrid* grid;
    QButtonGroup* _group;
    ChartData data;
    bool mustPlot;
    void defaultStyle();
    ChartActions _currentAction;
};

#endif // CHARTWIDGET_H
