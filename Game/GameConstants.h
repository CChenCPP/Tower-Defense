#pragma once
#include "Enemies/Enemy.h"

namespace GameConstants{
    namespace EnemyConstants{
        static constexpr qreal hpScale = 1;

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
        static constexpr int khyemisHp = 200;
        static constexpr int khyemisArmor = 0;
        static constexpr qreal khyemisSpeed = 6;

        static EnemyAttr kronusAttributes = EnemyAttr::Chrono;
        static constexpr int kronusHp = 100;
        static constexpr int kronusArmor = 30;
        static constexpr qreal kronusSpeed = 8;

        static EnemyAttr loldohrAttributes = EnemyAttr::HeadshotResistant | EnemyAttr::Frost | EnemyAttr::MaimResistant | EnemyAttr::Impenetrable;
        static constexpr int loldohrHp = 75;
        static constexpr int loldohrArmor = 40;
        static constexpr qreal loldohrSpeed = 5;

        static EnemyAttr phihenarAttributes = EnemyAttr::Regenerative | EnemyAttr::HeadshotResistant;
        static constexpr int phihenarHp = 75;
        static constexpr int phihenarArmor = 5;
        static constexpr qreal phihenarSpeed = 5;

        static EnemyAttr rihrusAttributes = EnemyAttr::Chrono | EnemyAttr::BurnResistant;
        static constexpr int rihrusHp = 200;
        static constexpr int rihrusArmor = 2;
        static constexpr qreal rihrusSpeed = 6;

        static EnemyAttr udallAttributes = EnemyAttr::PoisonResistant | EnemyAttr::Frost | EnemyAttr::MaimResistant | EnemyAttr::Impenetrable;
        static constexpr int udallHp = 150;
        static constexpr int udallArmor = 15;
        static constexpr qreal udallSpeed = 5;

        static EnemyAttr uesisAttributes = EnemyAttr::PoisonResistant | EnemyAttr::Frost | EnemyAttr::MaimResistant;
        static constexpr int uesisHp = 175;
        static constexpr int uesisArmor = 0;
        static constexpr qreal uesisSpeed = 6;

        static EnemyAttr zanbrisAttributes = EnemyAttr::BurnResistant | EnemyAttr::Impenetrable | EnemyAttr::HeadshotResistant | EnemyAttr::PoisonResistant | EnemyAttr::MaimResistant;
        static constexpr int zanbrisHp = 125;
        static constexpr int zanbrisArmor = 15;
        static constexpr qreal zanbrisSpeed = 5;
    }
}