#pragma once
#include "Tower.h"

class ArcherTower : public Tower
{
public:
    ArcherTower();

    static constexpr int defaultAttackRange = 500;
    static constexpr int defaultAttackInterval = 2500;
    static constexpr int defaultCost = 100;
    static constexpr int tier2Cost = 1000;
    static constexpr int tier3Cost = 10000;

    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    void attackTarget();
    void tier1Attack();
    void tier2Attack();
    void tier3Attack();
};

