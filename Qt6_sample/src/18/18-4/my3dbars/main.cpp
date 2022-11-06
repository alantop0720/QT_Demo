#include <QApplication>
#include <QtDataVisualization>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q3DBars bars;
    bars.setFlags(bars.flags() ^ Qt::FramelessWindowHint);
    bars.resize(800, 600);

    bars.rowAxis()->setRange(0, 1);
    bars.columnAxis()->setRange(0, 3);

    QBar3DSeries *series = new QBar3DSeries;
    QBarDataRow *data = new QBarDataRow;
    QBarDataRow *data1 = new QBarDataRow;
    *data << 1.0f << 3.0f << 7.5f << 5.0f ;
    *data1 << 2.0f << 1.0f << 4.0f << 3.5f;
    series->dataProxy()->addRow(data);
    series->dataProxy()->addRow(data1);
    bars.addSeries(series);
    bars.show();

    Q3DCamera *camera = bars.scene()->activeCamera();
    camera->setCameraPreset(Q3DCamera::CameraPresetIsometricRightHigh);
    camera->setZoomLevel(130);

    const QStringList rows = { "row0", "row1" };
    const QStringList cols = { "col0", "col1", "col2", "col3" };
    series->dataProxy()->setRowLabels(rows);
    series->dataProxy()->setColumnLabels(cols);
    series->setItemLabelFormat("@rowLabel, @colLabel: @valueLabel");

    bars.rowAxis()->setTitle("Row");
    bars.rowAxis()->setTitleVisible(true);
    bars.columnAxis()->setTitle("Column");
    bars.columnAxis()->setTitleVisible(true);
    bars.valueAxis()->setTitle("Value");
    bars.valueAxis()->setTitleVisible(true);
    bars.columnAxis()->setLabelAutoRotation(60);
    qDebug() << "rowAxis: " << bars.rowAxis()->orientation(); // Z轴
    qDebug() << "columnAxis: " << bars.columnAxis()->orientation(); // X轴
    qDebug() << "valueAxis: " << bars.valueAxis()->orientation();  // Y轴


    series->setMesh(QAbstract3DSeries::MeshCone);
    series->setMeshSmooth(true);

    bars.setBarThickness(0.6);
    bars.setBarSpacing(QSizeF(3.0, 2.0));
//  bars.setFloorLevel(3.0);

    bars.activeTheme()->setType(Q3DTheme::ThemeStoneMoss);
    const QList<QColor> colors = { Qt::green };
    bars.activeTheme()->setBaseColors(colors);
    bars.activeTheme()->setSingleHighlightColor(Qt::red);

    bars.setSelectionMode(QAbstract3DGraph::SelectionRow | QAbstract3DGraph::SelectionSlice);

    return a.exec();
}





