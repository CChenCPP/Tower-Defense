#include "UesisEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

UesisEnemy::UesisEnemy(int level) :
    Enemy(level)
{
    init();
}

void UesisEnemy::setAttributes()
{
    Enemy::setAttributes(uesisAttributes);
}

void UesisEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyUesis" + Parse::toQString(num) + ".png"), defaultSize);
    setPixmap(scaled);
}

void UesisEnemy::setProperties()
{
    distancePerInterval = uesisSpeed;
    hp = uesisHp * level / 3.0 * pow(defaultHpScale, level);
    spawnHp = hp;
    armor = uesisArmor;
    value = pow(hp, defaultValueDecay);
}
