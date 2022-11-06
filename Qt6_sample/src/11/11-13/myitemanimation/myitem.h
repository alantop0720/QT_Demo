#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsObject>

class MyItem : public QGraphicsObject
{
public:
    MyItem(QGraphicsItem *parent = 0);
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // MYITEM_H
