#include "ArcherTower.h"
#include "ArrowProjectile.h"
#include "Game.h"
#include "Utility.h"
#include <iostream>

extern Game* game;

ArcherTower::ArcherTower() :
    Tower()
{
    connect(this,&Tower::upgrade,this,&ArcherTower::upgrade);
    attackRange = ArcherTower::tier1AttackRange;
    attackInterval = ArcherTower::tier1AttackInterval;
    setPixmap(QPixmap(":/Towers/Images/ArcherTower1.png"));
    sellValue = std::pow(ArcherTower::tier1Cost, Tower::valueDecay);
}


// public methods
int ArcherTower::getDefaultCost()
{
    return ArcherTower::tier1Cost;
}

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
    int attackType = RNG::randomNum(1,tier);
    switch(attackType){
        case(1):
            shootArrow(); return;
        case(2):
            splitShot(); return;
        case(3):
            hurricane(); return;
    }
}

void ArcherTower::hurricane()
{
    for (int i = 0; i < 9; ++i){
        ArrowProjectile* arrow = new ArrowProjectile(tier, 3, this);
        linkToTarget(arrow, target);
        arrow->setRotation(arrow->rotation() + RNG::randomNum(-25,25));
    }

    ArrowProjectile* arrow = new ArrowProjectile(tier, 3, this);
    linkToTarget(arrow, target);
}

void ArcherTower::shootArrow()
{
    ArrowProjectile* arrow = new ArrowProjectile(tier, 1, this);
    linkToTarget(arrow, target);
}

void ArcherTower::splitShot()
{
    for (int i = 0; i < 2; ++i){
        ArrowProjectile* arrow = new ArrowProjectile(tier, 2, this);
        linkToTarget(arrow, target);
        arrow->setRotation(arrow->rotation() + RNG::randomNum(-20,20));
    }

    ArrowProjectile* arrow = new ArrowProjectile(tier, 2, this);
    linkToTarget(arrow, target);
}

// private slots
void ArcherTower::upgrade()
{
    switch (tier){
        case 2:
            setAttackRange(ArcherTower::tier2AttackRange);
            setAttackInterval(ArcherTower::tier2AttackInterval);
            return;
        case 3:
            setAttackRange(ArcherTower::tier3AttackRange);
            setAttackInterval(ArcherTower::tier3AttackInterval);
            return;
    }
}
