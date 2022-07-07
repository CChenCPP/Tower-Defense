#pragma once
#include <QGraphicsScene>
#include "Enemies/Enemy.h"

class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CustomGraphicsScene(QObject* parent = nullptr);

    static constexpr int defaultWidth = 900;
    static constexpr int defaultHeight = 792;
    static constexpr int projectileRenderLimit = 1250;

    void decrementProjectileCount();
    int getProjectileCount() const;
    void incrementProjectileCount();
    QList<QGraphicsItem*> itemsWithinRange(QGraphicsItem* graphicsItem, qreal radius);
    QList<QGraphicsItem*> itemsWithinRange(const QPointF point, qreal radius);
    qreal projectileCapacity() const;
private:
    int projectileCount;

signals:
};

