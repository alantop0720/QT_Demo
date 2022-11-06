#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class QMediaPlayer;
class QAudioOutput;
#include <QMediaPlayer>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;

private slots:
    void updatePosition(qint64 position);

    void on_pushButton_play_clicked();
    void on_pushButton_pause_clicked();
    void on_pushButton_stop_clicked();
    void on_horizontalSlider_position_sliderMoved(int position);
    void on_horizontalSlider_volume_sliderMoved(int position);

    void stateChanged(QMediaPlayer::PlaybackState state);
    void mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void showError(QMediaPlayer::Error error, const QString &errorString);

    void metaDataChanged();
};
#endif // WIDGET_H


