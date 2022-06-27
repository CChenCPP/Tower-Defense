#pragma once
#include "Tower.h"
#include <unordered_set>

class TeleportTower : public Tower
{
public:
    TeleportTower();
    ~TeleportTower();

    void init();
    static int getDefaultCost();
    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    static constexpr int tier1AttackRange = 225;
    static constexpr int tier1AttackInterval = 3000;
    static constexpr int tier1Cost = 300;

    void attackTarget();
    void tier1Attack();
    void tier2Attack();
    void tier3Attack();

private slots:
    void upgrade();
};

