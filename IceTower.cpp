#include "IceTower.h"
#include "Projectile.h"
#include "Game.h"
#include "IceProjectile.h"
#include "IceShard.h"
#include <iostream>

extern Game* game;

IceTower::IceTower() : Tower()
{
    attackRange = IceTower::defaultAttackRange;
    attackInterval = IceTower::defaultAttackInterval;
    setPixmap(QPixmap(":/Towers/Images/IceTower1.png"));
    sellValue = pow(IceTower::defaultCost, Tower::valueDecay);
}

// public methods
QString IceTower::getImageUrl(Tower* tower, bool HD)
{
    switch (tower->getTier()){
        case 1:
            return (HD) ? ":/Towers/Images/IceTower1HD.png" : ":/Towers/Images/IceTower1.png";
        case 2:
            return (HD) ? ":/Towers/Images/IceTower2HD.png" : ":/Towers/Images/IceTower2.png";
        case 3:
            return (HD) ? ":/Towers/Images/IceTower3HD.png" : ":/Towers/Images/IceTower3.png";
    }
}

int IceTower::getUpgradeCost(Tower* tower)
{
    switch (tower->getTier()){
        case 1:
            return IceTower::tier2Cost;
        case 2:
            return IceTower::tier3Cost;
    }
}

// private methods
void IceTower::attackTarget()
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


void IceTower::tier1Attack()
{
    IceProjectile* ice = new IceProjectile(tier, this);
    linkToTarget(ice, target);
}

void IceTower::tier2Attack()
{
    IceProjectile* ice = new IceProjectile(tier, this);
    linkToTarget(ice, target);
}

void IceTower::tier3Attack()
{
    IceProjectile* ice = new IceProjectile(tier, this);
    linkToTarget(ice, target);
}
