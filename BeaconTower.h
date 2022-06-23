#pragma once
#include "Tower.h"
#include <unordered_set>

class BeaconTower : public Tower
{
public:
    BeaconTower();
    ~BeaconTower();

    static constexpr int defaultCost = 100;
    static constexpr int tier2Cost = 1000;
    static constexpr int tier3Cost = 10000;

    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    std::unordered_set<Tower*> buffedAttackRateNeighbors;
    std::unordered_set<Tower*> buffedDamageNeighbors;

    void attackTarget(Enemy* target = nullptr);
    void tier1Attack();
    void tier2Attack();
    void tier3Attack();

private slots:
    void onNeighborDestructing(Tower* tower);
};

