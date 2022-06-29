#include "CustomGraphicsScene.h"
#include "Utility.h"
#include <QTimer>
#include <iostream>

CustomGraphicsScene::CustomGraphicsScene(QObject* parent) :
    QGraphicsScene(parent),
    projectileCount(0)
{
    setSceneRect(0,0,defaultWidth,defaultHeight);

    //    QTimer* test = new QTimer();
}

bool lessThan(QGraphicsItem * left, QGraphicsItem * right)
{
    return (left->x() < right->x());
}

QList<Tower*> CustomGraphicsScene::allTowers()
{
    QList<QGraphicsItem*> allItems = items();
    QList<Tower*> towers;
    for (QGraphicsItem* item : allItems){
        Tower* tower = dynamic_cast<Tower*>(item);
        if (tower)
        {
            towers.push_back(tower);
        }
    }
    return towers;
}

void CustomGraphicsScene::decrementProjectileCount()
{
    --projectileCount;
}

QList<Enemy*> CustomGraphicsScene::enemiesWithinRange(QGraphicsItem* graphicsItem, qreal radius)
{
    QList<QGraphicsItem*> allItems = items();
    QList<Enemy*> filtered;
    for (auto& item : allItems){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy && Geometry::distance2D(graphicsItem->pos(), enemy->pos()) <= radius){
            filtered.push_back(enemy);
        }
    }
    return filtered;
}

int CustomGraphicsScene::getProjectileCount() const
{
    return projectileCount;
}

void CustomGraphicsScene::incrementProjectileCount()
{
    ++projectileCount;
}

QList<QGraphicsItem *> CustomGraphicsScene::itemsWithinRange(QGraphicsItem *graphicsItem, qreal radius)
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

QList<QGraphicsLineItem *> CustomGraphicsScene::lineItemsWithinRange(const QPointF point, qreal radius)
{
    QList<QGraphicsItem*> allItems = items();
    QList<QGraphicsLineItem*> filtered;
    for (auto& item : allItems){
        QGraphicsLineItem* line = dynamic_cast<QGraphicsLineItem*>(item);
        if (line) {
            QPointF mid = Geometry::midPoint(line->line().p1(),line->line().p2());
            if (Geometry::distance2D(point, mid) <= radius){
                filtered.push_back(line);
            }
        };
    }
    return filtered;
}

qreal CustomGraphicsScene::projectileCapacity()
{
    return getProjectileCount() / static_cast<qreal>(CustomGraphicsScene::projectileRenderLimit);
}
