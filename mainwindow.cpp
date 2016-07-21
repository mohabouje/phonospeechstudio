#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QToolButton>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _audioSettings(new PhonoAudioSettings(this)),
    _procSettings(new ProcessingSettings(this))
{
    ui->setupUi(this);
    ui->energy->initData(1200);
    ui->energy->setAxisScale(QwtPlot::xBottom,0,1200);
    ui->energy->setAxisScale(QwtPlot::yLeft,-1,1);
    connect(ui->actionPlay, SIGNAL(triggered(bool)), AUDIOMANAGER, SLOT(record()));
    connect(AUDIOMANAGER, SIGNAL(audioBufferReady(AudioBuffer)), this, SLOT(audioBufferProbed(AudioBuffer)));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(openAudioFile()));
    connect(ui->actionAudio_Configuration, SIGNAL(triggered(bool)), this, SLOT(showAudioSettings()));
    connect(ui->actionProcessing_Configuration, SIGNAL(triggered(bool)), this, SLOT(showProcessingSettings()));

    addChartActions();

    MATHMANAGER->initFrameCutter(AUDIOMANAGER->sampleRate(), DEFAULT_BUFFER_TIME, 0.020, 0.005, Windowing::Hamming);
    MATHMANAGER->initAlgorithms(true);


    ui->spectrogram->initData(1200,MATHMANAGER->fft()->fftSize());

    ui->pitch->initData(MATHMANAGER->fft()->fftSize());
    ui->pitch->setAxisScale(QwtPlot::xBottom,0,MATHMANAGER->fft()->fftSize());




    /*ui->pitch->initData(1200);
    ui->pitch->setAxisScale(QwtPlot::xBottom,0,1200);
    ui->pitch->setAxisScale(QwtPlot::yLeft,-50,50);*/

#if !ENABLE_TESTING
    ui->actionLaunch_Test->setVisible(false);
#endif


#if VERBOSE_FRAMES
    qDebug() << QString("MathManager: Samplerate: %1, FrameSize: %2, HopeSize: %3, OverlapSize: %4")
                .arg(MATHMANAGER->sampleRate())
                .arg(MATHMANAGER->samplesPerFrame())
                .arg(MATHMANAGER->samplesPerHope())
                .arg(MATHMANAGER->samplesPerOverlap());

    const int samplesPerFrame = MATHMANAGER->samplesPerFrame();
    AudioSample* tmp = new AudioSample[samplesPerFrame];
    for (int i=0; i<samplesPerFrame; i++)
        tmp[i] = i+1;
    MATHMANAGER->appendData(tmp, samplesPerFrame);
    const FrameCollection frames = MATHMANAGER->frames();
    qDebug() << QString("FrameCollection: FrameCount: %1, FrameSize: %2").arg(frames.size()).arg(frames[0].size());

    for (int i=0; i<frames[0].size(); i++) {
        QString tmp = "";
        for (int j=0; j<frames.size();j++) {
            tmp +=  QString(" %1 ").arg(frames[j][i]);
        }
        qDebug() << tmp;
    }
#endif
}

QToolButton* MainWindow::createToolButton(const QString& name, const QString& tooltip, const QVariant& data) {
    QToolButton* btn = new QToolButton();
    btn->setText(name);
    btn->setToolTip(tooltip);
    btn->setAutoRaise(true);
    btn->setProperty("chart", data);
    return btn;
}


void MainWindow::addChartActions() {
    // Energy chart
    ui->energy->addButton(createToolButton("E", "Estimate the energy level of the signal", ChartActions::EnergyChart));
    ui->energy->addButton(createToolButton("P", "Estimate the instant power of the signal", ChartActions::PowerChart));
    ui->energy->addButton(createToolButton("L", "Estimate the loudness of the signal", ChartActions::LoudnessChart));
    ui->energy->addButton(createToolButton("ZCR", "Estimate the zero crossing rate of the signal", ChartActions::ZeroCrossingRateChart));

    // Spectral chart
    ui->pitch->addButton(createToolButton("PSD", "Estimate the power density spectrum of the signal", ChartActions::PowerDensitySpectralChart));
    ui->pitch->addButton(createToolButton("LPC", "Estimate the LPC spectrum of the signal", ChartActions::LPCSpectrumChart));
    ui->pitch->addButton(createToolButton("CEPS", "Estimate the cepstrum of the signal", ChartActions::CepstrumChart));

    QSettings settings;
    int index = settings.value("chart/energy/index", 0).toInt();
    ui->energy->setCurrentAction(index);

    index = settings.value("chart/pitch/index", 0).toInt();
    ui->pitch->setCurrentAction(index);

}


void MainWindow::showProcessingSettings() {
    _procSettings->exec();
}

void MainWindow::showAudioSettings() {
    _audioSettings->exec();
}


void MainWindow::audioBufferProbed(const AudioBuffer& buffer) {
    Frame temp(buffer.dataCount);
    for (unsigned int i=0; i<buffer.dataCount; i++) {
        temp[i] = buffer.data[i];
    }

    MATHMANAGER->frameCutter()->setInputData(temp);
    MATHMANAGER->frameCutter()->exec();

    FrameCollection frames;
    Frame timeFrame;

    switch (ui->pitch->currentAction()) {
    case PowerDensitySpectralChart:
        frames = FramesAnalyzer::applyForFrameCollection(MATHMANAGER->frameCutter()->frames(), MATHMANAGER->psd());;
        break;
    case LPCSpectrumChart:
        frames = FramesAnalyzer::applyForFrameCollection(MATHMANAGER->frameCutter()->frames(), MATHMANAGER->lpcSpectrum());;
        break;
    case CepstrumChart:
        frames = FramesAnalyzer::applyForFrameCollection(MATHMANAGER->frameCutter()->frames(), MATHMANAGER->cepstrum());;
        break;
    default:
        break;
    }

    /*Frame timeFrame = FramesAnalyzer::applyForFrame(MATHMANAGER->frameCutter()->frames(), MATHMANAGER->pitchCepstrum());
    ui->pitch->append(timeFrame.data(), timeFrame.size());*/
    switch (ui->energy->currentAction()) {
    case EnergyChart:
        timeFrame = FramesAnalyzer::applyForFrame(MATHMANAGER->frameCutter()->frames(), MATHMANAGER->energy());
        break;
    case PowerChart:
        timeFrame = FramesAnalyzer::applyForFrame(MATHMANAGER->frameCutter()->frames(), MATHMANAGER->power());
        break;
    case LoudnessChart:
        timeFrame = FramesAnalyzer::applyForFrame(MATHMANAGER->frameCutter()->frames(), MATHMANAGER->loudness());
        break;
    case ZeroCrossingRateChart:
        timeFrame = FramesAnalyzer::applyForFrame(MATHMANAGER->frameCutter()->frames(), MATHMANAGER->zcr());
        break;
    }

    ui->pitch->append(frames.first().data(), frames.last().size());
    ui->energy->append(timeFrame.data(), timeFrame.size());
    ui->spectrogram->append(frames);

    ui->levelWidget->setValue(*std::max_element(buffer.data, buffer.data+buffer.dataCount));
}


void MainWindow::openAudioFile() {
    const QString filePath = QFileDialog::getOpenFileName(this, tr("Select a file to open..."), QDir::homePath(), "WAV (*.wav)");
    if (filePath.isEmpty())
        return;
#if ENABLE_WAV_READER
    AUDIOMANAGER->loadFile(filePath);
    AUDIOMANAGER->play();
#endif
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionLaunch_Test_triggered()
{
    QFile file(":/testing/data.txt");
    if  (!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Could not open file for read";
        return;
    }
    Frame inputData;
    QTextStream in(&file);
    while (!in.atEnd()) {
        const QString line = in.readLine();
        inputData.append(line.toDouble());
    }
    const int size = inputData.size();
    /*qDebug() << "Testing fft...";
    FFT* fft = new FFT();
    fft->setInputSize(1024);
    fft->setEstimateSpectrum(true);
    fft->setLogarithmicScale(false);
    fft->init();
    fft->setInputData(inputData);
    fft->exec();
    ComplexSample* complex = fft->outputComplex();
    Frame spectrum = fft->outputFrame();
    for (int i=0; i<spectrum.size(); i++) {
        qDebug() << i << complex[i][0] << complex[i][1];
    }
    /*IFFT* ifft = new IFFT();
    ifft->setFFTSize(fft->fftSize());
    ifft->init();
    ifft->setComplexData(spec);
    ifft->exec();
    Frame recovery = ifft->outputFrame();
    for (int i=0; i<size; i++) {
        qDebug() << i << recovery[i];
    }*/

    AutoCorrelation* autocor = new AutoCorrelation();
    autocor->setSize(size);
    autocor->setFFTSize(1024);
    autocor->setNormalized(false);
    autocor->setUnbiased(false);
    autocor->init();
    autocor->setInputData(inputData);
    autocor->exec();
    Frame dat = autocor->outputFrame();
    for (int i=0; i<size; i++) {
        qDebug() << i << dat[i];
    }

    LPC* lpc = new LPC();
    lpc->setInputSize(size);
    lpc->setOrder(12);
    lpc->init();
    lpc->setInputData(inputData);
    lpc->exec();
    Frame _dat = lpc->outputFrame();
    for (int i=0; i<_dat.size(); i++) {
        qDebug() << i << _dat[i];
    }
   /* DCT* dct = new DCT();
    dct->setInputSize(size);
    dct->init();
    dct->setInputData(inputData);
    dct->exec();*/
   /* MFCC *mfcc = new MFCC();
    mfcc->setInputSize(size);
    mfcc->setNumBands(20);
    mfcc->setLowFrequencyBound(0);
    mfcc->setHighFrequencyBound(4000);
    mfcc->setSampleRate(8000);
    mfcc->setFftSize(1024);
    mfcc->init();
    mfcc->setInputData(inputData);
    mfcc->exec();
    Frame frame = mfcc->outputFrame();
    for (int i=0; i<frame.size(); i++) {
        qDebug() << i << frame[i];
    }*/

    /*Cepstrum* cepstrum = new Cepstrum;
    cepstrum->setInputSize(1024);
    cepstrum->init();
    cepstrum->setInputData(inputData);
    cepstrum->exec();
    Frame frame = cepstrum->outputFrame();
    for (int i=0; i<frame.size(); i++) {
        qDebug() << i << frame[i];
    }*/

}
