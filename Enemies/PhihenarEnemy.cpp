#include "PhihenarEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

PhihenarEnemy::PhihenarEnemy(int level) :
    Enemy(level)
{
    init();
}

void PhihenarEnemy::setAttributes()
{
    Enemy::setAttributes(phihenarAttributes);
}

void PhihenarEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyPhihenar" + Parse::toQString(num) + ".png"), defaultSize);
    setPixmap(scaled);
}

void PhihenarEnemy::setProperties()
{
    distancePerInterval = phihenarSpeed;
    hp = phihenarHp * level / 3.0 * pow(defaultHpScale, level);
    spawnHp = hp;
    armor = phihenarArmor;
    value = pow(hp, defaultValueDecay);
}
