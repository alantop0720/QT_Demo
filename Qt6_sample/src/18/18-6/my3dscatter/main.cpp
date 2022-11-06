#include <QApplication>
#include <QtDataVisualization>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q3DScatter scatter;
    scatter.setFlags(scatter.flags() ^ Qt::FramelessWindowHint);
    scatter.resize(800, 600);
    QScatter3DSeries *series = new QScatter3DSeries;
    QScatterDataArray data;
    data << QVector3D(0.5f, 0.5f, 0.5f) << QVector3D(-0.3f, -0.5f, -0.4f)
         << QVector3D(0.0f, -0.3f, 0.2f);
    series->dataProxy()->addItems(data);
    scatter.addSeries(series);
    scatter.show();

    return a.exec();
}


