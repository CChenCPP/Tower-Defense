#include "EzlotlEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

EzlotlEnemy::EzlotlEnemy(int level) :
    Enemy(level)
{
    init();
}

void EzlotlEnemy::setAttributes()
{
    Enemy::setAttributes(ezlotlAttributes);
}

void EzlotlEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyEzlotl" + Parse::toQString(num) + ".png"), defaultSize);
    setPixmap(scaled);
}

void EzlotlEnemy::setProperties()
{
    distancePerInterval = ezlotlSpeed;
    hp = ezlotlHp * level / 3.0 * pow(defaultHpScale, level);
    spawnHp = hp;
    armor = ezlotlArmor;
    value = pow(hp, defaultValueDecay);
}
