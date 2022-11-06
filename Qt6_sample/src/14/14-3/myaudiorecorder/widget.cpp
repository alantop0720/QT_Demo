#include "widget.h"
#include "ui_widget.h"
#include <QMediaDevices>
#include <QAudioDevice>
#include <QAudioInput>
#include <QMediaCaptureSession>
#include <QMediaRecorder>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    const QList<QAudioDevice> devices = QMediaDevices::audioInputs();
    QStringList list;
    for (const QAudioDevice &deviceInfo : devices) {
        qDebug() << "Device: " << deviceInfo.description();
        list << deviceInfo.description();
    }
    ui->comboBox->addItems(list);

    QMediaCaptureSession *session = new QMediaCaptureSession(this);
    audioInput = new QAudioInput(this);
    session->setAudioInput(audioInput);
    recorder = new QMediaRecorder(this);
    session->setRecorder(recorder);

    ui->pushButton_stop->setEnabled(false);


    connect(recorder, &QMediaRecorder::durationChanged, this, &Widget::updateProgress);
}

Widget::~Widget()
{
    delete ui;
}

// 选择按钮
void Widget::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName();
    ui->lineEdit->setText(fileName);
}
// 开始按钮
void Widget::on_pushButton_start_clicked()
{
    if(ui->lineEdit->text().isEmpty()) {
        QMessageBox::information(this, tr("提示"), tr("请先设置保存路径"), QMessageBox::Ok);
        ui->lineEdit->setFocus();
    } else {
        const QList<QAudioDevice> devices = QMediaDevices::audioInputs();
        int index = ui->comboBox->currentIndex();
        audioInput->setDevice(devices.at(index));
        recorder->setOutputLocation(QUrl::fromLocalFile(ui->lineEdit->text()));
        recorder->record();
        ui->pushButton_start->setEnabled(false);
        ui->pushButton_stop->setEnabled(true);
    }
}
// 停止按钮
void Widget::on_pushButton_stop_clicked()
{
    if(ui->pushButton_start->isEnabled()) {
        return;
    } else {
        recorder->stop();
        ui->pushButton_stop->setEnabled(false);
        ui->pushButton_start->setEnabled(true);
    }
}

void Widget::updateProgress(qint64 duration)
{
    if(recorder->error() != QMediaRecorder::NoError || duration < 1000)
        return;
    setWindowTitle(tr("Recorded %1 sec").arg(duration / 1000));
}




