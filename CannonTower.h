#pragma once
#include "Tower.h"

class CannonTower : public Tower
{
public:
    CannonTower();

    static constexpr int defaultAttackRange = 150;
    static constexpr int defaultAttackInterval = 1000;
    static constexpr int defaultCost = 50;
    static constexpr int tier2Cost = 500;
    static constexpr int tier3Cost = 15000;

    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    void attackTarget(Enemy* target);
    void setProjectileAttributes(Projectile* projectile);
    void tier1Attack(Enemy* target);
    void tier2Attack(Enemy* target);
    void tier3Attack(Enemy* target);

private slots:
    void explode(Projectile* projectile);
};

