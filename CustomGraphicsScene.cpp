#include "CustomGraphicsScene.h"
#include "Utility.h"
#include <QTimer>
#include <iostream>

CustomGraphicsScene::CustomGraphicsScene(QObject* parent) : QGraphicsScene(parent)
{
    setSceneRect(0,0,defaultWidth,defaultHeight);

//    QTimer* test = new QTimer();
}

QList<Enemy*> CustomGraphicsScene::enemiesWithinRange(QGraphicsItem* graphicsItem, int radius)
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
