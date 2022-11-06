#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class QMovie;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_clicked();

    void on_pushButton_2_toggled(bool checked);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::Widget *ui;
    QMovie *movie;
};
#endif // WIDGET_H
