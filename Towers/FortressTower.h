#pragma once
#include "Tower.h"

class FortressTower : public Tower
{
    Q_OBJECT
public:
    FortressTower();

    static int getTier1Cost();
    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    static constexpr int tier1AttackInterval = 10000;
    static constexpr int tier1Cost = 1000;
    static constexpr int tier1MinRoll = 50;
    static constexpr int tier1MaxRoll = 100;
    static constexpr int tier2AttackInterval = 10000;
    static constexpr int tier2Cost = 5000;
    static constexpr int tier2MinRoll = 150;
    static constexpr int tier2MaxRoll = 300;
    static constexpr int tier3AttackInterval = 10000;
    static constexpr int tier3Cost = 20000;
    static constexpr int tier3MinRoll = 500;
    static constexpr int tier3MaxRoll = 1000;

    int minRoll;
    int maxRoll;

    void attackTarget();

private slots:
    void upgrade();

signals:
    void generateRevenue(int amount);
};

