#include "EnioneEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

EnioneEnemy::EnioneEnemy(int level) :
    Enemy(level)
{
        init();
}

void EnioneEnemy::setAttributes()
{
    Enemy::setAttributes(enioneAttributes);
}

void EnioneEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyEnione" + Parse::toQString(num) + ".png"), defaultSize);
    setPixmap(scaled);
}

void EnioneEnemy::setProperties()
{
    distancePerInterval = enioneSpeed;
    hp = enioneHp * level / 3.0 * pow(defaultHpScale, level);
    spawnHp = hp;
    armor = enioneArmor;
    value = pow(hp, defaultValueDecay);
}
