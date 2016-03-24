#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QAudioProbe>
#include <QAudioRecorder>
#include <Parameter.h>
#include <globalvars.h>
#include <voiceprocessor.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void processBuffer(const QAudioBuffer&);

signals:
    void recording();

private slots:
    void on_Button_clicked();

    void CreateParam();

private:
    Ui::Dialog *ui;

    QAudioProbe* probe;

    QAudioRecorder* recorder;

    VoiceProcessor* vp;

    Parameter* param;
};

#endif // DIALOG_H
