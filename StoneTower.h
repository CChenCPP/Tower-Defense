#pragma once
#include "Tower.h"

class StoneTower : public Tower
{
public:
    StoneTower();

    static constexpr int defaultAttackRange = 225;
    static constexpr int defaultAttackInterval = 1000;
    static constexpr int defaultCost = 75;
    static constexpr int tier2Cost = 750;
    static constexpr int tier3Cost = 12500;

    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    void attackTarget(Enemy* target);
    void setProjectileAttributes(Projectile* projectile);
    void tier1Attack(Enemy* target);
    void tier2Attack(Enemy* target);
    void tier3Attack(Enemy* target);

private slots:
    void fragment(Projectile* projectile);
};

