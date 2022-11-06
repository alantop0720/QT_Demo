#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class QValidator;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::Widget *ui;
    QValidator *validator;
};

#endif // WIDGET_H
