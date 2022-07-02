#include "CustomGraphicsScene.h"
#include "Utility.h"
#include <QTimer>
#include "Game.h"
#include <iostream>

CustomGraphicsScene::CustomGraphicsScene(QObject* parent) :
    QGraphicsScene(parent),
    projectileCount(0)
{
    setSceneRect(0,0,defaultWidth,defaultHeight);
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
    static int granularity = CustomGraphicsScene::defaultWidth / Game::tileSize * sqrt(2);

    QList<QGraphicsItem*> allItems = items();
    QList<QGraphicsLineItem*> filtered;
    for (auto& item : allItems){
        QGraphicsLineItem* line = dynamic_cast<QGraphicsLineItem*>(item);
        if (line) {
            qreal dx = line->line().p2().x() - line->line().p1().x();
            qreal dy = line->line().p2().y() - line->line().p1().y();

            QPointF current(line->line().p1());
            for (qreal i = 0; i < 1; i += 1.0 / granularity){
                if (Geometry::distance2D(point, current) <= radius){
                    filtered.push_back(line);
                    break;
                }
                current.setX(line->line().p1().x() + i * dx);
                current.setY(line->line().p1().y() + i * dy);
            }
        };
    }
    return filtered;
}

qreal CustomGraphicsScene::projectileCapacity()
{
    return getProjectileCount() / static_cast<qreal>(CustomGraphicsScene::projectileRenderLimit);
}
