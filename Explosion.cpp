#include "Explosion.h"
#include "Utility.h"
#include "Game.h"
#include <iostream>

extern Game* game;

Explosion::Explosion(Projectile* parent) :
    Projectile()
{
    distancePerInterval = 0;
    maxDistance = 0;
    source = parent->getSource();
    target = parent->getTarget();
    damage = parent->getDamage();
    connect(source,&Tower::destructing,this,&Projectile::onTowerDestructing);
    connect(this,&Projectile::killedTarget,source,&Tower::onTargetKilled);
    setPixmap(Explosion::getExplosionPixmap(source->getTier()));
    setPos(parent->pos());
    setRotation(parent->rotation());
    game->mainScene->addItem(this);
    explode();
}

Explosion::~Explosion()
{
//    std::cout << "Destructing explosion" << std::endl;
}

void Explosion::explode()
{
//    if (target) { this->setPos(target->pos()); };

    QList<QGraphicsItem*> collidingItems = this->collidingItems();
    for (auto& item : collidingItems){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy){
            connect(enemy,&Enemy::killedBy,this,&Projectile::onTargetKilled);
            connect(enemy,&Enemy::damagedAmount,this,&Projectile::onEnemyDamaged);
            enemy->damage(this->damage * source->getDmgMultiplier(), this);
        }
    }
    updateInterval.disconnect();
    QTimer::singleShot(250, this, [this](){ delete this; });
}

// private methods
QPixmap Explosion::getExplosionPixmap(int tier)
{
    switch(tier)
    {
        case 1:
            return QPixmap(":/Special/Images/CannonballExplosion1a.png");
        case 2:
            return QPixmap(":/Special/Images/CannonballExplosion2a.png");
        case 3:
            return QPixmap(":/Special/Images/CannonballExplosion3a.png");
    }
}
