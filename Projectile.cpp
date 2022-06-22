#include "Projectile.h"
#include <QPixmap>
#include "Utility.h"
#include "Game.h"
#include "Enemy.h"
#include <iostream>

extern Game* game;

Projectile::Projectile(ProjType type, QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent),
    target(nullptr),
    type(type),
    distanceTravelled(0)
{
    setImage(type);
    setAttributes(type);
    connect(&updateInterval,&QTimer::timeout,this,&Projectile::move);
    connect(&updateInterval,&QTimer::timeout,this,&Projectile::hitEnemies);
    updateInterval.start(50);
}

void Projectile::setTarget(Enemy* target)
{
    this->target = target;
}

// private methods

void Projectile::rotateToTarget()
{
    if (type == ProjType::Arrow) { return; };
    if (target){
        QLineF line(pos(), target->pos());
        setRotation(-1 * line.angle());
    }
}

void Projectile::setImage(ProjType type)
{
    switch(type)
    {
        case ProjType::Arrow:
            setPixmap(QPixmap(":/Projectiles/Images/Arrow1.png"));
            break;

        case ProjType::Cannonball:
            setPixmap(QPixmap(":/Projectiles/Images/Cannonball1.png"));
            break;

        case ProjType::Stone:
            setPixmap(QPixmap(":/Projectiles/Images/Stone1.png"));
            break;
    }
}

void Projectile::setAttributes(ProjType type)
{
    switch(type)
    {
        case ProjType::Arrow:
            damage = 5;
            distancePerInterval = 100;
            maxDistance = 1500;
            break;

        case ProjType::Cannonball:
            damage = 25;
            distancePerInterval = 15;
            maxDistance = 400;
            break;

        case ProjType::Stone:
            damage = 10;
            distancePerInterval = 35;
            maxDistance = 750;
            break;
    }
}

// public slots
void Projectile::targetIsDead()
{
    target = nullptr;
}

// private slots
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

void Projectile::hitEnemies(){
    QList<QGraphicsItem*> collidingItems = this->collidingItems();
    for (auto& item : collidingItems){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy){
            enemy->damage(this->damage);
            delete this;
            return;
        }
    }
}
