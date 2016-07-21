#include "spectrogram.h"

#include <qwt_color_map.h>

Spectrogram::Spectrogram(const int rows, const int columns, const QString &title) : QwtPlotSpectrogram(title), _data(new SpectrogramData(rows, columns))
{
    setDisplayMode(QwtPlotSpectrogram::ImageMode);
    setColorMap(Spectro);
    _data->setResampleMode(QwtMatrixRasterData::NearestNeighbour);
}

void Spectrogram::setInterval(Qt::Axis axis, const QwtInterval &interval) {
    _data->setInterval(axis, interval);
}


void Spectrogram::setColorMap(ColorMap m_colormap){
    QwtLinearColorMap *m_colorMap;
    switch (m_colormap) {
    double pos;
    case Spectro: // spectrogram
            m_colorMap = new QwtLinearColorMap(QColor(0,0,0), QColor(255,0,0));
            pos = 1.0/25.0*1.0; m_colorMap->addColorStop(pos, QColor(0,0,0));
            pos = 1.0/25.0*2.0; m_colorMap->addColorStop(pos, QColor(0,0,0));
            pos = 1.0/25.0*3.0; m_colorMap->addColorStop(pos, QColor(0,0,51));
            pos = 1.0/25.0*4.0; m_colorMap->addColorStop(pos, QColor(0,0,102));
            pos = 1.0/25.0*5.0; m_colorMap->addColorStop(pos, QColor(0,0,153));
            pos = 1.0/25.0*6.0; m_colorMap->addColorStop(pos, QColor(0,50,255));
            pos = 1.0/25.0*7.0; m_colorMap->addColorStop(pos, QColor(0,100,255));
            pos = 1.0/25.0*8.0; m_colorMap->addColorStop(pos, QColor(0,150,255));
            pos = 1.0/25.0*9.0; m_colorMap->addColorStop(pos, QColor(0,200,255));
            pos = 1.0/25.0*10.0; m_colorMap->addColorStop(pos, QColor(0,255,255));
            pos = 1.0/25.0*11.0; m_colorMap->addColorStop(pos, QColor(36,255,219));
            pos = 1.0/25.0*12.0; m_colorMap->addColorStop(pos, QColor(73,255,182));
            pos = 1.0/25.0*13.0; m_colorMap->addColorStop(pos, QColor(109,255,146));
            pos = 1.0/25.0*14.0; m_colorMap->addColorStop(pos, QColor(146,255,109));
            pos = 1.0/25.0*15.0; m_colorMap->addColorStop(pos, QColor(182,255,73));
            pos = 1.0/25.0*16.0; m_colorMap->addColorStop(pos, QColor(219,255,36));
            pos = 1.0/25.0*17.0; m_colorMap->addColorStop(pos, QColor(255,255,0));
            pos = 1.0/25.0*18.0; m_colorMap->addColorStop(pos, QColor(255,180,0));
            pos = 1.0/25.0*19.0; m_colorMap->addColorStop(pos, QColor(255,120,0));
            pos = 1.0/25.0*20.0; m_colorMap->addColorStop(pos, QColor(255,80,0));
            pos = 1.0/25.0*21.0; m_colorMap->addColorStop(pos, QColor(255,60,0));
            pos = 1.0/25.0*22.0; m_colorMap->addColorStop(pos, QColor(255,50,0));
            pos = 1.0/25.0*23.0; m_colorMap->addColorStop(pos, QColor(255,36,0));
            pos = 1.0/25.0*24.0; m_colorMap->addColorStop(pos, QColor(255,0,0));
            pos = 1.0/25.0*25.0; m_colorMap->addColorStop(pos, QColor(219,0,0));
            break;
    case Jet: // jet
            m_colorMap = new QwtLinearColorMap(QColor(0,0,182), QColor(219,0,0));
            pos = 1.0/25.0*1.0; m_colorMap->addColorStop(pos, QColor(0,0,182));
            pos = 1.0/25.0*2.0; m_colorMap->addColorStop(pos, QColor(0,0,219));
            pos = 1.0/25.0*3.0; m_colorMap->addColorStop(pos, QColor(0,0,255));
            pos = 1.0/25.0*4.0; m_colorMap->addColorStop(pos, QColor(0,36,255));
            pos = 1.0/25.0*5.0; m_colorMap->addColorStop(pos, QColor(0,73,255));
            pos = 1.0/25.0*6.0; m_colorMap->addColorStop(pos, QColor(0,109,255));
            pos = 1.0/25.0*7.0; m_colorMap->addColorStop(pos, QColor(0,146,255));
            pos = 1.0/25.0*8.0; m_colorMap->addColorStop(pos, QColor(0,182,255));
            pos = 1.0/25.0*9.0; m_colorMap->addColorStop(pos, QColor(0,219,255));
            pos = 1.0/25.0*10.0; m_colorMap->addColorStop(pos, QColor(0,255,255));
            pos = 1.0/25.0*11.0; m_colorMap->addColorStop(pos, QColor(36,255,219));
            pos = 1.0/25.0*12.0; m_colorMap->addColorStop(pos, QColor(73,255,182));
            pos = 1.0/25.0*13.0; m_colorMap->addColorStop(pos, QColor(109,255,146));
            pos = 1.0/25.0*14.0; m_colorMap->addColorStop(pos, QColor(146,255,109));
            pos = 1.0/25.0*15.0; m_colorMap->addColorStop(pos, QColor(182,255,73));
            pos = 1.0/25.0*16.0; m_colorMap->addColorStop(pos, QColor(219,255,36));
            pos = 1.0/25.0*17.0; m_colorMap->addColorStop(pos, QColor(255,255,0));
            pos = 1.0/25.0*18.0; m_colorMap->addColorStop(pos, QColor(255,219,0));
            pos = 1.0/25.0*19.0; m_colorMap->addColorStop(pos, QColor(255,182,0));
            pos = 1.0/25.0*20.0; m_colorMap->addColorStop(pos, QColor(255,146,0));
            pos = 1.0/25.0*21.0; m_colorMap->addColorStop(pos, QColor(255,109,0));
            pos = 1.0/25.0*22.0; m_colorMap->addColorStop(pos, QColor(255,73,0));
            pos = 1.0/25.0*23.0; m_colorMap->addColorStop(pos, QColor(255,36,0));
            pos = 1.0/25.0*24.0; m_colorMap->addColorStop(pos, QColor(255,0,0));
            pos = 1.0/25.0*25.0; m_colorMap->addColorStop(pos, QColor(219,0,0));
            break;
    case Grey:// GREY
        m_colorMap = new QwtLinearColorMap(QColor(0,0,0), QColor(255,255,255));
        pos = 1.0/25.0*1.0; m_colorMap->addColorStop(pos, QColor(0,0,0));
        pos = 1.0/25.0*2.0; m_colorMap->addColorStop(pos, QColor(11,11,11));
        pos = 1.0/25.0*3.0; m_colorMap->addColorStop(pos, QColor(21,21,21));
        pos = 1.0/25.0*4.0; m_colorMap->addColorStop(pos, QColor(32,32,32));
        pos = 1.0/25.0*5.0; m_colorMap->addColorStop(pos, QColor(43,43,43));
        pos = 1.0/25.0*6.0; m_colorMap->addColorStop(pos, QColor(53,53,53));
        pos = 1.0/25.0*7.0; m_colorMap->addColorStop(pos, QColor(64,64,64));
        pos = 1.0/25.0*8.0; m_colorMap->addColorStop(pos, QColor(74,74,74));
        pos = 1.0/25.0*9.0; m_colorMap->addColorStop(pos, QColor(85,85,85));
        pos = 1.0/25.0*10.0; m_colorMap->addColorStop(pos, QColor(96,96,96));
        pos = 1.0/25.0*11.0; m_colorMap->addColorStop(pos, QColor(106,106,106));
        pos = 1.0/25.0*12.0; m_colorMap->addColorStop(pos, QColor(117,117,117));
        pos = 1.0/25.0*13.0; m_colorMap->addColorStop(pos, QColor(128,128,128));
        pos = 1.0/25.0*14.0; m_colorMap->addColorStop(pos, QColor(138,138,138));
        pos = 1.0/25.0*15.0; m_colorMap->addColorStop(pos, QColor(149,149,149));
        pos = 1.0/25.0*16.0; m_colorMap->addColorStop(pos, QColor(159,159,159));
        pos = 1.0/25.0*17.0; m_colorMap->addColorStop(pos, QColor(170,170,170));
        pos = 1.0/25.0*18.0; m_colorMap->addColorStop(pos, QColor(181,181,181));
        pos = 1.0/25.0*19.0; m_colorMap->addColorStop(pos, QColor(191,191,191));
        pos = 1.0/25.0*20.0; m_colorMap->addColorStop(pos, QColor(202,202,202));
        pos = 1.0/25.0*21.0; m_colorMap->addColorStop(pos, QColor(213,213,213));
        pos = 1.0/25.0*22.0; m_colorMap->addColorStop(pos, QColor(223,223,223));
        pos = 1.0/25.0*23.0; m_colorMap->addColorStop(pos, QColor(234,234,234));
        pos = 1.0/25.0*24.0; m_colorMap->addColorStop(pos, QColor(244,244,244));
        pos = 1.0/25.0*25.0; m_colorMap->addColorStop(pos, QColor(255,255,255));
        break;

    case Hot: // HOT
        m_colorMap = new QwtLinearColorMap(QColor(28,0,0), QColor(255,255,255));
        pos = 1.0/25.0*1.0; m_colorMap->addColorStop(pos, QColor(28,0,0));
        pos = 1.0/25.0*2.0; m_colorMap->addColorStop(pos, QColor(57,0,0));
        pos = 1.0/25.0*3.0; m_colorMap->addColorStop(pos, QColor(85,0,0));
        pos = 1.0/25.0*4.0; m_colorMap->addColorStop(pos, QColor(113,0,0));
        pos = 1.0/25.0*5.0; m_colorMap->addColorStop(pos, QColor(142,0,0));
        pos = 1.0/25.0*6.0; m_colorMap->addColorStop(pos, QColor(170,0,0));
        pos = 1.0/25.0*7.0; m_colorMap->addColorStop(pos, QColor(198,0,0));
        pos = 1.0/25.0*8.0; m_colorMap->addColorStop(pos, QColor(227,0,0));
        pos = 1.0/25.0*9.0; m_colorMap->addColorStop(pos, QColor(255,0,0));
        pos = 1.0/25.0*10.0; m_colorMap->addColorStop(pos, QColor(255,28,0));
        pos = 1.0/25.0*11.0; m_colorMap->addColorStop(pos, QColor(255,57,0));
        pos = 1.0/25.0*12.0; m_colorMap->addColorStop(pos, QColor(255,85,0));
        pos = 1.0/25.0*13.0; m_colorMap->addColorStop(pos, QColor(255,113,0));
        pos = 1.0/25.0*14.0; m_colorMap->addColorStop(pos, QColor(255,142,0));
        pos = 1.0/25.0*15.0; m_colorMap->addColorStop(pos, QColor(255,170,0));
        pos = 1.0/25.0*16.0; m_colorMap->addColorStop(pos, QColor(255,198,0));
        pos = 1.0/25.0*17.0; m_colorMap->addColorStop(pos, QColor(255,227,0));
        pos = 1.0/25.0*18.0; m_colorMap->addColorStop(pos, QColor(255,255,0));
        pos = 1.0/25.0*19.0; m_colorMap->addColorStop(pos, QColor(255,255,36));
        pos = 1.0/25.0*20.0; m_colorMap->addColorStop(pos, QColor(255,255,73));
        pos = 1.0/25.0*21.0; m_colorMap->addColorStop(pos, QColor(255,255,109));
        pos = 1.0/25.0*22.0; m_colorMap->addColorStop(pos, QColor(255,255,146));
        pos = 1.0/25.0*23.0; m_colorMap->addColorStop(pos, QColor(255,255,182));
        pos = 1.0/25.0*24.0; m_colorMap->addColorStop(pos, QColor(255,255,219));
        pos = 1.0/25.0*25.0; m_colorMap->addColorStop(pos, QColor(255,255,255));
        break;
    case Cooper: //Copper
        m_colorMap = new QwtLinearColorMap(QColor(0,0,0), QColor(255,199,127));
        pos = 1.0/25.0*1.0; m_colorMap->addColorStop(pos, QColor(0,0,0));
        pos = 1.0/25.0*2.0; m_colorMap->addColorStop(pos, QColor(13,8,5));
        pos = 1.0/25.0*3.0; m_colorMap->addColorStop(pos, QColor(27,17,11));
        pos = 1.0/25.0*4.0; m_colorMap->addColorStop(pos, QColor(40,25,16));
        pos = 1.0/25.0*5.0; m_colorMap->addColorStop(pos, QColor(53,33,21));
        pos = 1.0/25.0*6.0; m_colorMap->addColorStop(pos, QColor(66,42,26));
        pos = 1.0/25.0*7.0; m_colorMap->addColorStop(pos, QColor(80,50,32));
        pos = 1.0/25.0*8.0; m_colorMap->addColorStop(pos, QColor(93,58,37));
        pos = 1.0/25.0*9.0; m_colorMap->addColorStop(pos, QColor(106,66,42));
        pos = 1.0/25.0*10.0; m_colorMap->addColorStop(pos, QColor(120,75,48));
        pos = 1.0/25.0*11.0; m_colorMap->addColorStop(pos, QColor(133,83,53));
        pos = 1.0/25.0*12.0; m_colorMap->addColorStop(pos, QColor(146,91,58));
        pos = 1.0/25.0*13.0; m_colorMap->addColorStop(pos, QColor(159,100,63));
        pos = 1.0/25.0*14.0; m_colorMap->addColorStop(pos, QColor(173,108,69));
        pos = 1.0/25.0*15.0; m_colorMap->addColorStop(pos, QColor(186,116,74));
        pos = 1.0/25.0*16.0; m_colorMap->addColorStop(pos, QColor(199,125,79));
        pos = 1.0/25.0*17.0; m_colorMap->addColorStop(pos, QColor(212,133,85));
        pos = 1.0/25.0*18.0; m_colorMap->addColorStop(pos, QColor(226,141,90));
        pos = 1.0/25.0*19.0; m_colorMap->addColorStop(pos, QColor(239,149,95));
        pos = 1.0/25.0*20.0; m_colorMap->addColorStop(pos, QColor(252,158,100));
        pos = 1.0/25.0*21.0; m_colorMap->addColorStop(pos, QColor(255,166,106));
        pos = 1.0/25.0*22.0; m_colorMap->addColorStop(pos, QColor(255,174,111));
        pos = 1.0/25.0*23.0; m_colorMap->addColorStop(pos, QColor(255,183,116));
        pos = 1.0/25.0*24.0; m_colorMap->addColorStop(pos, QColor(255,191,122));
        pos = 1.0/25.0*25.0; m_colorMap->addColorStop(pos, QColor(255,199,127));
        break;
    default:
        m_colorMap = new QwtLinearColorMap(QColor(0,0,0), QColor(255,0,0));
        pos = 1.0/25.0*1.0; m_colorMap->addColorStop(pos, QColor(0,0,0));
        pos = 1.0/25.0*2.0; m_colorMap->addColorStop(pos, QColor(0,0,0));
        pos = 1.0/25.0*3.0; m_colorMap->addColorStop(pos, QColor(0,0,51));
        pos = 1.0/25.0*4.0; m_colorMap->addColorStop(pos, QColor(0,0,102));
        pos = 1.0/25.0*5.0; m_colorMap->addColorStop(pos, QColor(0,0,153));
        pos = 1.0/25.0*6.0; m_colorMap->addColorStop(pos, QColor(0,50,255));
        pos = 1.0/25.0*7.0; m_colorMap->addColorStop(pos, QColor(0,100,255));
        pos = 1.0/25.0*8.0; m_colorMap->addColorStop(pos, QColor(0,150,255));
        pos = 1.0/25.0*9.0; m_colorMap->addColorStop(pos, QColor(0,200,255));
        pos = 1.0/25.0*10.0; m_colorMap->addColorStop(pos, QColor(0,255,255));
        pos = 1.0/25.0*11.0; m_colorMap->addColorStop(pos, QColor(36,255,219));
        pos = 1.0/25.0*12.0; m_colorMap->addColorStop(pos, QColor(73,255,182));
        pos = 1.0/25.0*13.0; m_colorMap->addColorStop(pos, QColor(109,255,146));
        pos = 1.0/25.0*14.0; m_colorMap->addColorStop(pos, QColor(146,255,109));
        pos = 1.0/25.0*15.0; m_colorMap->addColorStop(pos, QColor(182,255,73));
        pos = 1.0/25.0*16.0; m_colorMap->addColorStop(pos, QColor(219,255,36));
        pos = 1.0/25.0*17.0; m_colorMap->addColorStop(pos, QColor(255,255,0));
        pos = 1.0/25.0*18.0; m_colorMap->addColorStop(pos, QColor(255,219,0));
        pos = 1.0/25.0*19.0; m_colorMap->addColorStop(pos, QColor(255,182,0));
        pos = 1.0/25.0*20.0; m_colorMap->addColorStop(pos, QColor(255,146,0));
        pos = 1.0/25.0*21.0; m_colorMap->addColorStop(pos, QColor(255,109,0));
        pos = 1.0/25.0*22.0; m_colorMap->addColorStop(pos, QColor(255,73,0));
        pos = 1.0/25.0*23.0; m_colorMap->addColorStop(pos, QColor(255,36,0));
        pos = 1.0/25.0*24.0; m_colorMap->addColorStop(pos, QColor(255,0,0));
        pos = 1.0/25.0*25.0; m_colorMap->addColorStop(pos, QColor(219,0,0));
        break;
    }
    QwtPlotSpectrogram::setColorMap(m_colorMap);
}


void Spectrogram::appendData(const FrameCollection& frames) {
    _data->append(frames);
    setData(_data);
}
