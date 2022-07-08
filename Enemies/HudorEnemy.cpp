#include "HudorEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

HudorEnemy::HudorEnemy(int level) :
    Enemy(level)
{
    init();
}

void HudorEnemy::setAttributes()
{
    Enemy::setAttributes(hudorAttributes);
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
    hp = hudorHp * level / 3.0 * pow(defaultHpScale, level);
    spawnHp = hp;
    armor = hudorArmor;
    value = pow(hp, defaultValueDecay);
}
