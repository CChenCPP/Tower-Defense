#include "LoldohrEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

LoldohrEnemy::LoldohrEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void LoldohrEnemy::setAttributes()
{
    Enemy::setAttributes(loldohrAttributes);
}

void LoldohrEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyLoldohr" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void LoldohrEnemy::setProperties()
{
    distancePerInterval = loldohrSpeed;
    hp = pow(loldohrHp * level, hpScale);
    spawnHp = hp;
    armor = loldohrArmor;
    value = pow(hp, Enemy::valueDecay);
}
