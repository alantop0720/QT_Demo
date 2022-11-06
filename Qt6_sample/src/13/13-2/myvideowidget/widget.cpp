#include "widget.h"
#include "ui_widget.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    videoWidget = new QVideoWidget(this);
    videoWidget->resize(600, 300);
    videoWidget->move(100, 150);
    player->setVideoOutput(videoWidget);
    player->setSource(QUrl::fromLocalFile("../myvideowidget/video.wmv"));
    player->play();
}

Widget::~Widget()
{
    delete ui;
}

