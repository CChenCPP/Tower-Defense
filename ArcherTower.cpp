#include "ArcherTower.h"
#include "ArrowProjectile.h"
#include "Game.h"
#include "Utility.h"
#include <iostream>

extern Game* game;

ArcherTower::ArcherTower() :
    Tower()
{
    attackRange = ArcherTower::defaultAttackRange;
    attackInterval = ArcherTower::defaultAttackInterval;
    setPixmap(QPixmap(":/Towers/Images/ArcherTower1.png"));
    sellValue = std::pow(ArcherTower::defaultCost, Tower::valueDecay);
}

// public methods
QString ArcherTower::getImageUrl(Tower* tower, bool HD)
{
    switch (tower->getTier()){
        case 1:
            return (HD) ? ":/Towers/Images/ArcherTower1HD.png" : ":/Towers/Images/ArcherTower1.png";
        case 2:
            return (HD) ? ":/Towers/Images/ArcherTower2HD.png" : ":/Towers/Images/ArcherTower2.png";
        case 3:
            return (HD) ? ":/Towers/Images/ArcherTower3HD.png" : ":/Towers/Images/ArcherTower3.png";
    }
}

int ArcherTower::getUpgradeCost(Tower* tower)
{
    switch (tower->getTier()){
        case 1:
            return ArcherTower::tier2Cost;
        case 2:
            return ArcherTower::tier3Cost;
    }
}

// private methods
void ArcherTower::attackTarget()
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

void ArcherTower::tier1Attack()
{
    ArrowProjectile* arrow = new ArrowProjectile(tier, this);
    linkToTarget(arrow, target);
}

void ArcherTower::tier2Attack()
{
    for (int i = 0; i < 2; ++i){
        ArrowProjectile* arrow = new ArrowProjectile(tier, this);
        linkToTarget(arrow, target);
        arrow->setRotation(arrow->rotation() + RNG::randomNum(-30,30));
    }

    ArrowProjectile* arrow = new ArrowProjectile(tier, this);
    linkToTarget(arrow, target);
}

void ArcherTower::tier3Attack()
{
    for (int i = 0; i < 4; ++i){
        ArrowProjectile* arrow = new ArrowProjectile(tier, this);
        linkToTarget(arrow, target);
        arrow->setRotation(arrow->rotation() + RNG::randomNum(-45,45));
    }

    ArrowProjectile* arrow = new ArrowProjectile(tier, this);
    linkToTarget(arrow, target);
}
