#include "CannonTower.h"
#include "Projectile.h"
#include "Game.h"
#include "CannonballProjectile.h"
#include <iostream>

extern Game* game;

CannonTower::CannonTower() : Tower()
{
    attackRange = 150;
    attackInterval = 1000;
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

void CannonTower::tier1Attack(Enemy* target)
{
    CannonballProjectile* cannonball = new CannonballProjectile(tier, this);
    initProjectile(this, cannonball, target);
}

void CannonTower::tier2Attack(Enemy* target)
{
    CannonballProjectile* cannonball = new CannonballProjectile(tier, this);
    initProjectile(this, cannonball, target);
}

void CannonTower::tier3Attack(Enemy* target)
{
    CannonballProjectile* cannonball = new CannonballProjectile(tier, this);
    initProjectile(this, cannonball, target);
}
