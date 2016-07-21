#include "processingsettings.h"
#include "ui_processingsettings.h"

ProcessingSettings::ProcessingSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProcessingSettings)
{
    ui->setupUi(this);
    loadSettings();

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

ProcessingSettings::~ProcessingSettings()
{
    delete ui;
}

void ProcessingSettings::loadSettings() {
    ui->buffer->setValue(loadFromSettings(keyBuffer, 5).toInt());
    ui->wTime->setValue(loadFromSettings(keyWindowTime, 0.02).toDouble());
    ui->wHope->setValue(loadFromSettings(keyWindowHope, 0.01).toDouble());
    ui->wType->setCurrentIndex(loadFromSettings(keyWindowType, 0).toInt());

    ui->specCombo->setCurrentIndex(loadFromSettings(keySpectrumType,0).toInt());
    ui->specSize->setValue(loadFromSettings(keySpectrumSize,512).toInt());
    ui->orderLPC->setValue(loadFromSettings(keySpectrumLPC,12).toInt());
    ui->orderCepstrum->setValue(loadFromSettings(keySpectrumCepstrum,10).toInt());
    ui->orderFilterBanks->setValue(loadFromSettings(keySpectrumFilterBank,25).toInt());

    ui->pitchCombo->setCurrentIndex(loadFromSettings(keyPitchAlgorithm,0).toInt());
}

void ProcessingSettings::save() {
    saveSettings();
    //MATHMANAGER->update();
    accept();
}


void ProcessingSettings::saveSettings() {
    saveInSettings(keyBuffer, ui->buffer->value());
    saveInSettings(keyWindowTime,ui->wTime->value());
    saveInSettings(keyWindowHope,ui->wHope->value());
    saveInSettings(keyWindowType,ui->wType->currentIndex());

    saveInSettings(keySpectrumType,ui->specCombo->currentIndex());
    saveInSettings(keySpectrumSize,ui->specSize->value());
    saveInSettings(keySpectrumLPC,ui->orderLPC->value());
    saveInSettings(keySpectrumCepstrum,ui->orderCepstrum->value());
    saveInSettings(keySpectrumFilterBank,ui->orderFilterBanks->value());

    saveInSettings(keyPitchAlgorithm,ui->pitchCombo->currentIndex());
}
