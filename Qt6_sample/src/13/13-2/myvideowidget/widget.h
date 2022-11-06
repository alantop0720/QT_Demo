#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class QMediaPlayer;
class QAudioOutput;
class QVideoWidget;

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
    QVideoWidget *videoWidget;
};
#endif // WIDGET_H
