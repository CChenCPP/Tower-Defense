#include "DharuerEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

DharuerEnemy::DharuerEnemy(int level) :
    Enemy(level)
{
    init();
}

void DharuerEnemy::setAttributes()
{
    Enemy::setAttributes(dharuerAttributes);
}

void DharuerEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyDharuer" + Parse::toQString(num) + ".png"), defaultSize);
    setPixmap(scaled);
}

void DharuerEnemy::setProperties()
{
    distancePerInterval = dharuerSpeed;
    hp = dharuerHp * level / 3.0 * pow(defaultHpScale, level);
    spawnHp = hp;
    armor = dharuerArmor;
    value = pow(hp, defaultValueDecay);
}
