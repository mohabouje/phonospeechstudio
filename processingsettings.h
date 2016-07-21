#ifndef PROCESSINGSETTINGS_H
#define PROCESSINGSETTINGS_H

#include "util.h"
#include "mathmanager.h"
#include <QDialog>


namespace Ui {
class ProcessingSettings;
}

class ProcessingSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ProcessingSettings(QWidget *parent = 0);
    ~ProcessingSettings();

private slots:
    void save();
private:
    Ui::ProcessingSettings *ui;
    void loadSettings();
    void saveSettings();
};

#endif // PROCESSINGSETTINGS_H
