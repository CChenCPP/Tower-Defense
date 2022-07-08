#pragma once
#include "Enemies/Enemy.h"

namespace GameConstants{
    static constexpr int tileSize = 36;
    static constexpr qreal defaultTowerWidth = tileSize * 1.3;
    static constexpr qreal defaultIconWidth = 55;

    static constexpr int archerTowerLimit = std::numeric_limits<int>::max();
    static constexpr int ballistaTowerLimit = std::numeric_limits<int>::max();
    static constexpr int beaconTowerLimit = std::numeric_limits<int>::max();
    static constexpr int cannonTowerLimit = std::numeric_limits<int>::max();
    static constexpr int fortressTowerLimit = 15;
    static constexpr int iceTowerLimit = 10;
    static constexpr int poisonTowerLimit = 10;
    static constexpr int stoneTowerLimit = std::numeric_limits<int>::max();
    static constexpr int teleportTowerLimit = 5;
    static constexpr int wizardTowerLimit = std::numeric_limits<int>::max();

    static constexpr qreal archerTowerIconSizeMultiplier = 0.95;
    static constexpr qreal ballistaTowerIconSizeMultiplier = 1.00;
    static constexpr qreal beaconTowerIconSizeMultiplier = 0.75;
    static constexpr qreal cannonTowerIconSizeMultiplier = 1.00;
    static constexpr qreal fortressTowerIconSizeMultiplier = 1.20;
    static constexpr qreal iceTowerIconSizeMultiplier = 1.10;
    static constexpr qreal poisonTowerIconSizeMultiplier = 1.15;
    static constexpr qreal stoneTowerIconSizeMultiplier = 1.00;
    static constexpr qreal teleportTowerIconSizeMultiplier = 0.75;
    static constexpr qreal wizardTowerIconSizeMultiplier = 0.85;
    static constexpr int startingHealth = 100;
    static constexpr int startingMoney = 1000;

    namespace EnemyConstants{
        static constexpr int defaultMoveIntervalMs = 40;
        static constexpr qreal defaultSize = 32;
        static constexpr qreal defaultValueDecay = 0.55;
        static constexpr qreal defaultHpScale = 1.038;

        static EnemyAttr cukzotzAttributes = EnemyAttr::MaimResistant | EnemyAttr::Impenetrable;
        static constexpr int cukzotzHp = 150;
        static constexpr int cukzotzArmor = 10;
        static constexpr qreal cukzotzSpeed = 5;

        static EnemyAttr dharuerAttributes = EnemyAttr::PoisonResistant | EnemyAttr::Frost | EnemyAttr::Chrono;
        static constexpr int dharuerHp =  125;
        static constexpr int dharuerArmor = 8;
        static constexpr qreal dharuerSpeed = 4;

        static EnemyAttr enioneAttributes = EnemyAttr::BurnResistant | EnemyAttr::PoisonResistant;
        static constexpr int enioneHp = 250;
        static constexpr int enioneArmor = 0;
        static constexpr qreal enioneSpeed = 5;

        static EnemyAttr ezlotlAttributes = EnemyAttr::Chrono | EnemyAttr::MaimResistant;
        static constexpr int ezlotlHp = 200;
        static constexpr int ezlotlArmor = 1;
        static constexpr qreal ezlotlSpeed = 5;

        static EnemyAttr hudorAttributes = EnemyAttr::PoisonResistant | EnemyAttr::Regenerative;
        static constexpr int hudorHp = 200;
        static constexpr int hudorArmor = 3;
        static constexpr qreal hudorSpeed = 5;

        static EnemyAttr khyemisAttributes = EnemyAttr::MaimResistant | EnemyAttr::Frost;
        static constexpr int khyemisHp = 250;
        static constexpr int khyemisArmor = 0;
        static constexpr qreal khyemisSpeed = 7;

        static EnemyAttr kronusAttributes = EnemyAttr::Chrono;
        static constexpr int kronusHp = 100;
        static constexpr int kronusArmor = 30;
        static constexpr qreal kronusSpeed = 8;

        static EnemyAttr loldohrAttributes = EnemyAttr::HeadshotResistant | EnemyAttr::Frost | EnemyAttr::Impenetrable;
        static constexpr int loldohrHp = 75;
        static constexpr int loldohrArmor = 40;
        static constexpr qreal loldohrSpeed = 5;

        static EnemyAttr phihenarAttributes = EnemyAttr::Regenerative | EnemyAttr::HeadshotResistant;
        static constexpr int phihenarHp = 75;
        static constexpr int phihenarArmor = 15;
        static constexpr qreal phihenarSpeed = 5;

        static EnemyAttr rihrusAttributes = EnemyAttr::Chrono | EnemyAttr::BurnResistant;
        static constexpr int rihrusHp = 200;
        static constexpr int rihrusArmor = 25;
        static constexpr qreal rihrusSpeed = 6;

        static EnemyAttr udallAttributes = EnemyAttr::PoisonResistant | EnemyAttr::Frost | EnemyAttr::Impenetrable;
        static constexpr int udallHp = 150;
        static constexpr int udallArmor = 12;
        static constexpr qreal udallSpeed = 5;

        static EnemyAttr uesisAttributes = EnemyAttr::PoisonResistant | EnemyAttr::Frost | EnemyAttr::MaimResistant;
        static constexpr int uesisHp = 175;
        static constexpr int uesisArmor = 3;
        static constexpr qreal uesisSpeed = 6;

        static EnemyAttr zanbrisAttributes = EnemyAttr::BurnResistant | EnemyAttr::Impenetrable | EnemyAttr::HeadshotResistant | EnemyAttr::MaimResistant;
        static constexpr int zanbrisHp = 125;
        static constexpr int zanbrisArmor = 18;
        static constexpr qreal zanbrisSpeed = 5;
    }

    namespace TowerConstants{
        static constexpr int consecutiveAttackChance = 30;
        static constexpr int minimumAttackInterval = 333;
        static constexpr qreal valueDecay = 0.90;
        static constexpr int defaultMaxTier = 3;

        static constexpr qreal archerTowerSizeMultiplier = 1.10;
        static constexpr qreal ballistaTowerSizeMultiplier = 0.95;
        static constexpr qreal beaconTowerSizeMultiplier = 0.95;
        static constexpr qreal cannonTowerSizeMultiplier = 1.00;
        static constexpr qreal fortressTowerSizeMultiplier = 1.40;
        static constexpr qreal iceTowerSizeMultiplier = 1.10;
        static constexpr qreal poisonTowerSizeMultiplier = 1.15;
        static constexpr qreal stoneTowerSizeMultiplier = 1.05;
        static constexpr qreal teleportTowerSizeMultiplier = 0.95;
        static constexpr qreal wizardTowerSizeMultiplier = 0.95;
    }
}