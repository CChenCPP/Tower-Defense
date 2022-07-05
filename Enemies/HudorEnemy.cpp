#include "HudorEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

HudorEnemy::HudorEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void HudorEnemy::setAttributes()
{
    Enemy::setAttributes(hudorAttributes);
    regen();
}

void HudorEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyHudor" + Parse::toQString(num) + ".png"), defaultSize);
    setPixmap(scaled);
}

void HudorEnemy::setProperties()
{
    distancePerInterval = hudorSpeed;
    hp = pow(hudorHp * level, hpScale);
    spawnHp = hp;
    armor = hudorArmor;
    value = pow(hp, valueDecay);
}
