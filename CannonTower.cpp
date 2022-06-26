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
void CannonTower::attackTarget()
{
    switch(tier){
        case(1):
            tier1Attack(); return;
        case(2):
            tier2Attack(); return;
        case(3):
            tier3Attack(); return;
    }
}

void CannonTower::tier1Attack()
{
    CannonballProjectile* cannonball = new CannonballProjectile(tier, this);
    linkToTarget(cannonball, target);
}

void CannonTower::tier2Attack()
{
    CannonballProjectile* cannonball = new CannonballProjectile(tier, this);
    linkToTarget(cannonball, target);
}

void CannonTower::tier3Attack()
{
    CannonballProjectile* cannonball = new CannonballProjectile(tier, this);
    linkToTarget(cannonball, target);
}

// private slots
