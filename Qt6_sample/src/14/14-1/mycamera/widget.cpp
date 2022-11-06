#include "widget.h"
#include "ui_widget.h"
#include <QCameraDevice>
#include <QMediaDevices>
#include <QCamera>
#include <QMediaCaptureSession>
#include <QVideoWidget>
#include <QImageCapture>
#include <QDebug>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    camera = new QCamera(this);

    QMediaCaptureSession *captureSession = new QMediaCaptureSession(this);
    captureSession->setCamera(camera);

    QVideoWidget *preview = new QVideoWidget(this);
    preview->resize(600, 350);
    captureSession->setVideoOutput(preview);

    imageCapture = new QImageCapture(this);
    captureSession->setImageCapture(imageCapture);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked() // 开启相机
{

    if(QMediaDevices::videoInputs().count()) {
        const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
        for (const QCameraDevice &cameraDevice : cameras) {
            qDebug() << cameraDevice.description();
        }

        camera->setCameraDevice(cameras.at(0));
        // 当开启相机以后如果拔掉摄像头设备，相机依然处于活动状态，必须先关闭才能再次开启
        if (camera->isActive()) camera->stop();
        camera->start();
    }
}


void Widget::on_pushButton_2_clicked() // 拍照
{
     QString fileName = QFileDialog::getSaveFileName();
     imageCapture->captureToFile(fileName);
}



