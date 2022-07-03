#pragma once
#include "Tower.h"

class IceTower : public Tower
{
public:
    IceTower();

    static int getDefaultCost();
    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    static constexpr int tier1AttackRange = 100;
    static constexpr int tier1AttackInterval = 1500;
    static constexpr int tier1Cost = 125;
    static constexpr int tier2AttackRange = 125;
    static constexpr int tier2AttackInterval = 1250;
    static constexpr int tier2Cost = 500;
    static constexpr int tier3AttackRange = 150;
    static constexpr int tier3AttackInterval = 1000;
    static constexpr int tier3Cost = 4000;

    void attackTarget();
    void tier1Attack();
    void tier2Attack();
    void tier3Attack();

private slots:
    void upgrade();
};

