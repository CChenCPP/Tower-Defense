#include "CannonTower.h"
#include "Game/Game.h"
#include "Game/GameConstants.h"
#include "Projectiles/Explosion.h"
#include "Misc/Utility.h"

using namespace GameConstants::TowerConstants;

extern Game* game;

CannonTower::CannonTower() : Tower()
{
    connect(this,&Tower::upgrade,this,&CannonTower::upgrade);
    type = TowerType::Cannon;
    attackRange = CannonTower::tier1AttackRange;
    attackInterval = CannonTower::tier1AttackInterval;
    sizeMultiplier = cannonTowerSizeMultiplier;
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Towers/Images/CannonTower1.png"), defaultTowerWidth * sizeMultiplier);
    setPixmap(scaled);
    sellValue = pow(CannonTower::tier1Cost, valueDecay);
}

// public methods
int CannonTower::getTier1Cost()
{
    return CannonTower::tier1Cost;
}

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
void CannonTower::upgrade()
{
    switch (tier){
        case 2:
            setAttackRange(CannonTower::tier2AttackRange);
            setAttackInterval(CannonTower::tier2AttackInterval);
            return;
        case 3:
            setAttackRange(CannonTower::tier3AttackRange);
            setAttackInterval(CannonTower::tier3AttackInterval);
            return;
    }
}

