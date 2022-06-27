#pragma once
#include "Tower.h"
#include <unordered_set>

class BeaconTower : public Tower
{
public:
    BeaconTower();
    ~BeaconTower();

    void init();
    static int getDefaultCost();
    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    static constexpr int tier1AttackRange = 150;
    static constexpr int tier1AttackInterval = 1000;
    static constexpr int tier1Cost = 100;
    static constexpr int tier2AttackRange = 200;
    static constexpr int tier2AttackInterval = 1000;
    static constexpr int tier2Cost = 500;
    static constexpr int tier3AttackRange = 225;
    static constexpr int tier3AttackInterval = 1000;
    static constexpr int tier3Cost = 7500;
    static constexpr float attackRangeMultiplierBuff = 1.05;
    static constexpr float attackIntervalMultiplierBuff = 0.93;
    static constexpr float damageMultiplierBuff = 1.1;

    std::unordered_set<Tower*> buffedAttackRangeNeighbors;
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
    void upgrade();
};

