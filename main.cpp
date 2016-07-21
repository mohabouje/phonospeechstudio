#include "mainwindow.h"
#include <QCoreApplication>
#include <QApplication>
#include <QStyleFactory>
#include "portaudiohelper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qRegisterMetaType<AM::AudioBuffer>();
    qRegisterMetaType<AM::AudioDeviceInfo>();



    qApp->setStyle(QStyleFactory::create("Fusion"));
    /*QPalette p = qApp->palette();
    p.setColor(QPalette::Window, QColor(53,53,53));
    p.setColor(QPalette::Button, QColor(53,53,53));
    p.setColor(QPalette::Highlight, QColor(142,45,197));
    p.setColor(QPalette::ButtonText, QColor(255,255,255));
    p.setColor(QPalette::WindowText, QColor(255,255,255));*/
    //qApp->setPalette(p);

    return a.exec();
}
