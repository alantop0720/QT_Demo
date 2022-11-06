#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class QCamera;
class QImageCapture;

class QMediaRecorder;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked(bool checked);

private:
    Ui::Widget *ui;

    QCamera *camera;
    QImageCapture *imageCapture;

    QMediaRecorder *recorder;

};
#endif // WIDGET_H
