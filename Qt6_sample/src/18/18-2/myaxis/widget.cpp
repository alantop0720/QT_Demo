#include "widget.h"
#include "ui_widget.h"
#include <QtCharts>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    view1 = new QChartView(this);
    view2 = new QChartView(this);
    view1->move(10, 10);
    view2->move(420, 10);
    view1->resize(400, 300);
    view2->resize(400, 300);
    resize(830, 320);
    view1->setRenderHint(QPainter::Antialiasing);
    view2->setRenderHint(QPainter::Antialiasing);

    // 添加系列
    view1->chart()->legend()->setVisible(false);
    QSplineSeries *series = new QSplineSeries;
    series->append(5, 10);
    series->append(12, 16);
    series->append(14, 64);
    *series << QPointF(16, 128) << QPointF(18, 32);
    view1->chart()->addSeries(series);
    // 设置系列数据点的显示
    series->setPointsVisible(true);
    series->setLightMarker(QImage("../myaxis/star.png"));
    series->setMarkerSize(10);
    series->setPointLabelsVisible(true);
    series->setPointLabelsFormat("(@xPoint, @yPoint)");
    series->setPointLabelsColor(Qt::lightGray);
    series->setPointLabelsClipping(false);
    // 添加X坐标轴
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 21);
    axisX->setTickCount(6);
    axisX->setMinorTickCount(1);
    axisX->setLabelFormat("%.2f");
    axisX->setLabelsAngle(30);
    axisX->setLabelsColor(Qt::darkYellow);
    view1->chart()->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    // 动态设置刻度线位置
    axisX->setTickType(QValueAxis::TicksDynamic);
    axisX->setTickAnchor(5);
    axisX->setTickInterval(5);

    // 设置Y坐标轴
    QLogValueAxis *axisY = new QLogValueAxis;
    axisY->setBase(2);
    axisY->setRange(8, 260);
    axisY->setMinorTickCount(1);
    view1->chart()->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);



    // 在第二个图表中添加柱形图
    QBarSet *set0 = new QBarSet("Jane");
    QBarSet *set1 = new QBarSet("John");
    QBarSet *set2 = new QBarSet("Axel");

    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5;

    QBarSeries *series1 = new QBarSeries();
    // QPercentBarSeries *series1 = new QPercentBarSeries();
    // QStackedBarSeries *series1 = new QStackedBarSeries();
    series1->append(set0);
    series1->append(set1);
    series1->append(set2);
    view2->chart()->addSeries(series1);

    // 添加柱形图分类坐标轴
    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    QBarCategoryAxis *axisX1 = new QBarCategoryAxis();
    axisX1->append(categories);
    view2->chart()->addAxis(axisX1, Qt::AlignBottom);
    series1->attachAxis(axisX1);

    // 添加分类坐标轴
    QCategoryAxis *axisY1 = new QCategoryAxis;
    axisY1->append("Low", 5);
    axisY1->append("Medium", 10);
    axisY1->append("High", 15);
    view2->chart()->addAxis(axisY1, Qt::AlignLeft);
    series1->attachAxis(axisY1);
}

Widget::~Widget()
{
    delete ui;
}






