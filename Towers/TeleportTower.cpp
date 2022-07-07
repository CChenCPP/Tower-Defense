#include "TeleportTower.h"
#include "Game/Game.h"
#include "Game/GameConstants.h"
#include "Projectiles/TeleportProjectile.h"
#include "Misc/Utility.h"
#include <iostream>

using namespace GameConstants::TowerConstants;

extern Game* game;

TeleportTower::TeleportTower() :
    Tower()
{
    connect(this,&Tower::upgrade,this,&TeleportTower::upgrade);
    type = TowerType::Teleport;
    maxTier = 1;
    attackRange = TeleportTower::tier1AttackRange;
    attackInterval = TeleportTower::tier1AttackInterval;
    sizeMultiplier = teleportTowerSizeMultiplier;
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Towers/Images/TeleportTower1.png"), defaultTowerWidth * sizeMultiplier);
    setPixmap(scaled);
    sellValue = std::pow(TeleportTower::tier1Cost, valueDecay);
}

TeleportTower::~TeleportTower()
{
}

// public methods
int TeleportTower::getTier1Cost()
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
    if (!targetWithinRange()) { return; };
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
