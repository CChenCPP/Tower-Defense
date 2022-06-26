#include "BeaconTower.h"
#include "WizardTower.h"
#include "Game.h"
#include <iostream>

extern Game* game;

BeaconTower::BeaconTower() :
    Tower()
{
    attackRange = BeaconTower::defaultAttackRange;
    attackInterval = BeaconTower::defaultAttackInterval;
    setPixmap(QPixmap(":/Towers/Images/BeaconTower1.png"));
    sellValue = std::pow(BeaconTower::defaultCost, Tower::valueDecay);
}

BeaconTower::~BeaconTower()
{
    for (Tower* tower : buffedAttackRateNeighbors){
        if (tower) { tower->setAttackIntervalMultiplier(1 / BeaconTower::attackRateMultiplier); };
    }
    for (Tower* tower : buffedDamageNeighbors){
        if (tower) { tower->setDmgMultiplier(1 / BeaconTower::damageMultiplier); };
    }
}

// public methods
void BeaconTower::init()
{
    Tower::init();
    setupTimers();
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
    checkNeighborsTimer.start(attackInterval);
}

// private methods
void BeaconTower::tier1Attack()
{
    QList<QGraphicsItem*> collisions = attackArea->collidingItems();

    for (auto& item : collisions){
        if (dynamic_cast<BeaconTower*>(item) || dynamic_cast<WizardTower*>(item)) { continue; };
        Tower* tower = dynamic_cast<Tower*>(item);
        if (tower && buffedAttackRateNeighbors.find(tower) == buffedAttackRateNeighbors.end()){
            connect(tower,&Tower::destructing,this,&BeaconTower::onNeighborDestructing);
            tower->setAttackIntervalMultiplier(BeaconTower::attackRateMultiplier);
            buffedAttackRateNeighbors.insert(tower);
        }
    }
}

void BeaconTower::tier2Attack()
{
    QList<QGraphicsItem*> collisions = attackArea->collidingItems();

    for (auto& item : collisions){
        if (dynamic_cast<BeaconTower*>(item)) { continue; };
        Tower* tower = dynamic_cast<Tower*>(item);
        if (tower && buffedDamageNeighbors.find(tower) == buffedDamageNeighbors.end()){
            connect(tower,&Tower::destructing,this,&BeaconTower::onNeighborDestructing);
            tower->setDmgMultiplier(BeaconTower::damageMultiplier);
            buffedDamageNeighbors.insert(tower);
        }
    }
}

void BeaconTower::tier3Attack()
{
    if (attackRange == BeaconTower::tier3Range) { return; };
    attackRange = BeaconTower::tier3Range;
    defineAttackArea();
}

// private slots
void BeaconTower::onNeighborDestructing(Tower* tower)
{
    buffedAttackRateNeighbors.erase(tower);
    buffedDamageNeighbors.erase(tower);
}
