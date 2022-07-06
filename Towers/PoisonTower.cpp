#include "PoisonTower.h"
#include "Game/Game.h"
#include "Game/GameConstants.h"
#include "Projectiles/VenomProjectile.h"
#include "Misc/Utility.h"
#include <iostream>

using namespace GameConstants::TowerConstants;

extern Game* game;

PoisonTower::PoisonTower() : Tower()
{
    connect(this,&Tower::upgrade,this,&PoisonTower::upgrade);
    attackRange = PoisonTower::tier1AttackRange;
    attackInterval = PoisonTower::tier1AttackInterval;
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Towers/Images/PoisonTower1.png"), defaultTowerWidth);
    setPixmap(scaled);
    sellValue = pow(PoisonTower::tier1Cost, valueDecay);
}

// public methods
int PoisonTower::getTier1Cost()
{
    return PoisonTower::tier1Cost;
}

QString PoisonTower::getImageUrl(Tower* tower, bool HD)
{
    switch (tower->getTier()){
        case 1:
            return (HD) ? ":/Towers/Images/PoisonTower1HD.png" : ":/Towers/Images/PoisonTower1.png";
        case 2:
            return (HD) ? ":/Towers/Images/PoisonTower2HD.png" : ":/Towers/Images/PoisonTower2.png";
        case 3:
            return (HD) ? ":/Towers/Images/PoisonTower3HD.png" : ":/Towers/Images/PoisonTower3.png";
    }
}

int PoisonTower::getUpgradeCost(Tower* tower)
{
    switch (tower->getTier()){
        case 1:
            return PoisonTower::tier2Cost;
        case 2:
            return PoisonTower::tier3Cost;
    }
}

// private methods

void PoisonTower::attackTarget()
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

void PoisonTower::tier1Attack()
{
    static constexpr int attacks = 4;
    for (int i = 0; i < attacks; ++i){
        VenomProjectile* venom = new VenomProjectile(tier, this);
        linkToTarget(venom, target);
        venom->setRotation(venom->rotation() + RNG::randomNum(-25, 25));
    }
}

void PoisonTower::tier2Attack()
{
    static constexpr int attacks = 5;
    for (int i = 0; i < attacks; ++i){
        VenomProjectile* venom = new VenomProjectile(tier, this);
        linkToTarget(venom, target);
        venom->setRotation(venom->rotation() + RNG::randomNum(-25, 25));
    }
}

void PoisonTower::tier3Attack()
{

    static constexpr int attacks = 6;
    for (int i = 0; i < attacks; ++i){
        VenomProjectile* venom = new VenomProjectile(tier, this);
        linkToTarget(venom, target);
        venom->setRotation(venom->rotation() + RNG::randomNum(-25, 25));
    }
}

void PoisonTower::upgrade()
{
    switch (tier){
        case 2:
            setAttackRange(PoisonTower::tier2AttackRange);
            setAttackInterval(PoisonTower::tier2AttackInterval);
            return;
        case 3:
            setAttackRange(PoisonTower::tier3AttackRange);
            setAttackInterval(PoisonTower::tier3AttackInterval);
            return;
    }
}
