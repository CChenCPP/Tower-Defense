#pragma once
#include "Tower.h"

class BallistaTower : public Tower
{
public:
    BallistaTower();

    static int getTier1Cost();
    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    static constexpr int tier1AttackRange = 400;
    static constexpr int tier1AttackInterval = 4000;
    static constexpr int tier1Cost = 200;
    static constexpr int tier2AttackRange = 500;
    static constexpr int tier2AttackInterval = 3500;
    static constexpr int tier2Cost = 1500;
    static constexpr int tier3AttackRange = 550;
    static constexpr int tier3AttackInterval = 3000;
    static constexpr int tier3Cost = 15000;

    void attackTarget();
    void tier1Attack();
    void tier2Attack();
    void tier3Attack();

private slots:
    void upgrade();
};

