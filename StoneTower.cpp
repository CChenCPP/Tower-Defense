#include "StoneTower.h"
#include "StoneProjectile.h"
#include "Game.h"
#include <iostream>

extern Game* game;

StoneTower::StoneTower() : Tower()
{
    attackRange = 300;
    attackInterval = 750;
    setPixmap(QPixmap(":/Towers/Images/StoneTower1.png"));
    sellValue = pow(StoneTower::defaultCost, Tower::valueDecay);
}

// public methods
QString StoneTower::getImageUrl(Tower* tower, bool HD)
{
    switch (tower->getTier()){
        case 1:
            return (HD) ? ":/Towers/Images/StoneTower1HD.png" : ":/Towers/Images/StoneTower1.png";
        case 2:
            return (HD) ? ":/Towers/Images/StoneTower2HD.png" : ":/Towers/Images/StoneTower2.png";
        case 3:
            return (HD) ? ":/Towers/Images/StoneTower3HD.png" : ":/Towers/Images/StoneTower3.png";
    }
}

int StoneTower::getUpgradeCost(Tower* tower)
{
    switch (tower->getTier()){
        case 1:
            return StoneTower::tier2Cost;
        case 2:
            return StoneTower::tier3Cost;
    }
}

// private methods

void StoneTower::attackTarget(Enemy* target)
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

void StoneTower::tier1Attack(Enemy* target)
{
    StoneProjectile* stone = new StoneProjectile(tier, this);
    initProjectile(this, stone, target);
}

void StoneTower::tier2Attack(Enemy* target)
{
    StoneProjectile* stone = new StoneProjectile(tier, this);
    initProjectile(this, stone, target);
}

void StoneTower::tier3Attack(Enemy* target)
{
    StoneProjectile* stone = new StoneProjectile(tier, this);
    initProjectile(this, stone, target);
}
