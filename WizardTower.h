#pragma once
#include "Tower.h"
#include <unordered_set>

class WizardTower : public Tower
{
    Q_OBJECT
public:
    WizardTower();
    ~WizardTower();

    static constexpr int defaultAttackRange = 150;
    static constexpr int defaultAttackInterval = 1750;
    static constexpr int defaultCost = 100;
    static constexpr int tier2Cost = 500;
    static constexpr int tier3Cost = 7500;

    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    static constexpr int tier3Range = 300;

    QTimer checkNeighborsTimer;
    bool novaSummoned;

    void attackTarget();
    void tier1Attack();
    void tier2Attack();
    void tier3Attack();

private slots:
    void novaReturned();
};

