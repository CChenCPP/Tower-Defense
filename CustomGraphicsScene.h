#pragma once
#include <QGraphicsScene>
#include "Enemy.h"

class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CustomGraphicsScene(QObject* parent = nullptr);

    static constexpr int defaultWidth = 792;
    static constexpr int defaultHeight = 792;
    static constexpr int projectileRenderLimit = 500;

    QList<Tower*> allTowers();
    void decrementProjectileCount();
    QList<Enemy*> enemiesWithinRange(QGraphicsItem* graphicsItem, qreal radius);
    int getProjectileCount() const;
    void incrementProjectileCount();
    QList<QGraphicsItem*> itemsWithinRange(QGraphicsItem* graphicsItem, qreal radius);
    QList<QGraphicsItem*> itemsWithinRange(const QPointF point, qreal radius);
    QList<QGraphicsLineItem*> lineItemsWithinRange(const QPointF point, qreal radius);
    qreal projectileCapacity();
private:
    int projectileCount;

signals:
};

