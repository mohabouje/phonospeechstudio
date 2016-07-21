#include "chartwidget.h"
#include "ui_chartwidget.h"
#include "boost/algorithm/minmax_element.hpp"
#include "utility"
#include <QFileDialog>
#include <QDir>
#include <QMenu>
#include <QPrinter>
#include <QPrintDialog>

ChartWidget::ChartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartWidget),
    plot(new QwtPlotCurve),
    grid(new QwtPlotGrid),
    mustPlot(false)
{
    ui->setupUi(this);

    plot->attach(ui->chart);
    grid->attach(ui->chart);
    defaultStyle();

    _group = new QButtonGroup;
    connect(_group, SIGNAL(buttonClicked(int)), this, SLOT(buttonClicked(int)));
    connect(ui->chart, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(populateContextMenu(QPoint)));
    connect(ui->print, SIGNAL(clicked(bool)), this, SLOT(print()));
    connect(ui->save, SIGNAL(clicked(bool)), this, SLOT(save()));
}

void ChartWidget::append(double* newData, const int count) {
    for (int i=0; i<count;i++) {
        data.circular.push_back(newData[i]);
    }
    std::copy(data.circular.begin(), data.circular.end(), data.yData);

    auto pair = boost::minmax_element(data.circular.begin(), data.circular.end());
    const double _min = *(pair.first);
    const double _max = *(pair.second);

    ui->chart->setAxisScale(QwtPlot::Axis::yLeft, _min, _max);
    ui->chart->replot();
}

void ChartWidget::addButton(QToolButton* button) {
    button->setCheckable(true);
    button->setChecked(false);
    ui->buttonsWidget->layout()->addWidget(button);
    _group->addButton(button);
}

void ChartWidget::setCurrentAction(const int index) {
    if (index < 0 || index > _group->buttons().size())
        return;

    _group->buttons().at(index)->setChecked(true);
    ChartActions chartAction = ChartActions(_group->buttons().at(index)->property("chart").toInt());
    if (_currentAction !=  chartAction) {
        _currentAction = chartAction;
        initData(_dataCount);
    }
}

void ChartWidget::buttonClicked(const int index) {
    ChartActions chartAction = ChartActions(_group->button(index)->property("chart").toInt());
    if (_currentAction !=  chartAction) {
        _currentAction = chartAction;
        initData(_dataCount);
    }
}

void ChartWidget::initData(const int count) {
    _dataCount = count;
    data.count = count;
    data.yData = new double[count];
    data.xData = new double[count];
    data.circular = CircularBuffer(count);
    for (int i=0; i<count; i++) {
        data.xData[i] = i;
        data.yData[i] = 0;
        data.circular.push_back(0);
    }
    plot->setRawSamples(data.xData, data.yData, data.count);
}


void ChartWidget::setAxisScale(const QwtPlot::Axis axis, const double min, const double max) {
    ui->chart->setAxisScale(axis, min, max);
}

void ChartWidget::defaultStyle() {
    plot->setPen(QPen(QColor(Qt::red),1));
    plot->setStyle(QwtPlotCurve::Lines);
    grid->setPen(QPen(Qt::gray, 0.0, Qt::DotLine));
    grid->enableX(true);
    grid->enableY(true);
    ui->chart->enableAxis(QwtPlot::xBottom, true);
    ui->chart->enableAxis(QwtPlot::yLeft, true);
}

QwtPlot* ChartWidget::chart() const {
    return ui->chart;
}

ChartActions ChartWidget::currentAction() const
{
    return _currentAction;
}


ChartWidget::~ChartWidget()
{
    delete ui;
}


void ChartWidget::print() {
    QPrinter printer;
    printer.setOrientation(QPrinter::Landscape);

    QPrintDialog dialog(&printer);
    if (dialog.exec()) {
    }

}

void ChartWidget::save() {
    const QPixmap qPix = ui->chart->grab();
    if  (qPix.isNull())
        return;
    QString fileName = QFileDialog::getSaveFileName(this,tr("Export Chart As File"),".",tr("JPEG (*.jpg)\nBMP (*.bmp)\nPNG (*.png)"));
    if (!fileName.isEmpty()) {
        QFileInfo f(fileName);
        const QString sufix = f.suffix();
        const QString name = f.baseName();
        if (sufix == "jpg"){
            qPix.save( name, "JPEG" );
        } else if (sufix == "png") {
            qPix.save( name, "PNG" );
        } else if (sufix == "bmp") {
            qPix.save( name, "BMP" );
        }
    }
}


void ChartWidget::populateContextMenu(const QPoint& pos) {

    QMenu* menu = new QMenu(this);
    QAction* copyChart = menu->addAction(tr("Copy"));
    copyChart->setIcon(QIcon(":resources/icons/copy.png"));
    QAction* exportChart = menu->addAction(tr("Export"));
    exportChart->setIcon(QIcon(":resources/icons/save.png"));
    QAction* actionClicked = menu->exec(ui->chart->mapToGlobal(pos));
    if (!actionClicked)
        return;

    if (actionClicked == copyChart) {
        //sender->savePng( QDir::currentPath()+"/temp.png",  0, 0, 1.0, -1);
        //QApplication::clipboard()->setPixmap( QPixmap(QDir::currentPath()+"/temp.png") );
    } else {
        save();
    }
}
