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
    void attackTarget();
    void tier1Attack();
    void tier2Attack();
    void tier3Attack();

};

