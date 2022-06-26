#pragma once
#include "Tower.h"
#include <unordered_set>

class BeaconTower : public Tower
{
public:
    BeaconTower();
    ~BeaconTower();

    static constexpr int defaultAttackRange = 150;
    static constexpr int defaultAttackInterval = 1000;
    static constexpr int defaultCost = 100;
    static constexpr int tier2Cost = 500;
    static constexpr int tier3Cost = 7500;

    void init();
    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    static constexpr float attackRateMultiplier = 0.93;
    static constexpr float damageMultiplier = log(3);
    static constexpr int tier3Range = 300;

    std::unordered_set<Tower*> buffedAttackRateNeighbors;
    std::unordered_set<Tower*> buffedDamageNeighbors;
    QTimer checkNeighborsTimer;

    void attackTarget();
    void setupTimers();
    void tier1Attack();
    void tier2Attack();
    void tier3Attack();

private slots:
    void onNeighborDestructing(Tower* tower);
};

