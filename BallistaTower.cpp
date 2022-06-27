#include "BallistaTower.h"
#include "JavelinProjectile.h"
#include "Game.h"
#include "Utility.h"
#include <iostream>

extern Game* game;

BallistaTower::BallistaTower() :
    Tower()
{
    connect(this,&Tower::upgrade,this,&BallistaTower::upgrade);
    attackRange = BallistaTower::tier1AttackRange;
    attackInterval = BallistaTower::tier1AttackInterval;
    setPixmap(QPixmap(":/Towers/Images/BallistaTower1.png"));
    sellValue = std::pow(BallistaTower::tier1Cost, Tower::valueDecay);
}

// public methods
int BallistaTower::getDefaultCost()
{
    return BallistaTower::tier1Cost;
}

QString BallistaTower::getImageUrl(Tower* tower, bool HD)
{
    switch (tower->getTier()){
        case 1:
            return (HD) ? ":/Towers/Images/BallistaTower1HD.png" : ":/Towers/Images/BallistaTower1.png";
        case 2:
            return (HD) ? ":/Towers/Images/BallistaTower2HD.png" : ":/Towers/Images/BallistaTower2.png";
        case 3:
            return (HD) ? ":/Towers/Images/BallistaTower3HD.png" : ":/Towers/Images/BallistaTower3.png";
    }
}

int BallistaTower::getUpgradeCost(Tower* tower)
{
    switch (tower->getTier()){
        case 1:
            return BallistaTower::tier2Cost;
        case 2:
            return BallistaTower::tier3Cost;
    }
}

// private methods
void BallistaTower::attackTarget()
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

void BallistaTower::tier1Attack()
{
    JavelinProjectile* javelin = new JavelinProjectile(tier, this);
    linkToTarget(javelin, target);
}

void BallistaTower::tier2Attack()
{
    JavelinProjectile* javelin = new JavelinProjectile(tier, this);
    linkToTarget(javelin, target);
}

void BallistaTower::tier3Attack()
{
    JavelinProjectile* javelin = new JavelinProjectile(tier, this);
    linkToTarget(javelin, target);
}

// private slots
void BallistaTower::upgrade()
{
    switch (tier){
        case 2:
            setAttackRange(BallistaTower::tier2AttackRange);
            setAttackInterval(BallistaTower::tier2AttackInterval);
            return;
        case 3:
            setAttackRange(BallistaTower::tier3AttackRange);
            setAttackInterval(BallistaTower::tier3AttackInterval);
            return;
    }
}
