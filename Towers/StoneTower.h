#pragma once
#include "Tower.h"

class StoneTower : public Tower
{
public:
    StoneTower();

    static int getTier1Cost();
    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    static constexpr int tier1AttackRange = 200;
    static constexpr int tier1AttackInterval = 1000;
    static constexpr int tier1Cost = 100;
    static constexpr int tier2AttackRange = 225;
    static constexpr int tier2AttackInterval = 1000;
    static constexpr int tier2Cost = 750;
    static constexpr int tier3AttackRange = 250;
    static constexpr int tier3AttackInterval = 1000;
    static constexpr int tier3Cost = 10000;

    void attackTarget();
    void tier1Attack();
    void tier2Attack();
    void tier3Attack();

private slots:
    void upgrade();
};

