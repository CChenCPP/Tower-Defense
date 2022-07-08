#include "IceTower.h"
#include "Game/Game.h"
#include "Game/GameConstants.h"
#include "Projectiles/IceShard.h"
#include "Misc/Utility.h"

using namespace GameConstants::TowerConstants;

extern Game* game;

IceTower::IceTower() : Tower()
{
    connect(this,&Tower::upgrade,this,&IceTower::upgrade);
    type = TowerType::Ice;
    attackRange = IceTower::tier1AttackRange;
    attackInterval = IceTower::tier1AttackInterval;
    sizeMultiplier = iceTowerSizeMultiplier;
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Towers/Images/IceTower1.png"), defaultTowerWidth * sizeMultiplier);
    setPixmap(scaled);
    sellValue = pow(IceTower::tier1Cost, valueDecay);
}

// public methods
int IceTower::getTier1Cost()
{
    return IceTower::tier1Cost;
}

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

// private slots
void IceTower::upgrade()
{
    switch (tier){
        case 2:
            setAttackRange(IceTower::tier2AttackRange);
            setAttackInterval(IceTower::tier2AttackInterval);
            return;
        case 3:
            setAttackRange(IceTower::tier3AttackRange);
            setAttackInterval(IceTower::tier3AttackInterval);
            return;
    }
}

