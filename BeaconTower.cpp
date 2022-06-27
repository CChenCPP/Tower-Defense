#include "BeaconTower.h"
#include "WizardTower.h"
#include "Game.h"
#include <iostream>

extern Game* game;

BeaconTower::BeaconTower() :
    Tower()
{
    connect(this,&Tower::upgrade,this,&BeaconTower::upgrade);
    attackRange = BeaconTower::tier1AttackRange;
    attackInterval = BeaconTower::tier1AttackInterval;
    setPixmap(QPixmap(":/Towers/Images/BeaconTower1.png"));
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
void BeaconTower::init()
{
    Tower::init();
    setupTimers();
}

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

void BeaconTower::attackTarget()
{
    switch(tier){
        case(1):
            tier1Attack();
            return;
        case(2):
            tier1Attack();
            tier2Attack();
            return;
        case(3):
            tier1Attack();
            tier2Attack();
            tier3Attack();
            return;
    }
}

void BeaconTower::setupTimers()
{
    attackIntervalTimer.disconnect();
    QObject::connect(&checkNeighborsTimer,&QTimer::timeout,[&](){ attackTarget();});
    checkNeighborsTimer.start(attackInterval * attackIntervalMultiplier);
}

// private methods
void BeaconTower::tier1Attack()
{
    QList<QGraphicsItem*> collisions = attackArea->collidingItems();

    for (auto& item : collisions){
        if (dynamic_cast<BeaconTower*>(item)) { continue; };
        Tower* tower = dynamic_cast<Tower*>(item);
        if (tower && buffedDamageNeighbors.find(tower) == buffedDamageNeighbors.end()){
            tower->setDamageMultiplier(tower->getDamageMultiplier() * BeaconTower::damageMultiplierBuff);
            buffedDamageNeighbors.insert(tower);
            connect(tower,&Tower::destructing,this,&BeaconTower::onNeighborDestructing,Qt::UniqueConnection);
        }
    }
}

void BeaconTower::tier2Attack()
{
    QList<QGraphicsItem*> collisions = attackArea->collidingItems();

    for (auto& item : collisions){
        if (dynamic_cast<BeaconTower*>(item)) { continue; };
        Tower* tower = dynamic_cast<Tower*>(item);
        if (tower && buffedAttackRateNeighbors.find(tower) == buffedAttackRateNeighbors.end()){
            tower->setAttackIntervalMultiplier(tower->getAttackIntervalMultiplier() * BeaconTower::attackIntervalMultiplierBuff);
            buffedAttackRateNeighbors.insert(tower);
            connect(tower,&Tower::destructing,this,&BeaconTower::onNeighborDestructing,Qt::UniqueConnection);
        }
    }
}

void BeaconTower::tier3Attack()
{
    QList<QGraphicsItem*> collisions = attackArea->collidingItems();

    for (auto& item : collisions){
        if (dynamic_cast<BeaconTower*>(item)) { continue; };
        Tower* tower = dynamic_cast<Tower*>(item);
        if (tower && buffedAttackRangeNeighbors.find(tower) == buffedAttackRangeNeighbors.end()){
            tower->setAttackRangeMultiplier(tower->getAttackRangeMultiplier() * BeaconTower::attackRangeMultiplierBuff);
            buffedAttackRangeNeighbors.insert(tower);
            connect(tower,&Tower::destructing,this,&BeaconTower::onNeighborDestructing,Qt::UniqueConnection);
        }
    }
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
