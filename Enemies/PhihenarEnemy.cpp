#include "PhihenarEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

PhihenarEnemy::PhihenarEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void PhihenarEnemy::setAttributes()
{
    Enemy::setAttributes(phihenarAttributes);
    regen();
}

void PhihenarEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyPhihenar" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void PhihenarEnemy::setProperties()
{
    distancePerInterval = phihenarSpeed;
    hp = pow(phihenarHp * level, hpScale);
    spawnHp = hp;
    armor = phihenarArmor;
    value = pow(hp, Enemy::valueDecay);
}
