#include "BuildingCursor.h"
#include "Game.h"
#include "Misc/Utility.h"

extern Game* game;

BuildingCursor::BuildingCursor(Tower* tower)
{
    towerPixmap.setPixmap(tower->pixmap());
    towerPixmap.setPos(x() - towerPixmap.pixmap().width() / 2, y() - towerPixmap.pixmap().height() + 25);
    generateAttackArea(tower);
    game->mainScene->addItem(this);
    game->mainScene->addItem(&towerPixmap);
    game->mainScene->addItem(&towerAttackArea);
}

// public functions
void BuildingCursor::updatePos(QPointF pos)
{
    int dx = x() - pos.x();
    int dy = y() - pos.y();
    setPos(pos);
    towerAttackArea.setPos(pos);
    towerPixmap.setPos(towerPixmap.x() - dx, towerPixmap.y() - dy);
}

QGraphicsPixmapItem& BuildingCursor::getTower()
{
    return towerPixmap;
}

// private functions
void BuildingCursor::generateAttackArea(Tower* tower)
{
    QVector<QPointF> circle = Geometry::generateCircle(45, tower->getAttackRange() * tower->getAttackRangeMultiplier());
    QPolygonF polygon(circle);
    towerAttackArea.setPolygon(polygon);
    towerAttackArea.setPen(Qt::NoPen);
    QColor transparentRed = Qt::red;
    transparentRed.setAlphaF(0.1);
    towerAttackArea.setBrush(transparentRed);
}
