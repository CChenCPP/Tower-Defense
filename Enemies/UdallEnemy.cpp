#include "UdallEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

UdallEnemy::UdallEnemy(int level) :
    Enemy(level)
{
    init();
}

void UdallEnemy::setAttributes()
{
    Enemy::setAttributes(udallAttributes);
}

void UdallEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyUdall" + Parse::toQString(num) + ".png"), defaultSize);
    setPixmap(scaled);
}

void UdallEnemy::setProperties()
{
    distancePerInterval = udallSpeed;
    hp = udallHp * level / 3.0 * pow(defaultHpScale, level);
    spawnHp = hp;
    armor = udallArmor;
    value = pow(hp, defaultValueDecay);
}
