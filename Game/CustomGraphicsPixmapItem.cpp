#include "CustomGraphicsPixmapItem.h"


CustomGraphicsPixmapItem::CustomGraphicsPixmapItem(QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent)
{
}

// public methods
void CustomGraphicsPixmapItem::centerToPoint(qreal x, qreal y)
{
    QPointF cent = center();
    qreal dx = x - cent.x();
    qreal dy = y - cent.y();
    setPos(this->x() + dx, this->y() + dy);
}

void CustomGraphicsPixmapItem::centerToPoint(QPointF point)
{
    centerToPoint(point.x(), point.y());
}