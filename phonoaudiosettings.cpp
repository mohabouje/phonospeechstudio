#include "phonoaudiosettings.h"
#include "ui_phonoaudiosettings.h"

#include "portaudiohelper.h"
#include "mathmanager.h"
PhonoAudioSettings::PhonoAudioSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PhonoAudioSettings)
{
    ui->setupUi(this);
    connect(ui->difCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSupportedSampleRates(int)));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(cancel()));
    loadCombos();

}

void PhonoAudioSettings::save() {
    saveInSettings(keyDefaultInputDevice, ui->difCombo->currentData().toInt());
    saveInSettings(keyDefaultOutputDevice, ui->dofCombo->currentData().toInt());
    saveInSettings(keyDefaultSampleRate, ui->srCombo->currentData().toInt());
    saveInSettings(keyDefaultSampleRate + QString("/%1").arg(ui->difCombo->currentText()), ui->srCombo->currentData().toInt());


    MATHMANAGER->initFrameCutter(ui->srCombo->currentData().toInt(), DEFAULT_BUFFER_TIME, 0.033, 0.012, Windowing::Hamming);
    AUDIOMANAGER->updateDevice();
}

void PhonoAudioSettings::cancel() {

}

void PhonoAudioSettings::loadCombos() {
    const QList<AudioDeviceInfo>& devices = AUDIOMANAGER->devices();
    for (int i=0; i< devices.size();i++) {
        const AudioDeviceInfo device = devices.at(i);
        if (!device.supportedSampleRates.isEmpty())
            ui->difCombo->addItem(QIcon(), device.deviceInfo.name, i);
        else
            ui->dofCombo->addItem(QIcon(), device.deviceInfo.name, i);
    }
    loadDefaultDevices();
}


void PhonoAudioSettings::loadDefaultDevices() {
    const PaDeviceIndex inputDevice = AUDIOMANAGER->defaultInputDevice();
    const PaDeviceIndex outputDevice = AUDIOMANAGER->defaultOutputDevice();
    for (int i=0; i<ui->difCombo->model()->rowCount(); i++) {
        if (ui->difCombo->itemData(i).toInt() == inputDevice) {
            ui->difCombo->setCurrentIndex(i);
            break;
        }
    }
    for (int i=0; i<ui->dofCombo->model()->rowCount(); i++) {
        if (ui->dofCombo->itemData(i).toInt() == outputDevice) {
            ui->dofCombo->setCurrentIndex(i);
            break;
        }
    }
}

void PhonoAudioSettings::updateSupportedSampleRates(const int index) {
    int _dif = ui->difCombo->itemData(index).toInt();
    ui->srCombo->clear();
    QList<AudioDeviceInfo> devices = AUDIOMANAGER->devices();
    AudioDeviceInfo info =  devices.at(_dif);
    foreach(int sample, info.supportedSampleRates) {
        ui->srCombo->addItem(QString::number(sample), sample);
    }
    // Load last sample rate used for this device
    const int sr =  loadFromSettings(keyDefaultSampleRate + QString("/%1").arg(ui->difCombo->currentText()), -1).toInt();
    ui->srCombo->setCurrentText(QString::number( sr > 0 ? sr : DEFAULT_SAMPLERATE));
}

PhonoAudioSettings::~PhonoAudioSettings()
{
    delete ui;
}
