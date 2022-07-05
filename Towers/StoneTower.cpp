#include "StoneTower.h"
#include "Game/Game.h"
#include "Game/GameConstants.h"
#include "Projectiles/StoneFragment.h"
#include "Misc/Utility.h"
#include <iostream>

using namespace GameConstants::TowerConstants;

extern Game* game;

StoneTower::StoneTower() : Tower()
{
    connect(this,&Tower::upgrade,this,&StoneTower::upgrade);
    attackRange = StoneTower::tier1AttackRange;
    attackInterval = StoneTower::tier1AttackInterval;
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Towers/Images/StoneTower1.png"), defaultTowerWidth);
    setPixmap(scaled);
    sellValue = pow(StoneTower::tier1Cost, valueDecay);
}

// public methods
int StoneTower::getDefaultCost()
{
    return StoneTower::tier1Cost;
}

QString StoneTower::getImageUrl(Tower* tower, bool HD)
{
    switch (tower->getTier()){
        case 1:
            return (HD) ? ":/Towers/Images/StoneTower1HD.png" : ":/Towers/Images/StoneTower1.png";
        case 2:
            return (HD) ? ":/Towers/Images/StoneTower2HD.png" : ":/Towers/Images/StoneTower2.png";
        case 3:
            return (HD) ? ":/Towers/Images/StoneTower3HD.png" : ":/Towers/Images/StoneTower3.png";
    }
}

int StoneTower::getUpgradeCost(Tower* tower)
{
    switch (tower->getTier()){
        case 1:
            return StoneTower::tier2Cost;
        case 2:
            return StoneTower::tier3Cost;
    }
}

// private methods

void StoneTower::attackTarget()
{
    if (!targetWithinRange()) { return; };
    switch(tier){
        case(1):
            tier1Attack(); return;
        case(2):
            tier2Attack(); return;
        case(3):
            tier3Attack(); return;
    }
}

void StoneTower::tier1Attack()
{
    StoneProjectile* stone = new StoneProjectile(tier, this);
    linkToTarget(stone, target);
}

void StoneTower::tier2Attack()
{
    StoneProjectile* stone = new StoneProjectile(tier, this);
    linkToTarget(stone, target);
}

void StoneTower::tier3Attack()
{
    StoneProjectile* stone = new StoneProjectile(tier, this);
    linkToTarget(stone, target);
}

void StoneTower::upgrade()
{
    switch (tier){
        case 2:
            setAttackRange(StoneTower::tier2AttackRange);
            setAttackInterval(StoneTower::tier2AttackInterval);
            return;
        case 3:
            setAttackRange(StoneTower::tier3AttackRange);
            setAttackInterval(StoneTower::tier3AttackInterval);
            return;
    }
}
