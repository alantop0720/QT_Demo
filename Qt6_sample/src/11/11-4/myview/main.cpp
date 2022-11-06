#include <QApplication>
#include "myitem.h"
#include "myview.h"
#include <QRandomGenerator>

int main(int argc, char* argv[ ])
{
    QApplication app(argc, argv);

    QGraphicsScene scene;
    scene.setSceneRect(-200, -150, 400, 300);
    for (int i = 0; i < 5; ++i) {
        MyItem *item = new MyItem;
        quint32 r = QRandomGenerator::global()->bounded(256);
        quint32 g = QRandomGenerator::global()->bounded(256);
        quint32 b = QRandomGenerator::global()->bounded(256);
        item->setColor(QColor(r, g, b));
        item->setPos(i * 50 - 90, -50);
        scene.addItem(item);
    }
    MyView view;
    view.setScene(&scene);
    view.setBackgroundBrush(QPixmap("../myView/background.png"));
    view.show();
    return app.exec();
}
