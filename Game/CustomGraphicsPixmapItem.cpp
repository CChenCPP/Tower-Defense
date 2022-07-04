#include "CustomGraphicsPixmapItem.h"

CustomGraphicsPixmapItem::CustomGraphicsPixmapItem(QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent)
{

}

// public methods
QPointF CustomGraphicsPixmapItem::center() const
{
    return mapToScene(QPointF(boundingRect().center().x(),boundingRect().center().y()));
}

void CustomGraphicsPixmapItem::centerToPoint(qreal x, qreal y)
{
    QPointF cent = center();
    qreal dx = x - cent.x();
    qreal dy = y - cent.y();
    setPos(x - dx, y - dy);
}

void CustomGraphicsPixmapItem::centerToPoint(QPointF point)
{
    centerToPoint(point.x(), point.y());
}

qreal CustomGraphicsPixmapItem::radius() const
{
    return std::max<qreal>(pixmap().width(), pixmap().height()) * sqrt(2) / 2;
}
