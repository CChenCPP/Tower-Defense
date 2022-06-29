#include "Projectile.h"
#include "Game.h"
#include "Explosion.h"
#include "IceShard.h"
#include "NovaProjectile.h"
#include "StoneFragment.h"
#include "Utility.h"
#include <iostream>

extern Game* game;

Projectile::Projectile(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent),
    attributes{},
    source(nullptr),
    target(nullptr),
    distanceTravelled(0),
    headshotChance(Projectile::defaultHeadshotChance),
    hypothermiaChance(Projectile::defaultHypothermiaChance),
    hypothermiaDurationMs(Projectile::defaultHypothermiaDurationMs),
    maimChance(Projectile::defaultMaimChance),
    maimDurationMs(Projectile::defaultMaimDurationMs),
    poisonChance(Projectile::defaultPoisonChance),
    poisonIntervalMs(Projectile::defaultPoisonIntervalMs)
{
    game->mainScene->incrementProjectileCount();
    determineIfRenderable();
    connect(&updateInterval,&QTimer::timeout,this,&Projectile::move);
    connect(&updateInterval,&QTimer::timeout,this,&Projectile::hitEnemies);
    updateInterval.start(10);
}

Projectile::~Projectile()
{
    game->mainScene->decrementProjectileCount();
    game->mainScene->removeItem(this);
}

// public methods
int Projectile::getDamage() const
{
    return damage;
}

int Projectile::getHeadshotChance() const
{
    return headshotChance;
}

int Projectile::getHypothermiaChance() const
{
    return hypothermiaChance;
}

int Projectile::getHypothermiaDurationMs() const
{
    return hypothermiaDurationMs;
}

int Projectile::getMaimChance() const
{
    return maimChance;
}

int Projectile::getMaimDurationMs() const
{
    return maimDurationMs;
}

int Projectile::getPoisonChance() const
{
    return poisonChance;
}

int Projectile::getPoisonIntervalMs() const
{
    return poisonIntervalMs;
}

int Projectile::getTier() const
{
    return tier;
}

Tower* Projectile::getSource() const
{
    return source;
}

Enemy* Projectile::getTarget() const
{
    return target;
}

bool Projectile::hasAttribute(ProjAttr attr) const
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

Projectile &Projectile::setAttributes(ProjAttr attr)
{
    attributes = attributes | attr;
    return *this;
}

void Projectile::setTarget(Enemy* target)
{
    this->target = target;
}

// public methods
void Projectile::determineIfRenderable()
{
    game->mainScene->projectileCapacity() > 1 ? hide() : show();
}

void Projectile::rotateToTarget()
{
    if (target){
        QLineF line(pos(),
                    target->pos());
        setRotation(-1 * line.angle());
    }
}

// private methods
void Projectile::explode()
{
    Explosion* explosion = new Explosion(this);
    delete this;
}

void Projectile::fragment()
{
    for (int i = 0; i < tier * 3; ++i){
        StoneFragment* fragment = new StoneFragment(this);
    }
    delete this;
}

void Projectile::shatter()
{
    for (int i = 0; i < tier * 7; ++i){
        IceShard* shard = new IceShard(this);
    }
    delete this;
}

// public slots
void Projectile::hitEnemies(){
    QList<QGraphicsItem*> collidingItems = this->collidingItems();
    for (auto& item : collidingItems){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy){
            if (this->hasAttribute(ProjAttr::Ethereal) && enemy != this->target) { continue; };
            if (this->hasAttribute(ProjAttr::Explosive)) { explode(); return; };
            if (this->hasAttribute(ProjAttr::Fragmenting)) { fragment();return; };
            if (this->hasAttribute(ProjAttr::Shattering)) { shatter();return; };

            connect(enemy,&Enemy::killedBy,this,&Projectile::onTargetKilled,Qt::UniqueConnection);
            connect(enemy,&Enemy::damagedAmount,this,&Projectile::onEnemyDamaged,Qt::UniqueConnection);

            enemy->damage(this->damage * source->getDamageMultiplier(), this);
            if (this->hasAttribute(ProjAttr::Warping) || this->hasAttribute(ProjAttr::Ethereal)) { return; };
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
        if (this->hasAttribute(ProjAttr::Explosive)) { explode(); return; };
        if (this->hasAttribute(ProjAttr::Fragmenting)) { fragment();return; };
        if (this->hasAttribute(ProjAttr::Shattering)) { shatter();return; };
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

    NovaProjectile* nova = dynamic_cast<NovaProjectile*>(this);
    if (nova) { nova->returnToSource(); };
}

// private slots
