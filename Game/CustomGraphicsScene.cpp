#include "CustomGraphicsScene.h"
#include "Misc/Utility.h"
#include <QTimer>
#include "Game.h"

CustomGraphicsScene::CustomGraphicsScene(QObject* parent) :
    QGraphicsScene(parent),
    projectileCount(0)
{
    setSceneRect(0,0,defaultWidth,defaultHeight);
    QTimer* t = new QTimer();
}

bool lessThan(QGraphicsItem * left, QGraphicsItem * right)
{
    return (left->x() < right->x());
}

void CustomGraphicsScene::decrementProjectileCount()
{
    --projectileCount;
}

int CustomGraphicsScene::getProjectileCount() const
{
    return projectileCount;
}

void CustomGraphicsScene::incrementProjectileCount()
{
    ++projectileCount;
}

QList<QGraphicsItem *> CustomGraphicsScene::itemsWithinRange(QGraphicsItem* graphicsItem, qreal radius)
{
    QList<QGraphicsItem*> allItems = items();
    QList<QGraphicsItem*> filtered;
    for (auto& item : allItems){
        if (Geometry::distance2D(graphicsItem->pos(), item->pos()) <= radius){
            filtered.push_back(item);
        }
    }
    return filtered;
}

QList<QGraphicsItem*> CustomGraphicsScene::itemsWithinRange(const QPointF point, qreal radius)
{
    QList<QGraphicsItem*> allItems = items();
    QList<QGraphicsItem*> filtered;
    for (auto& item : allItems){
        if (Geometry::distance2D(point, item->pos()) <= radius){
            filtered.push_back(item);
        }
    }
    return filtered;
}

qreal CustomGraphicsScene::projectileCapacity() const
{
    return getProjectileCount() / static_cast<qreal>(CustomGraphicsScene::projectileRenderLimit);
}
