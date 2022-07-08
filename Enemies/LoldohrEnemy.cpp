#include "LoldohrEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

LoldohrEnemy::LoldohrEnemy(int level) :
    Enemy(level)
{
    init();
}

void LoldohrEnemy::setAttributes()
{
    Enemy::setAttributes(loldohrAttributes);
}

void LoldohrEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyLoldohr" + Parse::toQString(num) + ".png"), defaultSize);
    setPixmap(scaled);
}

void LoldohrEnemy::setProperties()
{
    distancePerInterval = loldohrSpeed;
    hp = loldohrHp * level / 3.0 * pow(defaultHpScale, level);
    spawnHp = hp;
    armor = loldohrArmor;
    value = pow(hp, defaultValueDecay);
}
