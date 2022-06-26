#pragma once
#include "Tower.h"

class BallistaTower : public Tower
{
public:
    BallistaTower();

    static constexpr int defaultAttackRange = 600;
    static constexpr int defaultAttackInterval = 4000;
    static constexpr int defaultCost = 250;
    static constexpr int tier2Cost = 1500;
    static constexpr int tier3Cost = 6000;

    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    void attackTarget();
    void tier1Attack();
    void tier2Attack();
    void tier3Attack();
};

