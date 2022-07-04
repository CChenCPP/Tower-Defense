#pragma once
#include <QGraphicsPixmapItem>

class CustomGraphicsPixmapItem : public QGraphicsPixmapItem
{
public:
    CustomGraphicsPixmapItem(QGraphicsItem* parent = nullptr);

    QPointF center() const;
    void centerToPoint(qreal x, qreal y);
    void centerToPoint(QPointF point);
    qreal radius() const;
};

