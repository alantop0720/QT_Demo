#include <QApplication>
#include <QtDataVisualization>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q3DSurface surface;
    surface.setFlags(surface.flags() ^ Qt::FramelessWindowHint);
    surface.resize(800, 600);
    QSurfaceDataArray *data = new QSurfaceDataArray;
    QSurfaceDataRow *dataRow1 = new QSurfaceDataRow;
    QSurfaceDataRow *dataRow2 = new QSurfaceDataRow;

    *dataRow1 << QVector3D(0.0f, 0.1f, 0.5f) << QVector3D(1.0f, 0.5f, 0.5f);
    *dataRow2 << QVector3D(0.0f, 1.8f, 1.0f) << QVector3D(1.0f, 1.2f, 1.0f);
    *data << dataRow1 << dataRow2;

    QSurface3DSeries *series = new QSurface3DSeries;
    series->dataProxy()->resetArray(data);
    surface.addSeries(series);
    surface.show();


    Q3DSurface surface1;
    surface1.setFlags(surface1.flags() ^ Qt::FramelessWindowHint);
    surface1.resize(800, 600);
    surface1.activeTheme()->setType(Q3DTheme::ThemeStoneMoss);

    QSurface3DSeries *series1 = new QSurface3DSeries;
    QHeightMapSurfaceDataProxy *proxy =
            new QHeightMapSurfaceDataProxy("../my3dsurface/layer.png");
    series1->setDataProxy(proxy);
    series1->setDrawMode(QSurface3DSeries::DrawSurface);
    surface1.addSeries(series1);
    surface1.show();


    return a.exec();
}


