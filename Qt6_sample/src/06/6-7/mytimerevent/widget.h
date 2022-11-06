#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    int id1, id2, id3;

protected:
    void timerEvent(QTimerEvent *event) override;

private slots:
    void timerUpdate();


};

#endif // WIDGET_H
