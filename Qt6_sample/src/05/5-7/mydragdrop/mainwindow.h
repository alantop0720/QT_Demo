#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected:
    void dragEnterEvent(QDragEnterEvent *event) override; // 拖动进入事件
    void dropEvent(QDropEvent *event) override;           // 放下事件

};

#endif // MAINWINDOW_H
