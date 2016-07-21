#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "phonoaudiosettings.h"
#include "processingsettings.h"

#include <portaudiohelper.h>
#include <mathmanager.h>
#include "framesanalyzer.h"

#include <QMainWindow>
#include <QToolButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void audioBufferProbed(const AudioBuffer& buffer);
    void openAudioFile();
    void showAudioSettings();
    void showProcessingSettings();
    void on_actionLaunch_Test_triggered();

private:
    Ui::MainWindow *ui;


    // Settings
    PhonoAudioSettings* _audioSettings;
    ProcessingSettings* _procSettings;
    QToolButton *createToolButton(const QString &name, const QString &tooltip, const QVariant &data);
    void addChartActions();
};

#endif // MAINWINDOW_H
