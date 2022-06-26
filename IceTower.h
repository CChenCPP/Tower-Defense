#pragma once
#include "Tower.h"

class IceTower : public Tower
{
public:
    IceTower();

    static constexpr int defaultAttackRange = 100;
    static constexpr int defaultAttackInterval = 1500;
    static constexpr int defaultCost = 125;
    static constexpr int tier2Cost = 500;
    static constexpr int tier3Cost = 4000;

    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    void attackTarget();
    void tier1Attack();
    void tier2Attack();
    void tier3Attack();

};

