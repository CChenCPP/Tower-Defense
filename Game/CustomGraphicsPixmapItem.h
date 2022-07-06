#pragma once
#include <QGraphicsPixmapItem>

class CustomGraphicsPixmapItem : public QGraphicsPixmapItem
{
public:
    CustomGraphicsPixmapItem(QGraphicsItem* parent = nullptr);

    inline QPointF center() const;
    inline qreal centerX() const;
    inline qreal centerY() const;
    inline qreal radius() const;

    void centerToPoint(qreal x, qreal y);
    void centerToPoint(QPointF point);
};

inline QPointF CustomGraphicsPixmapItem::center() const
{   return mapToScene(QPointF(boundingRect().center().x(),boundingRect().center().y())); }

inline qreal CustomGraphicsPixmapItem::centerX() const
{   return center().x(); }

inline qreal CustomGraphicsPixmapItem::centerY() const
{   return center().y(); }

inline qreal CustomGraphicsPixmapItem::radius() const
{   return std::max<qreal>(pixmap().width(), pixmap().height()) * sqrt(2) / 2; }
