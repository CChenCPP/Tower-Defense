#include "ZanbrisEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

ZanbrisEnemy::ZanbrisEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void ZanbrisEnemy::setAttributes()
{
    Enemy::setAttributes(zanbrisAttributes);
}

void ZanbrisEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyZanbris" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void ZanbrisEnemy::setProperties()
{
    distancePerInterval = zanbrisSpeed;
    hp = pow(zanbrisHp * level, hpScale);
    spawnHp = hp;
    armor = zanbrisArmor;
    value = pow(hp, Enemy::valueDecay);
}
