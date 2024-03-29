#include <QApplication>
#include <QMediaPlayer>
#include <QGraphicsVideoItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QAudioOutput>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.resize(600, 320);
    QGraphicsVideoItem item;
    scene.addItem(&item);
    item.setSize(QSizeF(500, 300));
    QMediaPlayer player;
    player.setVideoOutput(&item);
    QAudioOutput audioOutput;
    player.setAudioOutput(&audioOutput);
    player.setSource(QUrl::fromLocalFile("../myvideoitem/video.wmv"));
    player.play();
    view.show();

    return a.exec();
}
