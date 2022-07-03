#pragma once
#include "Towers/Tower.h"


class BuildingCursor : public QGraphicsPixmapItem
{
public:
    BuildingCursor(Tower* tower);

    void updatePos(QPointF pos);
    QGraphicsPixmapItem& getTower();

private:
    QGraphicsPixmapItem towerPixmap;
    QGraphicsPolygonItem towerAttackArea;

    void generateAttackArea(Tower* tower);
};

