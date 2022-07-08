#include "Projectile.h"
#include "Game/Game.h"
#include "Explosion.h"
#include "IceShard.h"
#include "NovaProjectile.h"
#include "StoneFragment.h"
#include "Misc/Utility.h"

extern Game* game;

Projectile::Projectile(QGraphicsItem *parent) :
    CustomGraphicsPixmapItem(parent),
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
    poisonIntervalMs(Projectile::defaultPoisonIntervalMs),
    poisonMinRoll(Projectile::defaultPoisonMinRoll),
    poisonMaxRoll(Projectile::defaultPoisonMaxRoll)
{
    game->mainScene->incrementProjectileCount();
//    determineIfRenderable();
    connect(game,&Game::resetting,this,&Projectile::newGame);
    connect(&updateInterval,&QTimer::timeout,this,&Projectile::move);
    connect(&updateInterval,&QTimer::timeout,this,&Projectile::hitEnemies);
    updateInterval.start(18);
}

Projectile::~Projectile()
{
    game->mainScene->decrementProjectileCount();
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

int Projectile::getPoisonMinRoll() const
{
    return poisonMinRoll;
}

int Projectile::getPoisonMaxRoll() const
{
    return poisonMaxRoll;
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

void Projectile::setTarget(Enemy* target)
{
    this->target = target;
}

// protected methods
void Projectile::determineIfRenderable()
{
    game->mainScene->projectileCapacity() > 1 ? hide() : show();
}

void Projectile::rotateToTarget()
{
    if (target){ QLineF line(center(), target->center()); setRotation(-1 * line.angle()); };
}

// private methods
void Projectile::explode()
{
    Explosion* explosion = new Explosion(this);
    delete this;
}

void Projectile::fragment()
{
    for (int i = 0; i < tier * 2; ++i){
        StoneFragment* fragment = new StoneFragment(this);
    }
    delete this;
}

void Projectile::shatter()
{
    for (int i = 0; i < tier * 4; ++i){
        IceShard* shard = new IceShard(this);
    }
    delete this;
}

// public slots
void Projectile::hitEnemies(){
    for (Enemy* enemy : game->getEnemyList()){
        if (Geometry::distance2D(center(), enemy->center()) <= radius() + enemy->radius() - 1){
            if (isEthereal() && enemy != target) { continue; };
            if (isExplosive()) { explode(); return; };
            if (isFragmenting()) { fragment(); return; };
            if (isShattering()) { shatter(); return; };

            connect(enemy,&Enemy::killedBy,this,&Projectile::onTargetKilled,Qt::UniqueConnection);
            connect(enemy,&Enemy::damagedAmount,this,&Projectile::onEnemyDamaged,Qt::UniqueConnection);

            enemy->damage(this);
            if (!isWarping() && !isEthereal()) { delete this; };
            return;
        }
    }
}

void Projectile::move()
{
    rotateToTarget();
    qreal theta = rotation();
    qreal dx = distancePerInterval * qCos(qDegreesToRadians(theta));
    qreal dy = distancePerInterval * qSin(qDegreesToRadians(theta));
    setPos(x() + dx, y() + dy);
    distanceTravelled += distancePerInterval;
    if (distanceTravelled >= maxDistance) {
        if (isExplosive()) { explode(); return; };
        if (isFragmenting()) { fragment(); return; };
        if (isShattering()) { shatter(); return; };
        delete this;
    }
}

void Projectile::onEnemyDamaged(Projectile* projectile, int damage)
{
    if (projectile == this) {
        source->incrementDamageDone(damage);
    }
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
    if (nova) { nova->bounceNext(); };
}

// private slots
void Projectile::newGame()
{
    delete this;
}