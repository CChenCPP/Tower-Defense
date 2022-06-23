#include "Enemy.h"
#include <iostream>
#include "Utility.h"
#include "Game.h"

extern Game* game;

Enemy::Enemy(QList<QPointF>* path, int hp, int armor, int distPerInt, QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent),
    hp(hp),
    armor(armor),
    value(RNG::randomNum(hp,hp*2)),
    path(path),
    distancePerInterval(distPerInt),
    lastProjectile(nullptr)
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
void Enemy::damage(int damage, Projectile* projectile)
{
    lastProjectile = projectile;
    int trueDamage = std::max<int>(0, damage - armor);
    trueDamage = std::min<int>(hp, trueDamage);
    emit damagedAmount(trueDamage);
    hp -= trueDamage;
    if (hp <= 0) {
        game->enemyKilled(this);
        emit killedBy(lastProjectile, this);
        delete this; };
}

int Enemy::getValue()
{
    return value;
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
    pathIndex = 0;
    dest = (*path)[0];
    rotateToPoint(dest);
}


// slots
void Enemy::moveForward(){
    QLineF line(pos(), dest);

    if (line.length() < distancePerInterval){
        ++pathIndex;
        if (pathIndex == path->size()) {
            game->enemyLeaked();
            delete this;
            return; };
        dest = (*path)[pathIndex];
        rotateToPoint(QPointF(dest.x(), dest.y()));
    }

    double theta = rotation();
    double dx = distancePerInterval * qCos(qDegreesToRadians(theta));
    double dy = distancePerInterval * qSin(qDegreesToRadians(theta));
    setPos(x() + dx, y() + dy);
}
