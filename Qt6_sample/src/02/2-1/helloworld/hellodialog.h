#ifndef HELLODIALOG_H
#define HELLODIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class HelloDialog; }
QT_END_NAMESPACE

class HelloDialog : public QDialog
{
    Q_OBJECT

public:
    HelloDialog(QWidget *parent = nullptr);
    ~HelloDialog();

private:
    Ui::HelloDialog *ui;
};
#endif // HELLODIALOG_H
