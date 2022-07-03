#include "EzlotlEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

EzlotlEnemy::EzlotlEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void EzlotlEnemy::setAttributes()
{
    Enemy::setAttributes(ezlotlAttributes);
}

void EzlotlEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyEzlotl" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void EzlotlEnemy::setProperties()
{
    distancePerInterval = ezlotlSpeed;
    hp = pow(ezlotlHp * level, hpScale);
    spawnHp = hp;
    armor = ezlotlArmor;
    value = pow(hp, Enemy::valueDecay);
}
