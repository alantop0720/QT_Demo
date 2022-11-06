#include "widget.h"
#include "ui_widget.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaMetaData>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);

    player->setSource(QUrl::fromLocalFile("../myplayer/music.mp3"));

    connect(player, &QMediaPlayer::positionChanged,
            this, &Widget::updatePosition);

    ui->horizontalSlider_volume->setValue(100);


    connect(player, &QMediaPlayer::playbackStateChanged, this, &Widget::stateChanged);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &Widget::mediaStatusChanged);
    connect(player, &QMediaPlayer::errorOccurred, this, &Widget::showError);

    connect(player, &QMediaPlayer::metaDataChanged, this, &Widget::metaDataChanged);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::updatePosition(qint64 position)
{
    ui->horizontalSlider_position->setMaximum(player->duration() / 1000);
    ui->horizontalSlider_position->setValue(position / 1000);
}


void Widget::on_pushButton_play_clicked()
{
    player->play();
}


void Widget::on_pushButton_pause_clicked()
{
    player->pause();
}


void Widget::on_pushButton_stop_clicked()
{
    player->stop();
}


void Widget::on_horizontalSlider_position_sliderMoved(int position)
{
    player->setPosition(position * 1000);
}


void Widget::on_horizontalSlider_volume_sliderMoved(int position)
{
    audioOutput->setVolume(position / 100.0);
}



void Widget::stateChanged(QMediaPlayer::PlaybackState state)
{
    switch (state) {
    case QMediaPlayer::StoppedState:
        ui->label_state->setText(tr("停止状态！"));
        break;
    case QMediaPlayer::PlayingState:
        ui->label_state->setText(tr("播放状态！"));
        break;
    case QMediaPlayer::PausedState:
        ui->label_state->setText(tr("暂停状态！"));
        break;
    default: break;
    }
}

void Widget::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    switch (status) {
    case QMediaPlayer::NoMedia:
        ui->label_status->setText(tr("没有媒体文件！"));
        break;
    case QMediaPlayer::BufferingMedia:
        ui->label_status->setText(tr("正在缓冲媒体文件！"));
        break;
    case QMediaPlayer::BufferedMedia:
        ui->label_status->setText(tr("媒体文件缓冲完成！"));
        break;
    case QMediaPlayer::LoadingMedia:
        ui->label_status->setText(tr("正在加载媒体！"));
        break;
    case QMediaPlayer::StalledMedia:
        ui->label_status->setText(tr("播放停滞！"));
        break;
    case QMediaPlayer::EndOfMedia:
        ui->label_status->setText(tr("播放结束！"));
        break;
    case QMediaPlayer::LoadedMedia:
        ui->label_status->setText(tr("媒体加载完成！"));
        break;
    case QMediaPlayer::InvalidMedia:
        ui->label_status->setText(tr("不可用的媒体文件！"));
        break;
    default: break;
    }
}


void Widget::showError(QMediaPlayer::Error error, const QString &errorString)
{
    switch (error) {
    case QMediaPlayer::NoError:
        ui->label_error->setText(tr("没有错误！") + errorString);
        break;
    case QMediaPlayer::ResourceError:
        ui->label_error->setText(tr("媒体资源无法被解析！") + errorString);
        break;
    case QMediaPlayer::FormatError:
        ui->label_error->setText(tr("不支持该媒体格式！") + errorString);
        break;
    case QMediaPlayer::NetworkError:
        ui->label_error->setText(tr("发生了一个网络错误！") + errorString);
        break;
    case QMediaPlayer::AccessDeniedError:
        ui->label_error->setText(tr("没有播放权限！") + errorString);
        break;
    default: break;
    }
}


void Widget::metaDataChanged()
{
    QMediaMetaData metaData = player->metaData();
    QString title = metaData.stringValue(QMediaMetaData::Title);
    QString author = metaData.stringValue(QMediaMetaData::Author);
    setWindowTitle(title + "-" + author);
}









