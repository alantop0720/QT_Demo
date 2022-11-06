#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QWebEngineView;
class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void changeLocation();    // 改变路径
    void setProgress(int);    // 更新进度
    void adjustTitle();       // 更新标题显示
    void finishLoading(bool); // 加载完成后进行处理

private:
    Ui::MainWindow *ui;

    QWebEngineView *view;

    QLineEdit *locationEdit;      // 用于实现地址栏
    int progress;                 // 存储进度值
};
#endif // MAINWINDOW_H
