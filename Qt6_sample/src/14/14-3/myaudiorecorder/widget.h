#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QMediaRecorder;
class QAudioInput;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

    void updateProgress(qint64 duration);

private:
    Ui::Widget *ui;

    QAudioInput *audioInput;
    QMediaRecorder *recorder;


};

#endif // WIDGET_H
