#pragma once
#include "Tower.h"
#include <unordered_set>

class WizardTower : public Tower
{
    Q_OBJECT
public:
    WizardTower();
    ~WizardTower();

    static int getTier1Cost();
    static QString getImageUrl(Tower* tower, bool HD = false);
    static int getUpgradeCost(Tower* tower);

private:
    static constexpr int tetherChance = 80;
    static constexpr int tier1AttackRange = 150;
    static constexpr int tier1AttackInterval = 1750;
    static constexpr int tier1Cost = 300;
    static constexpr int tier2AttackRange = 200;
    static constexpr int tier2AttackInterval = 1500;
    static constexpr int tier2Cost = 1500;
    static constexpr int tier3AttackRange = 225;
    static constexpr int tier3AttackInterval = 1250;
    static constexpr int tier3Cost = 20000;

    QTimer checkNeighborsTimer;
    bool novaSummoned;
    QGraphicsPathItem* tether;
    QTimer tetherBlinkInterval;
    Tower* tetherTarget;

    void attackTarget();
    void linkTower(Tower* tower);
    void paintTether(Tower* tower);
    void tetherNeighbor();
    void summonBlackHole();
    void summonNova();

private slots:
    void novaReturned();
    void tetheredTargetDestructing(Tower* tower);
    void upgrade();

signals:
    void unlinkTether();
};

