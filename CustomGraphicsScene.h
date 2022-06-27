#pragma once
#include <QGraphicsScene>
#include "Enemy.h"

class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CustomGraphicsScene(QObject* parent = nullptr);

    static constexpr int defaultWidth = 800;
    static constexpr int defaultHeight = 800;

    QList<Tower*> allTowers();
    QList<Enemy*> enemiesWithinRange(QGraphicsItem* graphicsItem, int radius);
signals:
};

