#include <QFileDialog>
#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

/*
    float spektr[30];

    for(int i = 0; i < 30; i++){
        spektr[i]=i+1;
    }

    param->setParameter(spektr,30,12.5);
*/
    vp = new VoiceProcessor();

    param = new Parameter();

    recorder = new QAudioRecorder(this);

    QAudioEncoderSettings settings;
    settings.setSampleRate(RECORD_SAMPLE_SIZE);
    recorder->setAudioSettings(settings);

    recorder->setOutputLocation(QUrl::fromLocalFile("D:/Suli/Szakdolgozat/SpeechRecords"));

    probe = new QAudioProbe();
    if(probe->setSource(recorder)){
        connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(QAudioBuffer)));
    }

    connect(this, SIGNAL(recording()), this, SLOT(CreateParam()));
}

void Dialog::processBuffer(const QAudioBuffer &buffer){
    const short* data = buffer.constData<short>();
    int length = buffer.sampleCount();
    int dc = 0;

    while (dc != length){
        recordedSamples[recordedSamplesLastSetted] = data[dc];

        recordedSamplesLastSetted++;

        if (recordedSamplesLastSetted == RECORD_SAMPLE_SIZE) {
            recordedSamplesLastSetted = 0;
            qDebug() << "Ding!!";
        }
        dc++;
    }

    emit recording();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::CreateParam(){

//    float spektr[30];
//    for(int i = 0; i < 30; i++){
//        spektr[i]=i+1;
//    }
//    param->setParameter(spektr, 30, 42);

    param = vp->processSamples();
}

void Dialog::on_Button_clicked()
{
    if(recorder->state() == QMediaRecorder::StoppedState){
        recorder->record();
        ui->Button->setText("Stop");
    }else{
        recorder->stop();
        ui->Button->setText("Start");

        QString a = QString::number(param->amplitude);
        ui->lineEdit->setText(a);
    }
}
