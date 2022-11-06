#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QSqlTableModel;
class QChartView;
class QValueAxis;
class QSplineSeries;

class QTimer;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    QSqlTableModel *model;
    QChartView *chartView;
    QValueAxis *axisX;
    QSplineSeries *series;

    int id = 0;
    QTimer *timer;

public slots:
    void handleTimeout();
};
#endif // WIDGET_H
