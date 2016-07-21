#ifndef PHONOAUDIOSETTINGS_H
#define PHONOAUDIOSETTINGS_H

#include <QDialog>

namespace Ui {
class PhonoAudioSettings;
}

class PhonoAudioSettings : public QDialog
{
    Q_OBJECT

public:
    explicit PhonoAudioSettings(QWidget *parent = 0);
    ~PhonoAudioSettings();

private slots:
    void updateSupportedSampleRates(const int index);
    void save();
    void cancel();
private:
    Ui::PhonoAudioSettings *ui;
    void loadCombos();
    void loadDefaultDevices();
};

#endif // PHONOAUDIOSETTINGS_H
