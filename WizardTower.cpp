#include "WizardTower.h"
#include "BeaconTower.h"
#include "Game.h"
#include "NovaProjectile.h"
#include "Utility.h"
#include <iostream>

extern Game* game;

WizardTower::WizardTower() :
    Tower(),
    novaSummoned(false)
{
    attackRange = WizardTower::defaultAttackRange;
    attackInterval = WizardTower::defaultAttackInterval;
    setPixmap(QPixmap(":/Towers/Images/WizardTower1.png"));
    sellValue = std::pow(WizardTower::defaultCost, Tower::valueDecay);
}

WizardTower::~WizardTower()
{
}

// public methods
QString WizardTower::getImageUrl(Tower* tower, bool HD)
{
    switch (tower->getTier()){
        case 1:
            return (HD) ? ":/Towers/Images/WizardTower1HD.png" : ":/Towers/Images/WizardTower1.png";
        case 2:
            return (HD) ? ":/Towers/Images/WizardTower2HD.png" : ":/Towers/Images/WizardTower2.png";
        case 3:
            return (HD) ? ":/Towers/Images/WizardTower3HD.png" : ":/Towers/Images/WizardTower3.png";
    }
}

int WizardTower::getUpgradeCost(Tower* tower)
{
    switch (tower->getTier()){
        case 1:
            return WizardTower::tier2Cost;
        case 2:
            return WizardTower::tier3Cost;
    }
}

void WizardTower::attackTarget()
{
    int num = RNG::randomNum(1,tier);

    switch(num){
        case(1):
            tier1Attack();
            return;
        case(2):
            tier2Attack();
            return;
        case(3):
            tier3Attack();
            return;
    }
}

// private methods
void WizardTower::tier1Attack()
{
    if (novaSummoned) { return; };
    NovaProjectile* nova = new NovaProjectile(tier, this);
    linkToTarget(nova, target);
    novaSummoned = true;
    connect(nova,&NovaProjectile::returned,this,&WizardTower::novaReturned);
}

void WizardTower::tier2Attack()
{
    QList<QGraphicsItem*> collisions = attackArea->collidingItems();

    for (auto& item : collisions){
        if (dynamic_cast<WizardTower*>(item) || dynamic_cast<BeaconTower*>(item)) { continue; };
        Tower* tower = dynamic_cast<Tower*>(item);
        if (tower && RNG::randomNum(1,100) <= Tower::consecutiveAttackChance){
            tower->consecutiveAttack();
        }
    }
}

void WizardTower::tier3Attack()
{
    if (attackRange == WizardTower::tier3Range) { return; };
    attackRange = WizardTower::tier3Range;
    defineAttackArea();
}

// private slots
void WizardTower::novaReturned()
{
    novaSummoned = false;
}
