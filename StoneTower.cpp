#include "StoneTower.h"
#include "StoneProjectile.h"
#include "Game.h"
#include "Utility.h"
#include "StoneFragment.h"
#include <iostream>

extern Game* game;

StoneTower::StoneTower() : Tower()
{
    attackRange = StoneTower::defaultAttackRange;
    attackInterval = StoneTower::defaultAttackInterval;
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

void StoneTower::setProjectileAttributes(Projectile* projectile)
{
    switch(tier){
        case(1):
            projectile->setAttribute(ProjAttr::Fragmenting);
            return;
        case(2):
            projectile->setAttribute(ProjAttr::Fragmenting);
            return;
        case(3):
            projectile->setAttribute(ProjAttr::Fragmenting);
            return;
    }
}

void StoneTower::tier1Attack(Enemy* target)
{
    StoneProjectile* stone = new StoneProjectile(tier, this);
    connect(stone,&Projectile::fragment,this,&StoneTower::fragment);
    setProjectileAttributes(stone);
    initProjectile(this, stone, target);
}

void StoneTower::tier2Attack(Enemy* target)
{
    StoneProjectile* stone = new StoneProjectile(tier, this);
    connect(stone,&Projectile::fragment,this,&StoneTower::fragment);
    setProjectileAttributes(stone);
    initProjectile(this, stone, target);
}

void StoneTower::tier3Attack(Enemy* target)
{
    StoneProjectile* stone = new StoneProjectile(tier, this);
    connect(stone,&Projectile::fragment,this,&StoneTower::fragment);
    setProjectileAttributes(stone);
    initProjectile(this, stone, target);
}

//private slots
void StoneTower::fragment(Projectile* projectile)
{
    for (int i = 0; i < tier * 3; ++i){
        StoneFragment* fragment = new StoneFragment(projectile);
    }

    delete projectile;
    projectile = nullptr;
}
