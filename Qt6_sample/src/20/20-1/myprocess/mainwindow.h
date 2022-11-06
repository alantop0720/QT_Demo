#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void showResult();
    void showState(QProcess::ProcessState);
    void showError();
    void showFinished(int, QProcess::ExitStatus);

private:
    Ui::MainWindow *ui;

    QProcess *myProcess;
};
#endif // MAINWINDOW_H
