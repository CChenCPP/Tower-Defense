#pragma once
#include "Tower.h"

class ArcherTower : public Tower
{
public:
    ArcherTower();

    static constexpr int defaultCost = 100;
    static constexpr int tier2Cost = 1000;
    static constexpr int tier3Cost = 10000;

    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    void attackTarget(Enemy* target);
    void tier1Attack(Enemy* target);
    void tier2Attack(Enemy* target);
    void tier3Attack(Enemy* target);
};

