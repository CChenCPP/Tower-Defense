#include "BeaconTower.h"
#include "ArrowProjectile.h"
#include "Game.h"
#include <iostream>

extern Game* game;

BeaconTower::BeaconTower() :
    Tower()
{
    attackRange = 150;
    attackInterval = 1000;
    setPixmap(QPixmap(":/Towers/Images/BeaconTower1.png"));
    sellValue = std::pow(BeaconTower::defaultCost, Tower::valueDecay);
}

BeaconTower::~BeaconTower()
{
    for (Tower* tower : buffedAttackRateNeighbors){
        if (tower) { tower->setAttackIntervalMultiplier(1 / 0.93); };
    }
    for (Tower* tower : buffedDamageNeighbors){
        if (tower) { tower->setDmgMultiplier(1 / log(3)); };
    }
}

// public methods
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
void BeaconTower::attackTarget(Enemy* target)
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

void BeaconTower::tier1Attack()
{
    QList<QGraphicsItem*> collisions = attackArea->collidingItems();

    for (auto& item : collisions){
        if (dynamic_cast<BeaconTower*>(item)) { continue; };
        Tower* tower = dynamic_cast<Tower*>(item);
        if (tower && buffedAttackRateNeighbors.find(tower) == buffedAttackRateNeighbors.end()){
            connect(tower,&Tower::destructing,this,&BeaconTower::onNeighborDestructing);
            tower->setAttackIntervalMultiplier(0.93);
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
            tower->setDmgMultiplier(log(3));
            buffedDamageNeighbors.insert(tower);
        }
    }
}

void BeaconTower::tier3Attack()
{
}

// private slots
void BeaconTower::onNeighborDestructing(Tower* tower)
{
    std::cout << &tower << std::endl;
    buffedAttackRateNeighbors.erase(tower);
    buffedDamageNeighbors.erase(tower);
//    auto iter = buffedAttackRateNeighbors.find(tower);
//    *iter = nullptr;
//    auto iter2 = buffedDamageNeighbors.find(tower);
//    *iter2 = nullptr;
}
