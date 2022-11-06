#include "widget.h"
#include "ui_widget.h"

#include <QtDataVisualization>
#include <QTableWidget>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QTableWidget *tableWidget = new QTableWidget(2, 3, this);
    tableWidget->resize(360, 90);
    tableWidget->move(220, 10);

    QStringList days;
    days << "Monday" << "Tuesday" << "Wednesday";
    QStringList weeks;
    weeks << "week 1" << "week 2";

    // Set up data           Mon   Tue   Wed
    float expenses[2][3] = {{2.0f, 1.0f, 3.0f},  // week 1
                            {0.5f, 1.0f, 3.0f}}; // week 2

    for (int week = 0; week < weeks.size(); week++) {
        for (int day = 0; day < days.size(); day++) {
            QModelIndex index = tableWidget->model()->index(week, day);
            tableWidget->model()->setData(index, expenses[week][day]);
        }
    }

    tableWidget->setVerticalHeaderLabels(weeks);
    tableWidget->setHorizontalHeaderLabels(days);


    Q3DBars *graph = new Q3DBars();
    QWidget *container = QWidget::createWindowContainer(graph, this);
    container->resize(780, 450);
    container->move(10, 120);

    Q3DCamera *camera = graph->scene()->activeCamera();
    camera->setCameraPreset(Q3DCamera::CameraPresetIsometricRightHigh);
    graph->activeTheme()->setType(Q3DTheme::ThemeIsabelle);


    QItemModelBarDataProxy *proxy = new QItemModelBarDataProxy(tableWidget->model());
    proxy->setUseModelCategories(true);
    QBar3DSeries *series = new QBar3DSeries(proxy);
    series->setMesh(QAbstract3DSeries::MeshPyramid);
    graph->addSeries(series);

    graph->setSelectionMode(QAbstract3DGraph::SelectionRow | QAbstract3DGraph::SelectionSlice);

}

Widget::~Widget()
{
    delete ui;
}





