#include "Projectile.h"
#include <QPixmap>
#include "Utility.h"
#include "Game.h"
#include "Enemy.h"
#include "CannonballProjectile.h"
#include "StoneProjectile.h"
#include <iostream>

extern Game* game;

Projectile::Projectile(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent),
    attributes{},
    source(nullptr),
    target(nullptr),
    distanceTravelled(0)
{
    connect(&updateInterval,&QTimer::timeout,this,&Projectile::move);
    connect(&updateInterval,&QTimer::timeout,this,&Projectile::hitEnemies);
    updateInterval.start(10);
}

Projectile::~Projectile()
{

}

// public methods
int Projectile::getDamage() const
{
    return damage;
}

Tower* Projectile::getSource() const
{
    return source;
}

Enemy* Projectile::getTarget() const
{
    return target;
}

bool Projectile::hasAttribute(ProjAttr attr)
{
    return static_cast<bool>(attributes & attr);
}

Projectile& Projectile::removeAttribute(ProjAttr attr)
{
    attributes = attributes & ~attr;
    return *this;
}

Projectile &Projectile::removeAllAttributes()
{
    attributes = {};
    return *this;
}

Projectile& Projectile::setAttribute(ProjAttr attr)
{
    attributes = attributes | attr;
    return *this;
}

void Projectile::setTarget(Enemy* target)
{
    this->target = target;
}

// public methods
void Projectile::rotateToTarget()
{
    if (target){
        QLineF line(pos(), target->pos());
        setRotation(-1 * line.angle());
    }
}

// private methods

// public slots
void Projectile::hitEnemies(){
    QList<QGraphicsItem*> collidingItems = this->collidingItems();
    for (auto& item : collidingItems){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy){
            if (this->hasAttribute(ProjAttr::Explosive)) { emit explode(this); return; };
            if (this->hasAttribute(ProjAttr::Fragmenting)) { emit fragment(this);return; };
            connect(enemy,&Enemy::killedBy,this,&Projectile::onTargetKilled);
            connect(enemy,&Enemy::damagedAmount,this,&Projectile::onEnemyDamaged);
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
    if (distanceTravelled >= maxDistance) {
        if (this->hasAttribute(ProjAttr::Explosive)) { emit explode(this); return; };
        if (this->hasAttribute(ProjAttr::Fragmenting)) { emit fragment(this);return; };
        delete this;
    }
}

void Projectile::onEnemyDamaged(int damage)
{
    source->incrementDamageDone(damage);
}

void Projectile::onTargetKilled(Projectile* projectile, Enemy* enemy)
{
    if (projectile == this){
        emit killedTarget(enemy);
    }
}

void Projectile::onTowerDestructing()
{
    delete this;
}

void Projectile::targetIsDead()
{
    target = nullptr;
}

// private slots
