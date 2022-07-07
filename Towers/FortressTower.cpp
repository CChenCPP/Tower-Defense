#include "FortressTower.h"
#include "Game/Game.h"
#include "Game/GameConstants.h"
#include "Projectiles/Explosion.h"
#include "Misc/Utility.h"
#include <iostream>

using namespace GameConstants::TowerConstants;

extern Game* game;

FortressTower::FortressTower() :
    Tower(),
    minRoll(tier1MinRoll),
    maxRoll(tier1MaxRoll)
{
    connect(this,&Tower::upgrade,this,&FortressTower::upgrade);
    connect(this,&FortressTower::generateRevenue,game,&Game::onRevenueGenerated);
    type = TowerType::Fortress;
    attackRange = 0;
    attackInterval = FortressTower::tier1AttackInterval;
    sizeMultiplier = fortressTowerSizeMultiplier;
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Towers/Images/FortressTower1.png"), defaultTowerWidth * sizeMultiplier);
    setPixmap(scaled);
    sellValue = pow(FortressTower::tier1Cost, valueDecay);
}

// public methods
int FortressTower::getTier1Cost()
{
    return FortressTower::tier1Cost;
}

QString FortressTower::getImageUrl(Tower* tower, bool HD)
{
    switch (tower->getTier()){
        case 1:
            return (HD) ? ":/Towers/Images/FortressTower1HD.png" : ":/Towers/Images/FortressTower1.png";
        case 2:
            return (HD) ? ":/Towers/Images/FortressTower2HD.png" : ":/Towers/Images/FortressTower2.png";
        case 3:
            return (HD) ? ":/Towers/Images/FortressTower3HD.png" : ":/Towers/Images/FortressTower3.png";
    }
}

int FortressTower::getUpgradeCost(Tower* tower)
{
    switch (tower->getTier()){
        case 1:
            return FortressTower::tier2Cost;
        case 2:
            return FortressTower::tier3Cost;
    }
}

// private methods
void FortressTower::attackTarget()
{
    emit generateRevenue(RNG::randomNum(minRoll,maxRoll));
}

// private slots
void FortressTower::upgrade()
{
    switch (tier){
        case 2:
            minRoll = tier2MinRoll;
            maxRoll = tier2MaxRoll;
            setAttackInterval(FortressTower::tier2AttackInterval);
            return;
        case 3:
            minRoll = tier3MinRoll;
            maxRoll = tier3MaxRoll;
            setAttackInterval(FortressTower::tier3AttackInterval);
            return;
    }
}

