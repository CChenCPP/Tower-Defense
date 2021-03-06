#pragma once
#include "Tower.h"
#include <unordered_set>

class BeaconTower : public Tower
{
public:
    BeaconTower();
    ~BeaconTower();

    static int getTier1Cost();
    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    static constexpr int tier1AttackRange = 150;
    static constexpr int tier1AttackInterval = 1000;
    static constexpr int tier1Cost = 125;
    static constexpr int tier2AttackRange = 200;
    static constexpr int tier2AttackInterval = 1000;
    static constexpr int tier2Cost = 1500;
    static constexpr int tier3AttackRange = 225;
    static constexpr int tier3AttackInterval = 1000;
    static constexpr int tier3Cost = 7500;
    static constexpr qreal attackRangeMultiplierBuff = 1.05;
    static constexpr qreal attackIntervalMultiplierBuff = 0.93;
    static constexpr qreal damageMultiplierBuff = 1.1;

    std::unordered_set<Tower*> buffedAttackRangeNeighbors;
    std::unordered_set<Tower*> buffedAttackRateNeighbors;
    std::unordered_set<Tower*> buffedDamageNeighbors;

    void attackTarget();
    void buffAttackInterval();
    void buffAttackRange();
    void buffDamage();
    bool canBuffAttackIntervalMultiplier(Tower* tower) const;
    bool canBuffAttackRangeMultiplier(Tower* tower) const;
    bool canBuffDamageMultiplier(Tower* tower) const;
    bool isValidNeighbor(Tower* tower) const;

private slots:
    void onNeighborDestructing(Tower* tower);
    void upgrade();
};

