#pragma once
#include "Tower.h"
#include <unordered_set>

class TeleportTower : public Tower
{
public:
    TeleportTower();
    ~TeleportTower();

    static constexpr int defaultAttackRange = 225;
    static constexpr int defaultAttackInterval = 3000;
    static constexpr int defaultCost = 300;

    void init();
    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:

    void attackTarget();
    void tier1Attack();
    void tier2Attack();
    void tier3Attack();
};

