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

    // 缓冲区
    QPixmap pix;

    // 临时缓冲区
    QPixmap tempPix;

    QPoint startPoint;
    QPoint endPoint;

    // 是否正在绘图的标志
    bool isDrawing;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

};

#endif // WIDGET_H
