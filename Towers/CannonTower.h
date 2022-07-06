#pragma once
#include "Tower.h"

class CannonTower : public Tower
{
public:
    CannonTower();

    static int getTier1Cost();
    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    static constexpr int tier1AttackRange = 125;
    static constexpr int tier1AttackInterval = 1250;
    static constexpr int tier1Cost = 100;
    static constexpr int tier2AttackRange = 175;
    static constexpr int tier2AttackInterval = 1250;
    static constexpr int tier2Cost = 500;
    static constexpr int tier3AttackRange = 200;
    static constexpr int tier3AttackInterval = 1250;
    static constexpr int tier3Cost = 7500;

    void attackTarget();
    void tier1Attack();
    void tier2Attack();
    void tier3Attack();

private slots:
    void upgrade();
};

