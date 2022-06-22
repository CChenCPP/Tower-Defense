#include "Enemy.h"
#include <iostream>
#include "Game.h"
#include "Utility.h"

extern Game* game;

Enemy::Enemy(QList<QPointF>* path, int hp, int armor, int distPerInt, QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent),
    hp(hp),
    armor(armor),
    path(path),
    distancePerInterval(distPerInt)
{
    setPixmap(QPixmap(":/Enemies/Images/EnemyBlackCircle.png"));
    setPos((*path)[0]);
    startPath();
    setMoveInterval();
}

Enemy::~Enemy()
{
    emit destructing();
    game->mainScene->removeItem(this);
    game->enemyDestroyed();
}

// public methods
void Enemy::damage(int damage)
{
    int trueDamage = std::max<int>(0, damage - armor);
    hp -= trueDamage;
    if (hp <= 0) { delete this; };
}

// private methods
void Enemy::rotateToPoint(QPointF point)
{
    QLineF line(pos(), point);
    setRotation(-1 * line.angle());
}

void Enemy::setMoveInterval()
{
    connect(&moveInterval,&QTimer::timeout,this,&Enemy::moveForward);
    moveInterval.start(25);
}

void Enemy::startPath()
{
    pointsIndex = 0;
    dest = (*path)[0];
    rotateToPoint(dest);
}


// slots
void Enemy::moveForward(){
    QLineF line(pos(), dest);

    if (line.length() < distancePerInterval){
        ++pointsIndex;
        if (pointsIndex == path->size()) {
//            --pointsIndex;
            delete this;
            return; };
        dest = (*path)[pointsIndex];
        rotateToPoint(QPointF(dest.x(), dest.y()));
    }

    double theta = rotation();
    double dx = distancePerInterval * qCos(qDegreesToRadians(theta));
    double dy = distancePerInterval * qSin(qDegreesToRadians(theta));
    setPos(x() + dx, y() + dy);
}
