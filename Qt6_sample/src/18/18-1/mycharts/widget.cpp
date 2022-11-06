#include "widget.h"
#include "ui_widget.h"
#include <QLineSeries>
#include <QChartView>
#include <QValueAxis>
#include <QEasingCurve>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QLineSeries* series = new QLineSeries();
    series->append(0, 0);
    series->append(2, 4);

    QChartView *view = new QChartView(this);
    view->chart()->addSeries(series);
    view->resize(400, 300);


    QLineSeries* series1 = new QLineSeries();
    series1->append(0, 0);
    series1->append(1, 4);
    series1->append(3, 5);
    view->chart()->addSeries(series1);
    // 设置默认坐标轴
    view->chart()->createDefaultAxes();
    view->setRenderHint(QPainter::Antialiasing);


    // 设置标题
    view->chart()->setTitle(tr("My Charts"));
    view->chart()->setTitleBrush(Qt::darkYellow);
    view->chart()->setTitleFont(QFont("Arial", 20));
    series->setName("2020");
    series1->setName("2021");

    // 设置图例
    view->chart()->legend()->setMarkerShape(QLegend::MarkerShapeStar);
    view->chart()->legend()->setBackgroundVisible(true);
    view->chart()->legend()->setColor(QColor(255, 255, 255, 150));
    view->chart()->legend()->setLabelColor(Qt::darkYellow);
    view->chart()->legend()->setAlignment(Qt::AlignBottom);


    // 设置背景颜色
    view->chart()->setBackgroundBrush(Qt::lightGray);
    view->chart()->setPlotAreaBackgroundBrush(Qt::white);
    view->chart()->setPlotAreaBackgroundVisible(true);
    view->chart()->setBackgroundRoundness(15);
    view->chart()->setDropShadowEnabled(true);

    // 设置主题
    view->chart()->setTheme(QChart::ChartThemeBlueIcy);

    // 设置动画
    view->chart()->setAnimationOptions(QChart::AllAnimations);
    view->chart()->setAnimationDuration(2000);
    view->chart()->setAnimationEasingCurve(QEasingCurve(QEasingCurve::InQuad));

}

Widget::~Widget()
{
    delete ui;
}




