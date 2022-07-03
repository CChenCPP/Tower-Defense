#pragma once
#include "Tower.h"

class ArcherTower : public Tower
{
public:
    ArcherTower();

    static int getDefaultCost();
    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    static constexpr int tier1AttackRange = 300;
    static constexpr int tier1AttackInterval = 2500;
    static constexpr int tier1Cost = 100;
    static constexpr int tier2AttackRange = 400;
    static constexpr int tier2AttackInterval = 2500;
    static constexpr int tier2Cost = 1000;
    static constexpr int tier3AttackRange = 500;
    static constexpr int tier3AttackInterval = 2500;
    static constexpr int tier3Cost = 10000;

    void attackTarget();
    void hurricane();
    void shootArrow();
    void splitShot();

private slots:
    void upgrade();
};

