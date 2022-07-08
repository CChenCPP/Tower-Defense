#include "RihrusEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

RihrusEnemy::RihrusEnemy(int level) :
    Enemy(level)
{
    init();
}

void RihrusEnemy::setAttributes()
{
    Enemy::setAttributes(rihrusAttributes);
}

void RihrusEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyRihrus" + Parse::toQString(num) + ".png"), defaultSize);
    setPixmap(scaled);
}

void RihrusEnemy::setProperties()
{
    distancePerInterval = rihrusSpeed;
    hp = rihrusHp * level / 3.0 * pow(defaultHpScale, level);
    spawnHp = hp;
    armor = rihrusArmor;
    value = pow(hp, defaultValueDecay);
}
