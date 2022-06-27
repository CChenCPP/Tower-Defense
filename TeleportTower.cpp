#include "TeleportTower.h"
#include "TeleportProjectile.h"
#include <iostream>

TeleportTower::TeleportTower() :
    Tower()
{
    connect(this,&Tower::upgrade,this,&TeleportTower::upgrade);
    maxTier = 1;
    attackRange = TeleportTower::tier1AttackRange;
    attackInterval = TeleportTower::tier1AttackInterval;
    setPixmap(QPixmap(":/Towers/Images/TeleportTower1.png"));
    sellValue = std::pow(TeleportTower::tier1Cost, Tower::valueDecay);
}

TeleportTower::~TeleportTower()
{
}

// public methods
void TeleportTower::init()
{
    Tower::init();
}

int TeleportTower::getDefaultCost()
{
    return TeleportTower::tier1Cost;
}

QString TeleportTower::getImageUrl(Tower* tower, bool HD)
{
    switch (tower->getTier()){
        case 1:
            return (HD) ? ":/Towers/Images/TeleportTower1HD.png" : ":/Towers/Images/TeleportTower1.png";
    }
}

int TeleportTower::getUpgradeCost(Tower* tower)
{
    switch (tower->getTier()){
        case 1:
            return 0;
    }
}

void TeleportTower::attackTarget()
{
    switch(tier){
        case(1):
            tier1Attack();
            return;
    }
}

// private methods
void TeleportTower::tier1Attack()
{
    TeleportProjectile* null = new TeleportProjectile(this);
    linkToTarget(null, target);
}

// private slots
void TeleportTower::upgrade()
{
    return;
}
