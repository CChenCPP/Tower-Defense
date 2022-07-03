#include "BeaconTower.h"
#include "WizardTower.h"
#include "Game/Game.h"
#include "Misc/Utility.h"
#include <iostream>

extern Game* game;

BeaconTower::BeaconTower() :
    Tower()
{
    connect(this,&Tower::upgrade,this,&BeaconTower::upgrade);
    attackRange = BeaconTower::tier1AttackRange;
    attackInterval = BeaconTower::tier1AttackInterval;
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Towers/Images/BeaconTower1.png"), Game::defaultTowerWidth);;
    setPixmap(scaled);
    sellValue = std::pow(BeaconTower::tier1Cost, Tower::valueDecay);
}

BeaconTower::~BeaconTower()
{
    for (Tower* tower : buffedAttackRangeNeighbors){
        if (tower) { tower->setAttackRangeMultiplier(tower->getAttackRangeMultiplier() / BeaconTower::attackRangeMultiplierBuff); };
    }
    for (Tower* tower : buffedAttackRateNeighbors){
        if (tower) { tower->setAttackIntervalMultiplier(tower->getAttackIntervalMultiplier() / BeaconTower::attackIntervalMultiplierBuff); };
    }
    for (Tower* tower : buffedDamageNeighbors){
        if (tower) { tower->setDamageMultiplier(tower->getDamageMultiplier() / BeaconTower::damageMultiplierBuff); };
    }
}

// public methods
int BeaconTower::getDefaultCost()
{
    return BeaconTower::tier1Cost;
}

QString BeaconTower::getImageUrl(Tower* tower, bool HD)
{
    switch (tower->getTier()){
        case 1:
            return (HD) ? ":/Towers/Images/BeaconTower1HD.png" : ":/Towers/Images/BeaconTower1.png";
        case 2:
            return (HD) ? ":/Towers/Images/BeaconTower2HD.png" : ":/Towers/Images/BeaconTower2.png";
        case 3:
            return (HD) ? ":/Towers/Images/BeaconTower3HD.png" : ":/Towers/Images/BeaconTower3.png";
    }
}

int BeaconTower::getUpgradeCost(Tower* tower)
{
    switch (tower->getTier()){
        case 1:
            return BeaconTower::tier2Cost;
        case 2:
            return BeaconTower::tier3Cost;
    }
}

// private methods
void BeaconTower::attackTarget()
{
    switch(tier){
        case(1):
            buffDamage();
            return;
        case(2):
            buffDamage();
            buffAttackInterval();
            return;
        case(3):
            buffDamage();
            buffAttackInterval();
            buffAttackRange();
            return;
    }
}

void BeaconTower::buffDamage()
{
    for (Tower* tower : game->getTowerList()){
        bool valid = canBuffDamageMultiplier(tower);
        if (valid){
            tower->setDamageMultiplier(tower->getDamageMultiplier() * BeaconTower::damageMultiplierBuff);
            buffedDamageNeighbors.insert(tower);
            connect(tower,&Tower::destructing,this,&BeaconTower::onNeighborDestructing,Qt::UniqueConnection);
        }
    }
}

void BeaconTower::buffAttackInterval()
{
    for (Tower* tower : game->getTowerList()){
        bool valid = canBuffAttackIntervalMultiplier(tower);
        if (valid){
            tower->setAttackIntervalMultiplier(tower->getAttackIntervalMultiplier() * BeaconTower::attackIntervalMultiplierBuff);
            buffedAttackRateNeighbors.insert(tower);
            connect(tower,&Tower::destructing,this,&BeaconTower::onNeighborDestructing,Qt::UniqueConnection);
        }
    }
}

void BeaconTower::buffAttackRange()
{
    for (Tower* tower : game->getTowerList()){
        bool valid = canBuffAttackRangeMultiplier(tower);
        if (valid){
            tower->setAttackRangeMultiplier(tower->getAttackRangeMultiplier() * BeaconTower::attackRangeMultiplierBuff);
            buffedAttackRangeNeighbors.insert(tower);
            connect(tower,&Tower::destructing,this,&BeaconTower::onNeighborDestructing,Qt::UniqueConnection);
        }
    }
}

bool BeaconTower::canBuffAttackIntervalMultiplier(Tower* tower) const
{
    return !(dynamic_cast<BeaconTower*>(tower))
    && !(Geometry::distance2D(center(), tower->center()) > (attackRange + tower->radius() / 2))
    && (tower && tower->isBuilt() && buffedAttackRateNeighbors.find(tower) == buffedAttackRateNeighbors.end());
}

bool BeaconTower::canBuffAttackRangeMultiplier(Tower* tower) const
{
    return !(dynamic_cast<BeaconTower*>(tower))
    && !(Geometry::distance2D(center(), tower->center()) > (attackRange + tower->radius() / 2))
    && (tower && tower->isBuilt() && buffedAttackRangeNeighbors.find(tower) == buffedAttackRangeNeighbors.end());
}

bool BeaconTower::canBuffDamageMultiplier(Tower* tower) const
{
    return !(dynamic_cast<BeaconTower*>(tower))
    && !(Geometry::distance2D(center(), tower->center()) > (attackRange + tower->radius() / 2))
    && (tower && tower->isBuilt() && buffedDamageNeighbors.find(tower) == buffedDamageNeighbors.end());
}

// private slots
void BeaconTower::onNeighborDestructing(Tower* tower)
{
    buffedAttackRangeNeighbors.erase(tower);
    buffedAttackRateNeighbors.erase(tower);
    buffedDamageNeighbors.erase(tower);
}

void BeaconTower::upgrade()
{
    switch (tier){
        case 2:
            setAttackRange(BeaconTower::tier2AttackRange);
            setAttackInterval(BeaconTower::tier2AttackInterval);
            return;
        case 3:
            setAttackRange(BeaconTower::tier3AttackRange);
            setAttackInterval(BeaconTower::tier3AttackInterval);
            return;
    }
}
