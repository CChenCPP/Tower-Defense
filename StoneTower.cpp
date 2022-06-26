#include "StoneTower.h"
#include "StoneProjectile.h"
#include "Game.h"
#include "Utility.h"
#include "StoneFragment.h"
#include <iostream>

extern Game* game;

StoneTower::StoneTower() : Tower()
{
    attackRange = StoneTower::defaultAttackRange;
    attackInterval = StoneTower::defaultAttackInterval;
    setPixmap(QPixmap(":/Towers/Images/StoneTower1.png"));
    sellValue = pow(StoneTower::defaultCost, Tower::valueDecay);
}

// public methods
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
