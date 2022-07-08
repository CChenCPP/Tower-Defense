#include "CukzotzEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

CukzotzEnemy::CukzotzEnemy(int level) :
    Enemy(level)
{
    init();
}

void CukzotzEnemy::setAttributes()
{
    Enemy::setAttributes(cukzotzAttributes);
}

void CukzotzEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyCukzotz" + Parse::toQString(num) + ".png"), defaultSize);
    setPixmap(scaled);
}

void CukzotzEnemy::setProperties()
{
    distancePerInterval = cukzotzSpeed;
    hp = cukzotzHp * level / 3.0 * pow(defaultHpScale, level);
    spawnHp = hp;
    armor = cukzotzArmor;
    value = pow(hp, defaultValueDecay);
}
