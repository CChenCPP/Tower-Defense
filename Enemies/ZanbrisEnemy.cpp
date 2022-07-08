#include "ZanbrisEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

ZanbrisEnemy::ZanbrisEnemy(int level) :
    Enemy(level)
{
    init();
}

void ZanbrisEnemy::setAttributes()
{
    Enemy::setAttributes(zanbrisAttributes);
}

void ZanbrisEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyZanbris" + Parse::toQString(num) + ".png"), defaultSize);
    setPixmap(scaled);
}

void ZanbrisEnemy::setProperties()
{
    distancePerInterval = zanbrisSpeed;
    hp = zanbrisHp * level / 3.0 * pow(defaultHpScale, level);
    spawnHp = hp;
    armor = zanbrisArmor;
    value = pow(hp, defaultValueDecay);
}
