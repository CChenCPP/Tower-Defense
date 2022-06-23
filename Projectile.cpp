#include "Projectile.h"
#include <QPixmap>
#include "Utility.h"
#include "Game.h"
#include "Enemy.h"
#include <iostream>

extern Game* game;

Projectile::Projectile(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent),
    source(nullptr),
    target(nullptr),
    distanceTravelled(0)
{
    connect(&updateInterval,&QTimer::timeout,this,&Projectile::move);
    connect(&updateInterval,&QTimer::timeout,this,&Projectile::hitEnemies);
    updateInterval.start(10);
}

void Projectile::setTarget(Enemy* target)
{
    this->target = target;
}

// private methods
void Projectile::rotateToTarget()
{
    if (target){
        QLineF line(pos(), target->pos());
        setRotation(-1 * line.angle());
    }
}

// public slots

void Projectile::onTargetKilled(Projectile* projectile, Enemy* enemy)
{
    if (projectile == this){
        emit killedTarget(enemy);
    }
}

void Projectile::targetIsDead()
{
    target = nullptr;
}

// private slots
void Projectile::hitEnemies(){
    QList<QGraphicsItem*> collidingItems = this->collidingItems();
    for (auto& item : collidingItems){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy){
            connect(enemy,&Enemy::killedBy,this,&Projectile::onTargetKilled);
            connect(enemy,&Enemy::damagedAmount,this,&Projectile::onEnemyDamaged);
            std::cout << this->damage * source->getDmgMultiplier() << std::endl;
            enemy->damage(this->damage * source->getDmgMultiplier(), this);
            delete this;
            return;
        }
    }
}

void Projectile::move()
{
    rotateToTarget();
    double theta = rotation();
    double dx = distancePerInterval * qCos(qDegreesToRadians(theta));
    double dy = distancePerInterval * qSin(qDegreesToRadians(theta));
    setPos(x() + dx, y() + dy);
    distanceTravelled += distancePerInterval;
    if (distanceTravelled >= maxDistance) { delete this; };
}

void Projectile::onEnemyDamaged(int damage)
{
    source->incrementDamageDone(damage);
}
