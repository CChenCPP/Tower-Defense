#include "Tower.h"
#include <QVector>
#include <QPointF>
#include "Game.h"
#include "Enemy.h"
#include <iostream>

extern Game* game;

Tower::Tower(int attackRange, QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent),
    attackRange(attackRange),
    attackDestination(QPoint(0,0)),
    target(nullptr)
{
}

void Tower::init()
{
    setCenterOffset();
    defineAttackArea();
    setAttackInterval();
}

void Tower::defineAttackArea()
{
    QVector<QPointF> points;
    points << QPointF(1,0) << QPointF(2,0) << QPointF(3,1) << QPointF(3,2)
           << QPointF(2,3) << QPointF(1,3) << QPointF(0,2) << QPointF(0,1);

    for (size_t i = 0; i < points.size(); ++i){
        points[i] *= attackRange;
    }

    QPolygonF polygon(points);

    attackArea = new QGraphicsPolygonItem(polygon, this);

    QPointF polygonCenter(1.5,1.5);
    polygonCenter *= attackRange;
    polygonCenter = mapToScene(polygonCenter);

    QPointF towerCenter(x() + centerX, y() + centerY);

    QLineF line(polygonCenter,towerCenter);
    attackArea->setPos(x() + line.dx(), y() + line.dy());
    attackArea->setPen(Qt::NoPen);
}

double Tower::distanceTo(QPointF point)
{
    return QLineF(pos(), point).length();
}

void Tower::setAttackInterval()
{
    QObject::connect(&attackInterval,&QTimer::timeout,this,&Tower::determineTarget);
    attackInterval.start(1000);
}

void Tower::setCenterOffset()
{
    centerX = pixmap().width() / 2;
    centerY = pixmap().height() - pixmap().width() / 2;
}

// slots
void Tower::determineTarget()
{
    hasTarget = false;
    QList<QGraphicsItem*> collisions = attackArea->collidingItems();

    double closestDist = std::numeric_limits<int>::max();
    for (auto& item : collisions){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy){
            int distToTarget = distanceTo(enemy->pos());
            if (distToTarget < closestDist){
                double theta = enemy->rotation();
                double dx = qCos(qDegreesToRadians(theta));
                double dy = qSin(qDegreesToRadians(theta));
                closestDist = distToTarget;
                attackDestination = QPointF(enemy->pos().x() + dx*enemy->pixmap().width()/2, enemy->pos().y() + dy*enemy->pixmap().height()/2);
                target = enemy;
                hasTarget = true;
            }
        }
    }

    if (hasTarget) {
        attackTarget(target);
        target = nullptr; };
}
