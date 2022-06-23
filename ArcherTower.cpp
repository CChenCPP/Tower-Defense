#include "ArcherTower.h"
#include "ArrowProjectile.h"
#include "Game.h"
#include <iostream>

extern Game* game;

ArcherTower::ArcherTower() :
    Tower()
{
    attackRange = 300;
    attackInterval = 2500;
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
void ArcherTower::attackTarget(Enemy* target)
{
    switch(tier){
        case(1):
            tier1Attack(target); return;
        case(2):
            tier2Attack(target); return;
        case(3):
            tier3Attack(target); return;
    }
}

void ArcherTower::tier1Attack(Enemy* target)
{
    ArrowProjectile* arrow = new ArrowProjectile(tier, this);
    initProjectile(this, arrow, target);
}

void ArcherTower::tier2Attack(Enemy* target)
{
    ArrowProjectile* arrow = new ArrowProjectile(tier, this);
    initProjectile(this, arrow, target);
}

void ArcherTower::tier3Attack(Enemy* target)
{
    ArrowProjectile* arrow1 = new ArrowProjectile(tier, this);
    initProjectile(this, arrow1, target);
    arrow1->setTarget(nullptr);
    arrow1->setRotation(arrow1->rotation() - 10);

    ArrowProjectile* arrow2 = new ArrowProjectile(tier, this);
    initProjectile(this, arrow2, target);

    ArrowProjectile* arrow3 = new ArrowProjectile(tier, this);
    initProjectile(this, arrow3, target);
    arrow3->setTarget(nullptr);
    arrow3->setRotation(arrow3->rotation() - 10);
}
