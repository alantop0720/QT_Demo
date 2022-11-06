#include "widget.h"
#include "ui_widget.h"

#include <QtSql>
#include <QtCharts>
#include <QTableView>

#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 初始化模型和视图
    model = new QSqlTableModel(this);
    model->setTable("m_xy");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("序号"));
    model->setHeaderData(1, Qt::Horizontal, tr("X轴"));
    model->setHeaderData(2, Qt::Horizontal, tr("Y轴"));
    QTableView *view = new QTableView(this);
    view->setModel(model);
    view->resize(320, 300);
    view->move(10, 10);

    // 设置图表视图、添加系列和轴
    chartView = new QChartView(this);
    chartView->resize(400, 300);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->move(350, 10);
    chartView->chart()->legend()->setVisible(false);
    chartView->chart()->setAnimationOptions(QChart::AllAnimations);
    chartView->chart()->setTheme(QChart::ChartThemeBlueIcy);

    series = new QSplineSeries;
    chartView->chart()->addSeries(series);

    axisX = new QValueAxis;
    axisX->setRange(0, 10);
    axisX->setTickCount(11);
    axisX->setLabelFormat("%d");
    chartView->chart()->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 10);
    axisY->setTickCount(6);
    axisY->setMinorTickCount(1);
    chartView->chart()->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // 使用模型映射器关联模型中的数据到图表系列
    //    QVXYModelMapper *mapper = new QVXYModelMapper(this);
    //    mapper->setSeries(series);
    //    mapper->setModel(model);
    //    mapper->setXColumn(1);
    //    mapper->setYColumn(2);


    for (int i=0; i< 20; i++) {
        int count = model->rowCount();
        int value = model->data(model->index(count-1, 1)).toInt();
        int m_x = QRandomGenerator::global()->bounded(3) +1 + value;
        int m_y = QRandomGenerator::global()->bounded(10) + 1;
        model->insertRow(count);
        model->setData(model->index(count, 0), count);
        model->setData(model->index(count, 1), m_x);
        model->setData(model->index(count, 2), m_y);
        model->submitAll();
    }
    model->select();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::handleTimeout);
    timer->start(2000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::handleTimeout()
{
    if(id < model->rowCount()) {
        int m_x = model->data(model->index(id, 1)).toInt();
        int m_y = model->data(model->index(id, 2)).toInt();
        series->append(m_x, m_y);

        if(m_x > axisX->max() - 3) {
            int temp = model->data(model->index(id-1, 1)).toInt();
            qreal width = chartView->chart()->plotArea().width();
            qreal dx = width / (axisX->tickCount()-1) *(m_x - temp);
            chartView->chart()->scroll(dx, 0);
        }
        id++;
    } else timer->stop();
}







