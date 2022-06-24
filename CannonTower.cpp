#include "CannonTower.h"
#include "Projectile.h"
#include "Game.h"
#include "CannonballProjectile.h"
#include "Explosion.h"
#include <iostream>

extern Game* game;

CannonTower::CannonTower() : Tower()
{
    attackRange = CannonTower::defaultAttackRange;
    attackInterval = CannonTower::defaultAttackInterval;
    setPixmap(QPixmap(":/Towers/Images/CannonTower1.png"));
    sellValue = pow(CannonTower::defaultCost, Tower::valueDecay);
}

// public methods
QString CannonTower::getImageUrl(Tower* tower, bool HD)
{
    switch (tower->getTier()){
        case 1:
            return (HD) ? ":/Towers/Images/CannonTower1HD.png" : ":/Towers/Images/CannonTower1.png";
        case 2:
            return (HD) ? ":/Towers/Images/CannonTower2HD.png" : ":/Towers/Images/CannonTower2.png";
        case 3:
            return (HD) ? ":/Towers/Images/CannonTower3HD.png" : ":/Towers/Images/CannonTower3.png";
    }
}

int CannonTower::getUpgradeCost(Tower* tower)
{
    switch (tower->getTier()){
        case 1:
            return CannonTower::tier2Cost;
        case 2:
            return CannonTower::tier3Cost;
    }
}

// private methods
void CannonTower::attackTarget(Enemy* target)
{
    switch(tier){
        case(1):
            tier1Attack(target); return;
        case(2):
            tier2Attack(target); return;
        case(3):
            tier3Attack(target); return;
    }
}

void CannonTower::setProjectileAttributes(Projectile* projectile)
{
    switch(tier){
        case(1):
            projectile->setAttribute(ProjAttr::Explosive);
            return;
        case(2):
            projectile->setAttribute(ProjAttr::Explosive).setAttribute(ProjAttr::Piercing);
            return;
        case(3):
            projectile->setAttribute(ProjAttr::Explosive).setAttribute(ProjAttr::Piercing);
            return;
    }
}

void CannonTower::tier1Attack(Enemy* target)
{
    CannonballProjectile* cannonball = new CannonballProjectile(tier, this);
    connect(cannonball,&Projectile::explode,this,&CannonTower::explode);
    setProjectileAttributes(cannonball);
    initProjectile(this, cannonball, target);
}

void CannonTower::tier2Attack(Enemy* target)
{
    CannonballProjectile* cannonball = new CannonballProjectile(tier, this);
    connect(cannonball,&Projectile::explode,this,&CannonTower::explode);
    setProjectileAttributes(cannonball);
    initProjectile(this, cannonball, target);
}

void CannonTower::tier3Attack(Enemy* target)
{
    CannonballProjectile* cannonball = new CannonballProjectile(tier, this);
    connect(cannonball,&Projectile::explode,this,&CannonTower::explode);
    setProjectileAttributes(cannonball);
    initProjectile(this, cannonball, target);
}

// private slots
void CannonTower::explode(Projectile* projectile)
{
    Explosion* explosion = new Explosion(projectile);

    delete projectile;
    projectile = nullptr;
}
